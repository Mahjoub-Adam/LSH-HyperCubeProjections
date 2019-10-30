#include <iostream>
#include <cstddef>
#include "CubeList.h"
#include <list>
using namespace std;

class BinaryHashFunction{
	private :
		BList *array;
	public :
		BinaryHashFunction(){
			array=NULL;
		}
		
		int F(int value){
			if(array == NULL){
				array = new BList(value);
				return (array->check(array));
			}
			int j = array->find(value,array);
			return j;
		}
};
