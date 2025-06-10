# solvers
implement solvers for 15 puzzle and othello in  C++

# install

```bash
sudo apt update && sudo apt install g++
```

# 15 puzzle
## Usage
```bash
g++ -o 15_puzzle_1 15_puzzle_1.cpp
./15_puzzle_1
```

input
```txt
012345ABCDEF6789
move 0 to down
move 0 to down
move 0 to right
move 0 to down
move 0 to left
move 0 to up
move 0 to up
move 0 to right
move 0 to down
move 0 to down
move 0 to right
move 0 to up
move 0 to up
move 0 to left
move 0 to down
move 0 to down
move 0 to right
move 0 to right
move 0 to up
move 0 to up
move 0 to left
move 0 to down
move 0 to down
move 0 to left
move 0 to left
move 0 to up
move 0 to right
move 0 to right
move 0 to up
move 0 to left
move 0 to left
move 0 to up
```

# othello
## Usage


```sh
g++ -o othello_multiple_heuristics othello_multiple_heuristics.cpp
./othello_multiple_heuristics
+++O+++++OO++++XO+++++++++++++++++++
2
```


```bash
#old
g++ -o minimax_with_alpha_beta_p4 minimax_with_alpha_beta_p4.cpp
./minimax_with_alpha_beta_p4

6
OO++++XOOXXX+XOXX++OXXOO+XXOX++XXXX+
2
4
OO++++XOOXXX+XOXX++OXXOO+XXOX++XXXX+
2
6
OO++++XOOXXX+XOXX++OXXOO+XXOX++XXXX+
2
8
++++XOX+X+X+OOOOX+XOOOXOXOOOOXXO++++
1
4
++++XOX+X+X+OOOOX+XOOOXOXOOOOXXO++++
1
6
++++XOX+X+X+OOOOX+XOOOXOXOOOOXXO++++
1
8
```