/**
 * https://leetcode.com/problems/add-binary/
 * 1: max operation between two unsigned integers.
 * 2: Access chars in string.
 * 3: Pass string reference to a function.
 * 4: Convert between chars and u8.
 * 5: if cond {} else {} syntax.
 */
impl Solution {
    pub fn add_binary(a: String, b: String) -> String {
        let mut res : String = String::new();
        let maxLen : usize = a.len().max(b.len());
        let mut carryBit : u8  = 0;
        for idx in 0..maxLen{
            let mut aBit : u8 = Self::getBit(&a, idx);
            let mut bBit : u8 = Self::getBit(&b, idx);
            let addition : u8 = aBit + bBit + carryBit;
            let resBit : u8 = addition % 2;
            carryBit = if addition > 1 {1} else {0};
            res.push((resBit + '0' as u8) as char);
        }
        if carryBit == 1{
            res.push('1');
        }
        return res.chars().rev().collect();
    }

    fn getBit(s : &String, idx : usize) -> u8{
        let res : u8 = if idx >= s.len() {0}
                       else {s.as_bytes()[s.len() - 1 - idx] as u8 - b'0'};
        return res;
    }
}
