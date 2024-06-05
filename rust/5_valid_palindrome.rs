/**
 * https://leetcode.com/problems/valid-palindrome/
 * #string #str
 */
impl Solution {
    pub fn is_palindrome(s: String) -> bool {
        let reducedStr : String = Self::reduce_string(s); 
        //Notes:
        //    1: At this point, s cannot be used anymore as its
        //       ownership was passed to reduceString function.
        //    2: I tried to use the next syntax:
        //       let reducedStr : &[u8] = Self::reduce_string(s).as_bytes()
        //       But the compiler gives a temporary-value-dropped-while-borrowed
        //       since this syntax saves the returned string from 
        //       Self::reduce_string(s) as a temporary-value and then the value
        //       is dropped after as_bytes() is called, so reducedStr tries to
        //       hold a reference to a dropped value.
        let reducedStrAsBytes : &[u8] = reducedStr.as_bytes();
        let mut firstIdx : isize = 0;
        let mut lastIdx : isize = (reducedStr.len() as isize) - 1;
        let mut res : bool = true;
        ///Note: it's possible that lastIdx reaches -1, for example in a single
        //      letter case. That's why first and last idx are isize. However
        //      one cannot use the [] operator with isize, just usize (in 
        //      general, only uint types).
        while firstIdx < lastIdx && res{
            res = reducedStrAsBytes[firstIdx as usize] ==
                  reducedStrAsBytes[lastIdx as usize];
            firstIdx += 1;
            lastIdx -= 1;
        }
        return res;
    }
    
    fn reduce_string(rStr: String) -> String{
        let mut reducedStr : String = String::new();
        let sAsByteArr : &[u8] = rStr.as_bytes();
        for idx in 0..rStr.len(){
            if Self::is_char(sAsByteArr[idx]) {
                reducedStr.push(Self::to_lower(sAsByteArr[idx]));
            }else if Self::is_digit(sAsByteArr[idx]){
                reducedStr.push(sAsByteArr[idx] as char);
            }
        }
        return reducedStr;
    }

    fn is_digit(bChar : u8) -> bool{
        return bChar >= b'0' && bChar <= b'9';
    }

    fn is_char(bChar : u8) -> bool{
        return (b'a' <= bChar && bChar <= b'z') ||
               (b'A' <= bChar && bChar <= b'Z');
    }
    
    fn to_lower(bChar : u8) -> char{
        let mut res : char = if bChar >= b'a' {bChar as char}
                             else {(bChar + b'a' - b'A') as char};
        return res;
    }
}
