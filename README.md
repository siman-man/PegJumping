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

##Clarifications

* Each sequence will move only one peg.
各ペグは1つしか動かせない

* You can use the same peg in multiple jump sequences as long as it's on the board.
1つのペグをそれが許す限り複数回動かしても良い

* A peg will be removed from the board when another peg jumps over it.
他のペグにジャンプされた際、そのペグは消滅する

You don't have to remove all the pegs from the board.
あなたは全てのペグを削除することは出来ない

The top left corner of the board corresponds to row and column zero.
ボードの角は(0,0)で始まるものとする

## Notes
- The time limit is 15 seconds per test case (this includes only the time spent in your code). 
The memory limit is 1024 megabytes.
時間制限は15秒
メモリは1GBまでとする

- There is no explicit code size limit. The implicit source code size limit is around 1 MB 
(it is not advisable to submit codes of size close to that or larger). Once your code is compiled, 
the binary size should not exceed 1 MB.
コードサイズの上限は大体1MBぐらいまで

- The compilation time limit is 30 seconds. You can find information about compilers that we use 
and compilation options here.
コンパイルの時間制限は30秒

- There are 10 example test cases and 100 full submission (provisional) test cases.
