#include <fstream>
#include <iostream>
#include <vector>
#include "simple_matrix.hpp"
using namespace std;


 template<class T>
SMatrix<T> recmul(SMatrix<T> A, SMatrix<T> B){
    SMatrix<T> C(A.size());
    if(A.size()==1){
        C(0,0) = A(0,0) * B(0,0);
    }else{
        
        const int H = A.size()/2;

        
        
        SMatrix<T> tmp[2][2];
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                tmp[i][j].resize(H);
        
        
        for(int oi=0;oi<2;++oi){
            for(int oj=0;oj<2;++oj){
                
                SMatrix<T> tmpA[2], tmpB[2];
                for(int i=0;i<2;++i){
                    tmpA[i].resize(H);
                    tmpB[i].resize(H);
                    
                    for(int r = 0;r<H;++r)
                        for(int c = 0;c<H;++c){
                            tmpA[i](r,c) = A(H*oi+r, H*i+c);
                            tmpB[i](r,c) = B(H*i+r, H*oj+c);
                            
                        }
                }
                
                SMatrix<T> tmpC1(H), tmpC2(H), tmpC(H);
                tmpC1 = recmul(tmpA[0], tmpB[0]);
                tmpC2 = recmul(tmpA[1], tmpB[1]);
                
                for(int r = 0;r<H;++r){
                    for(int c = 0;c<H;++c){
                        tmp[oi][oj](r, c) = tmpC1(r, c) + tmpC2(r, c);
                    }
                }
                
            }
        }
        
        for(int i=0;i<2;++i){
            for(int j=0;j<2;++j){
                for(int r = 0;r<H;++r){
                    for(int c = 0;c<H;++c){
                        C(H*i+r, H*j+c) = tmp[i][j](r,c);
                    }
                }
            }
        }
    }// if ... else
    
    
        return C;
    
}

int main(int argc, char* argv[]){
    
    
    
    ifstream in(argv[1]);
    
    if(!in){
        cout<<"Cannot open  input file;"<<endl;
        return -1;
    }
    
    ofstream out(argv[2]);
    
    if(!out){
        cout<<"Cannot open  output file;"<<endl;
        return -1;
    }
int datasets; 
in>>datasets;

     
    
for(int i=0;i<datasets;i++)
{
    int N;
	in>>N;
    
    
    SMatrix<float> A(N), B(N), C(N);
        
        
	for(int j=0;j<N;j++)
	{
        for(int k=0;k<N;k++)
        {
		in>>A(j,k);
	}
    }
        for(int j=0;j<N;j++)
	   {
        for(int k=0;k<N;k++)
        {
		in>>B(j,k);
	    }
        }
    
        C = recmul(A, B);
    
        
        for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            out<<C(i,j)<<" ";
        }}
        
        out<<endl;
}
    
    return 0;
}

   
  

    

    
  
    
    
