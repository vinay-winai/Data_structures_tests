import java.util.LinkedList;

public class LinkedListSum {
    public static void main(String[] args) {
        LinkedList<Integer> list = createLinkedList(10_000_000);

        long startTime, endTime, duration;

        // Measure the time for the first iteration
        startTime = System.nanoTime();
        long sum = calculateSum(list);
        endTime = System.nanoTime();
        duration = endTime - startTime;
        System.out.println("Sum of all elements in the linked list (iteration 1): " + sum);
        System.out.println("Time taken for the first iteration: " + duration / 1_000_000 + " ms");

        // Measure the time for 100 iterations
        startTime = System.nanoTime();
        for (int i = 0; i < 100; i++) {
            sum = calculateSum(list);
            // System.out.println(sum);
        }
        endTime = System.nanoTime();
        duration = endTime - startTime;
        System.out.println("Time taken for 100 iterations: " + duration / 1_000_000 + " ms");
    }

    private static LinkedList<Integer> createLinkedList(int size) {
        LinkedList<Integer> list = new LinkedList<>();
        for (int i = 1; i <= size; i++) {
            list.add(i);
        }
        return list;
    }

    private static long calculateSum(LinkedList<Integer> list) {
        long sum = 0;
        for (int num : list) {
            sum += num;
        }
        return sum;
    }
}

// Sum of all elements in the linked list (iteration 1): 50000005000000
// Time taken for the first iteration: 75 ms
// Time taken for 100 iterations: 5166 ms