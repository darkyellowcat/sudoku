遇到的问题：
1.Clion汉字输出出现乱码：右下角编码形式改为GBK；
2.如何实现一个乱序的棋盘：因为之前学过一段时间算法，所以我想到的是用dfs；
3.随机化：原本想用random，但查使用方法时发现random已经不被推荐使用了，需要替代；
4.棋盘的实现：用vector实现一个二维数组，存储棋盘的状态；

# Sudoku Game (C++)

这是一个用 C++ 编写的控制台数独游戏。程序可以生成完整的数独解，挖空形成数独谜题，并允许你查看答案。

## ✨ 功能特色

- 自动生成一个合法的完整数独
- 可自定义保留格子的数量（17~81）
- 自动挖空生成谜题（确保唯一解）
- 按任意键查看答案（完整解）
