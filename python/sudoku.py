from grid import Grid


class Sudoku:
    def __init__(self, puzzle):
        self.grid = Grid(puzzle)

    # def get_inference(self):
    #     for row in range(Grid.GRID_SIZE):
    #         for col in range(Grid.GRID_SIZE):
    #             if self.grid.get_row(row)[col] == 0:  # If empty
    #                 candidates = self.get_possible_values(row, col)
    #                 print(f"候选值 ({row}, {col}): {' '.join(map(str, candidates))}")

    def backtrack(self):
        for row in range(Grid.GRID_SIZE):
            for col in range(Grid.GRID_SIZE):
                if self.grid.get_row(row)[col] == 0:  # 如果是空格
                    candidates = self.get_possible_values(row, col)
                    for candidate in candidates:
                        self.grid.grid[row][col] = candidate  # 填入候选值
                        if self.backtrack():  # 递归尝试解决
                            return True
                        self.grid.grid[row][col] = 0  # 回溯时重置
                    return False  # 找不到有效候选值
        return True  # 所有单元格已填充

    def get_inference(self):
        if self.backtrack():
            print("找到的解：")
            self.grid.print_grid()
        else:
            print("没有找到解。")
    def get_possible_values(self, row, col):
        possible_values = set(range(1, 10))

        row_values = self.grid.get_row(row)
        col_values = self.grid.get_column(col)
        box_values = self.grid.get_box(row, col)

        possible_values -= set(row_values)
        possible_values -= set(col_values)
        possible_values -= set(box_values)

        return possible_values