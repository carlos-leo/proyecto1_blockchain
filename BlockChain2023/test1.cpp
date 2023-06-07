/*
#include "BlockChain.h"
#include "Transaccion.h"
#include <iomanip>
#include "TextTable.h"
*/
#include "BD.h"

int main() {
    Database db;

    std::string nameFileIn = "dbc.csv"; // "dataset_pequeno_v1.csv";    // "dataset_grande_v1.csv";
    std::string nameFileOut = "dbc_salida.csv";

    if (db.readCSV(nameFileIn, ',')) {
        std::cout << "\nEl archivo " << nameFileIn << " tiene " << db.nroColumnas << " columnas\n";
        std::cout << "El archivo " << nameFileIn << " tiene " << db.nroFilas << " filas\n";


        // Consultar registro por codigo de bloque (y codigo de transaccion)
        Record queriedRecord = db.queryRecord(4, 5);
        std::cout << "\n\nConsulta de Registro: cod_bloque=" << queriedRecord.cod_block << ", id_tran="
            << queriedRecord.id_tran << ", desde=" << queriedRecord.emisor
            << ", hasta=" << queriedRecord.receptor << ", fecha transacción=" << queriedRecord.fecha_tran << std::endl;


        // Actualizar registro
        Record rec_tmp("4", "2020/06/25 15:40", "0000AASDF78SD9SD0SDG0GF123456", "00009876548SD9SD0SDG0GF87G7DF", "1234", "6", "25400", "Fidel", "Ana", "2020/07/25 08:13");
        if (db.updateRecord(rec_tmp))
        {
            std::cout << "Se actualizó el registro\n";
        }
        else {
            std::cout << "No se pudo actualizar el registro\n";
        }

        /*
        // Eliminar registro
        std::cout << "\n\nEliminar el Bloque 1 Transaccion 2:" << std::endl;
        db.deleteRecord(1, 2); // Borrar transaccion 2 del bloque 1

        std::cout << "\n\nConsultar el Bloque 1 Transaccion 1:" << std::endl;
        Record queriedRecord1 = db.queryRecord(1, 1);
        std::cout << queriedRecord1.id_tran << ", Emisor=" << queriedRecord1.emisor
            << ", Receptor=" << queriedRecord1.receptor << ", fecha transacción=" << queriedRecord.fecha_tran << std::endl;

        std::cout << "\n\nConsultar el Bloque 1 Transaccion 2:" << std::endl;
        queriedRecord1 = db.queryRecord(1, 2);
        std::cout << queriedRecord1.id_tran << ", Emisor=" << queriedRecord1.emisor
            << ", Receptor=" << queriedRecord1.receptor << ", fecha transacción=" << queriedRecord.fecha_tran << std::endl;

        // Inserción de nuevos registros
        db.insertRecord(Record("4", "2019/08/25 15:40", "0000AASDF78SD9SD0SDG0GF000000", "00001234568SD9SD0SDG0GF87G7DF", "8521", "1", "180.25", "Armando", "Lucia", "2022/08/25 09:13"));
        db.insertRecord(Record("4", "2019/08/25 15:40", "0000AASDF78SD9SD0SDG0GF000000", "00001234568SD9SD0SDG0GF87G7DF", "8521", "2", "180.25", "Lucia", "Armando", "2022/08/28 10:15"));
        */
        // Ordenar registros por columna deseada
        std::cout << "\n\nRegistros ordenados por Receptor:" << std::endl;
        db.sortRecordsByColumn("receptor");

        std::cout << "\n\nRegistros ordenados por Monto:" << std::endl;
        db.sortRecordsByColumn("monto");

        std::cout << "\n\nRegistros ordenados por Fecha de Transacción:" << std::endl;
        db.sortRecordsByColumn("fecha_tran");


        // Guardar los datos modificados
        if (db.toCSV(nameFileOut)) {
            std::cout << "La BD fue guardada en el archivo " << nameFileOut << " correctamente." << std::endl;
        }

        // Borrar el arbol desde la raiz
        db.deleteDB(db.searchNode(1000001));


    }


    return 0;
}