#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

class mytable{
    protected:
        float **M;
        float *Res;

    public:
      char name[20];
      int w=4, h=3;
      float Max;

    void create(){
       //M=new int[w*h];
       M = new float *[h];
       for (int i=0; i<h; i++)
          M[i]=new float [w];
       //M=(int *)malloc(w);
    }

    void destroy(){
       for (int i=0; i<h; i++)
       delete[] M[i];
    }

    int get_element(int r, int c){
        //return M[r][c];
        return M[r][c];
    }

    void put_element(int r, int c, float m){
        M[r][c]=m;
        //M[r][c]=m;
    }

    void random_put(){
        srand(time(0));
        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++)
                M[i][j]=rand()%50;
    }

     void manual_put(){
        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++){
                printf("\nM[%d][%d]=", i,j);
                cin >> M[i][j];
            }
    }

   //protected:
   void print_mass(){
        for(int i=0; i<h; i++){
            for(int j=0; j<w; j++)
                printf("%7.1f", M[i][j]);
            cout << "\n";
        }
    }

   void calc_max(){
         Max=get_element(0,0);
         for(int i=0; i<h; i++){
            for(int j=0; j<w; j++)
                if (M[i][j]>Max)
                    Max=M[i][j];
            }
      }

   void Gauss(){

	    if((w-h)!=1) {
			cout << "\nnot have root";
			exit(1);
		};

		int i,j,k;
        float tmp;


        float **G = new float *[h];
        for (i=0; i<h; i++)
          G[i]=new float [w];


        for (i=0; i<h; i++)
            for (j=0; j<w; j++)
                G[i][j]=M[i][j];

		for(i=0; i<h-1; i++){
            for(j=i+1; j<h; j++){
               tmp=G[j][i]/G[i][i];
               for(k=i; k<w; k++){
                    G[j][k]-=G[i][k]*tmp;
					if (fabs(G[j][k])<0.00001) fabs(G[j][k]=0;
               }
            }
        }

		int flag=1;
		cout << "\n\nGauss array: \n\n";
        for(i=0; i<h; i++){
			if(G[i][i] == 0 || fabs(G[i][i]) < 0.000001){
                flag = 0;
            }
            for(j=0; j<w; j++)
                printf("%7.1f", G[i][j]);

            cout << "\n";
        }

		if (!flag) {
                         cout << "Macierz osobliwa. Nie mozna ta metoda rozwiazac tego ukladu!";
                         exit(1);
		}

		Res = new float [h];

        for(i=h-1; i>=0; i--){
            tmp=G[i][w-1];
            for(j=i+1; j<w-1; j++){
                tmp-=G[i][j]*Res[j];
            }
            Res[i]=tmp/G[i][i];
        }

        cout << "\n\nResult: \n";
        for(i=0; i<h; i++)
                printf("\nx%d=%8.3f", i+1, Res[i]);
        cout << "\n";

       for (int i=0; i<h; i++)
       delete[] G[i];
   }

};

int main()
{
    mytable MT;
    //MT.w=10;
    //MT.h=9;
    cout << "\nw=";
    cin >> MT.w;

    cout << "\nh=";
    cin >> MT.h;

    MT.create();
    //MT.random_put();
    MT.manual_put();
    MT.print_mass();
    MT.Gauss();
    //MT3.calc_max();
    //cout<< "\n Max=" << MT.Max;

    return 0;
}

