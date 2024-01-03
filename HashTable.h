#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"  


template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	int h(std::string key){
		int suma = 0;
		for(size_t i=0; i<key.length(); i++){
			suma += static_cast<int>(key.at(i));
		}
		return suma % max;
	}

    public:

	HashTable(int size){
		table = new ListLinked<TableEntry<V>>[size];
		n = 0;
		max = size;
	}

	~HashTable(){
		delete[] table;
	}

	int capacity(){
		return max;
	}

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		out << "HashTable [entries: "<< th.n <<", capacity: " << th.max << "]"<< std::endl;
		out <<"=================="<<std::endl;

		for (int i = 0; i < th.max; i++){
			out<<"Cubeta "<<i<<std::endl<<"List =>  ["<<std::endl<<th.table[i]<<std::endl<<"]"<<std::endl;
		}

		out <<"=================="<<std::endl;
		return out;	
	}
	V operator[](std::string key){
		return search(key);
	}
        void insert(std::string key, V value) override final{
		for(int i = 0; i < table[h(key)].size(); i++){
			if(table[h(key)].get(i).key == key){
				throw std::runtime_error("Esta key ya existe\n");
			}	
		}
		table[h(key)].prepend(TableEntry<V>(key, value));
		n++;
	}

	V search(std::string key) override final{
		for(int i = 0; i<table[h(key)].size(); i++){
			if(table[h(key)].get(i).key == key){
				return table[h(key)].get(i).value;
			}
		}
		throw std::runtime_error("Key no encontrada.\n");
	}
        
	V remove(std::string key){
		for(int i = 0;  i< table[h(key)].size() ;i++){
			if(table[h(key)].get(i).key == key){				    
				TableEntry<V> valor=table[h(key)].remove(i);
				n--;
				return valor.value;
			}			
		}
		throw std::runtime_error("Key no encontrada.\n");
	}

	int entries() override final{
		return n;
	}

};

#endif
