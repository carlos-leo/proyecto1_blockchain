#pragma once
#include <cstdint>
#include <ctime>
#include <iostream>
#include <sstream>
#include "BlockChain.h"
#include "Transaccion.h"
#include <iomanip>
#include "TextTable.h"

using namespace std;

const string AGREGAR_BLOQUE = "AGREGAR BLOQUE";
const string MODIFICAR_BLOQUE = "MODIFICAR BLOQUE";
const string ELIMINAR_BLOQUE = "ELIMINAR BLOQUE";
const string CARGA_ARCHIVO = "CARGAR DESDE ARCHIVO";
const string GUARDAR_ARCHIVO = "GUARDAR EN ARCHIVO";
const string VISUALIZAR = "VISUALIZAR INFORMACION";
const string BUSCAR = "BUSQUEDA Y LISTADO";
const string CABECERA = "  ***********************************************************************************************";
const string CABECERA_PRIN = "  =======================================================================================================";
const string CABECERA_MENU = "\t\t\*************************************************";
const string CABECERA_SUBMENU = "\t\t\t-------------------------------------------------";

class VistaBlockchain {
	CBlockChain<CBlock<Transaccion>> cadenaBloques;
	CBlock<Transaccion> bloque;
	
public:
	void menuPrincipal(CBlockChain<CBlock<Transaccion>> cadena, CBlock<Transaccion>);
	void opcionAgregarBloque(CBlockChain<CBlock<Transaccion>> cadena, CBlock<Transaccion> bloque);
	Transaccion ingresarNuevaTransaccion();
	void mostrarTransaccion(Transaccion trx);
	void opcionModificarBloque();
	void opcionEliminarBloque();
	void opcionCargarDesdeArchivo();
	void opcionGuardarEnArchivo();
	void opcionVisualizar(CBlockChain<CBlock<Transaccion>> cadena, CBlock<Transaccion> bloque);
	void subOpcionVisualizarBloque(CBlockChain<CBlock<Transaccion>> cadena, CBlock<Transaccion> bloque);
	void opcionBusqueda();

	VistaBlockchain() = default;
};


void menuPrincipal(CBlockChain<CBlock<Transaccion>> cadena, CBlock<Transaccion> bloque)
{
	int opcion = 0;

	do
	{
		// Menu principal
		cout << CABECERA_PRIN << endl;
		cout << "  |\t\t\t\tPROYECTO BLOCKCHAIN - GRUPO 05\t\t\t\t\t\t|" << endl;
		cout << CABECERA_PRIN << endl << endl;
		cout << CABECERA_MENU << endl;
		cout << "\t\t*\t\tMENU PRINCIPAL\t\t\t*" << endl;
		cout << CABECERA_MENU << endl;
		cout << "\t\t\t 1.- " << AGREGAR_BLOQUE << endl;					// Añadir bloque nuevo (al final del ultimo bloque)
		cout << "\t\t\t 2.- " << MODIFICAR_BLOQUE << endl;				// Se realiza el recalculo en cascada
		cout << "\t\t\t 3.- " << ELIMINAR_BLOQUE << endl;					// Se realiza el recalculo en cascada
		cout << "\t\t\t 4.- " << CARGA_ARCHIVO << endl;
		cout << "\t\t\t 5.- " << GUARDAR_ARCHIVO << endl;
		cout << "\t\t\t 6.- " << VISUALIZAR << endl;
		cout << "\t\t\t 7.- " << BUSCAR << endl;
		cout << "\t\t\t 0.- SALIR" << endl << endl;
		cout << CABECERA_MENU << endl;
		cout << "\t\t\tEscoja una opcion: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1:
			system("cls");
			opcionAgregarBloque(cadena, bloque);
			system("pause"); system("cls");
			break;
		case 2:
			system("cls");
			opcionModificarBloque();
			system("pause"); system("cls");
			break;
		case 3:
			system("cls");
			opcionEliminarBloque();
			system("pause"); system("cls");
			break;
		case 4:
			system("cls");
			opcionCargarDesdeArchivo();
			system("pause"); system("cls");
			break;
		case 5:
			system("cls");
			opcionGuardarEnArchivo();
			system("pause"); system("cls");
			break;
		case 6:
			system("cls");
			opcionVisualizar(cadena, bloque);
			system("pause"); system("cls");
			break;

		case 7:
			system("cls");
			opcionBusqueda();
			system("pause"); system("cls");
			break;

		case 0: // Salir
			cout << "\n\tFin del programa.........." << endl;
			exit(0);

		default: // Otra opcion: no válida
			cout << "Opción desconocida!" << endl;
			break;
		}
	} while (opcion != 0);  // Si la opcion es 0, terminamos */
	cout << endl << CABECERA_PRIN << endl;
}

void opcionAgregarBloque(CBlockChain<CBlock<Transaccion>> cadena, CBlock<Transaccion> bloque) {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << AGREGAR_BLOQUE << endl;
	cout << CABECERA << "\n\n";

	string confirm;
	string res;
	//CBlockChain<CBlock<Transaccion>> cadenaBloques;
	//CBlock<Transaccion> block(1);

	do
	{
		Transaccion trx = ingresarNuevaTransaccion();
		bloque.NuevaTransaccion(trx);
		cout << "\n\tDesea ingresar nueva transaccion? Si (S) / No (N) : ";
		cin >> confirm;
	} while (confirm == "S" || confirm == "s");

	if (confirm == "N" || confirm == "n") {
		cout << "\tDesea minar el Bloque? Si (S) / No (N)  S \t: ";
		cin >> res; cout << endl;
		if (res == "S" || res == "s") {
			cadena.InsertarBloque(bloque); //llamar metodo minar;
		}
	}
	bloque.ImprimirTransacciones();
}

Transaccion ingresarNuevaTransaccion() {
	system("cls");
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << AGREGAR_BLOQUE << endl;
	cout << CABECERA << "\n\n";

	float monto = 0;
	string emisor;
	string receptor;
	string confirm;

	cout << endl;
	cout << "\t\t\t\t NUEVA TRANSACCION" << "\n";
	cout << LINEA_TABLA << endl;
	cout << "\t" << " - Ingrese Monto    :\t"; cin >> monto;
	cout << "\t" << " - Ingrese Emisor   :\t"; cin >> emisor;
	cout << "\t" << " - Ingrese Receptor :\t"; cin >> receptor; cout << endl;

	Transaccion trx = Transaccion(emisor, receptor, monto);
	mostrarTransaccion(trx);
	return trx;
}

void mostrarTransaccion(Transaccion trx) {
	cout << endl;
	cout << "\t\t\tINFORMACION DE LA TRANSACCION " << endl;
	cout << LINEA_TABLA << endl;
	//cout << "\t" << "Id Trx " << setw(10) << "Emisor " << setw(14) << "Receptor" << setw(12) << "Monto" << setw(20) << "Fecha Trx" << endl;
	cout << "\t " << setw(3) << left << "ID" << " | ";
	cout << "\t" << setw(10) << left << "Emisor" << " | ";
	cout << "\t" << setw(10) << left << "Receptor" << " | ";
	cout << "\t" << setw(8) << left << "Monto" << " | ";
	cout << "\t" << setw(16) << left << "Fecha Trx" << endl;
	cout << LINEA_TABLA << endl;
	//cout << "\t" << trx.getIdTran() << setw(10) << trx.getEmisor() << setw(14) << trx.getReceptor() << setw(14) << trx.getMonto() << setw(20) << trx.getFechaTran() << endl << endl;
	cout << "\t " << setw(3) << left << trx.getIdTran() << " | ";
	cout << "\t" << setw(10) << left << trx.getEmisor() << " | ";
	cout << "\t" << setw(10) << left << trx.getReceptor() << " | ";
	cout << "\t" << setw(8) << left << trx.getMonto() << " | ";
	cout << "\t" << setw(16) << left << trx.getFechaTran() << endl << endl;
	cout << LINEA_TABLA << endl;
}

void opcionModificarBloque() {
	cout << CABECERA << endl;
	cout << "  |\t\t\t\t" << MODIFICAR_BLOQUE << "\t\t\t\t\t\t|" << endl;
	cout << CABECERA << "\n\n";

	int opcion;
	do
	{
		cout << CABECERA_SUBMENU << endl;
		cout << "\t\t\t\tMenu Modificar Bloque" << endl;
		cout << CABECERA_SUBMENU << endl;
		cout << "\t\t\t 1.- Agregar Transaccion" << endl;
		cout << "\t\t\t 2.- Modificar una Transaccion" << endl;
		cout << "\t\t\t 3.- Eliminar Transaccion" << endl;
		cout << "\t\t\t 0.- Regresar Menu principal" << endl;
		cout << CABECERA_SUBMENU << endl;
		cout << "\n\t\t\tEscoja una opcion: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1: system("cls"); cout << "AgregarTransaccionEnBloque()"; system("pause"); system("cls");
			break;
		case 2: system("cls"); cout << "ModificarTransaccion()"; system("pause"); system("cls");
			break;
		case 3: system("cls"); cout << "EliminarTransaccion()"; system("pause"); system("cls");
			break;
		case 0: // Salir
			break;
		default: // Otra opcion: no válida
			cout << "Opción desconocida!" << endl;
			break;
		}
	} while (opcion != 0);
}

void opcionEliminarBloque() {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << ELIMINAR_BLOQUE << endl;
	cout << CABECERA << "\n\n";
}

void opcionCargarDesdeArchivo() {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << CARGA_ARCHIVO << endl;
	cout << CABECERA << "\n\n";
}

void opcionGuardarEnArchivo() {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << GUARDAR_ARCHIVO << endl;
	cout << CABECERA << "\n\n";
}

void opcionVisualizar(CBlockChain<CBlock<Transaccion>> cadena, CBlock<Transaccion> bloque) {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << VISUALIZAR << endl;
	cout << CABECERA << "\n\n";

	int opcion;
	do
	{
		cout << CABECERA_SUBMENU << endl;
		cout << "\t\t\t\tMenu Visualizar" << endl;
		cout << CABECERA_SUBMENU << endl;
		cout << "\t\t\t 1.- Visualizar un Bloque" << endl;
		cout << "\t\t\t 2.- Visualizar los Bloques" << endl;
		cout << "\t\t\t 0.- Regresar Menu principal" << endl;
		cout << CABECERA_SUBMENU << endl;
		cout << "\n\t\t\tEscoja una opcion: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1: system("cls"); 
				subOpcionVisualizarBloque(cadena, bloque);
				system("pause"); system("cls");
				break;
		case 2: system("cls"); 
				cadena.VisualizarCadena();
				system("pause"); system("cls");
				break;
		case 0: // Salir
			break;
		default: // Otra opcion: no válida
			cout << "Opción desconocida!" << endl;
			break;
		}
	} while (opcion != 0);
}

void subOpcionVisualizarBloque(CBlockChain<CBlock<Transaccion>> cadena, CBlock<Transaccion> bloque) {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << VISUALIZAR << endl;
	cout << CABECERA << "\n\n";

	int Idbloque;
	cout << "Ingrese el Id del Bloque: "; cin >> Idbloque;
	bloque = cadena.BuscarBloque(Idbloque);

	cadena.VisualizarBloque(bloque);

}

void opcionBusqueda() {
	cout << CABECERA << endl;
	cout << "  |\t\t\t\t" << BUSCAR << "\t\t\t\t\t\t|" << endl;
	cout << CABECERA << "\n\n";

	int opcion;
	do
	{
		cout << CABECERA_SUBMENU << endl;
		cout << "\t\t\t\t   Menu Buscar y Listar" << endl;
		cout << CABECERA_SUBMENU << endl;
		cout << "\t\t\t 1.-  Buscar bloque por ID" << endl;
		cout << "\t\t\t 2.-  Buscar bloque por fecha de creacion" << endl;
		cout << "\t\t\t 3.-  Buscar Transaccion por ID" << endl;
		cout << "\t\t\t 4.-  Buscar Transaccion por Emisor" << endl;
		cout << "\t\t\t 5.-  Buscar Transaccion por Receptor" << endl;
		cout << "\t\t\t 6.-  Buscar Transaccion por ID" << endl;
		cout << "\t\t\t 7.-  Buscar Transaccion por rango de Fecha" << endl;
		cout << "\t\t\t 8.-  Buscar Transaccion por Monto" << endl;
		cout << "\t\t\t 9.-  Buscar Transaccion por Rango de montos" << endl;
		cout << "\t\t\t 10.- Buscar la transaccion con el mayor monto" << endl;
		cout << "\t\t\t 11.- Buscar la transaccion con el menor monto" << endl;
		cout << "\t\t\t 0.-  Regresar Menu principal" << endl;
		cout << CABECERA_SUBMENU << endl;
		cout << "\n\t\t\tEscoja una opcion: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1: system("cls"); cout << "Buscar bloque por ID"; system("pause"); system("cls");
			break;
		case 2: system("cls"); cout << "Buscar bloque por fecha de creación"; system("pause"); system("cls");
			break;
		case 3: system("cls"); cout << "Buscar Transacción por ID"; system("pause"); system("cls");
			break;
		case 4: system("cls"); cout << "Buscar Transacción por Emisor"; system("pause"); system("cls");
			break;
		case 5: system("cls"); cout << "Buscar Transacción por Receptor"; system("pause"); system("cls");
			break;
		case 6: system("cls"); cout << "Buscar Transacción por Fecha de transacción"; system("pause"); system("cls");
			break;
		case 7: system("cls"); cout << "Buscar Transacción por rango de Fecha de transacción"; system("pause"); system("cls");
			break;
		case 8: system("cls"); cout << "Buscar Transacción por Monto Específico"; system("pause"); system("cls");
			break;
		case 9: system("cls"); cout << "Buscar Transacción por Rango de montos"; system("pause"); system("cls");
			break;
		case 10: system("cls"); cout << "Buscar la transacción con el mayor monto"; system("pause"); system("cls");
			break;
		case 11: system("cls"); cout << "Buscar la transacción con el menor monto"; system("pause"); system("cls");
			break;
		case 0: // Salir
			break;
		default: // Otra opcion: no válida
			cout << "Opción desconocida!" << endl;
			break;
		}
	} while (opcion != 0);
}
