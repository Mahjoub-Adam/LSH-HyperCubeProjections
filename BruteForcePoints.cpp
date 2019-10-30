#include <iostream>
#include <fstream>
#include <string>
#include <new>

#include <cstdio>
#include <sstream>
#include <cmath>

using namespace std;

int File_size(string name){
	ifstream input( name );
	int counter = 0;
	string str;

	while (std::getline(input, str)){
		counter++;
	}

	return counter;
}

void find(int i,int q,int d,string bf,string inputtt,string que){ //d oi diastaseis pou exoume
	string token;string assist;string var;
	ostringstream oss;
	string delimiter = " ";
	int internal_counter = 0;int min_id;int id;
	int *use,i_dec,a;
	int counterQuery=0;
	int min=999999;
	float ManhSum=0.0;
	size_t pos = 0;
	size_t mpos = 0;
	std::ifstream input( inputtt );
	std::ifstream query( que );
	std::string str;
	std::string inp;
	use = new int[d];
	ofstream BFfile(bf);
	if(BFfile.is_open()){
		while (std::getline(query, str)){
			internal_counter++;
//        	cout << str << "\n";
			while ((pos = str.find(delimiter)) != string::npos) {
    			token = str.substr(0, pos);
    			std::istringstream(token) >> i_dec;
    	//	cout << i_dec << " ";
				use[counterQuery]=i_dec;
    			counterQuery++;
    			str.erase(0, pos + delimiter.length());
			}

			std::ifstream input( inputtt );
			id = 1;
			while(std::getline(input,inp)){ //Tha anatrexoume kathe simeio tou input
				counterQuery=0;
				id++;
				while ((mpos = inp.find(delimiter)) != string::npos){ //Tha anatrexoume kathe syntetagmeni kathe simeiou
					assist = inp.substr(0, mpos);
					std::istringstream(assist) >> i_dec;
					if(counterQuery != 0){
						ManhSum = ManhSum + std::abs(i_dec-use[counterQuery]);
					}
				//Ypologismos manhatan
					counterQuery++;
					inp.erase(0, mpos + delimiter.length());
				}
				if(ManhSum < min){
					min=ManhSum;
					min_id = id;
				}
				ManhSum=0.0;
				counterQuery=0;
			}

			cout << "The shortest for "<< internal_counter << " is : " << min << " from : " << min_id << endl ;
		//	oss << "The shortest for "<< internal_counter << " is : " << min << " from : " << min_id << endl ;
		//	var = oss.str();
			var =  to_string(internal_counter) + " " +  to_string(min) + " " + to_string(min_id);
			BFfile<<var<< endl;
			var.clear();
			min=999999.0;
		//Tha anatrexoume kathe simeio tou input metrontas tin apostasi
			counterQuery=0;
    	}
    //	BFfile<<var<< endl;
    	BFfile.close();
    }else{
    	cerr<<"Unable to open file";
	}

}

int main(int argc,char *argv[]){
	string ajax;int noa;
	string input_file;string query_file;string output_file;
	for (noa = 1; noa < argc; noa=noa+2) {
		ajax = argv[noa];
        if(ajax.compare("-d") == 0){
        	input_file = argv[noa+1];
        //	cout << "Input " << input_file << endl;
		}
		else if(ajax.compare("-q") == 0){
        	query_file = argv[noa+1];
        //	cout << "Query " << query_file << endl;
		}else{//-o
			output_file = argv[noa+1];
		}
	}
	int query_size = File_size(query_file);
	int input_size = File_size(input_file);
	find(query_size,input_size,128,output_file,input_file,query_file);
	return 0;
}
