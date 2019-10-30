#include "Grid_Projection_Functions.h"
#include "arguments.h"
int main(int argc,char *argv[]){
  double w=65.0,avg,e=0.5;
  int k,L,M,*mArray,n1=0,n2=0,probes,max,size;
  string input,query,output,str,bf;
  arguments(input,query,output,bf,k,L,e,max,size,probes,argc,argv); //receive arguments from terminal
  ifstream inputData(input);
  while(getline(inputData, str)){
      n1++;
  }
  ifstream queryData(query);
  while(getline(queryData, str)){
      n2++;
  } //get the count of query and input //
  pair<int,vector<pair<double,double>>> inputPoints[n1],queryPoints[n2];
  HashTable<pair<int,vector<pair<double,double>>>> *htable = new HashTable<pair<int,vector<pair<double,double>>>>[L];
  vector<double> queryVector[n2][1],inputVector[n1][1];
  vector<vector<float>> GV;
  pair<int,double>trueNN[n2];
  vector<pair<pair<int,int>,vector<vector<pair<int,int>>>>> traversals;
  int d=read_data(true,bf,trueNN,avg,size,false,traversals,GV,floor(-2*log(e)/pow(e,2)),input,query,1,n1,n2,inputPoints,queryPoints,inputVector,queryVector);
  // read data from files
  int dt=log(n1);
  M = pow(2,32/k);
  G<vector<double>> **gs = new G<vector<double>>*[dt];
	for(int i=0;i<dt;i++){
		gs[i]=new G<vector<double>>(w,d,k);
	}
  mArray = new int[d];
	mArray[0]=1;
	for(int i=1;i<d;i++){
		int n=(int)(((long)pow(2, 32)-5)%M);
		mArray[i]=(mArray[i-1]*n)%M;
	}
  BinaryHashFunction F;
  unordered_multimap<string, pair<int,vector<pair<double,double>>>> um;
  inputHash(false,1,n1,inputPoints,inputVector,w,d,k,M,mArray,gs,htable,F,dt,um);
  findNN(max,false,trueNN,avg,false,1,n2,queryPoints,queryVector,w,d,k,M,mArray,gs,htable,dt,F,um,probes,output);
  for(int i=0;i<dt;i++){
    delete gs[i];
	}
  delete[] mArray;
  delete[] gs;
  // initiliaze parametres hash input and search for aNN and delete dynamically allocated memory
}
