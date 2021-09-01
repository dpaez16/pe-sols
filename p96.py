FILE_PATH  = "files/p096_sudoku.txt"
EMPTY_SPOT = "0"
GRID_SEP   = "grid"
N          = 9

class Sudoku:
    def __init__(self, board):
        self.board = board

    def solve(self):
        return self.helper(0, 0)
    
    def get_num(self):
        num_str = self.board[0][0] + self.board[0][1] + self.board[0][2]
        return int(num_str)
    
    def helper(self, row, col):
        n = len(self.board)
        if row == n:
            return True

        block_idxs = (
            row // 3,
            col // 3
        )
        next_col = (col + 1) % n
        next_row = row + 1 if next_col == 0 else row
        
        if self.board[row][col] != EMPTY_SPOT:
            return self.helper(next_row, next_col)
        
        for digit in "123456789":
            self.board[row][col] = digit
            if not self.checkRow(self.board, row) or \
                not self.checkCol(self.board, col) or \
                not self.checkBox(self.board, block_idxs[0], block_idxs[1]):
                continue
            if self.helper(next_row, next_col):
                return True
        
        self.board[row][col] = EMPTY_SPOT
        return False
    
    def checkCol(self, board, col):
        s = set()
        n = len(board)
        
        for r in range(n):
            if board[r][col] == EMPTY_SPOT:
                continue
            if board[r][col] in s:
                return False
            
            s.add(board[r][col])
        return True
    
    def checkRow(self, board, row):
        s = set()
        n = len(board)
        
        for c in range(n):
            if board[row][c] == EMPTY_SPOT:
                continue
            if board[row][c] in s:
                return False
            
            s.add(board[row][c])
        return True

    def checkBox(self, board, r, c):
        n = len(board)
        s = set()
        
        for i in range(r * (n // 3), (r + 1) * (n // 3)):
            for j in range(c * (n // 3), (c + 1) * (n // 3)):
                if board[i][j] == EMPTY_SPOT:
                    continue
                if board[i][j] in s:
                    return False
                
                s.add(board[i][j])
        
        return True

def get_board(f):
    board = []
    for i in range(N):
        line = f.readline()
        line = line.strip()
        row = [digit for digit in line]
        board.append(row)
    return board

def process_file():
    f = open(FILE_PATH)
    boards = []
    
    while True:
        line = f.readline()
        line = line.lower().strip()
        if len(line) == 0:
            break
        
        if GRID_SEP in line:
            board = get_board(f)
            boards.append(board)

    f.close()
    return boards

boards = process_file()
total = 0

for board in boards:
    sudoku = Sudoku(board)
    sudoku.solve()
    total += sudoku.get_num()

print(total)
