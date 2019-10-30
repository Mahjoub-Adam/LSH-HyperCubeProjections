#include <iostream>
#include  <cstdlib>
#include "HashFunctionG.h"
#include "HashTable.h"
#include <ctime>
#include <math.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <new>

using namespace std;
using namespace std::chrono;

int File_size(string name){
	ifstream input( name );
	int counter = 0;
	string str;

	while (std::getline(input, str)){
		counter++;
	}

	return counter;
}

int main(int argc,char *argv[]){
	int councount = 0;
	srand(time(NULL));
	double w=4500.0;double Klasma;double maxAf = -1.00000;
	int d=128;int noa=0;int id;
	int k=4.0;int L = 4;string var;
	string output_file,bf;string input_file;string query_file;
	string ajax;
	for (noa = 1; noa < argc; noa=noa+2) {
		ajax = argv[noa];
        if(ajax.compare("-d") == 0){
        	input_file = argv[noa+1];
        //	cout << "Input " << input_file << endl;
		}
		else if(ajax.compare("-q") == 0){
        	query_file = argv[noa+1];
        //	cout << "Query " << query_file << endl;
		}
		else if(ajax.compare("-k") == 0){
        	k = atoi(argv[noa+1]);
        //	cout << "k " << k << endl;
		}else if(ajax.compare("-L") == 0){
        	L = atoi(argv[noa+1]);
        //	cout << "L " << L << endl;
		}else if(ajax.compare("-bf") == 0){
        	bf = argv[noa+1];
		}
		else{ //-o
			output_file = argv[noa+1];
		}
    }

	int input_size = File_size(input_file);
	int query_size = File_size(query_file);
	HashNode<int*> *assist;

	const int *f;
	int totalTime=0;int min_id;
	HashNode<int*> *p;
	int i_dec,i,n,h,q;
	int **array = new int*[input_size];
	int **qry = new int*[query_size];
	int *bforce = new int[input_size];

	for(i=0 ; i<input_size ; i++){
		array[i] = new int[128];
	}
	for(i=0 ; i<query_size ; i++){
		qry[i] = new int[128];
	}

	int internal_counter=0;
	int external_counter=0;
	string delimiter = " ";
	string token;
	size_t pos = 0;

	HashTable<int*> *htable;

	htable = new HashTable<int*>[L]; //Ftiaxnoume L Hash tables





	std::ifstream input( input_file );
	std::string str;

	while (std::getline(input, str)){ //gia kathe simeio tou pinaka input
		internal_counter=0;
		while ((pos = str.find(delimiter)) != string::npos){
			token = str.substr(0, pos);
    		std::istringstream(token) >> i_dec;
    		if(internal_counter != 0){
    			array[external_counter][internal_counter-1]=i_dec;
    			councount = councount + i_dec;
			}
    		internal_counter++;
    		str.erase(0, pos + delimiter.length());
		}
		external_counter++;
	}
//	w = 4.0*(councount/(input_size*128));
	std::ifstream brute(bf);
	external_counter=0;
	int wCounter;
	while (std::getline(brute, str)){ //gia kathe simeio tou pinaka Brute force
		internal_counter=0;
		while ((pos = str.find(delimiter)) != string::npos){
				token = str.substr(0, pos);
    			std::istringstream(token) >> i_dec;

    			if(internal_counter==1){
    				bforce[external_counter]=i_dec;
    				wCounter = wCounter + i_dec;
    			}
				str.erase(0, pos + delimiter.length());
			internal_counter++;
		}
		external_counter++;
	}

	w = 400.0 * (wCounter/input_size);


	std::ifstream query( query_file );
	external_counter=0;
	while (std::getline(query, str)){ //gia kathe simeio tou pinaka query
		internal_counter=0;
		while ((pos = str.find(delimiter)) != string::npos){
			token = str.substr(0, pos);
    		std::istringstream(token) >> i_dec;
    		if(internal_counter != 0){
    			qry[external_counter][internal_counter-1]=i_dec;
    		//	cout << i_dec << "  ";
			}
    		internal_counter++;
    		str.erase(0, pos + delimiter.length());
		}
		external_counter++;
	//	cout << endl << endl << endl;
	}



	G<int*> g(w,d,k);
	G<int*> **gs = new G<int*>*[L];
	for(i=0;i<L;i++){
		gs[i]=new G<int*>(w,d,k);
	}


	int M = pow(2,32/k);

	int *mArray = new int[d];
	mArray[0]=1;
	for(i=1;i<d;i++){
	//	mArray[i] = (m^i)%M;
		n=(int)(((long)pow(2, 32)-5)%M);
		mArray[i]=(mArray[i-1]*n)%M;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////Teleiosan ta orismata,pame na topothetisoume ta input sta hash tables ///////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	for(q=0;q<L;q++){
		for(i=0;i<input_size;i++){
			h = gs[q]->G_function(array[i],w,d,k,M,mArray,true); //kathe ena tha topothetithei sto hash table me to g gia key tou

			htable[q].put(h, array[i],i);
		}
	}
	int counter=0;int b=0;int db;int count=0; int dist;
	ofstream LSHfile(output_file);
	if(LSHfile.is_open()){
		for(i=0;i<query_size;i++){ //gia kathe simeio tou query
			//tha broume to g tou ekastote simeioy gia kathe g
			db=999999;
			auto start = high_resolution_clock::now();
			for(q=0;q<L;q++){
				h = gs[q]->G_function(qry[i],w,d,k,M,mArray,true);
				p=htable[q].getBucket(h);
				//tha psaxo gia kathe simeio tou bucket na bro to kontinoterou simeioy
				count = 0;
				while(p != NULL && count < 150*L){
					f = p->getValue(); //Kathe simeio tou bucket
					id = p->get_Id();
					dist = 0; //Tha elegxoume gia kathe simeio tou bucket
					for(n=0;n<128;n++){
						dist = dist + std::abs(qry[i][n]-f[n]);
					}
					if(dist < db){
						db = dist;
						min_id = id+2;
					}
					p = p->getNext();
					count++;
				}
			}
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			totalTime = duration.count() + totalTime;
			cout << "The shortest point for " << i+1 << " is : " << db << " on time : " << duration.count() << " from : " << min_id << endl;
			if(bforce[i] != 0){
      			Klasma = (1.0*db) / bforce[i];
				if(Klasma > maxAf){
					maxAf = Klasma;
				}
			}
			var =  "Query : " + to_string(i+1);
			LSHfile<<var<< endl;
			var.clear();
			/////////////////////////////////
			var =  "Nearest Neighbor : " + to_string(min_id);
			LSHfile<<var<< endl;
			var.clear();
			/////////////////////////////////////////////
			var =  "distanceLSH : " + to_string(db);
			LSHfile<<var<< endl;
			var.clear();
			/////////////////////////////////////////////
			var =  "distanceTrue : " + to_string(bforce[i]);
			LSHfile<<var<< endl;
			var.clear();
			/////////////////////////////////////////////
			var =  "LSHtime : " + to_string(duration.count());
			LSHfile<<var<< endl;
			var.clear();
			/////////////////////////////////////////////
			var =  "-----------------------------------";
			LSHfile<<var<< endl;
			var.clear();
		/*	var =  "tLSH : " + to_string(124);
			BFfile<<var<< endl;
			var.clear(); */
			/////////////////////////////////////////////
		}
		cout << endl << "M.O. = " << totalTime/(query_size*1000.0) << endl;
		cout << endl << "maxAF = " << maxAf << endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////// Pername sto LSH ///////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	cout << "wCounter " << wCounter << endl;
	cout << "w : " << w << endl;
	cout << "input_counter : " << input_size << endl;

	for(i=0;i<input_size;i++){
		delete [] array[i];
	}
	for(i=0;i<query_size;i++){
		delete [] qry[i];
	}
	for(int i=0;i<L;i++){
    delete gs[i];
	}
  delete[] mArray;
  delete[] gs;
	delete [] qry;
	delete [] array;
	delete [] bforce;

	return 0;
}
