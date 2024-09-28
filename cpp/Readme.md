# 数独解算器文档

## 概述

本文档提供了用 C++ 实现的数独解算器的概述。该解算器读取数独谜题，处理并输出解决方案，使用回溯算法实现。

## 类

### `Grid`

`Grid` 类表示数独网格，并提供操作和检索数据的方法。

#### 成员

- **静态常量**：
  - `GRID_SIZE`：网格的大小（标准数独为 9）。
  - `BOX_SIZE`：每个 3x3 小方块的大小（标准数独为 3）。
- **属性**：
  - `vector<vector<int>> grid`：一个二维向量，表示数独网格。

#### 方法

- **`Grid(const string& puzzle)`**：构造函数，通过解析给定的谜题字符串初始化网格。
- **`void parse(const string& puzzle)`**：解析输入字符串并用整数值填充网格。验证输入格式的有效性。
- **`vector<int> getRow(int row)`**：返回指定行中的数字。
- **`vector<int> getColumn(int col)`**：返回指定列中的数字。
- **`vector<int> getBox(int row, int col)`**：返回包含指定单元格的 3x3 小方块中的数字。
- **`void printGrid() const`**：输出网格的当前状态到控制台。

------

### `Sudoku`

`Sudoku` 类处理数独谜题的整体求解过程。

#### 属性

- **`Grid grid`**：`Grid` 类的实例，表示数独网格。

#### 方法

- **`Sudoku(const string& puzzle)`**：构造函数，用给定的谜题字符串初始化 `Sudoku` 实例。
- **`void getInference()`**：尝试解决数独谜题，并在找到解决方案时打印结果。
- **`bool backtrack()`**：实现回溯算法来填充网格。如果找到解决方案，返回 `true`。
- **`set<int> getPossibleValues(int row, int col)`**：根据数独规则返回给定空单元格的可能值集合。

------

## 使用方法

要使用数独解算器，请创建 `Sudoku` 类的实例并传入谜题字符串，然后调用 `getInference()` 方法。

### 示例

```
int main() {
    string puzzle = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";
    Sudoku sudoku(puzzle);
    std::cout << "初始棋盘:" << std::endl;
    sudoku.getInference();
    return 0;
}
```

### 输入格式

输入的谜题字符串应包含 81 个字符，其中：

- 数字 `1-9` 表示已填充的单元格。
- `0` 或 `.`（点）表示空单元格。

### 输出

程序将打印解决后的数独网格，或指示没有找到解。

------

## 错误处理

程序会检查无效输入，例如：

- 谜题字符串长度不等于 81。
- 谜题字符串中包含非数字字符。

如果检测到任何无效输入，将抛出 `invalid_argument` 异常。