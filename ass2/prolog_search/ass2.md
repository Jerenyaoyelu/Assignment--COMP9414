Student: Yaoye LU

ID: 5188093



**Question 1: Search Algorithms for the 15-Puzzle**

(a)

| Algorithms | start10 | start20 | start27 | start35 | start43 |
| ---------- | ------- | ------- | ------- | ------- | ------- |
| UCS        | 2565    | Mem     | Mem     | Mem     | Mem     |
| IDS        | 2407    | 5297410 | Time    | Time    | Time    |
| A*         | 33      | 915     | 1873    | Mem     | Mem     |
| IDA*       | 29      | 952     | 2237    | 215612  | 2884650 |

(b)

UCS is efficient in time;

IDS is efficient in memory;

A* is more efficient in memory than UCS;

IDA* is more efficient in memory than A*.



**Question 2: Deceptive Starting States**

(a)

**start49:**

MBDC

LAKH

JFEI

 ONG

S = [4/1, 2/2, 1/2, 1/4, 1/3, 3/3, 3/2, 4/4, ... / ...|...],

H = 25.

**start51:**

GKJI

 MNC

EOHA

FBLD

S = [2/1, 3/4, 4/2, 2/4, 4/4, 3/1, 4/1, 1/1, ... / ...|...],

H = 43.

(b)

N = 551168

(c)

start49 has more successive expanded nodes that are not cut off than start50, and this successive search also increases the threshold steadily which makes start49 able to expand more nodes.

**Question 2: Heuristic Path Search** 

|        | start49 |           | start60 |           | start64 |            |
| ------ | ------- | --------- | ------- | --------- | ------- | ---------- |
| IDA*   | 49      | 178880187 | 60      | 321252368 | 64      | 1209086782 |
| 1.2    | 51      | 988332    | 62      | 230861    | 66      | 431033     |
| 1.4    | 57      | 311704    | 82      | 4432      | 94      | 190278     |
| Greedy | 133     | 5237      | 166     | 1617      | 184     | 2174       |

(b)

![Screen Shot 2019-04-04 at 11.42.46 pm](/Volumes/Guess_What/Master/Main_Course/9414/Assignment/ass2/prolog_search/ass2.assets/Screen Shot 2019-04-04 at 11.42.46 pm.png)

(d)

IDA* has the best quality of solution but consuming enormous time and memory to find it.

And by using the heuristic path algorithm, with apropriate w (1.2) scarifying some cost from initial state to goal state, the expanded nodes reduced dramatically and the quality of solutions doest not differ much from IDA*. However when  w becomes bigger, although the number of nodes keep dropping, the quality becomes worse.

Greedy has the fastest speed to get the solutions but the quality is very bad compared to other three algorithms.



**Question 3: Maze Search Heuristics**

(a)

Another admissible heuristic is the Sum-of-Moves to $x_{G}$ from $x$ and $y_{G}$ from $y$, the formula as following:

​	$h_{SM}(x,y,x_{G},y_{G}) = |x-x_{G}|+|y-y_{G}|​$

(b)

(i) Yes, because the $h_{SLD}\leq cost-to-goal​$ till holds.

(ii) No, because there exists some situations where  $h_{SM} > cost-to-goal$ ,$e.g.$ when there is no obstacles on the diagonal way to the goal from the current position, then the agent can move diagonally directly to the goal, this only costs one move for each step, however my heuristic costs two moves.

(iii)The best admissible heuristic will be the larger distance between from $x​$ to $x_{G}​$ and from $y​$ to $y_{G}​$, the formula will be:

 $h_{MD}(x,y,x_{G},y_{G}) = max(|x-x_{G}|,|y-y_{G}|)$

**Question 4 - Game Trees and Pruning**

(a)

![WechatIMG8](/Volumes/Guess_What/Master/Main_Course/9414/Assignment/ass2/prolog_search/ass2.assets/WechatIMG8.jpeg)

(b)

![WechatIMG9](/Volumes/Guess_What/Master/Main_Course/9414/Assignment/ass2/prolog_search/ass2.assets/WechatIMG9.jpeg)

(c)

25 leaves will be evaluated.

![WechatIMG10](/Volumes/Guess_What/Master/Main_Course/9414/Assignment/ass2/prolog_search/ass2.assets/WechatIMG10.jpeg)

(d)

let $h$ be the depth of the tree and $c$ be the number of children of each internal node,  then we have the time complexity(denoted as $T(h)$ equation as following:

​	$T(h) = 2cT(h-1)+2c+1​$

and given that the best move is always examined first, which means after examining the first move,we have $\alpha \geq \beta$ , then we can assume c = 1,

$\therefore$ $T(h) = O((2c)^h) = O(2^h)$                              (Therom)
