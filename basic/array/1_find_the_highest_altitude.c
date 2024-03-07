/**
 * Please read description here:
 * https://leetcode.com/problems/find-the-highest-altitude
 * #array #sum #max
 */
///SOLUTION
int largestAltitude(int* gain, int gainSize) {
    int maxAltitude = 0;
    int currAltitude = 0;
    for(int gainIdx = 0; gainIdx < gainSize; gainIdx++){
        currAltitude += gain[gainIdx];
        maxAltitude = maxAltitude < currAltitude ? currAltitude : maxAltitude;
    }
    return maxAltitude;
}
