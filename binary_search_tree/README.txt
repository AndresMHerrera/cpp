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

Example Output:

input count: 9
input: 10 3 20 19 12 6 5 8 7 

Printing Binary Search Tree
value: 10	level :0
value: 3	level :1
value: 20	level :1
value: 6	level :2
value: 19	level :2
value: 5	level :3
value: 8	level :3
value: 12	level :3
value: 7	level :4


Max Tree Height : 4
Max Width : 3
Max Width level : 3

