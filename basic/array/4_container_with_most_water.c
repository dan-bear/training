/**
 * Please read the question description in:
 * https://leetcode.com/problems/container-with-most-water
 * #two-pointers #TWO-POINTERS
 */
///Solution.
int maxArea(int* height, int heightSize) {
    int maxVol = 0;
    int leftHeightIdx = 0;
    int rightHeightIdx = heightSize - 1;
    int currDist = rightHeightIdx;
    while(leftHeightIdx < rightHeightIdx){
        int minHeight = 0;
        if(height[leftHeightIdx] < height[rightHeightIdx]){
            minHeight = height[leftHeightIdx];
            leftHeightIdx++;
        }else{
            minHeight = height[rightHeightIdx];
            rightHeightIdx--;
        }
        int currVol = minHeight * currDist;
        maxVol = maxVol < currVol ? currVol : maxVol;
        currDist--;
    }
    return maxVol;    
}
