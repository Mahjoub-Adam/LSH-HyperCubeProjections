#include "Grid_Projection_Functions.h"
void arguments(string &input,string &query,string &output,string &bf,int &k,int &L,double &e,int&M,int &size,int &probes,int argc,char *argv[]){
//simple arguments read from terminal
string ajax;
int noa;
  for (noa = 1; noa < argc; noa=noa+2) {
    ajax = argv[noa];
        if(ajax.compare("-d") == 0){
          input = argv[noa+1];
    }
    else if(ajax.compare("-q") == 0){
          query = argv[noa+1];
    }
    else if(ajax.compare("-bf") == 0){
          bf = argv[noa+1];
    }
    else if(ajax.compare("-M") == 0){
          M = atoi(argv[noa+1]);
    }
    else if(ajax.compare("-k_vec") == 0){
          k = atoi(argv[noa+1]);
    }
    else if(ajax.compare("-k_hypercube") == 0){
          k = atoi(argv[noa+1]);
    }
    else if(ajax.compare("-e") == 0){
          e = stod(argv[noa+1]);
    }else if(ajax.compare("-L_grid") == 0){
          L = atoi(argv[noa+1]);
    }
    else if(ajax.compare("-L_vec") == 0){
          L = atoi(argv[noa+1]);
    }
    else if(ajax.compare("-probes") == 0){
          probes = atoi(argv[noa+1]);
    }
    else if(ajax.compare("-size") == 0){
          size = atoi(argv[noa+1]);
    }
    else{
      output = argv[noa+1];
    }
  }
}
