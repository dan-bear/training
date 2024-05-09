/**
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons
 * #intervals #sort #greedy
 */
class Solution {
public:
    ///The problem is just to gather up intervals under
    ///the "intersecting" relation. The number of classes
    ///is the number of arrows.
    ///If intersecting was a transitive relation it would
    ///be an easier task.

    ///Solution1: 
    ///Sort by the left value, and update the intersection till
    ///you reach a non-intersecting point. Once a non-intersecting
    ///point is reached, increase the arrowCount and update the intersection.
    ///[[1, 6], [2, 8], [7, 12], [10, 16]]
    ///intersection: [1, 6]
    ///              [2, 6]
    ///intersection: [7, 12]
    ///              [10, 12]


    ///Solution2:
    ///Sort by the point's right value.
    ///start with the minimal right value and iterate the points
    ///till the minimal right value is smaller than the current point
    ///minimal (left) value. Update the minimal right value to the
    ///current point right value and increase the value count by 1.
    int findMinArrowShots(vector<vector<int>>& points) {
        ///Solution1 approach:
        //return updatedIntersectionApproach(points);
        ///Solution2 approach:
        return rightPartApproach(points);
    }

private:
    int rightPartApproach(vector<vector<int>>& points){
        sortByPointMaxVal(points);
        int arrowCount = 1;
        int lastVal = points[0][1];
        for(const vector<int>& point : points){
            if(lastVal < point[0]){
                lastVal = point[1];
                arrowCount++;
            }
        }
        return arrowCount;
    }

    void sortByPointMaxVal(vector<vector<int>>& points){
        ranges::sort(points, [](const vector<int>& point1, const vector<int>& point2){
            if(point1[1] < point2[1]){
                return true;
            }else if(point1[1] == point2[1]){
                return point1[0] < point2[0];
            }else{
                return false;
            }
        });
    }
    
    
    int updatedIntersectionApproach(vector<vector<int>>& points){
        ///Sort by points' minimal val in ascending order.
        sortPointsByLeftXVal(points);
        int arrowCount = 1;
        vector<int> intersection = points[0];
        for(const vector<int>& point : points){
            if(isIntersecting(intersection, point)){
                updateIntersection(point, intersection);
            }else{
                arrowCount += 1;
                intersection = point;
            }
        }
        return arrowCount;    
    }
    
    bool isIntersecting(const vector<int>& intersection, const vector<int>& point){
        return !(intersection[1] < point[0] || point[1] < intersection[0]);
    }

    void updateIntersection(const vector<int>& point, vector<int>& intersection){
        intersection[0] = max(intersection[0], point[0]);
        intersection[1] = min(intersection[1], point[1]);
    }
    
    void sortPointsByLeftXVal(vector<vector<int>>& points){
        ranges::sort(points, [](const vector<int>& point1, const vector<int>& point2){
            return point1[0] < point2[0];
        });
    }
};
