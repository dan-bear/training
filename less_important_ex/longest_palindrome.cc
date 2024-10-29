/**
 * https://leetcode.com/problems/longest-palindrome
 * #histogram
 */
class Solution {
public:
    static constexpr int skNumOfAsciiChars{256};

    int longestPalindrome(string s) {
        std::array<int, skNumOfAsciiChars> histo = generateHisto(s);
        bool isReminder = false;
        int numOfPairs = 0;
        for(int count: histo){
            if(!isReminder && count % 2 != 0){
                isReminder = true;
            }
            numOfPairs += (count / 2);
        }
        return (2 * numOfPairs) + (isReminder ? 1 : 0);
    }
private:
    // reminder - const in the end of a method guarantees the method does not
    //            change the state of the class.
    std::array<int, skNumOfAsciiChars> generateHisto(std::string_view rStr) const{
        std::array<int, skNumOfAsciiChars> histo{0};
        for(char c: rStr){
            histo[static_cast<unsigned int>(c)]++;
        }
        return histo;
    }
};
