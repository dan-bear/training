/**
 * https://leetcode.com/problems/rotate-array
 * #array
 */
impl Solution {
    //&mut Vec<i32> is a mutable reference to a vector.
    pub fn rotate(nums: &mut Vec<i32>, k: i32) {
        //Works but slow.
        //Solution::approach1(nums, k);
        
        //Works but too slow (exceeds time limit).
        //Self::approach2(nums, k);

        Self::approach3(nums, k);
    }

    fn approach3(nums: &mut Vec<i32>, k: i32){
        //1 2 3 4 5 6 , k = 2, len = 6
        //reverse nums[0 : 4], reverse nums[4 : 6]
        //4 3 2 1 6 5 
        //reverse nums[0 : 6]
        //5 6 1 2 3 4
        let moduledK : usize = k as usize % nums.len();
        Self::reverse(nums, 0, nums.len() - moduledK - 1);
        Self::reverse(nums, nums.len() - moduledK, nums.len() - 1);
        nums.reverse();
        //Note:
        //one could also go with reverse all and then reverse slices!
    }

    fn reverse(nums: &mut Vec<i32>, mut startIdx: usize, mut endIdx: usize){
        while startIdx < endIdx{
            nums.swap(startIdx, endIdx);
            startIdx += 1;
            endIdx -= 1;
        }
    }


    fn approach1(nums: &mut Vec<i32>, k: i32){
        //Syntax:
        //    1: usize - an unsigned integer with pointer size width.
        //    2: nums.len() returns the number of elements in the
        //       vector as a usize type.
        //Notes:
        //    1: k might be greater than nums.len().
        //    2: It's assumed nums.len() != 0.
        //
        let swip : usize = k as usize % nums.len();
        //_ gets the value from 0 to swip - 1.
        for _ in 0..swip{
            //Syntax:
            //1: Vec<T>::pop():
            //    1.1: pop method signature: pub fn pop(&mut self) -> Option<T>
            //    1.2: pop() gets a mutable reference to the vector itself, i.e.
            //         it can change the vector.
            //    1.3: pop returns an Option<T>, in our case, Option<int> since
            //         the vector might be an empty one, in this case pop 
            //         returns Option::None
            //2: Option::unwrap(): 
            //   gets the value from an Option<T> and results in panic in case
            //   the Option's value is None.
            let val : i32 = nums.pop().unwrap();
            //Insert val to position 0.
            nums.insert(0, val);
        }
    }

    fn approach2(nums: &mut Vec<i32>, k: i32){
        let moduledK : usize = k as usize % nums.len();
        for _ in 0..moduledK{
            Self::shiftRight(nums);
        }
    }

    fn shiftRight(nums: &mut Vec<i32>){
        let last: i32 = nums[nums.len() - 1];
        ///Note: (1..nums.len()).rev => nums.len() - 1, nums.len() - 2, ... ,  1
        for idx in (1..nums.len()).rev(){
            nums[idx] = nums[idx - 1];
        }
        nums[0] = last;
    }
}
