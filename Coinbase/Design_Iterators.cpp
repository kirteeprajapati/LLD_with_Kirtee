// Iterator Pattern (Gang of Four)

// Aggregate → vector<int> (or any collection)
// Iterator → our class Iterator with next() and hasNext()


// Executive Design Strategy
// North Star
// Single, consistent interface
// Composition over inheritance
// Lazy evaluation
// O(1) extra space where possible
// STL-friendly
// Open for extension, closed for modification


// We’ll lean on:
// Iterator Pattern (core)
// Decorator Pattern (filtering, cyclic)
// Adapter Pattern (wrapping containers)
// Strategy Pattern (zigzag traversal logic)

// #include <vector>
// #include <stdexcept>            // runtime_error, invalid_argument, out_of_range

// Templates allow us to express behavioral polymorphism without sacrificing type safety.

// Allows IITerator<int>, IITerator<string>, IITerator<MyClass>
// Prevents code duplication,  Keeps strong compile-time type safety

template<typename T> // this makes iterator generic over element type 
class IITerator2{            // Pure abstract based class iow: c++ interface
    // Name starts with I: Signal convention: pure defination no data

    public:
        // Virtual Enables runtime polymorphism. 
        // any one however they want can customise it
        virtual bool hasNext() const = 0;
        virtual T next() = 0;
        
    // Any polymorphic base class must have a virtual destructor.
    // Compiler generates optimal distructor
        virtual ~IITerator() = default;
};

// Basic Iterator using the defination above Plug - n - play
#include <vector>
#include <stdexcept>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

// we'll make it general in terms of type so defining with a template literal
template <typename T>

class IIterator{
    // this is pure abstract based c++ interface no data
    public:
        
        virtual bool hasNext() const=0;
        virtual T next()=0;
        // virtual distuctor
        virtual ~IIterator() = default; // letting compiler handel it with the default behaviour  
    
};

template <typename T>
class VectorIterator : public IIterator<T>{
    // we are extending VectorIterator with the c
    
    private:
        vector<T> data;      // Here the data is asking for reference
    // Iterator does NOT own data
        size_t index = 0;
    
    public: 
    
        // Constructor
        explicit VectorIterator(vector<T> vec) : data(std::move(vec)){}
    // Iterator DOES own data
    
        T next() override{
            if(!hasNext()) throw out_of_range("No more elements to access");
            return data[index++];
        }
        
        bool hasNext() const override{
            return index<data.size();
        }
};

template <typename T>
class ZigZagIterator: public IIterator<T>{
    private:
        vector<vector<T>> data;
        queue<pair<int, int>> q;                 // this will store the Index so explicitely mentioning that
    
    public:
        ZigZagIterator(vector<vector<T>> vec): data(std::move(vec)) {
            for(int i=0; i<data.size(); i++){
                if(!data[i].empty()){
                    q.push({i, 0});
                }
            }
        }
    
        T next() override{
            if(!hasNext()){
               throw out_of_range("No more elements in ZigZagIterator to visit");
            }
            auto [row, col] = q.front();
            q.pop();
            
            T val= data[row][col];
            
            if(col+1<data[row].size()) q.push({row, col+1});
            
            return val;
        }
    
    bool hasNext() const override{
        return !q.empty();
    }
};


int main(){
    
    /*--------------------------------------------------
     PART 1 — Vector Traversal of a 2D List
    --------------------------------------------------*/
    VectorIterator<int> vecIT({1, 3, 54});
    while(vecIT.hasNext()){
        cout<<"Next element in the vector is: "<< vecIT.next()<< endl;
    }
    cout<<"You likely consumed everything"<<endl;
    
    
    /*--------------------------------------------------
     PART 2 — Zigzag Traversal of a 2D List
    --------------------------------------------------*/
    {
        ZigZagIterator<string> zzIT({
        {"sdasf", "two"}, \
        {"kirtee"}, 
        {"fa", "dsafa", "dfasfaga", "fdafaga"}});
    
        while(zzIT.hasNext()){
            cout<<zzIT.next()<<endl;
        }
        cout<<"Taversal finnished and seems like queue got empty for string data type"<<endl;
    }
    
    {
        std::vector<vector<int>> numsMatrix={{1, 3, 54}, {3}, {}, {343, 5}};
        ZigZagIterator<int> zizzagIntIterator(numsMatrix);
        while(zizzagIntIterator.hasNext()){
        cout<<zizzagIntIterator.next()<<endl;
    }
    cout<<"Taversal finnished and seems like queue got empty for int data type"<<endl;
    
    }
    
}