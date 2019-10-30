#include <iostream>
using namespace std;

class BList{
	private : 
		int value;
		int binary;
		BList *next;
	public :
		BList(int& Value) :
         	next(NULL)
		 {
		 	value = Value;
		 	//random timi gia to binary
		 	binary = 0;
		 }
		
		find(int Value,BList *root){
			if(root != NULL){
				if(root->value == Value){
					return root->binary;
				}			
				root = root->next;
				while(root != NULL){
					if(root->value == Value){
						return root->binary;
					}
					root = root->next;
				}
				//Efoson den brethike
				Blist New(Value);
				root->next = New;
				return New->binary;
			}
			else{
				Blist New(Value);
				root = New;
				return New->binary;
			}
		}
};
