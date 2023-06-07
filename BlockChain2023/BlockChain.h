#ifndef __BLOCKCHAIN_H
#define __BLOCKCHAIN_H


#include <cstdint>
#include "CircularDouble.h"
#include "Block.h"
#include "BD.h"

using namespace std;

const int DIFICULTAD_PRUEBA_DE_TRABAJO = 3;

template<class T>
class CBlockChain {
public:
	CBlockChain();



	void InsertarBloque(T& nuevoBloque);

	T BuscarBloque(int IdBloque);

	void ModificarBloque(T nuevoBloque);

	void EliminarBloque(T Bloque);

	void ReguardarBloques(T bloqueInicial);

	void VisualizarBloque(int IdBloque);

	void VisualizarCadena();

	void ImprimirBloque(T nuevoBloque);

private:
	Database db;
	int m_dificultad;

	CircularDoubleList<T> m_chain;

	// BD DB_blockchain; // atributo de Base de Datos

	T GetUltimoBloque();

	T GetBloqueSiguiente();

	void RecalcularHash(T bloque);

	int GetSizeCadena();
};


// BD DB_blockchain()             // debe ser global!!!!  


template<class T>
CBlockChain<T>::CBlockChain() {
	this->m_dificultad = DIFICULTAD_PRUEBA_DE_TRABAJO;
	T BloqueGenesis;
	BloqueGenesis.Minar(this->m_dificultad);
	this->m_chain.push_back(BloqueGenesis); // El BlockChain nace con el bloque Génesis 
}

template<class T>
void CBlockChain<T>::InsertarBloque(T& nuevoBloque) {
	nuevoBloque.SetCodBlock(GetUltimoBloque().GetCodBlock() + 1);
	nuevoBloque.SetHashPrevio(GetUltimoBloque().GetHashActual());
	nuevoBloque.Minar(this->m_dificultad);
	this->m_chain.push_back(nuevoBloque); // pone el nuevo bloque en la siguiente posición de la lista

	// sigue con el guardado en la BD (BD.h)
	nuevoBloque.GuardarBloqueDB(db);
}

template<class T>
void CBlockChain<T>::ModificarBloque(T BloqueModificado) {
	cout << endl << "Recalculando Hash desde el Bloque " << BloqueModificado.GetCodBlock() << endl << endl;
	BloqueModificado.Minar(this->m_dificultad);
	m_chain.GetCurrent()->data = BloqueModificado;
	RecalcularHash(BloqueModificado);
	ReguardarBloques(BloqueModificado);
}

// ************************* EN MANTENIMIENTO !!!!! ************************
template<class T>
void CBlockChain<T>::ReguardarBloques(T bloqueInicial)
{
	db.deleteDB(db.getNodoInicial());   // Actualizar la BD (desde el nodo inicial!!!)

	/*
	for (const auto &block : this->m_chain) {
		block.GuardarBloqueDB(db);
	}
	*/
	
	typename CircularDoubleList<T>::iterator it = m_chain.begin(); // desde el principio
	T bloquex;
	while (it != m_chain.end()) { // Para insertar cada nuevo cambio
		//m_chain.SetCurrent(it.GetCurrent());
		bloquex = *it;
		++it;
		if (bloquex.GetCodBlock() != 0) {
			bloquex.GuardarBloqueDB(db);
		}
	}
}



template<class T>
T CBlockChain<T>::BuscarBloque(int IdBloque) {
	for (typename CircularDoubleList<T>::iterator it = m_chain.begin(); it != m_chain.end(); ++it) {
		if ((*it).GetCodBlock() == IdBloque) {
			m_chain.SetCurrent(it.GetCurrent());
			return *it;
		}
	}

	// Si no se encuentra el bloque, se devuelve un bloque vacío
	T BloqueVacio;
	return BloqueVacio;
}

template<class T>
void CBlockChain<T>::VisualizarBloque(int IdBloque) {

	T bloque = BuscarBloque(IdBloque);

	if (!bloque.EstaVacio())
	{
		ImprimirBloque(bloque);
		bloque.ImprimirTransacciones();
		cout << endl << endl;
	}
	else
	{
		cout << endl << endl << "\t\t\ BLOQUE NO EXISTE" << endl;
		cout << endl << endl;
	}
}


/*
void CBlockChain<T>::insertDB(T newBlock)
{

	for (cada transaccion)
	{
		// parsear cada transaccion y la va ha guardar en la BD
		DB_blockchain.insertRecord(id y otros datos del bloque y la transaccion o un registro correspondiente); // guardar cada transaccion en la BD
	}
}

// Obtener y generar los bloques desde la BD
void CBlockChain<T>::loadDB()
{
  // recorrer todos los registros para generar cada bloque y sus transacciones

}
*/

// Se recorre para mostrar
// Obtener los datos desde la BD
template<class T>
void CBlockChain<T>::VisualizarCadena() {
	if (m_chain.is_empty()) {
		cout << "La cadena de bloques está vacía." << endl;
		return;
	}
	cout << endl;
	cout << "\t\t\t\t VISUALIZAR CADENA DE BLOQUES" << "\n";
	cout << LINEA_TABLA << endl;
	for (const auto& block : this->m_chain) {
		ImprimirBloque(block);
		cout << LINEA_TABLA << endl;
		cout << endl;
	}
}

template<class T>
void CBlockChain<T>::ImprimirBloque(T nuevoBloque) {
	cout << "\n\t--------------" << endl;
	cout << "\t| BLOQUE [" << nuevoBloque.GetCodBlock() << "] |" << endl;
	cout << LINEA_TABLA << endl;
	cout << "\t " << "Hash         : " << nuevoBloque.GetHashActual() << endl;
	cout << "\t " << "Hash Previo  : " << nuevoBloque.GetHashPrevio() << endl;
	cout << "\t " << "Nonce        : " << nuevoBloque.GetNounce() << endl;
	cout << "\t " << "Fecha Bloque : " << nuevoBloque.GetFechaBlock() << endl;
}


template<class T>
T CBlockChain<T>::GetUltimoBloque() {
	return this->m_chain.back();
}

template<class T>
T CBlockChain<T>::GetBloqueSiguiente() {
	return this->m_chain.next();
}

template<class T>
int CBlockChain<T>::GetSizeCadena() {
	return this->m_chain.size();
}

template<class T>
void CBlockChain<T>::EliminarBloque(T Bloque) {
	typename CircularDoubleList<T>::iterator it = m_chain.GetCurrent();
	Node<T>* bloqueEliminar = it.GetCurrent();
	int CodBloqueEliminado = bloqueEliminar->data.GetCodBlock();
	Node<T>* siguiente = bloqueEliminar->next;
	siguiente->data.SetHashPrevio(bloqueEliminar->prev->data.GetHashActual());
	m_chain.pop(bloqueEliminar);
	cout << endl << "\t " << "Bloque " << CodBloqueEliminado << " ha sido eliminado." << endl;
}

template<class T>
void CBlockChain<T>::RecalcularHash(T bloque) {
	string hashPrevio = bloque.GetHashActual();
	typename CircularDoubleList<T>::iterator it = m_chain.GetCurrent();
	++it; // Mueve el siguiente bloque
	T bloquex;
	while (it != m_chain.end()) {
		m_chain.SetCurrent(it.GetCurrent()); // Mueve el current al it actual
		bloquex = *it;
		bloquex.SetHashPrevio(hashPrevio);
		bloquex.Minar(m_dificultad);
		hashPrevio = bloquex.GetHashActual();
		m_chain.GetCurrent()->data = bloquex;
		++it;
	}
}

#endif // !__BLOCKCHAIN_H