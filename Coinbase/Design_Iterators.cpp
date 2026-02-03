// Iterator Pattern (Gang of Four)

// Aggregate → vector<int> (or any collection)
// Iterator → our class Iterator with next() and hasNext()

#include <vector>           // std::vector
#include <stdexcept>        // runtime_error, invalid_argument

class Iterator{
    private:
        vector<int> data;   // Encapculated Collection
        size_t index;        // Current Position
    
    public: 
        // Constructor
        Iterator(const vector<int> &data) : data(data), index(0){}
    
        bool hasNext() const{
            return  index<data.size();
        }
    
        int next(){
            if(!hasNext()){
                throw out_of_range("No more element");
            }
            return data[index++];
        }
};

int main(){
    vector<int> nums = {1, 2, 4, 5};
    Iterator it(nums);
    while(it.hasNext()){
        cout<<"Next element in the secquence is: "<<it.next()<<endl;
    }
    cout<<"No more elements";
}
