#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <queue>
#include <iomanip>
using namespace std;

struct Node{
    Node* left;
    Node* right;
    int value;
    //int position;
};

class BST{
    private:
        Node root;
        int size=0;
        int* elem;
        int space=1;
        vector<string> for_heap;

        void insert(int n,Node* node){
            Node* g = new Node{nullptr,nullptr,n};
            if(g->value<node->value){
                if(node->right!=nullptr){
                    insert(n,node->right);
                }
                else{
                    node->right = g;
                    //g->position = 2*(node->position)+1;
                }
            }
            else if(g->value>node->value){
                if(node->left!=nullptr){
                    insert(n,node->left);
                }
                else{
                    node->left = g;
                    //g->position = 2*(node->position);
                }
            }
        }

        bool find_in(int x,const Node g){
            if(x==g.value){
                return 1;
            }
            else if(x<g.value){
                if(g.right!=nullptr){
                    return find_in(x,(*g.right));
                }
                else{
                    return 0;
                }
            }
            else{
                if(g.left!=nullptr){
                    return find_in(x,(*g.left));
                }
                else{
                    return 0;
                }
            }
        }

        void delete_elem_(int x,Node* g){
            if(x<g->value){
                if(x==g->right->value){
                    g->right=nullptr;
                    return;
                }
                else{delete_elem_(x,g->right);}
            }
            else{
                if(x==g->left->value){
                    g->left=nullptr;
                    return;
                }
                else{delete_elem_(x,g->left);}
            }
        }

        int depth(Node* n){
            if(n==nullptr){
                return -1;
            }
            else{
                return 1 + max(depth(n->left),depth(n->right));
            }
        }
        
        int get_root_depth(){
            return depth(&root);
        }
    

    void make_heap(Node n){
        queue<Node*> q;
        q.push(&n);
        while(!q.empty() && for_heap.size()<pow(2,this->get_root_depth()+1)-1){
            auto x = q.front();
            if(x==nullptr){
                for_heap.push_back(" ");
                q.pop();
                q.push(nullptr);
                q.push(nullptr);

            }
            else{
                for_heap.push_back(convert_to_string((*x).value));
                q.pop();
                q.push(x->right);
                q.push(x->left);
            }
          
        }
    }

    string convert_to_string(int i){
        stringstream ss;
        ss<<i;
        string s;
        ss>>s;
        return s;
    }

    int formating(){
        int max=0;
        for(auto i:for_heap){
            if(i.size()>max){
                max=i.size();
            }
        }
        return max;
    }

    /*int find_pos(int x,const Node g){
            if(x==g.value){
                return g.position;
            }
            else if(x<g.value){
                if(g.right!=nullptr){
                    return find_in(x,(*g.right));
                }
                else{
                    return 0;
                }
            }
            else{
                if(g.left!=nullptr){
                    return find_in(x,(*g.left));
                }
                else{
                    return 0;
                }
            }
        }*/

    public:
        BST(int n)
            :size{1}
        {
            root.left=nullptr;
            root.right=nullptr;
            root.value=n;
        }
        /*BST(initializer_list<int> lst)
            :size{(int) lst.size()}{
                for(auto x:lst){
                    this->insert(x);
                }
            }*/
        void insert(int n){
            insert(n,&root);
            ++size;
        }

        friend ostream& operator<<(ostream&os,BST b){
            b.make_heap(b.root);
            int width_of_word=b.formating();
            int height = ceil(log2(b.for_heap.size()+1));
            int last_level = pow(2,height-1);
            int k = (int) (2*last_level-1)/2;
            int tstart=0;
            int tend=1;
            int c = 0;
            int l = 2;
            while(c<b.for_heap.size()){
                for(int i=0;i<k;i++){
                    os<<setw(width_of_word)<<" ";
                }
                for(int i=tstart;i<tend;i++){
                    if(i<b.for_heap.size()){
                        os<<setw(width_of_word)<<b.for_heap[i];
                    }
                    for(int j=0;j<2*k+1;j++){
                        os<<setw(width_of_word)<<" ";
                    }
                    ++c;
                }
                tstart = tend;
                tend = pow(2,l)-1;
                last_level = last_level/2;
                k = (int) (2*last_level-1)/2;
                ++l;
                os<<'\n';
            }
            os<<"\n";
            vector<int> for_heap;
            return os;
        }

        bool find_in(int x){
            return find_in(x,root);
        }

        void print_for_heap(){
            make_heap(root);
            for(int i=0;i<for_heap.size();i++){
                cout<<for_heap[i]<<" ";
            }
        }
        void delete_elem(int x){
            if(x==root.value){
                delete[] elem;
            }            
            else{
                delete_elem_(x,&root);
            }

        }

        int get_pos(int node){
            this->make_heap(root);
            for(int i=0;i<for_heap.size();++i){
                if(convert_to_string(node) == for_heap[i]){
                    return i;
                }
            }
            return 0;
        }

};

int main(){
    BST b{2};
    b.insert(0);
    b.insert(1);
    b.insert(2);
    b.insert(4);
    b.insert(3);
    b.insert(5);
    b.insert(-1);
    cout<<b;
    b.delete_elem(4);
    cout<<b;
    cout<<b.get_pos(3);
}
//u dont need resize and stuff becuase they are just pointers!
/*void reserve(int new_alloc){
            if(new_alloc<space){
                return;
            }
            else{
                int *p = new int[new_alloc*2];
                copy(elem,elem+size,p);
                delete[] elem;
                elem = p;
                space = 2*new_alloc; 
            }
        }
        void resize(int newsize){
            reserve(newsize);
            for(int i=size;i<newsize;i++){
                elem[i]=0;
            }
            size=newsize;
        }*/