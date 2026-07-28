// https://leetcode.com/problems/excel-sheet-column-title/
class Solution {
public:
    string convertToTitle(int columnNumber) {
        string title;
        int numOfChars = static_cast<int>('Z') - static_cast<int>('A') + 1;
        int firstLetter = static_cast<int>('A');
        while(columnNumber != 0){
            int mod = columnNumber % numOfChars;
            char c = mod == 0 ? 'Z' : static_cast<char>(firstLetter + mod - 1);
            title.push_back(c);
            if(mod == 0){
                columnNumber -= numOfChars;
            }
            columnNumber /= numOfChars;
        }
        // std::reverse(title.begin(), title.end());
        std::ranges::reverse(title);
        return title;
    }
};

// A   1
// B   2
// C   3 => 3*3^0 instead of 1*3^1 + 0*3^0 => put C, dec by 3, divide by 3
// AA  4
// AB  5
// AC  6
// in general, every number that equals 0 % 3 can be write in the form of:
// N * 3 and also (N - 1)*3 + 3*1, so it's weird ternary representation is
// a0*3^m + ... + a1*3^1 + 3*3^0, thus the last char is C (3*3^0) and we
// are left with the same problem only for a0*3^m + ... + a1*3^1.
//
// mod 26 example:
// 18278 % 26 = 0  => Z
// 18278 - 26 = 18252
// 18252 / 26 = 702
// 702 % 26 = 0 => Z
// 702 - 26 = 676
// 676 / 26 = 26
// 26 % 26 = 0 => Z
// 26 - 26 = 0
