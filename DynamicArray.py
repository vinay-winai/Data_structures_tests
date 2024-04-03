import time
import random
from typing import List
from numba import jit

ARRAY_SIZE = 100_000_000

def delete_by_value(arr: List[int]) -> None:
    index = arr.index(1)
    del arr[index]

def insert_at_first_zero(arr: List[int]) -> None:
    index = arr.index(0)
    arr.insert(index, 1)

def benchmark_lookup_by_value(arr: List[int]) -> None:
    target1 = arr[0]
    target2 = arr[ARRAY_SIZE // 4]
    target3 = arr[ARRAY_SIZE // 2]
    target4 = arr[3 * ARRAY_SIZE // 4]
    target5 = arr[ARRAY_SIZE - 1]

    start = time.perf_counter_ns()
    arr.index(target1)
    arr.index(target2) 
    arr.index(target3) 
    arr.index(target4) 
    arr.index(target5) 

    end = time.perf_counter_ns()
    print(f"Lookup By Value Time: {(end - start) / 1e6}ms")
    print(f"In nanosecs: {end - start}ns\n")

def benchmark_insert(arr: List[int]) -> None:
    arr[0] = 0
    arr[ARRAY_SIZE // 4] = 0
    arr[ARRAY_SIZE // 2] = 0
    arr[3 * ARRAY_SIZE // 4] = 0
    arr[ARRAY_SIZE - 1] = 0
    value_to_insert = 1

    # Insert at beginning
    start = time.perf_counter_ns()
    arr.insert(0, value_to_insert)
    end = time.perf_counter_ns()
    print(f"Insert (Beginning) Time: {(end - start) / 1e6}ms")

    # Insert at q1 
    start = time.perf_counter_ns()
    insert_at_first_zero(arr) 
    end = time.perf_counter_ns()
    print(f"Insert (q1) Time: "
          f"{(end - start) / 1e6}ms")

    # Insert at middle 
    start = time.perf_counter_ns()
    insert_at_first_zero(arr) 
    end = time.perf_counter_ns()
    print(f"Insert (Middle) Time: " 
          f"{(end - start) / 1e6}ms")

    # Insert at q3 
    start = time.perf_counter_ns()
    insert_at_first_zero(arr) 
    end = time.perf_counter_ns()
    print(f"Insert (q3) Time: "
          f"{(end - start) / 1e6}ms")
    # Insert at end
    start = time.perf_counter_ns()
    arr.append(value_to_insert)
    end = time.perf_counter_ns()
    print(f"Insert (End) Time: {end - start}ns")

def benchmark_delete(arr : List[int]) -> None:
    # Delete at beginning
    start = time.perf_counter_ns()
    del arr[0]
    end = time.perf_counter_ns()
    print(f"Delete (Beginning) Time: {(end - start) / 1e6}ms")

     # Delete at q1
    start = time.perf_counter_ns()
    delete_by_value(arr)
    end = time.perf_counter_ns()
    print(f"Delete (q1) Time: " 
          f"{(end - start) / 1e6}ms")

    # Delete at middle
    start = time.perf_counter_ns()
    delete_by_value(arr)
    end = time.perf_counter_ns()
    print(f"Delete (Middle) Time: "
          f"{(end - start) / 1e6}ms") 
    
    # Delete at q3
    start = time.perf_counter_ns()
    delete_by_value(arr)
    end = time.perf_counter_ns()
    print(f"Delete (q3) Time: "
          f"{(end - start) / 1e6}ms")

    # Delete at end
    start = time.perf_counter_ns()
    arr.pop()
    end = time.perf_counter_ns()
    print(f"Delete (End) Time: {end - start}ns\n")

if __name__ == "__main__":
    @jit(nopython=True)  # Numba decorator for the random generation part
    def array_generator(array_size : int) -> List[int]:
        array = [random.randint(2, 2**31 -1) for _ in range(array_size)]
        return array
    start = time.perf_counter_ns()
    array = array_generator(ARRAY_SIZE)
    end = time.perf_counter_ns()
    print(f"Pre-allocate Time: {(end - start)/ 1e9}s")  
    run = 5
    
    
    
    
    
    while run > 0:
        benchmark_lookup_by_value(array)
        benchmark_insert(array)
        benchmark_delete(array)
        
        
        run -= 1


# sequential access
# Memory ~ 4.7GB fixed
# CPU ~ 15% - used all 4 vCPUs


# Lookup By Value Time: 0.0012ms
# In nanosecs: 1200ns
# Pre-allocate Time: 56.4956791s
# Lookup By Value Time: 2319.6686ms
# In nanosecs: 2319668600ns
# Insert (Beginning) Time: 85.3623ms
# Insert (q1) Time: 80.3338ms
# Insert (Middle) Time: 82.7477ms
# Insert (q3) Time: 84.4563ms
# Insert (End) Time: 2900ns
# Delete (Beginning) Time: 48.59ms
# Delete (q1) Time: 48.086ms
# Delete (Middle) Time: 48.4375ms
# Delete (q3) Time: 47.5464ms
# Delete (End) Time: 5200ns
# Insert (Beginning) Time: 88.2901ms
# Insert (q1) Time: 86.3329ms
# Insert (Middle) Time: 83.7199ms
# Insert (q3) Time: 86.7761ms
# Insert (End) Time: 2800ns
# Delete (Beginning) Time: 49.4073ms
# Delete (q1) Time: 49.4448ms
# Delete (Middle) Time: 49.554ms
# Delete (q3) Time: 50.7834ms
# Delete (End) Time: 3300ns

# jit
# Lookup By Value Time: 0.0009ms
# In nanosecs: 900ns
# Pre-allocate Time: 4.0960867s
# Lookup By Value Time: 2732.2539ms
# In nanosecs: 2732253900ns
# Insert (Beginning) Time: 330.1893ms
# Insert (q1) Time: 87.3683ms
# Insert (Middle) Time: 83.7902ms
# Insert (q3) Time: 85.7951ms
# Insert (End) Time: 3100ns
# Delete (Beginning) Time: 53.9158ms
# Delete (q1) Time: 52.6279ms
# Delete (Middle) Time: 59.0801ms
# Delete (q3) Time: 66.343ms
# Delete (End) Time: 1900ns
# Insert (Beginning) Time: 87.9431ms
# Insert (q1) Time: 83.0772ms
# Insert (Middle) Time: 85.4076ms
# Insert (q3) Time: 87.7507ms
# Insert (End) Time: 2600ns
# Delete (Beginning) Time: 54.8807ms
# Delete (q1) Time: 52.0578ms
# Delete (Middle) Time: 51.4013ms
# Delete (q3) Time: 47.9779ms
# Delete (End) Time: 2300ns
