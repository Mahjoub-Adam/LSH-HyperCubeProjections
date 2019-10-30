#include <iostream>
using namespace std;

//class template
template <class T> //orizoume edo oti theloume na apothikeyoume sto hash table os T kai to kleidi tou kathe simeiou os K
class HashNode{
	private:
		HashNode(const HashNode &);
    	HashNode & operator=(const HashNode &);
		//data set
		int _key;
		T _value; //en prokeimeno theloume ena pinaka apo int diastaseos 128
		int id;
		//pointer to the nex
		HashNode *_next;
	public:
		HashNode(const int &key,  T& value,int ID) :
        _key(key), _value(value), id(ID), _next(NULL){}

    	int getKey() const{
        	return _key;
    	}

		int get_Id() const{
			return id;
		}

    	T getValue() const{
        	return _value;
    	}

    	void setValue(T value){
       		_value = value;
    	}

    	HashNode *getNext() const{
        	return _next;
    	}

    	void setNext(HashNode *next){
        	_next = next;
    	}
};


//Tha orisoume kai to pinaka

template <> //orizoume edo oti theloume na apothikeyoume sto hash table os T kai to kleidi tou kathe simeiou os K
class HashNode <int*>{
	private:
		HashNode(const HashNode &);
    	HashNode & operator=(const HashNode &);
		//data set
		int _key;
		int* _value; //en prokeimeno theloume ena pinaka apo int diastaseos 128
		int id;
		//pointer to the nex
		HashNode *_next;
	public:
		HashNode(const int &key, int*  value,int &ID ) :
        _key(key), _value(value), id(ID), _next(NULL){
			int i;
		}

    	int getKey() const{
        	return _key;
    	}

    	int get_Id() const{
			return id;
		}

    	int * getValue() const{
        	return _value;
    	}

    	void setValue(int *value){
       		_value = value;
    	}

    	HashNode *getNext() const{
        	return _next;
    	}

    	void setNext(HashNode *next){
        	_next = next;
    	}
};
