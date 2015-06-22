# PegJumping
PegJumping

# Problem
You are given a square board containing N by N cells. On the board you have M types of pegs, 
あなたにはN*Nの正方形が与えられます。 そしてM個の種類のペグが与えられます

each type has its own value for scoring purposes. A peg can move on the board by jumping over 
各タイプにはそれぞれスコアがついています。 ペグは他の隣接するペグを飛び越えて移動することが可能です。

an adjacent peg and landing on an empty space. A peg can perform a sequence of jumps, one after the other. 
ペグは連続的にジャンプすることが出来ます。

A peg will be removed from the board when another peg jumps over it. The score you get for 
ジャンプされたペグはボードから削除されます。

a sequence of jumps performed by a peg is the sum of the values of the pegs removed from the board 
この時削除されたペグの数だけスコアを得ます。

during the sequence, multiplied by the length of that sequence.

Your task is to maximize the sum of the scores gained when performing peg sequence jumps.
あなたの目的はこのスコアを最大にすることです。

# Implementation

Your code should implement the method getMoves(int[] pegValue, string[] board). 
あなたはgetMoves(int[] pegValue, string[] board)を実装する必要があります。

Your getMoves method will be called once and should return a string[] containing your moves.

pegValue gives you information about each type of peg. Peg type i will add a value 
各ペグのスコア

of pegValue[i] to the score of a sequence when it's removed from the board.

board gives you the board containing N by N cells. Each string contains a row of the board. 
N * Nで与えられるボード

Any numeric character ('0'..'9') denotes the zero based type of the peg in that cell and '.' denotes an empty space.
'0' - '9'はペグ、'.'は空の要素
