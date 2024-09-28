#棋盘类
class Grid:
    GRID_SIZE = 9
    BOX_SIZE = 3

    def __init__(self, puzzle):
        self.grid = self.parse(puzzle)

    def parse(self, puzzle):
        if len(puzzle) != 81:
            raise ValueError("Puzzle string must be 81 characters long.")

        grid = [[0] * self.GRID_SIZE for _ in range(self.GRID_SIZE)]
        idx = 0
        for i in range(self.GRID_SIZE):
            for j in range(self.GRID_SIZE):
                ch = puzzle[idx]
                if ch < '0' or ch > '9':
                    raise ValueError("Puzzle string must contain only digits.")
                grid[i][j] = int(ch)
                idx += 1
        return grid

    def get_row(self, row):
        return self.grid[row]

    def get_column(self, col):
        return [self.grid[i][col] for i in range(self.GRID_SIZE)]

    def get_box(self, row, col):
        box = []
        start_row = (row // self.BOX_SIZE) * self.BOX_SIZE
        start_col = (col // self.BOX_SIZE) * self.BOX_SIZE

        for i in range(start_row, start_row + self.BOX_SIZE):
            for j in range(start_col, start_col + self.BOX_SIZE):
                box.append(self.grid[i][j])
        return box

    def print_grid(self):
        for row in self.grid:
            print(" ".join(str(num) if num != 0 else "." for num in row))