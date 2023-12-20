#https://leetcode.com/problems/image-smoother/

class Solution:
    
    def imageSmoother(self, img: List[List[int]]) -> List[List[int]]:
        numOfRows = len(img)
        numOfCols = len(img[0])
        currRowIdx = 0
        rowAboveCopy = [0 for i in range(numOfCols)]
        
        while currRowIdx < numOfRows:
            currRowCopy = [img[currRowIdx][i] for i in range(numOfCols)]    
            self.applyFilterToRow(currRowIdx, currRowCopy, rowAboveCopy, img)
            rowAboveCopy = currRowCopy
            currRowIdx += 1
            
        return img

    def applyFilterToRow(self, rowIdx, rowCopy, rowAboveCopy, img):
        numOfCols = len(img[0])
        for colIdx in range(numOfCols):
            self.applyFilterToCell(rowIdx,
                                   colIdx,
                                   rowCopy,
                                   rowAboveCopy,
                                   img)
    
    def applyFilterToCell(self, rowIdx, colIdx, rowCopy, rowAboveCopy, img):
        numOfRows = len(img)
        numOfCols = len(img[0])
        rowDirArr = [-1, 0, 1]
        colDirArr = [-1, 0, 1]
        participatingCellCount = 0
        cellsSum = 0
        for rowDir in rowDirArr:
            for colDir in colDirArr:
                if self.isValidCellPosition(rowIdx + rowDir,
                                            colIdx + colDir,
                                            numOfRows,
                                            numOfCols):
                    participatingCellCount += 1
                    cellsSum += self.getCellVal(rowIdx,
                                                colIdx,
                                                rowDir,
                                                colDir,
                                                rowCopy,
                                                rowAboveCopy,
                                                img)
        
        flooredAvg = cellsSum // participatingCellCount
        img[rowIdx][colIdx] = flooredAvg

    def isValidCellPosition(self, rowIdx, colIdx, numOfRows, numOfCols):
        bRes = True
        
        if rowIdx < 0:
            bRes = False
        elif colIdx < 0:
            bRes = False
        elif rowIdx >= numOfRows:
            bRes = False
        elif colIdx >= numOfCols:
            bRes = False
        
        return bRes

    def getCellVal(self,
                    rowIdx,
                    colIdx,
                    rowDir, 
                    colDir,
                    rowCopy,
                    rowAboveCopy,
                    img):
        res = None
        if rowDir == -1:
            res = rowAboveCopy[colIdx + colDir]
        elif rowDir == 0:
            res = rowCopy[colIdx + colDir]
        elif rowDir == 1:
            res = img[rowIdx + rowDir][colIdx + colDir]
        return res
