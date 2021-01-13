#  Sorting and order statistics

## 1. K-th order statistics

Input: standard input

Output: standard output

The clone battalion is in formation. All the Imperials stood in a row and counted: first, second, third, ..., _n_-th. Each of them is holding a piece of paper with the result of their IQ test. As you know, the result of IQ testing is a number from 1 to 109.

Count Duko approaches the battalion from time to time, swings his sword and makes a request: "If all clones from the _i_-th to the _j_-th are ordered according to the test result, then what value will the clone standing on the _k_-th place have?" — and quickly demands an answer, threatening to waste the entire party. Solve the problem and help the clones survive.

### Input

The first line contains an integer _n_ (1 ≤ _n_ ≤ 1000) — the number of clones.

The second line contains these _n_ integers separated by spaces. The numbers are in the range from 1 to 10^9.

The third line contains an integer _m_ (1 ≤ _m_ ≤ 10^5) — the number of queries.

The rest _m_ lines contain queries in the format "_i j k_". It is guaranteed that the queries are correct, i.e. 1 ≤ _i_ ≤ _j_ ≤ _n_ and in the range from _i_-th to _j_-th element inclusive, there are at least _k_ elements.

### Output

For each query, print a single number — the result of that query.

### Example

**input**
```c++
5
1 3 2 4 5
3
1 3 2
1 5 1
1 5 2
```

**output**
```c++
2
1
2
```

## 2. Counting sort

Input: standard input

Output: standard output

Given a list of _N_ elements that take integer values from 0 to 100, sort this list in non-decreasing order. Output the resulting list.

### Input

The single input line contains _N_ (1 ≤ _N_ ≤ 2 * 10^5) array elements. It is guaranteed that all elements are in the range from 0 to 100.

### Output

Print the sorted array elements.

### Example

**input**
```c++
7 3 4 2 5
```

**output**
```c++
2 3 4 5 7 
```

## 3. Radix sort

Input: standard input

Output: standard output

Given _n_ strings, print their order after _k_ radix sorting phases.

### Input

The first line contains an integer _n_  — the number of strings, _m_ — the length of strings, and _k_ — the number of radix sorting phases (1 ≤ _n_ ≤ 1000, 1 ≤ _k_ ≤ _m_ ≤ 1000). The next _n_ lines contain the strings themselves.

### Output

Print the strings in the order in which they will be after _k_ radix sorting phases.

### Examples

**input**
```c++
3 3 1
bbb
aba
baa
```

**output**
```c++
aba
baa
bbb
```

**input**
```c++
3 3 2
bbb
aba
baa
```

**output**
```c++
baa
aba
bbb
```

**input**
```c++
3 3 3
bbb
aba
baa
```

**output**
```c++
aba
baa
bbb
```

## 4. Anagrams

Input: standard input

Output: standard output

The next day after the party, Gregory decided to give blow his children minds. He took a lot of cards and wrote on each of them one Latin letter in lowercase. After that, he came up with some string and gave the children a task to make as many substrings of that string as possible using cards. Gregory's string consists only of letters of the Latin alphabet in lowercase. You need to determine how many of its substrings can be composed using only the given cards.

Let's write down the letters written on the cards, one after the other. Let Gregory's string be "aaab" and the cards "aba". Then we can make three "a" substrings, one "b", two "aa", one "ab", and one "aab". The substrings "aaa" and "aaab" are not allowed, since there are only two cards with the letter "a".

### Input

The first line contains two integers, _n_ and _m_ (1 ≤ _n_, _m_ ≤ 10^5) — the length of Gregory's string and the length of cards string.

The second line contains Gregory's string _s_ of length _n_. The string consists only of lowercase Latin letters.

The third line contains the cards string _t_ of length _m_. The string consists only of lowercase Latin letters.

### Output

Print the number of substrings in _s_ which can be composed of the letters in _t_.

### Examples

**input**
```c++
4 3
aaab
aba
```

**output**
```c++
8
```

**input**
```c++
7 3
abacaba
abc
```

**output**
```c++
15
```
