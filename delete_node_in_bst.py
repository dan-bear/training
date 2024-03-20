# https://leetcode.com/problems/delete-node-in-a-bst
# #bst #binary_tree #recursive
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def deleteNode(self, root, key):
        """
        :type root: TreeNode
        :type key: int
        :rtype: TreeNode
        """
        if root:
            if root.val > key:
                root.left = self.deleteNode(root.left, key)
            elif root.val < key:
                root.right = self.deleteNode(root.right, key)
            else:
                if root.right:
                    self.getLeftMostLeaf(root.right).left = root.left
                    root = root.right
                else:
                    root = root.left
        
        return root

    def getLeftMostLeaf(self, root):
        while root.left:
            root = root.left
        return root
