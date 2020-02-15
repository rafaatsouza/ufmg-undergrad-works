# AEDS (Algorithms and data structure) II - 3rd Assignment

Practical assignment that consists in a module of array sorting algorithm's. You can choose the algorithm and the element quantity to be sorted. At the end, it shows the time wasted with sorting, and the movements and comparison quantities.

#### Build
Generates executable file using *Makefile*.

### Instructions

When executing, inform parameters:

**1 - Sort algorithm type:**
 * bol – BubbleSort
* sel – Seleção
* ins – Inserção
* she – ShellSort
* qui – QuickSort
* hea – HeapSort
* mer – MergeSort
* rad – RadixSort

**2 - Elements quantity**

**3 - Initial array sort:**
* asc – Already ordered
* desc – Inversed ordered
* ale –  Randomly
* qasc – 90% ordered, 10% randomly

**4 - "-P" flag in order to show arrays**

Example: 
```
./tp2.out she 10 ale -P
```
Reorders random array containing 10 elements using *ShellSort*, and showing array at screen.
