#include <iostream>
using namespace std;

class Queue{
    private:
        int size=0;
        int space=1;
        int* elem;
        int* first;

    void reserve(int new_alloc){
        if(new_alloc<space){
                return;
            }
            else{
                int* p = new int[space*2];
                copy(elem,elem+size,p);
                delete[] elem;
                elem = p;
                space = new_alloc;
            }
    }
    void resize(int newsize){
            reserve(newsize);
            for(int i=size;i<newsize;i++){
                elem[i]=0;
            }
            size = newsize;
        }

    public:
        Queue()
            :size{0},elem{nullptr}{}
        Queue(int s)
            :size{s},elem{nullptr}{}
        Queue(Queue& q)
            :size{q.size},elem{new int[size]},first{elem}
            {
                copy(q.elem,q.elem+size,elem);
            }
        Queue(initializer_list<int> lst)
            :size{(int) lst.size()},elem{new int[size]}
            {
                copy(lst.begin(),lst.end(),elem);
            }
        
        void push_back(int n){
            resize(size);
            elem[size]=n;
            ++size;
        }

        int pop(){
            int temp = *first;
            ++first;
            return temp;

        }

        friend ostream& operator<<(ostream& os,Queue q){
            for(int* i = q.first;i<q.first + q.size;++i){
                os<<*i<<" ";
            }
            return os;
        }

};

int main(){
    Queue q {1,2};
    cout<<q<<endl;
    q.pop();
    cout<<q.pop()<<endl;
    /*q.push_back(2);
    q.push_back(3);
    cout<<q;*/
}