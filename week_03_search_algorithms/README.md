#  Search Algorithms

## 1. Approximate Binary Search

Input: standard input

Output: standard output

Two arrays are given. The first array is sorted in non-descending order, the second array contains queries (integer values).

For each query, print the number from the first array that is closest (i.e. with the minimum modulus of difference) to the value of this query. If there are several of them, print the smallest one.

### Input

The first line contains integers _n_ and _k_ (0 < _n_, _k_ ≤ 10^5).

The second line contains _n_ values of the first array, sorted in non-descending order.

The third line contains _k_ values of the second array.

Each number modulo does not exceed 2 * 10^9 for both arrays.

### Output

For each of the _k_ numbers, print the number from the first array that is closest to this one on a separate line. If there are several of them, print the smallest one.

### Example

**input**
```c++
5 5
1 3 5 7 9
2 4 8 1 6
```

**output**
```c++
1
3
7
1
5
```

## 2. Fast (Binary) Search

Input: standard input

Output: standard output

You are given an array of _n_ integers _a\_1_, _a\_2_, ..., _a\_n_.

Your task is to answer on the queries of the following type: "How many items are between _l_ and _r_?"

### Input

The first line of the input contains _n_ — the length of the array (1 ≤ _n_ ≤ 10^5).

The second line contains _n_ integers _a\_1_, _a\_2_, ..., _a\_n_ (−10^9 ≤ _a\_i_ ≤ 10^9).

The third line contains integer _k_ — number of queries (1 ≤ _k_ ≤ 10^5).

The following _k_ lines contain a pair of integers (_l_, _r_) — query, described above (−10^9 ≤ _l_ ≤ _r_ ≤ 10^9).

### Output

The output must consist of _k_ integers — responses for the queries.

### Example

**input**
```c++
5
10 1 10 3 4
4
1 10
2 9
3 4
2 2
```

**output**
```c++
5 2 2 0 
```

## 3. Square Root and Square (Real Binary Search)

Input: standard input

Output: standard output

Find _x_ such that _x_^2 + sqrt(_x_) = _C_ with the precision at least 6 digits after the point.

### Input

The sole line of the input contains one double 1.0 ≤ _C_ ≤ 10^10.

### Output

The sole line of the output should contain the required _x_.

### Examples

**input**
```c++
2.0000000000
```

**output**
```c++
1.0
```

**input**
```c++
18.0000000000
```

**output**
```c++
4.0
```

## 4. Bridge

Input: standard input

Output: standard output

There was a flood in the town of Graffiti Walls! During the disaster the wooden bridge across the river was demolished. Bipper and his sister Maple were happy to help citizens but that wasn't enough.

Now is your turn to save this wonderful town! There are _n_ new timbers prepared for you and the bridge has to consist of exactly _k_ timbers. You can cut timbers into smaller ones with integer length, but you can't combine them into one, because that would not be solid enough.

Your task is to find maximal width of the bridge.

### Input

The first line of input contains two integers _n_ and _k_ (1 ≤ _n_, _k_ ≤ 10001).

Each of the following _n_ lines contain one integer _a\_i_ — the length of the _i_-th timber (1 ≤ _a\_i_ ≤ 10^8).

### Output

The output must contain one integer — maximal width of the bridge.

If there is no way to make a bridge with the given constraints, answer should be 0.

### Example

**input**
```c++
4 11
802
743
457
539
```

**output**
```c++
200
```

## 5. A Very Easy Task

Input: standard input

Output: standard output

This morning, the jury decided to add another Very Easy Task to the Olympics version. The Executive secretary of the Organizing Committee printed its text in one copy, and now he needs to make _n_ more copies before the start of the Olympiad. He has two copiers at his disposal, one of which makes a copy of a sheet in _x_ seconds, and the other in _y_. (It is allowed to use either one copier or both at the same time. You can copy not only from the original, but also from the copy.) Help him find out what the minimum time it will take to do this.

### Input

The first line of input contains three natural numbers _n_, _x_ and _y_ separated by spaces (1 ≤ _n_ ≤ 2 * 10^8, 1 ≤ _x_, _y_ ≤ 10).

### Output

The sole line of the output should contain the minimum time in seconds required to get _n_ copies.

### Examples

**input**
```c++
4 1 1
```

**output**
```c++
3
```

**input**
```c++
5 1 2
```

**output**
```c++
4
```

## 6. Into the Jungle (Ternary Search)

Input: standard input

Output: standard output

Tarzan has just collected orchids for Jane's Birthday and wants to return back as soon as possible. But the way back goes across field and the mighty jungle and it's hard to find the optimal path. The plan of the nearest area can be represented as a square, where

* Tarzan's current position is (0, 1);
* Tarzan's house on a tree is at (1, 0);
* the border between field and jungle is a horizontal line _y_ = _a_ (0 ≤ _a_ ≤ 1);
* _v\_f_, _v\_j_ — Tarzan's speed on the field and in the jungle, respectively. Moving along the border is either on the field or in the jungle.

Find the point on the border, where Tarzan has to enter the jungle, to return back as soon as possible.

### Input

First line contains two positive integers _v\_f_ and _v\_j_ (1 ≤ _v\_f_, _v\_j_ ≤ 105) — speed on the field and in the jungle, respectively.

Second line contains a single real number _a_ (0 ≤ _a_ ≤ 1) — coordinate on vertical axis of the border between field and jungle. 

### Output

Output a single real number — coordinate on horizontal axis, where Tarzan should enter the jungle, with accuracy no less than 10^(-4).

### Example

**input**
```c++
5 3
0.4
```

**output**
```c++
0.783310604
```
