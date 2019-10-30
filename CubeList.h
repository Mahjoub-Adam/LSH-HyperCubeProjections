#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>
using namespace std;

class BList{
	private :
		int value;
		int binary;
		BList *next;
	public :
		BList(int& Value) :
         	next(NULL){
		 	value = Value;
		 	//random timi gia to binary
		 	binary = rand()%2;
		 }

		int check(BList *root){
			return root->binary;
		}

		int find(int Value,BList *root){
			BList *assist = root;

			if(assist != NULL){
				if(assist->value == Value){
		//			cout << "There is already this one." << endl;
				//	return assist->binary;
				}

				while(assist->next != NULL){
					if(assist->next->value == Value){
			//			cout << "There is already this one." << endl;
						return assist->next->binary;
					}
					assist = assist->next;
				}
				//Efoson den brethike
				BList *New = new BList(Value);
				assist->next = New;
				return this->check(New);
				/*
			//	return this->check(assist->next); */

			}
			else{ /*
				cout << "2" << endl;
				BList *New = new BList(Value);
			//	root = New;
				return this->check(New->next);
			//	return this->check(root);
			/*	BList New(Value);
				*root = New;
			///	*root = new BList(Value);
			//	return this->check(root); */
			}
		}
};
