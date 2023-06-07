#ifndef __TABLAHASH_H
#define __TABLAHASH_H

#include <iostream>
#include <string>

const int TABLE_SIZE = 100000;

/// <summary>
/// Forward List
/// </summary>
/// <typeparam name="Key"></typeparam>
/// <typeparam name="Value"></typeparam>
template<class Key, class Value>
struct HashNode {
    Key key;
    Value value;
    HashNode* next;

    HashNode(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
};

/// <summary>
/// Tabla Hash - Hecha a base de un arreglo simple para mantener los índices
/// </summary>
/// <typeparam name="Key"></typeparam>
/// <typeparam name="Value"></typeparam>
template<class Key, class Value>
class HashTable {
public:
    HashTable<Key, Value>() : table(new HashNode<Key, Value>*[TABLE_SIZE]()) {}

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode<Key, Value>* node = table[i];
            while (node) {
                HashNode<Key, Value>* prev = node;
                node = node->next;
                delete prev;
            }
        }
        delete[] table;
    }

    Value& operator[](const Key& key) {
        int index = hashFunction(key);
        HashNode<Key, Value>* node = table[index];

        while (node) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }

        node = new HashNode<Key, Value>(key, nullptr);
        node->next = table[index];
        table[index] = node;

        return node->value;
    }

    void erase(const Key& key) {
        int index = hashFunction(key);
        HashNode<Key, Value>* node = table[index];
        HashNode<Key, Value>* prev = nullptr;

        while (node) {
            if (node->key == key) {
                if (prev) {
                    prev->next = node->next;
                } else {
                    table[index] = node->next;
                }
                delete node;
                return;
            }
            prev = node;
            node = node->next;
        }
    }

    Value* find(const Key& key) {
        int index = hashFunction(key);
        HashNode<Key, Value>* node = table[index];

        while (node) {
            if (node->key == key) {
                return &(node->value);
            }
            node = node->next;
        }

        return nullptr;
    }

    HashNode<Key, Value>** begin() {
        return &table[0];
    }

    HashNode<Key, Value>** end() {
        return &table[TABLE_SIZE];
    }

private:
    HashNode<Key, Value>** table;

    /// <summary>
    /// Función que crea un valor hash único a partir de una clave o Key
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    int hashFunction(const Key& key) {
    	std::string strKey = std::to_string(key);
        int hash = 0;
        for (char c : strKey) {
            hash += c;
        }
        return hash % TABLE_SIZE;
    }
};

#endif // !__TABLAHASH_H
