Write a program in C++ called that reads a list of positive and negative integers
from user input (i.e. standard input) until a “END” statement is entered. The program should
not display any text prompting the user for input. It should just start reading from standard
input.

Organize these integers into a binary search tree. The first integer will be the root, the second
integer should be inserted left, if smaller than the root, or right if larger.
After all numbers are inserted, the program should display the maximum height of the tree. The
root node will be at level 0. Your program should also display the maximum width of the tree.
This is the total number of nodes at any level. It should also display the level of the maximum
width.

Program output:
yourName@elec>make clean
yourName@elec>make all
yourName@elec>./bst < testFile.txt
