import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.TimeUnit;

public class DynamicArrayBenchmark {
    static final int ARRAY_SIZE = 100_000_000;
    static Random random = new Random();

    public static void main(String[] args) {
        ArrayList<Integer> array = new ArrayList<>(ARRAY_SIZE);

        // Fill the array with random integers
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array.add(random.nextInt());
        }
        int run = 32;
        while (run>0){
            benchmarkLookupByValue(array);
            benchmarkInsert(array);
            benchmarkDelete(array);
        run--;
        }
    }

    static void benchmarkLookupByValue(ArrayList<Integer> array) {
        int target1 = array.get(0);
        int target2 = array.get(ARRAY_SIZE / 4);
        int target3 = array.get(ARRAY_SIZE / 2);
        int target4 = array.get(3 * ARRAY_SIZE / 4);
        int target5 = array.get(ARRAY_SIZE - 1);

        long start = System.currentTimeMillis();
        array.indexOf(target1); // Find first
        array.indexOf(target2); // Find Q1
        array.indexOf(target3); // Find Q2
        array.indexOf(target4); // Find Q3
        array.indexOf(target5); // Find last
        long end = System.currentTimeMillis();
        System.out.println("Lookup By Value Time: " + (end - start) + "ms");
    }

    static void benchmarkInsert(ArrayList<Integer> array) {
        int valueToInsert = random.nextInt();

        // Insert at beginning
        long start = System.currentTimeMillis();
        array.add(0, valueToInsert);
        long end = System.currentTimeMillis();
        System.out.println("Insert (Beginning) Time: " + (end - start) + "ms");

        // Insert at middle (modify the index if needed)
        start = System.currentTimeMillis();
        array.add(ARRAY_SIZE / 2, valueToInsert); 
        end = System.currentTimeMillis();
        System.out.println("Insert (Middle) Time: " + (end - start) + "ms"); 

        // Insert at end
        start = System.nanoTime();
        array.add(valueToInsert); 
        end = System.nanoTime();
        long insetTime = TimeUnit.NANOSECONDS.toMicros(end - start);
        System.out.println("Insert (End) Time: " + insetTime + "us"); 
    }

    static void benchmarkDelete(ArrayList<Integer> array) {
        // Delete at beginning
        long start = System.currentTimeMillis();
        array.remove(0); 
        long end = System.currentTimeMillis();
        System.out.println("Delete (Beginning) Time: " + (end - start) + "ms"); 

        // Delete at middle 
        start = System.currentTimeMillis();
        array.remove(ARRAY_SIZE / 2); 
        end = System.currentTimeMillis();
        System.out.println("Delete (Middle) Time: " + (end - start) + "ms"); 

        // Delete at end 
        start = System.nanoTime();
        array.remove(array.size() - 1); 
        end = System.nanoTime();
        long deleteTime = TimeUnit.NANOSECONDS.toMicros(end - start);
        System.out.println("Delete (End) Time: " + deleteTime + "us"); 
    }
}

// Best
// Memory ~ 3GB fixed
// CPU ~ 40% - used all 12 vCPUs
// Lookup By Value Time: 288ms
// Insert (Beginning) Time: 78ms
// Insert (Middle) Time: 48ms
// Insert (End) Time: 3us
// Delete (Beginning) Time: 90ms
// Delete (Middle) Time: 46ms
// Delete (End) Time: 5us