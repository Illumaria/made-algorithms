# Data Structures

## 1. Minimum on Stack

Input: standard input

Output: standard output

You have to implement the data structure that supports the following operations:

1. `1 x` — add _x_ to an end of the data structure.
2. `2` — retrieve the last element from the data structure.
3. `3` — find the minimal element in the data structure.

### Input

The first line of the input contains one integer _n_ (1 ≤ _n_ ≤ 10^6) — the number of operations. Next _n_ lines contain the description of operations, one per line. The argument _x_ in an operation of the first type lies in [-10^9, 10^9]. It is guaranteed that before retrieval the data structure is not empty.

### Output

Output the result for each operation of the third type, one per line.

### Example

**input**
```c++
8
1 2
1 3
1 -3
3
2
3
2
3
```

**output**
```c++
-3
2
2
```

## 2. Postfix Notation

Input: standard input

Output: standard output

In a postfix notation (Reverse Polish notation), two operands are followed by an operation. For example, the sum of two numbers A and B is written as `A B +`. The expression `B C + D *` means `(B + C) * D`, and the expression `A B C + D * +` means `A + (B + C) * D`. The advantage of a postfix notation is that it does not require brackets and additional operator precedence agreements for its reading.

An expression is given in the reverse Polish notation. Calculate the result.

### Input

The input contains the expression in the postfix notation containing single-digit numbers and the operations +, -, *. The string contains no more than 100 numbers and operations.

### Output

Output the result of the expression. It is guaranteed that the result of the expression, as well as the results of all intermediate calculations is less than 2^31 by an absolute value.

### Example

**input**
```c++
8 9 + 1 7 - *
```

**output**
```c++
-102
```

## 3. Queue

Input: standard input

Output: standard output

You have to implement a queue with two operations:

* `+ x` — add an element _x_ to the queue;
* `-` — retrieve an element from the queue.

For each retrieval operation output the result of the operation.

### Input

The first line of the input contains the number of operations — _n_ (1 ≤ _n_ ≤ 10^5). Next _n_ lines contain the description of operations one per line. The added element cannot exceed 10^9.

### Output

Output the results of all retrieve operations in the corresponding order, one per line.

### Example

**input**
```c++
4
+ 1
+ 10
-
-
```

**output**
```c++
1
10
```

## 4. Priority queue

Input: standard input

Output: standard output

Implement a data structure that supports three operations:

* `push x` — add an element _x_;
* `extract-min` — extract the minimal element;
* `decrease-key id v` — decrease an element to _v_ added by previous operation _id_.

If you are asked to decrease an element that was already extracted then you should do nothing.

All operations are enumerated starting from 1.

### Input

The input file contains performed operations, one per line. Arguments of `push` and `decrease-key` operations do not exceed 10^9 by an absolute value.

It is guaranteed that for any `decrease-key id v` the operation with identifier _id_ is `push` operation.

### Output

For each operation `extract-min` output two integers on a separate line: the value of the element and the identifier of `push` operation that added it. If there are several minimal elements, output any of them. If the data structure is empty, output "*".

### Example

**input**
```c++
push 3
push 4
push 2
extract-min
decrease-key 2 1
extract-min
extract-min
extract-min
```

**output**
```c++
2 3
1 2
3 1
*
```
