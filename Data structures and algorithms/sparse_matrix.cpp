#include <iostream>
using namespace std;

class SparseMatrix{
    private:
        int m[10][3];
        int rows,cols;
        int nonzero=0;
    public:
        SparseMatrix(int r,int c)
            :rows{r},cols{c}{
                m[0][0]=rows;
                m[0][1]=cols;
                m[0][2]=0;
            }
        
        SparseMatrix(int r, int c, int a[3][3] ) { 
            rows = r;
            cols = c;
            for(int i=0;i<r;++i){
                for(int j=0;j<c;++j){
                    if(a[i][j]!=0){
                        m[nonzero+1][0]=i;
                        m[nonzero+1][1]=j;
                        m[nonzero+1][2]=a[i][j];
                        ++nonzero;
                    }
                }
            }
            m[0][0]=rows;
            m[0][1]=cols;
            m[0][2]=nonzero;   
        }

        void insert(int rn,int cn, int val){
            if(rn>m[0][0]){
                m[0][0]=rn;
            }
            if(cn>m[0][1]){
                m[0][1]=rn;
            }
            m[nonzero+1][0]=rn;
            m[nonzero+1][1]=cn;
            m[nonzero+1][2]=val;
            ++nonzero;
        }

        friend ostream& operator<<(ostream& os,SparseMatrix sm){
            for(int i=0; i<sm.m[0][0] + 1 ; ++i){
                    os<<sm.m[i][0]<<"\t"<<sm.m[i][1]<<"\t"<<sm.m[i][2]<<"\n";
            }
            return os;
        }

};

int main(){
    int a[][3] = { {1,0,0},{0,1,0},{0,0,1} };
    
    SparseMatrix sm(3,3,a);
    cout<<sm;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            cout<<a[i][j];
                    
        }
    }



}