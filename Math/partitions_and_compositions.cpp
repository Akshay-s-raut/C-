#include <iostream>
#include <map>
#define BigInt unsigned long long int 
using namespace std;

map<int,BigInt> dict;
BigInt NumberOfCompositions(int n){
    BigInt sum=0;
    if(n==0){
        return 1;
    }
    else if(n<0){
        return 0;
    }
    else if(dict.find(n) != dict.end()){
        return dict[n];
    }
    else{
        for(BigInt i=1;i<n+1;++i){
            sum = sum + NumberOfCompositions(n-i);
        }
        dict[n] = sum;
        return sum;
    }
}

BigInt NumberOfPartitions(int n, int max){
    BigInt sum=0;
    if(n==0){
        return 1;
    }
    else if(n<0){
        return 0;
    }
    else{
        for(BigInt i=1;i<n+1;++i){
            if(i<=max){
                sum = sum + NumberOfPartitions(n-i,i);
            }
        }
        return sum;
    }
}

int main(){
    int N;
    cout<<"Enter the value of N: ";
    cin>>N;
    cout<<NumberOfCompositions(N)<<endl;
    cout<<NumberOfPartitions(N,N+1);
}