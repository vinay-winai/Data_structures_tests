// Dynamic Array
package main

// import (
// 	"bufio"
// 	"fmt"
// 	"os"
// 	"strconv"
// 	"time"
// )

// func main() {
// 	// Read numbers from file
// 	file, err := os.Open("./../numbers.txt")
// 	if err != nil {
// 		fmt.Println("Failed to open file for reading:", err)
// 		return
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	numbers := make([]int, 0)
// 	start := time.Now()
// 	for scanner.Scan() {
// 		num, err := strconv.Atoi(scanner.Text())
// 		if err != nil {
// 			fmt.Println("Error parsing number:", err)
// 			return
// 		}
// 		insert(&numbers, num)
// 	}
// 	if err := scanner.Err(); err != nil {
// 		fmt.Println("Error reading file:", err)
// 		return
// 	}
// 	insertionDuration := time.Since(start).Milliseconds()
// 	fmt.Println("Total time taken to insert", len(numbers), "numbers:", insertionDuration, "ms")

// 	// Read delete values from file
// 	deleteFile, err := os.Open("./../delete.txt")
// 	if err != nil {
// 		fmt.Println("Failed to open delete file for reading:", err)
// 		return
// 	}
// 	defer deleteFile.Close()

// 	scanner = bufio.NewScanner(deleteFile)
// 	start = time.Now()
// 	for scanner.Scan() {
// 		deleteVal, err := strconv.Atoi(scanner.Text())
// 		if err != nil {
// 			fmt.Println("Error parsing delete value:", err)
// 			return
// 		}
// 		delete(&numbers, deleteVal)
// 	}
// 	if err := scanner.Err(); err != nil {
// 		fmt.Println("Error reading delete file:", err)
// 		return
// 	}
// 	deletionDuration := time.Since(start).Milliseconds()
// 	fmt.Println("Deleted,", len(numbers), "numbers left. Time:", deletionDuration, "ms")
// }

// func insert(numbers *[]int, num int) {
// 	for i, v := range *numbers {
// 		if v > num {
// 			*numbers = append((*numbers)[:i], append([]int{num}, (*numbers)[i:]...)...)
// 			return
// 		}
// 	}
// 	*numbers = append(*numbers, num)
// }

// func delete(numbers *[]int, num int) {
// 	for i, v := range *numbers {
// 		if v == num {
// 			*numbers = append((*numbers)[:i], (*numbers)[i+1:]...)
// 			return
// 		}
// 	}
// }

// Total time taken to insert 100000 numbers: 4032 ms
// Deleted, 0 numbers left. Time: 1584 ms

// LinkedList

// import (
// 	"bufio"
// 	"container/list"
// 	"fmt"
// 	"os"
// 	"strconv"
// 	"time"
// )

// func main() {
// 	// Read numbers from file
// 	file, err := os.Open("./../numbers.txt")
// 	if err != nil {
// 		fmt.Println("Failed to open file for reading:", err)
// 		return
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	numbers := list.New()
// 	start := time.Now()
// 	for scanner.Scan() {
// 		num, err := strconv.Atoi(scanner.Text())
// 		if err != nil {
// 			fmt.Println("Error parsing number:", err)
// 			return
// 		}
// 		insertNumber(numbers, num)
// 	}
// 	if err := scanner.Err(); err != nil {
// 		fmt.Println("Error reading file:", err)
// 		return
// 	}
// 	insertionDuration := time.Since(start).Milliseconds()
// 	fmt.Println("Total time taken to insert", numbers.Len(), "numbers:", insertionDuration, "ms")

// 	// Read delete values from file
// 	deleteFile, err := os.Open("../delete.txt")
// 	if err != nil {
// 		fmt.Println("Failed to open delete file for reading:", err)
// 		return
// 	}
// 	defer deleteFile.Close()

// 	scanner = bufio.NewScanner(deleteFile)
// 	start = time.Now()
// 	for scanner.Scan() {
// 		deleteVal, err := strconv.Atoi(scanner.Text())
// 		if err != nil {
// 			fmt.Println("Error parsing delete value:", err)
// 			return
// 		}
// 		deleteNumber(numbers, deleteVal)
// 	}
// 	if err := scanner.Err(); err != nil {
// 		fmt.Println("Error reading delete file:", err)
// 		return
// 	}
// 	deletionDuration := time.Since(start).Milliseconds()
// 	fmt.Println("Deleted,", numbers.Len(), "numbers left. Time:", deletionDuration, "ms")
// }

// func insertNumber(numbers *list.List, num int) {
// 	for e := numbers.Front(); e != nil; e = e.Next() {
// 		if e.Value.(int) > num {
// 			numbers.InsertBefore(num, e)
// 			return
// 		}
// 	}
// 	numbers.PushBack(num)
// }

// func deleteNumber(numbers *list.List, num int) {
// 	for e := numbers.Front(); e != nil; e = e.Next() {
// 		if e.Value.(int) == num {
// 			numbers.Remove(e)
// 			return
// 		}
// 	}
// }

// Total time taken to insert 100000 numbers: 29168 ms 
// Deleted, 0 numbers left. Time: 31609 ms

// Binary Search



// import (
// 	"bufio"
// 	"fmt"
// 	"os"
// 	"sort"
// 	"strconv"
// 	"time"
// )

// func main() {
// 	// Read numbers from file
// 	file, err := os.Open("../numbers.txt")
// 	if err != nil {
// 		fmt.Println("Failed to open file for reading:", err)
// 		return
// 	}
// 	defer file.Close()

// 	scanner := bufio.NewScanner(file)
// 	numbers := make([]int, 0)
// 	start := time.Now()
// 	for scanner.Scan() {
// 		num, err := strconv.Atoi(scanner.Text())
// 		if err != nil {
// 			fmt.Println("Error parsing number:", err)
// 			return
// 		}
// 		i := sort.SearchInts(numbers, num)
// 		numbers = append(numbers, 0)
// 		copy(numbers[i+1:], numbers[i:])
// 		numbers[i] = num
// 	}
// 	if err := scanner.Err(); err != nil {
// 		fmt.Println("Error reading file:", err)
// 		return
// 	}
// 	insertionDuration := time.Since(start).Milliseconds()
// 	fmt.Println("Total time taken to insert", len(numbers), "numbers:", insertionDuration, "ms")

// 	// Read delete values from file
// 	deleteFile, err := os.Open("../delete.txt")
// 	if err != nil {
// 		fmt.Println("Failed to open delete file for reading:", err)
// 		return
// 	}
// 	defer deleteFile.Close()

// 	scanner = bufio.NewScanner(deleteFile)
// 	start = time.Now()
// 	for scanner.Scan() {
// 		deleteVal, err := strconv.Atoi(scanner.Text())
// 		if err != nil {
// 			fmt.Println("Error parsing delete value:", err)
// 			return
// 		}
// 		i := sort.SearchInts(numbers, deleteVal)
// 		if i < len(numbers) && numbers[i] == deleteVal {
// 			numbers = append(numbers[:i], numbers[i+1:]...)
// 		}
// 	}
// 	if err := scanner.Err(); err != nil {
// 		fmt.Println("Error reading delete file:", err)
// 		return
// 	}
// 	deletionDuration := time.Since(start).Milliseconds()
// 	fmt.Println("Deleted,", len(numbers), "numbers left. Time:", deletionDuration, "ms")
// }

// Total time taken to insert 100000 numbers: 296 ms
// Deleted, 0 numbers left. Time: 291 ms
