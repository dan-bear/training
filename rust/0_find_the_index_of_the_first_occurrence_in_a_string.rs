//https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
impl Solution {
    pub fn str_str(haystack: String, needle: String) -> i32 {
        let mut res : i32 = -1;
        let haystack_len = haystack.len(); // String::len() returns usize.
        let needle_len = needle.len(); 
        if haystack_len >= needle_len {
            // the ..= makes the index to move from 0 to the last value
            // including the last value.
            for front_idx in 0..=(haystack_len - needle_len) {
                //Note: have to pass reference to the strings since the string 
                //      themselves are used in the next iteration, so the 
                //      string can be borrowed but not to be moved.
                //Note: front_idx is not moved, but passed by copy.
                if Self::check_needle_from_current_idx(&haystack, &needle, front_idx){
                    res = front_idx as i32;
                    break;
                }
            }
        }
        res
        //same as: "return res;""
        //Note: "res;" does not compile since it's a statement
        //       and not an expression. 
    }

    fn check_needle_from_current_idx(r_haystack : &String,
                                     r_needle : &String,
                                     front_idx : usize) -> bool{
        // [idx1..idx2] operator for string returns a slice
        // and the == operator is implemented between slices and
        // strings. The problem is that == is not implemented between
        // slices and reference to string, that's why r_needle[..] is used
        // to make a slice out of needed, so the comparison can be made
        // between two slices. 
        return r_haystack[front_idx..(front_idx + r_needle.len())] == r_needle[..];
    }

    //More notes:
    //1: The next syntax does not compile: 
    //    "for idx : i32 in 0..100{///loop code}"
    //    however it can be done with:
    //    "for idx in 0i32 in 0..100{///loop code}"
    // 2: The String's [] cannot be used with 
    //    std::ops::Index<std::ops::Range<i32>> as a parameter,
    //    which is the return type if one tries to use the next
    //    line: for front_idx in 0i32..=(haystacl_len - needle_len){}
    //    but it works with usize instead of 0i32.
    // 3: The return value of String::len() is usize.
    // 4: usize type in rust: the unsigned integer with the minimal
    //    width that can represent any memory address on the machine
    //    running the code.
    // 5: the val1..val2 syntax in rust defines a std::ops::Range<Idx>
    //    struct type. Where Idx is also a defined type, I guess the 
    //    struct index enforces the behaviour needed for a type to act
    //    like an index which can be used for range. For example
    //    Idx<usize> is a valid Idx implementation. But I have not checked
    //    it out yet.
}
