/**
 * https://leetcode.com/problems/length-of-last-word
 * #string #str
 */
impl Solution {
    pub fn length_of_last_word(s: String) -> i32 {
        let mut lastWordLen : i32 = 0;
        let space : u8 = b' '; //the u8 ascii value of space.
        //1: s.as_bytes
        //    1.1: signature: pub fn as_bytes(&self) -> &[u8]
        //    1.2: The method returns a byte-slice of the string content.
        //    Note: the type of the elements in the returned slice are u8.
        //2: iter()
        //    2.1: iter creates an std::slice::Iter struct.
        //3: rev()
        //    3.1: The rev method reverses the iterator direction.
        for &letter in s.as_bytes().iter().rev(){
            if letter != space{
                lastWordLen += 1;
            }else{
                if lastWordLen != 0{
                    break;
                }
            }
        }
        return lastWordLen;


        //Another approach:
        //1: String::split_whitespace()
        //2: last()
        //3: unwrap()
        //4: len()
        //return s.split_whitespace().last().unwrap().len() as i32;
    }
}
