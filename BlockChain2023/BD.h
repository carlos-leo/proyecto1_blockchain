#ifndef __BD_CSV_H
#define __BD_CSV_H


#include <iostream>
#include<vector>
#include "TablaHash.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

const int MAX_COLUMNS = 50;

// Generación de la clave única por registro
int gen_key_record(int cod_block, int id_tran)
{
    return 1000000 * cod_block + id_tran;
}

// DefiniciÃ³n de una estructura de datos para almacenar registros en la base de datos
struct Record {
    int key_record;  // Clave única del registro
    int cod_block;
    std::string fecha_block;
    std::string hash_previo;
    std::string hash_actual;
    int nounce;
    int id_tran;
    double monto;
    std::string emisor;
    std::string receptor;
    std::string fecha_tran;

    Record(std::string cod_block, std::string fecha_block, std::string hash_previo, std::string hash_actual,
        std::string nounce, std::string id_tran, std::string monto, std::string emisor, std::string receptor,
        std::string fecha_tran)
    {
        Record::key_record = gen_key_record(std::stoi(cod_block), std::stoi(id_tran));
        Record::cod_block = std::stoi(cod_block);
        Record::fecha_block = fecha_block;
        Record::hash_previo = hash_previo;
        Record::hash_actual = hash_actual;
        Record::nounce = std::stoi(nounce);
        Record::id_tran = std::stoi(id_tran);
        Record::monto = std::stod(monto);
        Record::emisor = emisor;
        Record::receptor = receptor;
        Record::fecha_tran = fecha_tran;
    };

    Record() {
        Record::key_record = -1;
        Record::cod_block = -1;
        Record::fecha_block = "0000/00/0000 00:00";
        Record::hash_previo = "00000000000000000000000000000000000";
        Record::hash_actual = "00000000000000000000000000000000000";
        Record::nounce = -1;
        Record::id_tran = -1;
        Record::monto = -1.0;
        Record::emisor = "";
        Record::receptor = "";
        Record::fecha_tran = "0000/00/0000 00:00";;
    }
};

/// <summary>
/// Definición de la estructura para el arbol de busqueda
/// </summary>
struct TreeNode {
    Record data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Record& record)
        : data(record), left(nullptr), right(nullptr) {}
};

/// <summary>
/// La clase BD es la que gestiona la información del BlockChain (Bloques y sus Transacciones)
/// Esta hecha a base de un arbol BTS
/// </summary>
class Database {

private:
    TreeNode* root; // Raiz del arbol binario de busqueda
    HashTable<int, TreeNode*> recordsMap; // Tabla hash para acceder a los nodos por su ID
    std::map<std::string, std::vector<TreeNode*>> indexMap; // Tabla hash para almacenar Ã­ndices por columna deseada

public:
    int nroFilas, nroColumnas;
    std::string lstColumnas[MAX_COLUMNS];


    Database() : root(nullptr), nroColumnas(0), nroFilas(0) {}

    TreeNode* getNodoInicial() {
        return root;
    }

    std::string* split(const std::string& line, char delimiter) const {
        //std::vector<std::string> fields;
        std::string* fields = new std::string[MAX_COLUMNS];
        std::stringstream ss(line);
        std::string field;
        int i = 0;
        while (std::getline(ss, field, delimiter)) {
            fields[i] = field;
            i++;
        }
        return fields;
    }

    
    // Leer archivo CSV y guardar en la BD  
    bool readCSV(const std::string& filename, char delimiter) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "No se pudo abrir el archivo " <<filename<< std::endl;
            return false;
        }

        int f = 0;
        int c = 0;
        //Record rec_tmp;
        std::string line;
        std::cout << "Guardando los datos en la BD:\n";
        while (std::getline(file, line)) {
            std::string *fields = split(line, delimiter);
            if (f == 0) { // Obtener los nombres de las columnas
                std::cout << "Nombre de columnas:\n";
                //for (const auto& col : fields)
                while(fields[c] != "")
                {
                    lstColumnas[c] = fields[c];
                    std::cout << fields[c] << "\t";
                    c++;
                }
                nroColumnas = c; // NÃºmero de columnas
            }
            else {
                // Guardar cada registro en la BD
                //std::string* s = fields.data();
                Record rec_tmp(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5], fields[6], fields[7], fields[8], fields[9]);
                insertRecord(rec_tmp); // guardando cada registro 
            }
            f++;
            std::cout << "\n";
        }
        nroFilas = f - 1; // filas sin contar la 1ra fila de cabeceras
        file.close();
        return true;
    }

    // Extrayendo información del árbol
    void dumpToCSVHelper(TreeNode* node, std::ofstream& file) {
        if (!node) {
            return;
        }

        dumpToCSVHelper(node->left, file);
        file << node->data.cod_block << "," 
             << node->data.fecha_block << ","
             << node->data.hash_previo << ","
             << node->data.hash_actual << ","
             << node->data.nounce << ","
             << node->data.id_tran << ","
             << node->data.monto << ","
             << node->data.emisor << ","
             << node->data.receptor << ","
             << node->data.fecha_tran << std::endl;
        dumpToCSVHelper(node->right, file);
    }

    // guardar la información de la BD a un archivo csv
    bool toCSV(std::string& nameFile) 
    {
        std::ofstream file(nameFile);
        if (!file) {
            std::cerr << "No se pudo crear el archivo " << nameFile << std::endl;
            return false;
        }
        
        // Guardar los nombres de las columans
        file << lstColumnas[0] << ","
            << lstColumnas[1] << ","
            << lstColumnas[2] << ","
            << lstColumnas[3] << ","
            << lstColumnas[4] << ","
            << lstColumnas[5] << ","
            << lstColumnas[6] << ","
            << lstColumnas[7] << ","
            << lstColumnas[8] << ","
            << lstColumnas[9] << std::endl;

        dumpToCSVHelper(root, file);
        file.close();
        return true;
    }

    // Guardar registro
    void insertRecord(const Record& record) {
        TreeNode* newNode = new TreeNode(record);
        root = insertHelper(root, newNode);
        recordsMap[record.key_record] = newNode;
        updateIndexMap(newNode);
    }

    /// <summary>
    /// Insertar según el nodo dado, el valor del nuevo nodo (der o izq)
    /// Si nodo dado es nulo, entonces insertar en la raiz
    /// Si valor de nuevo nodo es menor que nodo dado, insertar a la izq
    /// Si valor de nuevo nodo es mayor que nodo dado, insertar a la der
    /// </summary>
    /// <param name="node"></param>
    /// <param name="newNode"></param>
    /// <returns>nodo insertado</returns>
    TreeNode* insertHelper(TreeNode* node, TreeNode* newNode) {
        if (node == nullptr) {
            return newNode;
        }

        if (newNode->data.key_record < node->data.key_record) {
            node->left = insertHelper(node->left, newNode);
        }
        else if (newNode->data.key_record > node->data.key_record) {
            node->right = insertHelper(node->right, newNode);
        }

        return node;
    }

    /// <summary>
    /// Eliminar un registro de la BD, es eliminar una transacción 
    /// </summary>
    /// <param name="id_block"></param>
    /// <param name="id_tran"></param>
    void deleteRecord(int id_block, int id_tran = -1) {
        int key_record = gen_key_record(id_block, id_tran);
        if (id_tran == -1) // Borrar todo bloque (todas sus transacciones)
        {
            std::cout << "Falta implementar el borrado de bloque\n";
        }
        else { // Borrar una transacción
            TreeNode* node = searchNode(key_record);
            if (node != nullptr) {
                root = deleteHelper(root, node);
                recordsMap.erase(key_record);
                removeFromIndexMap(node);
            }
        }
    }

    /// <summary>
    /// Borrar toda la BD
    /// </summary>
    /// <param name="node"></param>
    void deleteDB(TreeNode* node) {

        if (!node) {
            return;
        }

        deleteDB(node->left);
        deleteDB(node->right);
        deleteRecord(node->data.cod_block, node->data.id_tran);
        //delete node;
    }

    TreeNode* deleteHelper(TreeNode* node, TreeNode* deleteNode) {
        if (node == nullptr) {
            return node;
        }

        if (deleteNode->data.key_record < node->data.key_record) {
            node->left = deleteHelper(node->left, deleteNode);
        }
        else if (deleteNode->data.key_record > node->data.key_record) {
            node->right = deleteHelper(node->right, deleteNode);
        }
        else {
            if (node->left == nullptr) {   // si la izq no tiene, lo tiene la derecha
                TreeNode* temp = node->right;  // salvaguardar la derecha
                delete node;               // eliminar este nodo
                return temp;               // retornar nodo salvaguardado
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* successor = minValueNode(node->right);
            node->data = successor->data;
            node->right = deleteHelper(node->right, successor);
        }

        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    bool updateRecord(const Record& updatedRecord) {
        TreeNode* node = searchNode(updatedRecord.key_record);
        if (node != nullptr) {
            node->data = updatedRecord;
            removeFromIndexMap(node);
            updateIndexMap(node);
            return true;
        }
        return false;
    }

    // retordar la data de una transacción (un record)
    Record queryRecord(int id_block, int id_tran = -1) {
        if (id_tran == -1) // Consultar todo bloque (todas sus transacciones)
        {
            std::cout << "Falta implementar la consulta de todo el bloque\n";
            std::string s = "-1"; // variable por un tema de referencia
            return Record(s, "1980/01/01 00:00", "", "", s, s, "0.0", "", "", "1980/01/01 00:00");
        }
        else { // Consultar una transacción
            int key_record = gen_key_record(id_block, id_tran);
            TreeNode* node = searchNode(key_record);

            if (node != nullptr) {
                return node->data;
            }
            else {
                return Record();
            }
        }
    }

    /// <summary>
    /// Se busca un nodo por el id del nodo 
    /// Si no encuentra el nodo devuelbe nulo
    /// </summary>
    /// <param name="id"></param>
    /// <returns>Se obtiene el nodo con toda su información </returns>
    TreeNode* searchNode(int id) {
        
        TreeNode **it = recordsMap.find(id);
        if (it == nullptr) {
            return nullptr;
        }
        else {
            return *it;
        }
    }

    /// <summary>
    /// Ordenamiento de datos por alguna columna
    /// </summary>
    /// <param name="column"></param>
    void sortRecordsByColumn(const std::string& column) {
        std::vector<TreeNode*> sortedNodes = indexMap[column];

        std::sort(sortedNodes.begin(), sortedNodes.end(), [column](const TreeNode* a, const TreeNode* b) {
            if (column == "cod_block") {
                return a->data.cod_block < b->data.cod_block;
            }
            else if (column == "fecha_block") {
                return a->data.fecha_block < b->data.fecha_block;
            }
            else if (column == "hash_previo") {
                return a->data.hash_previo < b->data.hash_previo;
            }
            else if (column == "hash_actual") {
                return a->data.hash_actual < b->data.hash_actual;
            }
            else if (column == "nounce") {
                return a->data.nounce < b->data.nounce;
            }
            else if (column == "id_tran") {
                return a->data.id_tran < b->data.id_tran;
            }
            else if (column == "monto") {
                return a->data.monto < b->data.monto;
            }
            else if (column == "emisor") {
                return a->data.emisor < b->data.emisor;
            }
            else if (column == "receptor") {
                return a->data.receptor < b->data.receptor;
            }
            else if (column == "fecha_tran") {
                return a->data.fecha_tran < b->data.fecha_tran;
            }
            else {
                // Si no se elije algún campo válido
                return false;
            }
            });

        for (TreeNode* node : sortedNodes) {  // Presentación tabla
            std::cout << "Cod. Bloque: " << node->data.cod_block << ", H Prev: " << node->data.hash_previo
                << ", H actual: " << node->data.hash_actual << ", Nounce: " << node->data.nounce
                << ", Id Transac.: " << node->data.id_tran << ", Monto: " << node->data.monto
                << ", De: " << node->data.emisor << ", Para:" << node->data.receptor 
                << ", Fecha Transacción: "<<node->data.fecha_tran<<std::endl;
        }
    }

private:
    // Actualiza otros campos 
    void updateIndexMap(TreeNode* node) {
        indexMap["key_record"].push_back(node);
        indexMap["cod_block"].push_back(node);
        indexMap["fecha_block"].push_back(node);
        indexMap["hash_previo"].push_back(node);
        indexMap["hash_actual"].push_back(node);
        indexMap["nounce"].push_back(node);
        indexMap["id_tran"].push_back(node);
        indexMap["monto"].push_back(node);
        indexMap["emisor"].push_back(node);
        indexMap["receptor"].push_back(node);
        indexMap["fecha_tran"].push_back(node);
    }

    void removeFromIndexMap(TreeNode* node) {
        removeFromVector(indexMap["key_record"], node);
        removeFromVector(indexMap["cod_block"], node);
        removeFromVector(indexMap["fecha_block"], node);
        removeFromVector(indexMap["hash_previo"], node);
        removeFromVector(indexMap["hash_actual"], node);
        removeFromVector(indexMap["nounce"], node);
        removeFromVector(indexMap["id_tran"], node);
        removeFromVector(indexMap["monto"], node);
        removeFromVector(indexMap["emisor"], node);
        removeFromVector(indexMap["receptor"], node);
        removeFromVector(indexMap["fecha_tran"], node);
        // Remover otros campos
    }

    void removeFromVector(std::vector<TreeNode*>& vec, TreeNode* node) {
        vec.erase(std::remove(vec.begin(), vec.end(), node), vec.end());
    }
};

#endif // !__BD_CSV_H