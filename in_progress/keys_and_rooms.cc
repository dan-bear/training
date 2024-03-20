/**
 * https://leetcode.com/problems/keys-and-rooms
 * #dfs #recursive #graph
 */
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<bool> visitedRoomsHisto(rooms.size(), false);
        visitedRoomsHisto[0] = true;
        dfsTraverse(rooms, visitedRoomsHisto, 0);
        bool res = find(visitedRoomsHisto.begin(),
                        visitedRoomsHisto.end(),
                        false) == visitedRoomsHisto.end();
        return res;
    }
private:
    void dfsTraverse(const vector<vector<int>>& rooms, 
                     vector<bool>& histo,
                     int roomIdx){
        for(int key : rooms[roomIdx]){
            if(!histo[key]){
                histo[key] = true;
                dfsTraverse(rooms, histo, key);
            }
        }
    }
};
