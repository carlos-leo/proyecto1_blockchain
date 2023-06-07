#include "BlockChain.h"
#include "Transaccion.h"
#include <iomanip>
#include "TextTable.h"
#include "BD.h"
//#include "VistaBlockchain.h"

void menuPrincipal(CBlockChain<CBlock<Transaccion>>& cadena);
void opcionAgregarBloque(CBlockChain<CBlock<Transaccion>>& cadena);
Transaccion ingresarNuevaTransaccion();
void mostrarTransaccion(Transaccion trx);
void opcionModificarBloque(CBlockChain<CBlock<Transaccion>>& cadena);
void supOpcionNuevaTransaccionPorBloque(CBlockChain<CBlock<Transaccion>>& cadena);
void subOpcionModificarTransaccion(CBlockChain<CBlock<Transaccion>>& cadena);
void subOpcionEliminarTransaccion(CBlockChain<CBlock<Transaccion>>& cadena);
void opcionEliminarBloque(CBlockChain<CBlock<Transaccion>>& cadena);
void opcionCargarDesdeArchivo();
void opcionGuardarEnArchivo();
void opcionVisualizar(CBlockChain<CBlock<Transaccion>>& cadena);
void subOpcionVisualizarBloque(CBlockChain<CBlock<Transaccion>>& cadena);
void opcionBusqueda();

const string AGREGAR_BLOQUE = "AGREGAR BLOQUE";
const string MODIFICAR_BLOQUE = "MODIFICAR BLOQUE";
const string ELIMINAR_BLOQUE = "ELIMINAR BLOQUE";
const string CARGA_ARCHIVO = "CARGAR DESDE ARCHIVO";
const string GUARDAR_ARCHIVO = "GUARDAR EN ARCHIVO";
const string VISUALIZAR = "VISUALIZAR INFORMACION";
const string BUSCAR = "BUSQUEDA Y LISTADO";
const string CABECERA = "  ***********************************************************************************************";
const string CABECERA_PRIN = "  =======================================================================================================";
const string CABECERA_MENU = "\t\t*************************************************";
const string CABECERA_SUBMENU = "\t\t\t-------------------------------------------------";

Database db1;

int main(int argc, char* argv[]) {
	CBlockChain<CBlock<Transaccion>> cadenaBloques;
	menuPrincipal(cadenaBloques);
	system("pause");
	return 0;
}

void menuPrincipal(CBlockChain<CBlock<Transaccion>>& cadena)
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
			opcionAgregarBloque(cadena);
			system("pause"); system("cls");
			break;
		case 2:
			system("cls");
			opcionModificarBloque(cadena);
			system("pause"); system("cls");
			break;
		case 3:
			system("cls");
			opcionEliminarBloque(cadena);
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
			opcionVisualizar(cadena);
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

void opcionAgregarBloque(CBlockChain<CBlock<Transaccion>>& cadena) {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << AGREGAR_BLOQUE << endl;
	cout << CABECERA << "\n\n";

	string confirm;
	string res;

	CBlock<Transaccion> bloque;
	do
	{
		Transaccion trx = ingresarNuevaTransaccion();
		bloque.NuevaTransaccion(trx);
		mostrarTransaccion(trx);
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
	cadena.VisualizarBloque(bloque.GetCodBlock());
}

Transaccion ingresarNuevaTransaccion() {
	/*system("cls");
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
	return trx;*/

	system("cls");
	float monto = 0;
	string emisor;
	string receptor;
	string confirm;

	cout << endl;
	cout << "\t\t\t\t NUEVA TRANSACCION" << "\n";
	cout << LINEA_TABLA << endl;

	while (true) {
		cout << "\t" << " - Ingrese Monto    :\t";
		if (cin >> monto) {
			break;
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\t\t\t\tVALOR INVALIDO!!!\n";
		}
	}
	cout << "\t" << " - Ingrese Emisor   :\t"; cin >> emisor;
	cout << "\t" << " - Ingrese Receptor :\t"; cin >> receptor; cout << endl;

	Transaccion trx = Transaccion(emisor, receptor, monto);

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

void opcionModificarBloque(CBlockChain<CBlock<Transaccion>>& cadena) {
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
		case 1: system("cls");
			supOpcionNuevaTransaccionPorBloque(cadena);
			system("pause"); system("cls");
			break;
		case 2: system("cls");
			subOpcionModificarTransaccion(cadena);
			system("pause"); system("cls");
			break;
		case 3: system("cls"); subOpcionEliminarTransaccion(cadena);
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

void supOpcionNuevaTransaccionPorBloque(CBlockChain<CBlock<Transaccion>>& cadena) {
	cout << CABECERA << endl;
	cout << "  |\t\t\t\t" << MODIFICAR_BLOQUE << "\t\t\t\t\t\t|" << endl;
	cout << CABECERA << "\n\n";

	string confirm;
	int Idbloque;

	cout << "\n\tIngrese el Id del Bloque: "; cin >> Idbloque;

	CBlock<Transaccion> bloque = cadena.BuscarBloque(Idbloque);
	if (!bloque.EstaVacio()) {
		do
		{
			Transaccion trx = ingresarNuevaTransaccion();
			bloque.NuevaTransaccion(trx);
			mostrarTransaccion(trx);
			cout << "\n\tDesea ingresar nueva transaccion? Si (S) / No (N) : ";
			cin >> confirm;
			system("cls");
		} while (confirm == "S" || confirm == "s");
		if (confirm == "N" || confirm == "n") {
			cadena.ModificarBloque(bloque); // incluyo recalculo de hash por bloque
			cadena.VisualizarCadena();
		}
	}
	else
	{
		cout << endl << endl << "\t\t\ BLOQUE NO EXISTE" << endl;
		cout << endl << endl;
	}
}

void subOpcionModificarTransaccion(CBlockChain<CBlock<Transaccion>>& cadena) {
	cout << CABECERA << endl;
	cout << "  |\t\t\t\t" << MODIFICAR_BLOQUE << "\t\t\t\t\t\t|" << endl;
	cout << CABECERA << "\n\n";

	string confirm;
	int Idbloque;
	int IdTrx;

	cout << "\n\tIngrese el Id del Bloque: "; cin >> Idbloque;
	CBlock<Transaccion> bloque = cadena.BuscarBloque(Idbloque);
	if (!bloque.EstaVacio())
	{
		cout << "\n\tIngrese el Id de la Transacion: "; cin >> IdTrx;
		bool existeTransaccion = bloque.BuscarTransaccion(IdTrx);
		if (existeTransaccion) {
			Transaccion trx = ingresarNuevaTransaccion();
			trx.SetIdTran(IdTrx);
			bloque.ModificarTransaccion(trx);
			cadena.ModificarBloque(bloque); // incluyo recalculo de hash por bloque
		}
		else
		{
			cout << endl << endl << "\t\t\ TRANSACCION NO EXISTE" << endl;
			cout << endl << endl;
		}
	}
	else
	{
		cout << endl << endl << "\t\t\ BLOQUE NO EXISTE" << endl;
		cout << endl << endl;
	}
}

void subOpcionEliminarTransaccion(CBlockChain<CBlock<Transaccion>>& cadena) {
	cout << CABECERA << endl;
	cout << "  |\t\t\t\t" << MODIFICAR_BLOQUE << "\t\t\t\t\t\t|" << endl;
	cout << CABECERA << "\n\n";

	string confirm;
	int Idbloque;
	int IdTrx;

	cout << "\n\tIngrese el Id del Bloque: "; cin >> Idbloque;

	CBlock<Transaccion> bloque = cadena.BuscarBloque(Idbloque);
	if (!bloque.EstaVacio())
	{
		cout << "\n\tIngrese el Id de la Transacion: "; cin >> IdTrx;
		bool existeTransaccion = bloque.BuscarTransaccion(IdTrx);
		if (existeTransaccion) {
			cout << "\n\tEsta seguro que desea eliminar la transaccion <" << IdTrx << "> del Bloque<" << Idbloque << "> ? Si(S) / No(N) : ";
			cin >> confirm;
			if (confirm == "S" || confirm == "s")
			{
				bloque.EliminarTransaccion(IdTrx);
				cadena.ModificarBloque(bloque);
			}
		}
		else
		{
			cout << endl << endl << "\t\t\ TRANSACCION NO EXISTE" << endl;
			cout << endl << endl;
		}
	}
	else
	{
		cout << endl << endl << "\t\t\ BLOQUE NO EXISTE" << endl;
		cout << endl << endl;
	}
}

void opcionEliminarBloque(CBlockChain<CBlock<Transaccion>>& cadena) {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << ELIMINAR_BLOQUE << endl;
	cout << CABECERA << "\n\n";

	string confirm;

	int Idbloque;
	cout << "\n\tIngrese el Id del Bloque: "; cin >> Idbloque;
	CBlock<Transaccion> bloque = cadena.BuscarBloque(Idbloque);
	if (Idbloque == 0) cout << endl << endl << "\t\t\ BLOQUE GENESIS NO SE PUEDE ELIMINAR" << endl << endl;
	else {
		if (!bloque.EstaVacio())
		{
			cout << "\n\tEsta seguro que desea eliminar el bloque <" << Idbloque << "> ? Si(S) / No(N) : ";
			cin >> confirm;
			if (confirm == "S" || confirm == "s")
			{
				cadena.EliminarBloque(bloque);
				cadena.VisualizarCadena();
			}
		}
		else
		{
			cout << endl << endl << "\t\t\ BLOQUE NO EXISTE" << endl;
			cout << endl << endl;
		}
	}
}

void opcionCargarDesdeArchivo() {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << CARGA_ARCHIVO << endl;
	cout << CABECERA << "\n\n";

	std::string nameFileIn; // = "dbc.csv"; // "dataset_pequeno_v1.csv";    // "dataset_grande_v1.csv";

	cout << "Ingrese el nombre del archivo:"; cin >> nameFileIn;
	if (db1.readCSV(nameFileIn, ',')) {
		std::cout << "\nEl archivo " << nameFileIn << " tiene " << db1.nroColumnas << " columnas\n";
		std::cout << "El archivo " << nameFileIn << " tiene " << db1.nroFilas << " filas\n";
	}
}

void opcionGuardarEnArchivo() {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << GUARDAR_ARCHIVO << endl;
	cout << CABECERA << "\n\n";

	std::string nameFileOut; // = "dbc_salida.csv";
	cout << "Ingrese el nombre del archivo:"; cin >> nameFileOut;
	// Guardar los datos modificados
	if (db1.toCSV(nameFileOut)) {
		std::cout << "La BD fue guardada en el archivo " << nameFileOut << " correctamente." << std::endl;
	}

}

void opcionVisualizar(CBlockChain<CBlock<Transaccion>>& cadena) {
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
			subOpcionVisualizarBloque(cadena);
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

void subOpcionVisualizarBloque(CBlockChain<CBlock<Transaccion>>& cadena) {
	cout << CABECERA << endl;
	cout << "\t\t\t\t\t" << VISUALIZAR << endl;
	cout << CABECERA << "\n\n";

	int Idbloque;
	cout << "Ingrese el Id del Bloque: "; cin >> Idbloque;
	cadena.VisualizarBloque(Idbloque);
}

void opcionBusqueda() {
	cout << CABECERA << endl;
	cout << "  |\t\t\t\t" << BUSCAR << "\t\t\t\t\t\t|" << endl;
	cout << CABECERA << "\n\n";
	string confirm;
	int Idbloque, IdTran;
	int IdTrx;
	Record queriedRecord;

	int opcion = 0;
	do
	{
		cout << CABECERA_SUBMENU << endl;
		cout << "\t\t\t\t   Menu Buscar y Listar" << endl;
		cout << CABECERA_SUBMENU << endl;
		cout << "\t\t\t 1.-  Buscar bloque por ID Bloque e ID Transacción" << endl;
		cout << "\t\t\t 2.-  Listar ordenado por Receptor" << endl;
		cout << "\t\t\t 3.-  Listar ordenado por Monto" << endl;
		cout << "\t\t\t 4.-  Listar ordenado por Fecha de Transacción" << endl;
		cout << "\t\t\t 0.-  Regresar Menu principal" << endl;
		cout << CABECERA_SUBMENU << endl;
		cout << "\n\t\t\tEscoja una opcion: ";
		cin >> opcion;
		
		switch (opcion)
		{
		case 1: system("cls"); cout << "Buscar bloque por ID Bloque e ID Transacción"; 

			cout << "\n\tIngrese el Id del Bloque: "; cin >> Idbloque;
			cout << "\n\tIngrese el Id de la Transacción: "; cin >> IdTran;
			queriedRecord = db1.queryRecord(Idbloque, IdTran);
			if (queriedRecord.cod_block == -1) {
				cout << "Bloque No existe" << endl;
			}
			else
			{
				std::cout << "\n\nConsulta de Registro: cod_bloque=" << queriedRecord.cod_block << ", id_tran="
					<< queriedRecord.id_tran << ", desde=" << queriedRecord.emisor
					<< ", hasta=" << queriedRecord.receptor << ", fecha transacción=" << queriedRecord.fecha_tran << std::endl;
			}
			system("pause"); system("cls");
			break;

		case 2: system("cls"); cout << "Buscar Transacción por Emisor"; 
		
			std::cout << "\n\nRegistros ordenados por Receptor:" << std::endl;
			db1.sortRecordsByColumn("receptor");
			
			system("pause"); system("cls");
			break;
		case 3: system("cls"); cout << "Listar ordenado por Monto"; 
			
			std::cout << "\n\nRegistros ordenados por Monto:" << std::endl;
			db1.sortRecordsByColumn("monto");

			system("pause"); 
			system("cls");
			break;
		case 4: system("cls"); cout << "Listar ordenado por Fecha de Transacción"; 
			
			std::cout << "\n\nRegistros ordenados por Fecha de Transacción:" << std::endl;
			db1.sortRecordsByColumn("fecha_tran");
			
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
