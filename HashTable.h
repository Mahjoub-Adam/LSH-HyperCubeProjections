#include "HashNode.h"
#include <iostream>
#include <cstddef>
using namespace std;

template <typename V>
class HashTable{
	private:
		HashTable(const HashTable & other);
    	const HashTable & operator=(const HashTable & other);
    	// hash table
    	HashNode<V> **table;
    	int tableSize;

	public :
		HashTable(int Size = 1000) : tableSize(Size)
        	{
        		table = new HashNode<V> * [Size];
        		int i;
				for(i=0;i<Size;i++){
					table[i] = NULL;
				}
			}

        ~HashTable(){ //destruction
        	// destroy all buckets one by one
        	for (size_t i = 0; i < tableSize; ++i) {
            	HashNode<V> *entry = table[i];

            	while (entry != NULL) {
                	HashNode<V> *prev = entry;
                	entry = entry->getNext();
                	delete prev;
            	}
				table[i] = NULL;
        	}
    	}

    	HashNode<V> *getBucket(int key){
    		return table[key];
		}

    	int get(const int &key, V value){
        	int hashValue = key; //allakse ti synartisi
        	HashNode<V> *entry = table[hashValue];

        	while (entry != NULL) {
            	if (entry->getKey() == key) {
                	value = entry->getValue();
                	return value;
            	}
				entry = entry->getNext();
        	}
			return -1;
		}

		void put(const int &key,  V value,int &j){
			int i;
        	unsigned long hashValue = key;
        	HashNode<V> *prev = NULL;
        	HashNode<V> *entry = table[hashValue];

        	while (entry != NULL && entry->getKey() == key) {
           	 	prev = entry;
            	entry = entry->getNext();
        	}

        	if (entry == NULL) {
            	entry = new HashNode<V>(key, value, j);

            	if (prev == NULL) {
              	  	// insert as first bucket
                	table[hashValue] = entry;}
				else {
                	prev->setNext(entry);
            	}
			}else{
		//
            	// just update the value
            	entry->setValue(value);
        	}
    	}
};
