#  Sorting

## 1. A+B (Trial Problem)

Input: standard input

Output: standard output

You are given two integers _a_ and _b_. Print _a + b_.

### Input

The first line contains an integer _t_ (1 ≤ _t_ ≤ 10^4) — the number of test cases in the input. Then _t_ test cases follow.

Each test case is given as a line of two integers _a_ and _b_ (-1000 ≤ _a, b_ ≤ 1000).

### Output

Print _t_ integers — the required numbers _a + b_.

### Example

**input**
```c++
4
1 5
314 15
-99 99
123 987
```

**output**
```c++
6
329
0
1110
```

## 2. Simple sort (O(n^2))

Input: standard input

Output: standard output

You are given an array of integers. Your task is to sort them in non-decreasing order.

### Input

The first line of the input contains one integer _n_ (1 ≤ _n_ ≤ 1000) — the number of elements in the array. The second line contains _n_ integers which do not exceed 10^9 by modulo.

### Output

The sole line of the output should contain the same array but in the non-decreasing order. The elements should be separated by space.

### Example

**input**
```c++
10
1 8 2 1 4 7 3 2 3 6
```

**output**
```c++
1 1 2 2 3 3 4 6 7 8 
```

## 3. Merge sort

Input: standard input

Output: standard output

You are given an array of integers. Your task is to sort them in non-decreasing order.

### Input

The first line of the input contains one integer _n_ (1 ≤ _n_ ≤ 100000) — the number of elements in the array. The second line contains _n_ integers which do not exceed 10^9 by modulo.

### Output

The sole line of the output should contain the same array but in the non-decreasing order. The elements should be separated by space.

### Example

**input**
```c++
10
1 8 2 1 4 7 3 2 3 6
```

**output**
```c++
1 1 2 2 3 3 4 6 7 8 
```

## 4. Number of inversions

Input: standard input

Output: standard output

Given an array _A = ⟨a\_1, a\_2, ..., a\_n⟩_ of distinct integers, you have to find the number of pairs of indices (_i, j_) such that _i_ < _j_ and _a\_i_ > _a\_j_.

### Input

The first line of the input contains integer _n_ (1 ≤ _n_ ≤ 500000) — number of elements in array A.

The second line contains the elements of the array _a\_i_ (0 ≤ _a\_i_ ≤ 10^6) separated by space. No two elements of the array coincide.

### Output

Output one integer — the number of inversions in the given array.

### Examples

**input**
```c++
4
1 2 4 5
```

**output**
```c++
0
```

**input**
```c++
4
5 4 2 1
```

**output**
```c++
6
```

## 5. Quick sort

Input: standard input

Output: standard output

You are given an array of integers. Your task is to sort them in non-decreasing order.

### Input

The first line of the input contains one integer _n_ (1 ≤ _n_ ≤ 100000) — the number of elements in the array. The second line contains _n_ integers which do not exceed 10^9 by modulo.

### Output

The sole line of the output should contain the same array but in the non-decreasing order. The elements should be separated by space.

### Example

**input**
```c++
10
1 8 2 1 4 7 3 2 3 6
```

**output**
```c++
1 1 2 2 3 3 4 6 7 8 
```

## 6. "King" sort

Input: standard input

Output: standard output

**WIP**

### Input

**WIP**

### Output

**WIP**

### Examples

**input**
```c++
2
Louis IX
Louis VIII
```

**output**
```c++
Louis VIII
Louis IX
```

**input**
```c++
2
Louis IX
Philippe II
```

**output**
```c++
Louis IX
Philippe II
```

**input**
```c++
2
Philippe II
Philip II
```

**output**
```c++
Philip II
Philippe II
```

### Notes
* Numbers from 1 to 10 have the following roman notations: I, II, III, IV, V, VI, VII, VIII, IX, and X.
* Numbers 20, 30, 40, and 50 have the following roman notations: XX, XXX, XL, and L.
* For other two-digit numbers less than 50 the roman notation can be obtained by concatenating the roman notation of tens and units of the number. For example, 47 = 40 + 7 = "XL" + "VII" = "XLVII".
