#include <iostream>
#include  <cstdlib>
#include <ctime>
#include <random>
#include <math.h>

using namespace std;
template <class T>
class G{
	private:
		int **s; //o pinakas ton s poy tha exei diastasi dxk
		int sizex,sizey;
	public:



		G(int w,int d,int k) { //construction
			sizex=d;
			sizey=k;
			int i,j;
			s = new int*[k];
			for(i=0;i<k;i++){
				s[i] = new int[d];
			}
			for(i=0;i<k;i++){
				for(j=0;j<d;j++){
					s[i][j]=generateNumber(0,w);

				}

			}
		}

		~G(){
			int i;
			for(i=1;i<sizey;i++){
				delete(s[i]);
			}
			delete(s);
		}

		int mod(int a, unsigned int b) {

    		return (a % b + b) % b;
		}
		double generateNumber(double const& down, double const& up){
				random_device rand_dev;
				mt19937 generator(rand_dev());
				uniform_real_distribution<> distr(down,up);
				return distr(generator);
		}
		int G_function(T xs,double w,int d,int k,unsigned int M,int xM[],bool flag){
			int i,j;

			double l;
			int sum=0;
			double a;
			unsigned int g=0;
			for(i=0;i<k;i++){ //gia oles tis h
				for(j=0;j<d;j++){ //gia ola ta si
					l = (xs[j]-s[i][j])/w;
					if(flag==false)a = l;
					else a=floor(l);
					sum = sum + (a)*(xM[d-1-j]);

				}
				sum = this->mod(sum,M);

				g+=sum;
				g <<=32/k;
				sum=0;
			}
			return g%1000;
		}
};
