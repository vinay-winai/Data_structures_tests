# not verified, gpt generated.
import random
import time

LIST_SIZE = 100_000_000

class Node:
    def __init__(self, val):
        self.val = val
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def append(self, val):
        new_node = Node(val)
        if not self.head:
            self.head = self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node
        self.size += 1

    def insert(self, val, index):
        new_node = Node(val)
        if index == 0:
            new_node.next = self.head
            self.head = new_node
        else:
            curr = self.head
            for _ in range(index - 1):
                curr = curr.next
            new_node.next = curr.next
            curr.next = new_node
        self.size += 1

    def delete(self, index):
        if index == 0:
            self.head = self.head.next
        else:
            curr = self.head
            for _ in range(index - 1):
                curr = curr.next
            curr.next = curr.next.next
        self.size -= 1

    def __len__(self):
        return self.size

    def __iter__(self):
        curr = self.head
        while curr:
            yield curr.val
            curr = curr.next

def benchmark_lookup_by_value(lst):
    it = iter(lst)
    target1 = next(it)
    for _ in range(LIST_SIZE // 4):
        next(it)
    target2 = next(it)
    for _ in range(LIST_SIZE // 4):
        next(it)
    target3 = next(it)
    for _ in range(LIST_SIZE // 4):
        next(it)
    target4 = next(it)
    for _ in range(LIST_SIZE // 4):
        next(it)
    target5 = next(it)

    start = time.perf_counter_ns()
    [value for value in lst if value in (target1, target2, target3, target4, target5)]
    end = time.perf_counter_ns()

    print(f"Lookup By Value Time: {(end - start) // 1_000_000}ms")
    print(f"In nanosecs: {end - start}ns")

def benchmark_insert(lst):
    it = iter(lst)
    next(it)
    lst.insert(0, 0)
    for _ in range(LIST_SIZE // 4 - 1):
        next(it)
    lst.insert(LIST_SIZE // 4 + 1, 0)
    for _ in range(LIST_SIZE // 4):
        next(it)
    lst.insert(LIST_SIZE // 2 + 1, 0)
    for _ in range(LIST_SIZE // 4):
        next(it)
    lst.insert(3 * LIST_SIZE // 4 + 1, 0)
    for _ in range((LIST_SIZE // 4) - 1):
        next(it)
    lst.append(0)
    value_to_insert = 1

    start = time.perf_counter_ns()
    lst.insert(0, value_to_insert)
    end = time.perf_counter_ns()
    print(f"Insert (Beginning) Time: {end - start}ns")

    start = time.perf_counter_ns()
    lst.insert(LIST_SIZE // 4 + 1, value_to_insert)
    end = time.perf_counter_ns()
    print(f"Insert (q1) Time: {(end - start) // 1_000_000}ms")

    start = time.perf_counter_ns()
    lst.insert(LIST_SIZE // 2 + 1, value_to_insert)
    end = time.perf_counter_ns()
    print(f"Insert (Middle) Time: {(end - start) // 1_000_000}ms")

    start = time.perf_counter_ns()
    lst.insert(3 * LIST_SIZE // 4 + 1, value_to_insert)
    end = time.perf_counter_ns()
    print(f"Insert (q3) Time: {(end - start) // 1_000_000}ms")

    start = time.perf_counter_ns()
    lst.append(value_to_insert)
    end = time.perf_counter_ns()
    print(f"Insert (End) Time: {end - start}ns")

def benchmark_delete(lst):
    start = time.perf_counter_ns()
    lst.delete(0)
    end = time.perf_counter_ns()
    print(f"Delete (Beginning) Time: {end - start}ns")

    start = time.perf_counter_ns()
    lst.delete(lst.index(1))
    end = time.perf_counter_ns()
    print(f"Delete (q1) Time: {(end - start) // 1_000_000}ms")

    start = time.perf_counter_ns()
    lst.delete(lst.index(1))
    end = time.perf_counter_ns()
    print(f"Delete (Middle) Time: {(end - start) // 1_000_000}ms")

    start = time.perf_counter_ns()
    lst.delete(lst.index(1))
    end = time.perf_counter_ns()
    print(f"Delete (q3) Time: {(end - start) // 1_000_000}ms")

    start = time.perf_counter_ns()
    lst.delete(len(lst) - 1)
    end = time.perf_counter_ns()
    print(f"Delete (End) Time: {end - start}ns")

def main():
    lst = LinkedList()

    start = time.perf_counter_ns()
    for _ in range(LIST_SIZE):
        lst.append(random.randint(2, 2**31 - 1))
    end = time.perf_counter_ns()
    print(f"Pre-allocate Time: {(end - start) // 1_000_000}ms")

    run = 2
    while run > 0:
        benchmark_lookup_by_value(lst)
        benchmark_insert(lst)
        benchmark_delete(lst)
        run -= 1

    start = time.perf_counter_ns()
    insertions = 100
    step = len(lst) // insertions
    it = iter(lst)
    count = 0
    for val in lst:
        if count % step == 0:
            lst.insert(count, 0)
        count += 1
    for i, val in enumerate(lst):
        if val == 0:
            lst.insert(i + 1, 1)
    end = time.perf_counter_ns()
    print(f"Heavy Time: {(end - start) // 1_000_000}ms")

    start = time.perf_counter_ns()
    deletions = 100
    while deletions > 0:
        lst.delete(lst.index(1))
        deletions -= 1
    end = time.perf_counter_ns()
    print(f"Heavy Delete Time: {(end - start) // 1_000_000}ms")

    start = time.perf_counter_ns()
    sum = 0
    for val in lst:
        sum += val
    end = time.perf_counter_ns()
    print(f"{sum}")
    print(f"Heavy Lookup Time: {(end - start) // 1_000_000}ms")

if __name__ == "__main__":
    main()