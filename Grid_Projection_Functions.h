#include <iostream>
#include  <cstdlib>
#include "HashFunctionG.h"
#include "HashTable.h"
#include "CubeHash.h"
#include <ctime>
#include <math.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <new>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
typedef unordered_multimap<string, pair<int,vector<pair<double,double>> >> ::iterator umit;
pair<int,double> store_data(bool,vector<pair<pair<int,int>,vector<vector<pair<int,int>> >>> &,vector<vector<float>> &,int,string,int,int,double[][2],pair<int,vector<pair<double,double>>>[],void *,int,double,bool);
int read_data(bool,string,pair<int,double>[],double &,int,bool,vector<pair<pair<int,int>,vector<vector<pair<int,int>> >>> &,vector<vector<float>> &,int,string,string,int,int,int, pair<int,vector<pair<double,double>>>[],pair<int,vector<pair<double,double>>>[],void *,void *);
void inputHash(bool,int,int,pair<int,vector<pair<double,double>>>[],void *,double,int,int,int,int *,G<vector<double>> **,HashTable<pair<int,vector<pair<double,double>> >>[],BinaryHashFunction&,int,  unordered_multimap<string, pair<int,vector<pair<double,double>> >>&);
void findNN(int,bool,pair<int,double>[],double,bool,int,int,pair<int,vector<pair<double,double>>>[],void *,double,int,int,int,int *,G<vector<double>> **,HashTable<pair<int,vector<pair<double,double>> >>[],int,BinaryHashFunction&,  unordered_multimap<string, pair<int,vector<pair<double,double>> >>&,int,string);
double distance(vector<pair<double,double>>,vector<pair<double,double>>);
