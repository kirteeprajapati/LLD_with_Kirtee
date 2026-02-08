template <typename T>
class Iterator{
    public:
        virtual bool hasNext()=0;
        virtual T next()=0;
        virtual ~Iterator()=default;
};

class ListIterator:public Iterator<int>{
private:    
    vector<int> data;
    int index = 0;
    
public:
    ListIterator(const vector<int> &list) : data(list) {}
    
    bool hasNext() override{
        return index<data.size();
    }
    
    int next() override{
        if(!hasNext()) throw runtime_error("No more elements");
        return data[index++];
    }
};

class RangeIterator : public Iterator<int>{
private:
    int current;
    int end;
    int step;
    
public:
    RangeIterator(int start, int end, int step) 
        : current(start), end(end), step(step){
            if(step==0) throw invalid_argument("Step cannot be zero");
        }
    
        bool hasNext() override{
            // A range iterator can move in two directions:
            // Forward: step > 0
            // Backward: step < 0
            return step>0 ? current<=end : current>=end;
        }
        
        int next() override{
            if(!hasNext()) throw runtime_error("No more elements");
            int val = current;
            current+=step;
            return val;         // i return current element and moved the iterator to the next step
        }
};

class ZigZagIterator : public Iterator<int>{
private:
    queue<Iterator*> q;
public:
    ZigZagIterator(const vector<vector<int>>&Lists){
        for(const auto& list : Lists){
            if(!list.empty()){
                q.push(new ListIterator(list));
            }
        }
    }
    
    bool hasNext() override{
        return !q.empty();
    }
    
    int next() override{
        if(!hasNext()) throw runtime_error("No Next element");
        
        Iterator* it = q.front();
        q.pop();
        
        int val = it->next();
        if(it->hasNext()){
            q.push(it);
        }
        return val;
    }
};

// This solves:
// List + Range
// Range + Range
// Nested zigzags
// Future iterators not yet invented

class RoundRobinIterator : public Iterator<int>{
private:
    queue<Iterator*> q;
public:
    RoundRobinIterator(const vector<Iterator*> &iterators){
        for(auto it:iterators) if(it->hasNext()) q.push(it);
    }
    
    bool hasNext() override{
        return !q.empty();
    }
    
    int next() override{
        if(!hasNext()) throw runtime_error("No next element");
        
        Iterator* it =q.front();
        q.pop();
        
        int val = it->next();
        if(it->hasNext()) q.push(it);
        return val;
    }
    
};

int main(){
    
    cout<<"Level 3: Simple List Iterator"<<endl;
    
    vector<int> simpleList = {0, 1, 2, 3, 4, 5, 6};
    Iterator<int>* listIt = new ListIterator(simpleList);
    
    while(listIt->hasNext()){
        cout<<"Next element in the Simple List is:"<< listIt->next()<<endl;
    }
    
    cout<<"Level 4: Range Based Iterator (Steps can be +ve or -ve)"<<endl;
    
    Iterator<int>* rangeList = new RangeIterator(30, 4, -4);
    while(rangeList->hasNext()){
        cout<<"Next Element in range :"<<rangeList->next()<<endl;
    }
    
    Iterator<int>* zigzagIterator = new ZigZagIterator({{1, 2, 3}, {4}, {}, {5, 6, 7, 8}});
    while(zigzagIterator->hasNext()){
        cout<<"Next zig-zag element :"<<zigzagIterator->next()<<endl;
    }
    
    cout<<"Leavel 5: Round Robin Iterator over Mixed Iterators"<<endl;
    
    Iterator<int>* listIt2 = new ListIterator({1, 2, 3});
    Iterator<int>* RangeIt2 = new RangeIterator(80, 40, -10);
    Iterator<int>* ListIt3 = new ZigZagIterator({{1, 2, 3}, {34, 5}, {}, {32531, 532}});
    
    vector<Iterator<int>*> mixedIterators={
        listIt2, RangeIt2, ListIt3
    };
    
    Iterator<int>* rrIt = new RoundRobinIterator(mixedIterators);
    
    while(rrIt->hasNext()){
        cout<<"Next Iterator:"<<rrIt->next()<<endl;
    }
};