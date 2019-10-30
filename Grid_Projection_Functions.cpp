#include "Grid_Projection_Functions.h"
double random(double const& down, double const& up){
			random_device rand_dev;
			mt19937 generator(rand_dev());
			uniform_real_distribution<> distr(down,up);
			return distr(generator);
}
void getTraversalsUtil(int i, int j, int m, int n,vector<pair<int,int>> current, vector<vector<pair<int,int>>> &paths, set<pair<int,int>> coords){
    current.push_back(make_pair(i,j)); // save temp path in case we need it
    if(coords.find(make_pair(i,j)) == coords.end()) return; // illegal i,j
    if(i>m || j>n) return; //moved to far away
    if (i == m && j==n)
    {
        paths.push_back(current); //reached the end save the path
        return;
    }
    //we can only move right,bottom,and bottom-right;
    getTraversalsUtil(i+1, j, m, n, current,paths, coords);
    getTraversalsUtil(i, j+1, m, n, current,paths, coords);
    getTraversalsUtil(i+1, j+1, m, n, current,paths, coords);
}
void getTraversals(vector<vector<pair<int,int>>> &paths,double m, double n){ //y=ax+b,main diagonal may pass from multiple i and j
  double m1=n/m,m2=m/n;
  set<pair<int,int>> coords;
  for(int i=1;i<=m;i++){
     double k=i*m1;
     if(k==floor(k)){
       coords.insert(make_pair(i,k));
       coords.insert(make_pair(i+1,k));
     }
     else {
       coords.insert(make_pair(i,ceil(k)));
       coords.insert(make_pair(i+1,ceil(k)));
     }
  }
 for(int j=1;j<=n;j++){
    double k=j*m2;
    if(k==floor(k)){
      coords.insert(make_pair(k,j));
      coords.insert(make_pair(k+1,j));
    }
    else {
      coords.insert(make_pair(ceil(k),j));
      coords.insert(make_pair(ceil(k)+1,j));
    }
  }
    vector<pair<int,int>> current;
    getTraversalsUtil(1, 1, m, n, current,paths,coords);//get paths for this m,n combination
}
pair<int,double> store_data(bool flag2,vector<pair<pair<int,int>,vector<vector<pair<int,int>>>>> &traversals,vector<vector<float>> &GV,int gn,string data,int L,int n,double t[][2],pair<int,vector<pair<double,double>>> dataPoints[],void *dataV,int max,double maxs,bool flag){
  string str,delimiter="(";
  size_t pos,pos2;
  int id,num,j=0;
  ifstream dataStream(data);
  vector<double> tempy[n][L],tempx[n][L];
  double x,y, delta=0.001;
  vector<double> (*dataVector)[n][L] = (  vector<double> (*)[n][L]) dataV; // 2d array of vectors
  while(getline(dataStream, str)){ // read line by line
      string str2 =str.substr(0,str.find("\t"));
      stringstream temp(str2);
      temp>>id;
      dataPoints[j].first=id;
      while ((pos = str.find(delimiter)) != string::npos){ // find "(".")","," so we can get the x,y
        str=str.substr(str.find(delimiter)+1,str.length());
        if(delimiter=="("){
          pos2=str.find(",");
          delimiter=",";
          stringstream temp(str.substr(0,pos2));
          temp>>x;
        }
        else if(delimiter==","){
          pos2=str.find(")");
          delimiter=")";
          stringstream temp(str.substr(0,pos2));
          temp>>y;
        }
        else {
          dataPoints[j].second.push_back(make_pair(x,y)); //push this point
          delimiter="(";
        }
      }
      if(flag2==true){ // grid
        for(int q=0;q<L;q++){
          double previous[2]={DBL_MAX,DBL_MAX};
          for(int i=0;i<dataPoints[j].second.size();i++) {
            double x1=round((dataPoints[j].second[i].first-t[q][0])/delta)*delta+t[q][0];
            double y1=round((dataPoints[j].second[i].second-t[q][1])/delta)*delta+t[q][1];
            if(!(previous[0]==x1 && previous[1]==y1 && i!=0)){ // consecutive x,y are removed
              tempx[j][q].push_back(x1);
              tempy[j][q].push_back(y1);
              previous[0]=x1;
              previous[1]=y1;
              if(flag==true){
                if(x1>maxs)maxs=x1;
                if(y1>maxs)maxs=y1;
              }
            }
          }
          for(int i=0;i<tempx[j][q].size();i++){
              (*dataVector)[j][q].push_back(tempy[j][q][i]);
          }
          for(int i=0;i<tempy[j][q].size();i++){
              (*dataVector)[j][q].push_back(tempy[j][q][i]);
          } // get all x,y to vector
          num=(*dataVector)[j][q].size();
          if(flag==true && max<num) max=num;
        }
      }
      else { // projection
        max=gn;
        double arr[gn];
        for(int q=0;q<L;q++){ // make vector of gn values,vector=G*(all x)
          for(int i=0;i<gn;i++) arr[i]=0.0;
          for(int k=0;k<gn;k++) {
            for(int i=0;i<traversals.size();i++){
              if(flag==true){
                if(traversals[i].first.first==dataPoints[j].second.size()){
                  for(int z=0;z<traversals[i].second.size();z++){
                    for(int l=0;l<traversals[i].second[z].size();l++){
                      arr[k]+=GV[q][k]*traversals[i].second[z][l].first;
                    }
                  }
                }
              }
              else {
                if(traversals[i].first.second==dataPoints[j].second.size()){
                  for(int z=0;z<traversals[i].second.size();z++){
                    for(int l=0;l<traversals[i].second[z].size();l++){
                      arr[k]+=GV[q][k]*traversals[i].second[z][l].second;
                    }
                  }
                }
              }
            }
            (*dataVector)[j][q].push_back(arr[k]);
          }
        }
      }
      j++;
  }
  if(flag2==true){ //padding for grid
    for(int i=0;i<j;i++){
      for(int q=0;q<L;q++){
        num= (*dataVector)[i][q].size();
        while(num++!=max){
          (*dataVector)[i][q].push_back(maxs+1);
        }
      }
    }
  }
  else {
    max=gn;
  }
  return make_pair(max,maxs);
}
void G_calc(vector<vector<float>> &GV,int L,int n){ //calculate G
  vector<float>Gx;
  for(int q=0;q<L;q++){
    for(int i=0;i<n;i++){ // uniformly canonical random numbers
        float x,y;
        do{
          x=random(-1,1);
          y=random(-1,1);
        }while( x<=0 || y<=0 || pow(x,2)+pow(y,2)>=1 || pow(x,2)+pow(y,2)==0);
        Gx.push_back(x*sqrt(-2*log(pow(x,2)+pow(y,2)/(pow(x,2)+pow(y,2)))));
    }
    GV.push_back(Gx);
    Gx.clear();
  }
}
void read_bf(string bf,pair<int,double>trueNN[],double &avg){ // read brute force data
  ifstream data(bf);
  string str,str2;
  int i=0;
  size_t pos;
  while(getline(data,str)){
    if((pos=str.find(": ")) != std::string::npos){
      str2=str.substr(pos+2,str.length());
      str2=str2.substr(0,str2.find(" "));
      stringstream temp(str2);
      temp>>avg;
    }
    else{
      int k;
      double d;
      str=str.substr(str.find("\t")+1,str.length());
      str2=str.substr(0,str.length());
      stringstream temp(str2);
      temp>>d;
      str=str.substr(str.find("\t")+1,str.length());
      str2=str.substr(0,str.length());
      stringstream temp2(str2);
      temp2>>k;
      trueNN[i]=make_pair(k,d);
    }
    i++;
  }
}
int read_data(bool flag2,string bf,pair<int,double>trueNN[],double &avg,int m,bool flag,vector<pair<pair<int,int>,vector<vector<pair<int,int>>>>> &traversals,vector<vector<float>> &GV,int gn,string input,string query,int L,int n1,int n2, pair<int,vector<pair<double,double>>> inputPoints[],pair<int,vector<pair<double,double>>> queryPoints[],void *inputVector,void *queryVector){
  size_t pos;
  string str;
  double t[L][2];
  if(flag2==true){
    read_bf(bf,trueNN,avg);
  }
  if(flag==true){
    for(int q=0;q<L;q++) { //initialize t
          t[q][0]=random(0,2);
          t[q][1]=random(0,2);
    }
  }
  else {
    vector<vector<pair<int,int>>> paths;
    for(int i=1;i<=m;i++){
      for(int j=1;j<=m;j++){
        if(j>i-4 && j<i+4) {
          getTraversals(paths,i,j);
          traversals.push_back(make_pair(make_pair(i,j),paths));
        }
        paths.clear();
      }
    }
    G_calc(GV,L,gn);
    //initialize traversals and G
  }
  pair<int,double> p=store_data(flag,traversals,GV,gn,input,L,n1,t,inputPoints,inputVector,0,0.0,true);
  store_data(flag,traversals,GV,gn,query,L,n2,t,queryPoints,queryVector,p.first,p.second,false);
  // find vectors for query and input
  return p.first;
}
void inputHash(bool flag,int L,int n,pair<int,vector<pair<double,double>>> inputPoints[],void *inputV,double w,int d,int k,int M,int *mArray,G<vector<double>> **gs,HashTable<pair<int,vector<pair<double,double>>>> htable[],BinaryHashFunction &F,int dt,unordered_multimap<string, pair<int,vector<pair<double,double>>>>&um){
  vector<double> (*inputVector)[n][L] = (  vector<double> (*)[n][L]) inputV;
  string strings;
  int j;
  for(int i=0;i<n;i++){
    pair<int,vector<pair<double,double>>> v;
    v=inputPoints[i];
    if(flag==true){ // lsh
      for(int q=0;q<L;q++){
    		int h = gs[q]->G_function((*inputVector)[i][q],w,d,k,M,mArray,false);
        htable[q].put(h,v,v.first); //hash and put
    	}
    }
    else { //cube
      strings.clear();
      for(j=0;j<dt;j++){
  			int h = gs[j]->G_function((*inputVector)[i][0],w,d,k,M,mArray,false); //We take the Gj value
        h = F.F(h); //We take the binary value
  			//We are going to add it on the binary string
  			if(h==0){
  				strings.append("0");
  			}
  			else{
  				strings.append("1");
  			}
        um.insert(make_pair(strings, v));
  		}
    }
  }
}
double distance(vector<pair<double,double>>  v,vector<pair<double,double>>  f){ // simple DTW with eucledian distance
  int si=v.size();
  int sj=f.size();
  double c[si][sj];
  int i,j;
  for(i=0;i<si;i++) {
    for(j=0;j<sj;j++) {
      if(j==i && i==0)
        c[i][j]=sqrt(pow((v[i].first-f[j].first),2)+pow((v[i].second-f[j].second),2));
      else if(j==0)
        c[i][j]=c[i-1][j]+sqrt(pow((v[i].first-f[j].first),2)+pow((v[i].second-f[j].second),2));
      else if (i==0)
        c[i][j]=c[i][j-1]+sqrt(pow((v[i].first-f[j].first),2)+pow((v[i].second-f[j].second),2));
      else
        c[i][j]=fmin(fmin(c[i-1][j],c[i][j-1]),c[i-1][j-1])+sqrt(pow((v[i].first-f[j].first),2)+pow((v[i].second-f[j].second),2));
    }
  }
  return c[si-1][sj-1];
}
void findNN(int max,bool flag2,pair<int,double> trueNN[],double avg,bool flag,int L,int n,pair<int,vector<pair<double,double>>> queryPoints[],void *queryV,double w,int d,int k,int M,int *mArray,G<vector<double>> **gs,HashTable<pair<int,vector<pair<double,double>>>> htable[],int dt,BinaryHashFunction &F,unordered_multimap<string, pair<int,vector<pair<double,double>>>> &um,int forbes,string output){
  HashNode<pair<int,vector<pair<double,double>>>> *p;
  int j;
  double r=0.0;
  string strings,rep1 = "1",rep0 = "0",assist_string;
  int id;
  vector<double> (*queryP)[n][L] = (  vector<double> (*)[n][L]) queryV;
  vector<double> queryVector[n][L]=*queryP;
  ofstream myfile;
  myfile.open(output);
  clock_t begin = clock();
  for(int i=0;i<n;i++){
    strings.clear();
    double dist=DBL_MAX; //Tha elegxoume gia kathe simeio tou bucket
    int count=0;
    vector<pair<double,double>> v;
    int minID=-1;
    v=queryPoints[i].second;
    id=queryPoints[i].first;
    if(flag==true){
      for(int q=0;q<L;q++){
  			int h = gs[q]->G_function(queryVector[i][q],w,d,k,M,mArray,false); // hash query
        p=htable[q].getBucket(h); // for every bucket
        while(p != NULL && count<50*L){ //threshold
    			vector<pair<double,double>> f = p->getValue().second; // get its points
          double d=distance(v,f); // find dtw distance
          if(dist >d){
            dist =d;
            minID=p->getValue().first;
          }
    			p = p->getNext();
          count++;
    		}
      }
		}
    else {
      for(j=0;j<dt;j++){
        int h = gs[j]->G_function(queryVector[i][0],w,d,k,M,mArray,false); //We take the Gj value
        h = F.F(h);
        if(h==0){
          strings.append("0");
        }
        else{
            strings.append("1");
        }
      }
      int internal_counter = 0;
      int external_counter = 0;
      assist_string = strings;
      int temp=max;
      while(--temp>0 && internal_counter < 6 && external_counter < 500){ //threshold
  			umit it = um.begin();
  			if(internal_counter == 0){
  				assist_string = strings;
  				//Nothing, we use binary string as it is.
  			}
  			else{ //We have already checked the main one.
  				if(strings[forbes-internal_counter] == '0'){
  					assist_string = strings;
  					assist_string.replace(forbes-internal_counter,1,rep0);
  				}
  				else{
  					assist_string = strings;
  					assist_string.replace(forbes-internal_counter,1,rep1);
  				}
  			}
  			auto p = um.equal_range(assist_string);
  			for (auto it = p.first; it != p.second; ++it){
        	external_counter++;
          vector<pair<double,double>>f=it->second.second;
          double d=distance(v,f); // find dtw distance
          if(d < dist){
      			dist = d;
            minID=it->second.first;
      		}
        }
        assist_string.clear();
        internal_counter++;
      }
    }
    string hash=flag==true?"LSH":"Hypercube";
    string method=flag2==true?"Grid":"Projection";
    myfile << "Query : curve"<<id<<endl;
    myfile<<"Method : "<<method<<endl;
    myfile<<"HashFunction : "<<hash<<endl;
    if(minID==-1)myfile<<"Found Nearest neighbor : NotFound"<<endl;
    else myfile<<"Found Nearest neighbor : curve"<<minID<<endl;
    myfile<<"True Nearest neighbor : curve"<<trueNN[i].first<<endl;
    if(minID==-1)myfile<<"distanceFound : NotFound"<<endl;
    else myfile<<"distanceFound : "<<dist<<endl;
    myfile<<"distanceTrue : "<<trueNN[i].second<<endl;
    myfile<<"-----------------------------------------"<<endl;
    if(trueNN[i].second!=0.0 && minID!=-1){
      if(r<dist/trueNN[i].second)r=dist/trueNN[i].second;
    }
	}
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  myfile<<"Average time : "<<elapsed_secs/n<<" seconds per query"<<endl;
  myfile<<"Brute force average time : "<<avg<<" seconds per query"<<endl;
  myfile<<"MaxAf : "<<r<<endl;
  queryP=&queryVector;
  queryV=&queryP;
  myfile.close();
}
