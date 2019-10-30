#include "arguments.h"
#include "Grid_Projection_Functions.h"
int main(int argc,char *argv[]){

  double w=65.0,e;
  int k=1,L=1,M,n1=0,n2=0,max,size,probes;
  string input,query,output,str,bf;
  arguments(input,query,output,bf,k,L,e,max,size,probes,argc,argv);
  ifstream inputData(input);
  while(getline(inputData, str)){
      n1++;
  }
  ifstream queryData(query);
  while(getline(queryData, str)){
      n2++;
  }

  pair<int,vector<pair<double,double>>> inputPoints[n1],queryPoints[n1];
  vector<double> queryVector[n2][L],inputVector[n1][L];
  vector<vector<float>> GV;
  pair<int,double> trueNN[n2];
  vector<pair<pair<int,int>,vector<vector<pair<int,int>>>>> traversals;
  double avg=0.0;
  int d=read_data(false,bf,trueNN,avg,0,true,traversals,GV,0,input,query,1,n1,n2,inputPoints,queryPoints,inputVector,queryVector);
  ofstream myfile;
  myfile.open(output);
  clock_t begin = clock();
  double r=0.0;
  for(int i=0;i<n2;i++){
    double dist=DBL_MAX;
    int minj=i;
    for(int j=0;j<n1;j++){
      double d=distance(inputPoints[j].second,queryPoints[i].second);
      if(d<dist){
        dist=d;
        minj=j;
      }
    }
    myfile<<queryPoints[i].first<<"\t"<<dist<<"\t"<<inputPoints[minj].first<<endl;
    r+=dist;
  }
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  myfile<<"Average time : "<<elapsed_secs/n2<<" seconds per query"<<endl;
  myfile.close();
}
