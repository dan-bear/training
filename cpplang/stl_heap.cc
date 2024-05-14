
///-----------------------------------------------------------------------------
using namespace std;
class HeapExample{
public:
    void priorityQueueExample(){
        
        std::function<bool, (const int, const int)> maxCmp =
          [](const int val1, const int val2){return val1 < val2;};
        
        auto minCmp = [](const int val1, const int val2){
          return val1 > val2;};
  
        ///elements type, container type, cmp func type.
        priority_queue<int, vector<int>,
                       function<bool, (const int, const int)>> maxHeap(maxCmp);
        priority_queue<int, vector<int>, decltype(minHeapCmp)> minHeap(minCmp);
      
        minHeap.push(3);
        minHeap.push(2);
        minHeap.push(1);
        while(minHeap.size() > 0){
            cout << minHeap.top() << "\n";
            minHeap.pop();
        }
    }
};
      

};
