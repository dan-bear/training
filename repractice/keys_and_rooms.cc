/**
 * https://leetcode.com/problems/keys-and-rooms
 * #bfs #dfs #recursive #graph
 */
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms){
        return dfsCanVisitAllRooms(rooms);
        //return bfsCanVisitAllRooms(rooms);
    }

private:
    bool bfsCanVisitAllRooms(const vector<vector<int>>& rooms){
        vector<bool> visitedRoomsHisto(rooms.size(), false);
        visitedRoomsHisto[0] = true;
        queue<int> bfsQ;
        bfsQ.push(0);

        visitRooms(rooms, visitedRoomsHisto, bfsQ);
        bool res = visitedAllRooms(visitedRoomsHisto);        
        return res; 
    }

    void visitRooms(const vector<vector<int>>& rooms,
                    vector<bool>& visitedRoomsHisto, 
                    queue<int>& bfsQ){
        while(!bfsQ.empty()){
            int roomIdx = bfsQ.front();
            bfsQ.pop();
            for(int key : rooms[roomIdx]){
                if(!visitedRoomsHisto[key]){
                    visitedRoomsHisto[key] = true;
                    bfsQ.push(key);
                }
            }
        }
    }

    bool visitedAllRooms(const vector<bool>& visitedRoomsHisto){
        bool bValToFind = false;
        bool bRes = (find(visitedRoomsHisto.begin(),
                          visitedRoomsHisto.end(), 
                          bValToFind) == visitedRoomsHisto.end());
        return bRes;
    }

    bool dfsCanVisitAllRooms(const vector<vector<int>>& rooms) {
        vector<bool> visitedRoomsHisto(rooms.size(), false);
        visitedRoomsHisto[0] = true;
        dfsTraverse(rooms, visitedRoomsHisto, 0);
        bool res = visitedAllRooms(visitedRoomsHisto);
        return res;
    }
    
    
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
