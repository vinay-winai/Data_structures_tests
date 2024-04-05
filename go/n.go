package main

import (
	"container/list"
	"fmt"
	"time"
)

func createLinkedList(size int) *list.List {
	lst := list.New()
	for i := 1; i <= size; i++ {
		lst.PushBack(i)
	}
	return lst
}

func calculateSum(lst *list.List) int64 {
	var sum int64
	for e := lst.Front(); e != nil; e = e.Next() {
		sum += int64(e.Value.(int))
	}
	return sum
}

func main() {
	lst := createLinkedList(10_000_000)

	start := time.Now()
	sum := calculateSum(lst)
	duration := time.Since(start).Milliseconds()
	fmt.Println("Sum of all elements in the linked list (iteration 1):", sum)
	fmt.Println("Time taken for the first iteration:", duration, "ms")

	start = time.Now()
	for i := 0; i < 100; i++ {
		sum = calculateSum(lst)
	}
	duration = time.Since(start).Milliseconds()
	fmt.Println("Time taken for 100 iterations:", duration, "ms")
}


// Sum of all elements in the linked list (iteration 1): 50000005000000        
// Time taken for the first iteration: 33 ms
// Time taken for 100 iterations: 4094 ms