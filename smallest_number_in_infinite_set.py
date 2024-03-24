#https://leetcode.com/problems/smallest-number-in-infinite-set
# #heap #min_heap #HEAP
import heapq
class SmallestInfiniteSet:

    def __init__(self):
        self.currMin = 1
        self.addedMinHeap = []

    def popSmallest(self) -> int:
        res = None
        if self.addedMinHeap:
            res = heappop(self.addedMinHeap)
        else:
            res = self.currMin
            self.currMin += 1
        return res

    def addBack(self, num: int) -> None:
        if num < self.currMin and num not in self.addedMinHeap:
            heappush(self.addedMinHeap, num)
            


# Your SmallestInfiniteSet object will be instantiated and called as such:
# obj = SmallestInfiniteSet()
# param_1 = obj.popSmallest()
# obj.addBack(num)
