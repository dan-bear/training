# https://leetcode.com/problems/keys-and-rooms
# bfs #dfs #recursion
class Solution:
    def canVisitAllRooms(self, rooms: List[List[int]]) -> bool:
        #return self.bfsCanVisitAllRooms(rooms)
        return self.dfsCanVisitAllRooms(rooms)


    def dfsCanVisitAllRooms(self, rooms: List[List[int]]) -> bool:
        roomsVisitedState = [False] * len(rooms);
        roomsVisitedState[0] = True
        self.dfsTraverse(rooms, roomsVisitedState, 0)
        return not False in roomsVisitedState


    def dfsTraverse(self, 
                    rooms: List[List[int]], 
                    roomsVisitedState: List[bool], 
                    roomIdx: int):
        for key in rooms[roomIdx]:
            if not roomsVisitedState[key]:
                roomsVisitedState[key] = True
                self.dfsTraverse(rooms, roomsVisitedState, key)


    def bfsCanVisitAllRooms(self, rooms: List[List[int]]) -> bool:
        roomsVisitedState = [False] * len(rooms)
        roomsVisitedState[0] = True
        bfsQ = deque()
        bfsQ.append(0)
        self.visitRooms(rooms, roomsVisitedState, bfsQ)
        reachedAllRooms = not (False in roomsVisitedState)
        return reachedAllRooms

    def visitRooms(self, rooms: List[List[int]], roomsVisitedState: List[bool], bfsQ):
        while bfsQ:
            key = bfsQ.popleft()
            for roomIdx in rooms[key]:
                if not roomsVisitedState[roomIdx]:
                    roomsVisitedState[roomIdx] = True
                    bfsQ.append(roomIdx)
