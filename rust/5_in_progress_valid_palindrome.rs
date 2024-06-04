/**
 * https://leetcode.com/problems/valid-palindrome/
 * #string #str
 */
impl Solution {
    pub fn is_palindrome(s: String) -> bool {
        let reducedStr : &[u8] = Self::reduceString(&s).as_bytes();
        let mut firstIdx : usize = 0;
        let mut lastIdx : usize = reducedStr.len() - 1;
        let mut res : bool = true;
        while firstIdx < lastIdx && res{
            res = reducedStr[firstIdx] == reducedStr[lastIdx];
            firstIdx += 1;
            lastIdx -= 1;
        }
        return res;
    }
    
    ///https://stackoverflow.com/questions/29428227/return-local-string-as-a-slice-str
    ///https://stackoverflow.com/questions/29781331/why-cant-i-return-an-str-value-generated-from-a-string
    ///https://stackoverflow.com/questions/43079077/proper-way-to-return-a-new-string-in-rust
    fn reduceString(rStr: &String) -> &String{
        let mut reducedStr : String = String::new();
        let sAsByteArr : &[u8] = rStr.as_bytes();
        for idx in 0..rStr.len(){
            if Self::isChar(sAsByteArr[idx]) {
                reducedStr.push(Self::toLower(sAsByteArr[idx]));
            }
        }
        return &reducedStr;
    }

    fn isChar(bChar : u8) -> bool{
        return (b'a' <= bChar && bChar <= b'z') ||
               (b'A' <= bChar && bChar <= b'Z');
    }
    
    fn toLower(bChar : u8) -> char{
        let mut res : char = if bChar >= b'a' {bChar as char}
                             else {(bChar + b'a' - b'A') as char};
        return res;
    }
}
