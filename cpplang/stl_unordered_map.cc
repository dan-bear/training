///-----------------------------------------------------------------------------
using namespace std;
int main(){
    unordered_map<int, bool> histo1; //amoritezed O(1) histo using hash table.
    histo1[3] = true;
    histo1[31] = true;
    histo1[314] = true;
    histo1[3141] = true;
    unordered_map<int, bool> histo2= {{31415, true},
                                      {314159, true},
                                      {3141592, true}};
    if(histo1.find(271828) == histo1.end()){
        histo1[271828] = true;
    }

    for(const pair<int, bool>& mapPair : histo1){
        cout << mapPair.first << " " << mapPair.second << "\n";
    }

    return 0;
}
