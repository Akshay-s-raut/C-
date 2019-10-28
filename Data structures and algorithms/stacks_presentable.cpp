#include <iostream>
using namespace std;

template<typename T>  
class Stack{
    private:
        int size=0;
        int space=1;
        T* elem;
        void reserve(int new_alloc);
        void resize(int newsize);
    public:
        Stack()                          
            :size{0},elem{nullptr}{}
        Stack(int s)                     
            :size{s},elem{new T[size]},space{s}{}   
        Stack(const Stack& s)            
            :size{s.size},elem{new T[s.size]},space{s.size}
            {
                copy(s.elem,s.elem+size,elem);
            }
        Stack(initializer_list<T> lst)   
            :size{(int) lst.size()},elem{new T[size]}
            {
                copy(lst.begin(),lst.end(),elem);
            }
        
        void push_back(T element){
            resize(size);
            elem[size]=element;
            ++size;
        }

        T pop(){
            T temp = elem[size-1];       
            --size;                      
            return temp;     
        }

        Stack &operator=(const Stack& s);
        Stack &operator=(Stack && s);
        friend ostream& operator<<(ostream& os,Stack s);

};
template<typename T>
void Stack<T>::reserve(int new_alloc){       //increase the size of Stack;
    if(new_alloc<space){
        return;
    }
    else{
        T* p = new T[space*2];
        copy(elem,elem+size,p);
        delete[] elem;
        elem = p;
        space = new_alloc;
        }
}
template<typename T>
void Stack<T>::resize(int newsize){
    reserve(newsize);
    for(int i=size;i<newsize;i++){
        elem[i]=0;
    }
    size = newsize;
}
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& s){
    T* p = new T[s.size];
    copy(s.elem,s.elem+s.size,p);
    delete[] elem;
    elem = p;
    size = s.size;
    return *this;
}
template<typename T>
Stack<T>& Stack<T>::operator=(Stack && s){
    delete[] elem;
    elem = s.elem;
    size = s.size;
    s.elem = nullptr;
    s.size=0;
    return *this;
}
template<typename T>
ostream& Stack<T>::operator<<(ostream& os, Stack<T> s){
    for(int i =s.size-1;i>=0;--i){
        os<<s.elem[i]<<" ";
    }
    return os;
}



int main(){
    Stack <int> s {1,2,3,4,5,6};
    Stack<int> s2 = s;
    cout<<s2<<endl;
    s2.push_back(2);
    cout<<s2<<endl;
    s2.pop();
    Stack<string> s3 {"Akshay","Batman","Spider-man"};
    cout<<s3<<endl;
    s3.pop();
    cout<<s3;
}