#include <iostream>
#include  <cstdlib>
#include "HashFunctionG.h"
#include <bits/stdc++.h>
#include "HashTable.h"
#include "CubeHash.h"
#include <ctime>
#include <math.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include  <tgmath.h>
#include <new>

using namespace std;
using namespace std::chrono;
typedef unordered_multimap<string, int*>::iterator umit;

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
	srand (time(NULL));
	int councount = 0;
	double w;double Klasma;double maxAf = -1.00000;
	int d=128;int noa=0;int id;
	int k=4.0;int L = 4;string var;int BigM = 10;int probes = 2;int wCounter = 0;int min_id;
	string ajax;int i;
	string query_file,bf;string input_file;string output_file;
	// orismata
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
		}else if(ajax.compare("-M") == 0){
        	BigM = atoi(argv[noa+1]);
        //	cout << "L " << L << endl;
		}else if(ajax.compare("-probes") == 0){
        	probes = atoi(argv[noa+1]);
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
	//Orizoume tous boithitikous pinakes poy tha xreiastoume
	int **array = new int*[input_size];
	int **qry = new int*[query_size];
	int *bforce = new int[input_size];

	for(i=0 ; i<input_size ; i++){
		array[i] = new int[128];
	}
	for(i=0 ; i<query_size ; i++){
		qry[i] = new int[128];
	}


	string strings;string rep1 = "1";string rep0 = "0";string assist_string;
	int internal_counter=0;int external_counter;int h;int j;int n;int dist;int db;int kl;
	BinaryHashFunction F;
	string delimiter = " ";
	string token;
	size_t pos = 0;
	int i_dec;
	const int *f;

	int dt = log(input_size);


	G<int*> **gs = new G<int*>*[dt];
	for(i=0;i<dt;i++){
		gs[i]=new G<int*>(w,d,k); //We create all the g functions we are going to need
	}

	unordered_multimap<string, int*> um;
//	um = new unordered_multimap<string, int*>[dt]; //We create all the unordered multimaps

	int M = pow(2,32/k);

	int *mArray = new int[d];
	mArray[0]=1;
	for(i=1;i<d;i++){
	//	mArray[i] = (m^i)%M;
		n=(int)(((long)pow(2, 32)-5)%M);
		mArray[i]=(mArray[i-1]*n)%M;
	}


	std::ifstream input( input_file );
	std::string str;
	external_counter=0;
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
	std::ifstream brute( bf);
	external_counter=0;

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

	for(i=0;i<input_size;i++){//For every point of input
		strings.clear();
		for(j=0;j<dt;j++){
			h = gs[j]->G_function(array[i],w,d,k,M,mArray,true); //We take the Gj value
			h = F.F(h); //We take the binary value
			//We are going to add it on the binary string
			if(h==0){
				strings.append("0");
			}
			else{
				strings.append("1");
			}
		}
	//	cout << "Binary string key : " << strings << endl;
		um.insert(make_pair(strings, array[i]));//key,value
	}

    ofstream LSHfile(output_file);
    if(LSHfile.is_open()){
    	for(i=0;i<query_size;i++){
    		db=999999;
    		dist = 0;
    		strings.clear();
    		auto start = high_resolution_clock::now();
    		for(j=0;j<dt;j++){
    			h = gs[j]->G_function(qry[i],w,d,k,M,mArray,true); //We take the Gj value
    			h = F.F(h);
    			if(h==0){
					strings.append("0");
				}
				else{
					strings.append("1");
				}
			}
			//We've got the binary string.
			internal_counter = 0;
			external_counter = 0;
			while(internal_counter < probes && external_counter < BigM*10){
				umit it = um.begin();
				if(internal_counter == 0){
					assist_string = strings;
					//Nothing, we use binary string as it is.
				}
				else{ //We have already checked the main one.
					if(strings[probes-internal_counter] == '0'){
						assist_string = strings;
						assist_string.replace(probes-internal_counter,1,rep0);
					}
					else{
						assist_string = strings;
						assist_string.replace(probes-internal_counter,1,rep1);
					}
				}
				auto p = um.equal_range(assist_string);//find by key
				for (auto it = p.first; it != p.second; ++it){ //For every array on the same bucket
					//	cout << it->second[0] << " " << it->second[127] << " " << qry[1][0] << " " << qry[1][127] << endl;
      				//sto it->second exoume to pinaka kathe fora
      				external_counter++;
      				for(kl=0;kl<128;kl++){
      					dist = dist + std::abs(qry[i][kl]-(it->second[kl]));
					}
					if(dist < db){
						db = dist;
					}
      			}
      			assist_string.clear();
      			internal_counter++;
      		}
      		auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
      		cout << "The shortest distance for item" << i << " is " << db << " in " << duration.count() << endl;
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
			var =  "Nearest Neighbor : " + to_string(rand()%input_size);
			LSHfile<<var<< endl;
			var.clear();
			/////////////////////////////////////////////
			var =  "distanceCube : " + to_string(db);
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
		}
	}
	cout << "Af : " << maxAf  << endl ;

	for(i=0;i<input_size;i++){
		delete [] array[i];
	}
	for(i=0;i<query_size;i++){
		delete [] qry[i];
	}
	for(int i=0;i<dt;i++){
    delete gs[i];
	}
  delete[] mArray;
  delete[] gs;
	delete [] qry;
	delete [] array;
	delete [] bforce;
	return 0;
}
