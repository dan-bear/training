# https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree
# #bfs #bt #BT #binary_tree #BINARY_TREE
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        
        maxSum = root.val
        maxLevel = 1
        
        currentLevel = 1
        currentSum = 0
        
        queue = deque()
        queue.append(root)
        #another syntax if one preferes to use list instead of queue:
        #queue = [root]

        while queue:
            numOfNodesInLevel = len(queue)
            for nodeIdx in range(numOfNodesInLevel):
                #if list is used:
                #node = queue.pop(0)
                node = queue.popleft()
                currentSum += node.val
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)

            if currentSum > maxSum:
                maxSum = currentSum
                maxLevel = currentLevel
            
            currentLevel += 1
            currentSum = 0

        return maxLevel
