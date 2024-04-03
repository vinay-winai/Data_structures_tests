import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.TimeUnit;

public class DynamicArrayBenchmark {
    static final int ARRAY_SIZE = 100_000_000;
    static Random random = new Random();

    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        ArrayList<Integer> array = new ArrayList<>(ARRAY_SIZE);
        // Fill the array with random integers
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array.add(random.nextInt(Integer.MAX_VALUE - 2) + 2);
        }
        long end = System.currentTimeMillis();
        System.out.println("Pre-allocation Time: " + (end - start) + "ms");
        int run = 2;
        while (run>0){
            benchmarkLookupByValue(array);
            benchmarkInsert(array);
            benchmarkDelete(array);
            run--;
        }
        // Change values to 0
        int insertions = 100;
        start = System.nanoTime();
        int step = array.size() / insertions; 
        for (int i = 0; i < array.size(); i += step) {
            array.set(i, 0);
        } 

        // Insert 1 next to 0s
        for (int i = 0; i < array.size(); ++i) {
            if (array.get(i) == 0) {
                if (i < array.size() - 1) {  
                    array.add(i + 1, 1);
                    ++i;  
                }
            }
        }
        end = System.nanoTime();
        long heavyTime = TimeUnit.NANOSECONDS.toMillis(end - start);
        System.out.println("Heavy Time: " + heavyTime + "ms");

        // Delete # scattered items 
        start = System.nanoTime();
        int deletions = 100;
        while (deletions>0) {
            int index = array.indexOf(1);
            array.remove(index);
            deletions--;
        }
        end = System.nanoTime();
        long heavyDeleteTime = TimeUnit.NANOSECONDS.toMillis(end - start);
        System.out.println("Heavy Delete Time: " + heavyDeleteTime  + "ms");

        // Lookup advanced
        start = System.nanoTime();
        long sum = 0;
        for (int i = 0; i < array.size(); ++i) {
            sum += array.get(i); 
        }
        end = System.nanoTime();
        System.out.println(sum); // Print the sum
        long heavyLookupTime = TimeUnit.NANOSECONDS.toMillis(end - start);
        System.out.println("Heavy Lookup Time: " + heavyLookupTime + "ms");
    }
    
    private static boolean deleteByValue(ArrayList<Integer> array, int item) {
        int index = array.indexOf(item);  // Find the first '1'
        if (index != -1) {
            array.remove(index);
            return true;
        } else {
            return false;
        }
    }

    private static boolean insertAtFirstZero(ArrayList<Integer> array) {
        int index = array.indexOf(0); // Find the first '0'
        if (index != -1) {
            array.add(index, 1);
            return true;
        } else {
            return false;
        }
    }
    
    static void benchmarkLookupByValue(ArrayList<Integer> array) {
        int target1 = array.get(0);
        int target2 = array.get(ARRAY_SIZE / 4);
        int target3 = array.get(ARRAY_SIZE / 2);
        int target4 = array.get(3 * ARRAY_SIZE / 4);
        int target5 = array.get(ARRAY_SIZE - 1);

        long start = System.nanoTime();
        array.indexOf(target1); // Find first
        array.indexOf(target2); // Find Q1
        array.indexOf(target3); // Find Q2
        array.indexOf(target4); // Find Q3
        array.indexOf(target5); // Find last
        long end = System.nanoTime();
        long lookUp = TimeUnit.NANOSECONDS.toMillis(end - start);
        System.out.println("Lookup By Value Time: " + lookUp + "ms");
        System.out.println("Lookup in ns: " + (end - start) + "ns");
    }

    static void benchmarkInsert(ArrayList<Integer> array) {
        array.set(0, 0);
        array.set(ARRAY_SIZE / 4, 0);
        array.set(ARRAY_SIZE / 2, 0);
        array.set(3 * ARRAY_SIZE / 4, 0);
        array.set(ARRAY_SIZE - 1, 0);
        int valueToInsert = 1;

        // Insert at beginning
        long start = System.currentTimeMillis();
        array.add(0, valueToInsert);
        long end = System.currentTimeMillis();
        System.out.println("Insert (Beginning) Time: " + (end - start) + "ms");

        // Insert at q1
        start = System.currentTimeMillis();
        insertAtFirstZero(array);
        end = System.currentTimeMillis();
        System.out.println("Insert (q1) Time: " + (end - start) + "ms");

        // Insert at middle (modify the index if needed)
        start = System.currentTimeMillis();
        insertAtFirstZero(array);
        end = System.currentTimeMillis();
        System.out.println("Insert (Middle) Time: " + (end - start) + "ms"); 
        
        // Insert at q1
        start = System.currentTimeMillis();
        insertAtFirstZero(array);
        end = System.currentTimeMillis();
        System.out.println("Insert (q3) Time: " + (end - start) + "ms");
        
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

        // Delete at q1
        start = System.currentTimeMillis();
        deleteByValue(array,1);
        end = System.currentTimeMillis();
        System.out.println("Delete (q1) Time: " + (end - start) + "ms");
        
        // Delete at middle 
        start = System.currentTimeMillis();
        deleteByValue(array,1);
        end = System.currentTimeMillis();
        System.out.println("Delete (Middle) Time: " + (end - start) + "ms"); 
        
        // Delete at q3
        start = System.currentTimeMillis();
        deleteByValue(array,1);
        end = System.currentTimeMillis();
        System.out.println("Delete (q3) Time: " + (end - start) + "ms");
        
        // Delete at end 
        start = System.nanoTime();
        array.remove(array.size() - 1); 
        end = System.nanoTime();
        long deleteTime = TimeUnit.NANOSECONDS.toMicros(end - start);
        System.out.println("Delete (End) Time: " + deleteTime + "us"); 
    }
}

// Sequential 2 shot 100 mil
// Memory ~ 3GB fixed
// CPU ~ 75% - used all 12 vCPUs
// Pre-allocation Time: 3378ms
// Lookup By Value Time: 577ms
// Lookup in ns: 577878900ns
// Insert (Beginning) Time: 1212ms
// Insert (q1) Time: 88ms
// Insert (Middle) Time: 83ms
// Insert (q3) Time: 88ms
// Insert (End) Time: 6us
// Delete (Beginning) Time: 90ms
// Delete (q1) Time: 89ms
// Delete (Middle) Time: 84ms
// Delete (q3) Time: 96ms
// Delete (End) Time: 7us
// Lookup By Value Time: 0ms
// Lookup in ns: 2800ns
// Insert (Beginning) Time: 91ms
// Insert (q1) Time: 99ms
// Insert (Middle) Time: 96ms
// Insert (q3) Time: 98ms
// Insert (End) Time: 2us
// Delete (Beginning) Time: 89ms
// Delete (q1) Time: 96ms
// Delete (Middle) Time: 96ms
// Delete (q3) Time: 91ms
// Delete (End) Time: 2us
// Heavy Time: 3640ms
// Heavy Delete Time: 9551ms
// 107376563538362572
// Heavy Lookup Time: 125ms


// Sequential 2 shot 10 mil
// Pre-allocation Time: 189ms
// Lookup By Value Time: 45ms
// Lookup in ns: 45029400ns
// Insert (Beginning) Time: 28ms
// Insert (q1) Time: 8ms
// Insert (Middle) Time: 9ms
// Insert (q3) Time: 8ms
// Insert (End) Time: 9us
// Delete (Beginning) Time: 6ms
// Delete (q1) Time: 6ms
// Delete (Middle) Time: 8ms
// Delete (q3) Time: 6ms
// Delete (End) Time: 8us
// Lookup By Value Time: 0ms
// Lookup in ns: 2500ns
// Insert (Beginning) Time: 9ms
// Insert (q1) Time: 11ms
// Insert (Middle) Time: 7ms
// Insert (q3) Time: 8ms
// Insert (End) Time: 7us
// Delete (Beginning) Time: 6ms
// Delete (q1) Time: 6ms
// Delete (Middle) Time: 8ms
// Delete (q3) Time: 9ms
// Delete (End) Time: 2us
// Heavy Time: 178ms
// Heavy Delete Time: 865ms
// 10735875620229077
// Heavy Lookup Time: 17ms