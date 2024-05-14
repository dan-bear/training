#include <iostream>
#include <string>

class StrExamles{
public:
    static void sStringFind(const string& strToFind){
        string s("31415");
        ///check whether a char is in a string:
        if(s.find(strToFind) != string::npos){
            cout << "found " << strToFind << " in " << s << "\n";
        }else{
            cout << "did not find " << strToFind << " in " << s << "\n;
        }
    }
};


int main(){
    sStringFind("



  return 0;
}
