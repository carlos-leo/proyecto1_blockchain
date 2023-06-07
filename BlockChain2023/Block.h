#include <cstdint>
#include <ctime>
#include <iostream>
#include <sstream>
#include<iomanip>
#include "CircularArray.h"
#include "SHA256.h"
#include "Utiles.h"
#include "BD.h"

using namespace std;

const int MAX_TRANSACCIONES_POR_BLOQUE = 100;
const string LINEA_TABLA = "\t-------------------------------------------------------------------------";

template<class T>
class CBlock {

public:

	CBlock(); // Constructor (nace un bloque) con valores por defecto

	CBlock(int indexIn);

	int GetCodBlock() const;

	string GetFechaBlock() const;

	string GetHashActual() const;

	string GetHashPrevio() const;

	int GetNounce() const;

	void SetCodBlock(int _index);

	void SetHashPrevio(string HashPrevio);

	void SetHashActual(string HashActual);

	void Minar(int difficulty); // Metodo Minar

	void NuevaTransaccion(T& data); //Metodo Nueva Transaccion

	void ModificarTransaccion(T data);

	bool BuscarTransaccion(int IdTran);

	void EliminarTransaccion(int idTran);

	void ImprimirTransacciones();

	bool EstaVacio();

	void GuardarBloqueDB(Database& db);

	//void addTransaction(<T> data);
	//void findTransaction(int IndexTran);


private:
	int cod_block;
	string fecha_block;
	string hash_previo;
	string hash_actual;
	int nounce;
	CircularArray<T> m_data;

	string CalcularHash(); // Genera Hash del bloque
};

template<class T>
CBlock<T>::CBlock() {
	this->fecha_block = ObtieneFechaActual();
}

template<class T>
CBlock<T>::CBlock(int indexIn) : cod_block(indexIn) {
	this->nounce = -1;
}

// Getters
template<class T>
int CBlock<T>::GetCodBlock() const {
	return this->cod_block;
}

template<class T>
string CBlock<T>::GetFechaBlock() const {
	return this->fecha_block;
}

template<class T>
string CBlock<T>::GetHashActual() const {
	return this->hash_actual;
}

template<class T>
string CBlock<T>::GetHashPrevio() const {
	return this->hash_previo;
}

template<class T>
int CBlock<T>::GetNounce() const {
	return this->nounce;
}

template<class T>
void CBlock<T>::SetCodBlock(int _index) {
	this->cod_block = _index;
}

template<class T>
void CBlock<T>::SetHashPrevio(string HashPrevio) {
	this->hash_previo = HashPrevio;
}
template<class T>
void CBlock<T>::SetHashActual(string HashActual) {
	this->hash_actual = HashActual;
}

// Metodo Minar
template<class T>
void CBlock<T>::Minar(int difficulty) {
	char* cstr = new char[difficulty + 1];

	for (uint32_t i = 0; i < difficulty; ++i) {
		cstr[i] = '0';
	}
	cstr[difficulty] = '\0';

	string str(cstr);

	while (true) {
		this->nounce++;
		this->hash_actual = CalcularHash();

		if (this->hash_actual.substr(0, difficulty) == str) {
			break;
		}
	}
	if (this->cod_block == 0)
	{
		this->hash_actual = "0000000000000000000000000000000000000000000000000000000000000000";
	}
	else {
		cout << "Bloque " << this->cod_block << " minado: " << this->hash_actual << endl;
	}
}

// Metodo CalculaHash de Bloque
template<class T>
string CBlock<T>::CalcularHash() {
	stringstream ss;

	ss << this->cod_block << this->fecha_block << this->nounce << this->hash_previo;

	if (!this->m_data.is_empty()) {
		for (typename CircularArray<T>::iterator it = this->m_data.begin(); it != this->m_data.end(); ++it) {
			ss << (*it).getIdTran() << (*it).getEmisor() << (*it).getReceptor() << (*it).getMonto() << (*it).getFechaTran();
		}
	}

	return sha256(ss.str());
}

/*
template<class T>
string CBlock<T>::ObtieneFechaActual() {
	time_t t = time(nullptr);
	tm* now = std::localtime(&t);
	char buffer[17];
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M", now);
	return buffer;
}
*/

// Metodo Nueva Transaccion
template<class T>
void CBlock<T>::NuevaTransaccion(T& data)
{
	typename CircularArray<T>::iterator it = m_data.end();
	--it;
	int IdBlock = (*it).getIdTran();
	data.SetIdTran(IdBlock + 1);
	if (m_data.size() <= MAX_TRANSACCIONES_POR_BLOQUE)
		m_data.push_back(data);
}

template<class T>
void CBlock<T>::ModificarTransaccion(T data) {

	if (m_data.size() == 0) {
		cout << "No hay transacciones en el bloque. No se puede modificar ninguna transacción." << endl;
		return;
	}

	bool encontrado = false;
	int i = -1;
	for (typename CircularArray<T>::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		i++;
		if ((*it).getIdTran() == data.getIdTran()) {
			m_data[i] = data;
			encontrado = true;
			break;
		}
	}

	if (encontrado) {
		cout << "La transaccion con el ID " << data.getIdTran() << " del Bloque " << this->GetCodBlock() << " ha sido modificada." << endl;
	}
	else {
		cout << "No se encontró la transacción especificada." << endl;
	}
}

template<class T>
void CBlock<T>::EliminarTransaccion(int idTran)
{
	if (m_data.size() == 0) {
		cout << "No hay transacciones en el bloque. No se puede eliminar ninguna transacción." << endl;
		return;
	}

	bool encontrado = false;
	int i = -1;
	for (typename CircularArray<T>::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		i++;
		if ((*it).getIdTran() == idTran) {
			m_data.erase(i);
			encontrado = true;
			break;
		}
	}

	if (encontrado) {
		cout << "La transaccion con el ID " << idTran << " del Bloque " << this->GetCodBlock() << " ha sido eliminada." << endl;
	}
	else {
		cout << "No se encontró la transacción especificada." << endl;
	}
}


template<class T>
void CBlock<T>::ImprimirTransacciones() {
	//system("cls");
	/*if (m_data.is_empty()) {
		cout << "No hay transacciones en el bloque." << endl;
		return;
	}

	cout << endl << endl << "\t\t\tTRANSACCIONES DEL BLOQUE " << GetCodBlock() << endl;
	cout << LINEA_TABLA << endl;
	cout << "\t " << setw(3) << left << "ID" << " | ";
	cout << "\t" << setw(10) << left << "Emisor" << " | ";
	cout << "\t" << setw(10) << left << "Receptor" << " | ";
	cout << "\t" << setw(8) << left << "Monto" << " | ";
	cout << "\t" << setw(16) << left << "Fecha Trx" << endl;
	cout << LINEA_TABLA << endl;

	for (typename CircularArray<T>::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		cout << "\t " << setw(3) << left << (*it).getIdTran() << " | ";
		cout << "\t" << setw(10) << left << (*it).getEmisor() << " | ";
		cout << "\t" << setw(10) << left << (*it).getReceptor() << " | ";
		cout << "\t" << setw(8) << left << (*it).getMonto() << " | ";
		cout << "\t" << setw(16) << left << (*it).getFechaTran() << endl;
	}
	cout << endl << LINEA_TABLA << endl;*/

	if (m_data.is_empty()) {
		cout << "No hay transacciones en el bloque." << endl;
		return;
	}

	cout << LINEA_TABLA << endl;
	cout << "\t " << setw(5) << left << "ID Trx" << " | ";
	cout << "\t" << setw(10) << left << "Emisor" << " | ";
	cout << "\t" << setw(10) << left << "Receptor" << " | ";
	cout << "\t" << setw(8) << left << "Monto" << " | ";
	cout << "\t" << setw(14) << left << "Fecha Trx" << endl;
	cout << LINEA_TABLA << endl;

	for (typename CircularArray<T>::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		cout << "\t  " << setw(5) << left << (*it).getIdTran() << " | ";
		cout << "\t" << setw(10) << left << (*it).getEmisor() << " | ";
		cout << "\t" << setw(10) << left << (*it).getReceptor() << " | ";
		cout << "\t" << setw(8) << left << (*it).getMonto() << " | ";
		cout << "\t" << setw(14) << left << (*it).getFechaTran() << endl;
	}
	cout << endl << LINEA_TABLA << endl;
}

template<class T>
void CBlock<T>::GuardarBloqueDB(Database &db)
{
	for (typename CircularArray<T>::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		db.insertRecord(Record(std::to_string(cod_block), fecha_block, hash_previo, hash_actual, std::to_string(nounce), std::to_string((*it).getIdTran()),
			                   std::to_string((*it).getMonto()), (*it).getEmisor(), (*it).getReceptor(), (*it).getFechaTran()));
	}
}

template<class T>
bool CBlock<T>::EstaVacio() { // bloque vacio No tiene transacciones
	return m_data.is_empty();
}

template<class T>
bool CBlock<T>::BuscarTransaccion(int IdTran)
{
	if (m_data.is_empty()) {
		//cout << "No hay transacciones en el bloque." << endl;
		return false;
	}

	for (typename CircularArray<T>::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		if ((*it).getIdTran() == IdTran) {
			//cout << "La transaccion con el ID " << IdTran << " se encontró en el Bloque " << this->GetCodBlock() << "." << endl;
			return true;
		}
	}

	//cout << "No se encontró la transacción con el ID " << IdTran << "." << endl;
	return false;
}

