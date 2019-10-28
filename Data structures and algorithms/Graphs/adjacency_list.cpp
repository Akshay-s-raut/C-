#include<iostream>
#include <vector>
#include <string>
using namespace std;

struct Node{
    string key;
    vector<string>* conected;
    int number_of_connected_node=0;
};

class Adjacency_list{
    private:
        Node* elem;
        int size=0;
        int space=1;

        void reserve(int new_alloc){
            if(new_alloc<space){
                return;
            }
            else{
                Node* p = new Node[space*2];
                copy(elem,elem+size,p);
                delete[] elem;
                elem = p;
                space = new_alloc;
            }
        }
        void resize(int newsize){
            reserve(newsize);
            size = newsize;
        }

    public:
        void insert(string n1,string n2){
            resize(size);
            for(int i=0;i<size;++i){
                if(elem[i].key==n1){
                    for(int j=0;j<elem[i].number_of_connected_node;++j){
                        

                    }
                }
            }
        }



};