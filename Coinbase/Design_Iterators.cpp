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

#include <vector>
#include <stdexcept>            // runtime_error, invalid_argument, out_of_range

// Templates allow us to express behavioral polymorphism without sacrificing type safety.

// Allows IITerator<int>, IITerator<string>, IITerator<MyClass>
// Prevents code duplication,  Keeps strong compile-time type safety

template<typename T> // this makes iterator generic over element type 
class IITerator{            // Pure abstract based class iow: c++ interface
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
template <typename T>
class VectorIterator : public IITerator<T>{
    private:
        const vector<T> &data;
        size_t index = 0;           // already marked as 0
    
    public: 
        explicit VectorIterator(const vector<T> &vec) : data(vec){}
    
        bool hasNext() const override{
            return index<data.size();
        }
        
        T next() override{
            if(!hasNext()) throw out_of_range("No more elements");
            return data[index++];
        }
};

int main(){
    vector<int> nums = {1, 3, 54, 63, 6373, 23};
    VectorIterator<int> IT(nums);
    
    while(IT.hasNext()){
        cout<<"Items in nums "<<IT.next()<<endl;
    }
    cout<<"No more elements to print"<<endl;
}