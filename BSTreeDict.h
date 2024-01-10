#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
	    BSTree<TableEntry<V>>* tree;

    public:
	    BSTreeDict(){
	    	tree = new BSTree<TableEntry<V>>();
	    }

	    ~BSTreeDict(){
	    	delete tree;
	    }

	    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
	    	if(bs.tree->size() > 0){
			out << *(bs.tree) << std::endl;
		}
		return out;
	    }

	    V operator[](std::string key){
	    	return tree->search(TableEntry<V>(key)).value;
	    }
	    void insert(std::string key, V value){
		    tree->insert(TableEntry<V>(key, value));
	    }
	    V search(std::string key){
		    return tree->search(TableEntry<V>(key)).value;
	    }

	    V remove(std::string key){
		    V prueba = tree->search(TableEntry<V>(key)).value;
		    tree->remove(TableEntry<V>(key));
		    return prueba;
	     }

	    int entries(){
		    return tree->size();
	    }
        
};

#endif
