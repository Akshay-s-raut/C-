#include <iostream>
#include <cmath>
using namespace std;
template <typename T>
class heap{
    private:
        int size = 0;
        int space=1;
        T *elem;

        void reserve(int new_alloc){
            if(new_alloc<space){
                return;
            }
            else{
                int *p = new T[new_alloc*2];
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
        }

        void max_heapify(int i){
            /*if(2*i+1>size){
                return;
            if(elem[i]>elem[(int)(i-1)/2]){
                int temp=elem[i];
                elem[i] = elem[(int)(i-1)/2];
                elem[(int)(i-1)/2] = temp;
                this->max_heapify(2*i+1);
            }*/
            if(2*i+1>size-1){
                return;
            }
            else if (2*i+2>size-1 && 2*i<=size-1){
                if(elem[i]<elem[2*i+1]){
                    int temp = elem[i];
                    elem[i] = elem[2*i+1];
                    elem[2*i+1] = temp;
                    this->max_heapify(2*i+1); 
                }
            }
            else{
                if(elem[i]<elem[2*i+1] || elem[i]<elem[2*i+2]){
                    if(elem[2*i+1]>elem[2*i+2]){
                        int temp = elem[i];
                        elem[i] = elem[2*i+1];
                        elem[2*i+1] = temp;
                        this->max_heapify(2*i+1);
                    }
                    else{
                        int temp = elem[i];
                        elem[i] = elem[2*i+2];
                        elem[2*i+2] = temp;
                        this->max_heapify(2*i+2);
                    }
                }
            }
        }

        void min_heapify(int i){
            if(2*i+1>size){
                return;
            }
            else if (2*i+2>size){
                if(elem[i]>elem[2*i+1]){
                    int temp = elem[i];
                    elem[i] = elem[2*i+1];
                    elem[2*i+1] = temp;
                    this->max_heapify(2*i+1); 
                }
            }
            else{
                if(elem[i]>elem[2*i+1] || elem[i]>elem[2*i+2]){
                    if(elem[2*i+1]<elem[2*i+2]){
                        int temp = elem[i];
                        elem[i] = elem[2*i+1];
                        elem[2*i+1] = temp;
                        this->max_heapify(2*i+1);
                    }
                    else{
                        int temp = elem[i];
                        elem[i] = elem[2*i+2];
                        elem[2*i+2] = temp;
                        this->max_heapify(2*i+2);
                    }
                }
            }

        }

    public:
        heap()
            :size{0},elem{nullptr}{}
        heap(int sz)
            :size{sz},elem{new T[sz]}{}
        heap(const heap& h)
            :size{h.size},elem{new T[size]}
            {
                copy(h.elem,h.elem+h.size,elem);
            }
        heap(const initializer_list<int> & lst)
            :size{(int) lst.size()},elem{new T[size]}
            {
                copy(lst.begin(),lst.end(),elem);
            }
        heap &operator=(const heap& h){
            int *p = new T[h.size];
            copy(h.elem,h.elem+h.size,p);
            delete[] elem;
            elem = p;
            size = h.size;
            return *this;
        }
        heap &operator=(heap&& h){
            delete[] elem;
            elem = h.elem;
            size = h.size;
            h.elem=nullptr;
            h.size=0;
            return *this;
        }

        void push_back(int i) {
            reserve(size);
            elem[size]=i;
            ++size;
        }

        friend ostream& operator<<(ostream& os,const heap h){
            os<<"Heap\n";
            int height = ceil(log2(h.size+1));
            int last_level = pow(2,height-1);
            int k = (int) (2*last_level-1)/2;
            int tstart=0;
            int tend=1;
            int c = 0;
            int l = 2;
            while(c<h.size){
                for(int i=0;i<k;i++){
                    os<<" ";
                }
                for(int i=tstart;i<tend;i++){
                    if(i<h.size){
                        os<<h.elem[i];
                    }
                    for(int j=0;j<2*k+1;j++){
                        os<<" ";
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
            return os;
        }

        void max_heap(){
            for(int i=size;i>-1;i--){
                max_heapify(i);
            }
        }

        void min_heap(){
            for(int i=size;i>-1;i--){
                min_heapify(i);
            }
        }

};

int main(){
    heap<int> h {1,2,3,4,5,6,7};
    cout<<h;
    h.max_heap();
    cout<<h;
}
