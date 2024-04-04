import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Random;

public class ll_benchmark {
    private static final int LIST_SIZE = 100_000_000;

    public static void benchmarkLookupByValue(LinkedList<Integer> lst) {
        ListIterator<Integer> it = lst.listIterator();
        int target1 = it.next();
        for (int i = 0; i < LIST_SIZE / 4 - 1; i++) {
            it.next();
        }
        int target2 = it.next();
        for (int i = 0; i < LIST_SIZE / 4 - 1; i++) {
            it.next();
        }
        int target3 = it.next();
        for (int i = 0; i < LIST_SIZE / 4 - 1; i++) {
            it.next();
        }
        int target4 = it.next();
        for (int i = 0; i < LIST_SIZE / 4 - 2; i++) {
            it.next();
        }
        int target5 = it.next();

        long start = System.nanoTime();
        lst.indexOf(target1);
        lst.indexOf(target2);
        lst.indexOf(target3);
        lst.indexOf(target4);
        lst.indexOf(target5);
        long end = System.nanoTime();

        System.out.println("Lookup By Value Time: " + (end - start) / 1_000_000 + "ms");
        System.out.println("In nanosecs: " + (end - start) + "ns");
    }

    public static void benchmarkInsert(LinkedList<Integer> lst) {
        ListIterator<Integer> it = lst.listIterator();
        int valueToInsert = 1;
        
        long start = System.nanoTime();
        lst.addFirst(valueToInsert);
        long end = System.nanoTime();
        System.out.println("Insert (Beginning) Time: " + (end - start) + "ns");

        start = System.nanoTime();
        it = lst.listIterator(LIST_SIZE / 4);
        it.next();
        it.add(valueToInsert);
        end = System.nanoTime();
        System.out.println("Insert (q1) Time: " + (end - start) / 1_000_000 + "ms");

        start = System.nanoTime();
        it = lst.listIterator(LIST_SIZE / 2);
        it.next();
        it.add(valueToInsert);
        end = System.nanoTime();
        System.out.println("Insert (Middle) Time: " + (end - start) / 1_000_000 + "ms");

        start = System.nanoTime();
        it = lst.listIterator(3 * LIST_SIZE / 4);
        it.next();
        it.add(valueToInsert);
        end = System.nanoTime();
        System.out.println("Insert (q3) Time: " + (end - start) / 1_000_000 + "ms");

        start = System.nanoTime();
        lst.addLast(valueToInsert);
        end = System.nanoTime();
        System.out.println("Insert (End) Time: " + (end - start) + "ns");
    }

    public static void benchmarkDelete(LinkedList<Integer> lst) {
        long start = System.nanoTime();
        lst.removeFirst();
        long end = System.nanoTime();
        System.out.println("Delete (Beginning) Time: " + (end - start) + "ns");

        start = System.nanoTime();
        int index = lst.indexOf(1);
        lst.remove(index);
        end = System.nanoTime();
        System.out.println("Delete (q1) Time: " + (end - start) / 1_000_000 + "ms");

        start = System.nanoTime();
        index = lst.indexOf(1);
        lst.remove(index);
        end = System.nanoTime();
        System.out.println("Delete (Middle) Time: " + (end - start) / 1_000_000 + "ms");

        start = System.nanoTime();
        index = lst.indexOf(1);
        lst.remove(index);
        end = System.nanoTime();
        System.out.println("Delete (q3) Time: " + (end - start) / 1_000_000 + "ms");

        start = System.nanoTime();
        lst.removeLast();
        end = System.nanoTime();
        System.out.println("Delete (End) Time: " + (end - start) + "ns");
    }

    public static void main(String[] args) {
        Random random = new Random();
        LinkedList<Integer> lst = new LinkedList<>();

        long start = System.nanoTime();
        for (int i = 0; i < LIST_SIZE; i++) {
            lst.add(random.nextInt(Integer.MAX_VALUE - 2) + 2);
        }
        long end = System.nanoTime();
        System.out.println("Pre-allocate Time: " + (end - start) / 1_000_000 + "ms");

        int run = 2;
        while (run > 0) {
            benchmarkLookupByValue(lst);
            benchmarkInsert(lst);
            benchmarkDelete(lst);
            run--;
        }

        start = System.nanoTime();
        int insertions = 100;
        int step = lst.size() / insertions;
        ListIterator<Integer> it = lst.listIterator();
        int count = 0;
        while (it.hasNext()) {
            it.next();
            if (count % step == 0) {
                it.set(0);
            }
            count++;
        }

        // Insert 1s after the 0s
        it = lst.listIterator();
        while (it.hasNext()) {
            int value = it.next();
            if (value == 0) {
                it.add(1);
            }
        }
        end = System.nanoTime();
        System.out.println("Heavy Time: " + (end - start) / 1_000_000 + "ms");

        start = System.nanoTime();
        int deletions = 100;
        while (deletions > 0) {
            int index = lst.indexOf(1);
            lst.remove(index);
            deletions--;
        }
        end = System.nanoTime();
        System.out.println("Heavy Delete Time: " + (end - start) / 1_000_000 + "ms");

        start = System.nanoTime();
        long sum = 0;
        for (Integer value : lst) {
            sum += value;
        }
        end = System.nanoTime();
        System.out.println(sum);
        System.out.println("Heavy Lookup Time: " + (end - start) / 1_000_000 + "ms");
    }
}

// Sequential 2 shot 100 mil
// Memory 4.5GB 
// CPU MAX~ 86%
// Pre-allocate Time: 29904ms
// Lookup By Value Time: 1552ms
// In nanosecs: 1552128500ns
// Insert (Beginning) Time: 52800ns
// Insert (q1) Time: 164ms
// Insert (Middle) Time: 326ms
// Insert (q3) Time: 143ms
// Insert (End) Time: 9100ns
// Delete (Beginning) Time: 5100ns
// Delete (q1) Time: 314ms
// Delete (Middle) Time: 637ms
// Delete (q3) Time: 604ms
// Delete (End) Time: 21200ns
// Lookup By Value Time: 1543ms
// In nanosecs: 1543066000ns
// Insert (Beginning) Time: 2200ns
// Insert (q1) Time: 164ms
// Insert (Middle) Time: 324ms
// Insert (q3) Time: 142ms
// Insert (End) Time: 1000ns
// Delete (Beginning) Time: 1200ns
// Delete (q1) Time: 316ms
// Delete (Middle) Time: 639ms
// Delete (q3) Time: 605ms
// Delete (End) Time: 1200ns
// Heavy Time: 1579ms
// Heavy Delete Time: 46175ms
// 107380387961924400
// Heavy Lookup Time: 775ms

// Sequential 2 shot 10 mil
// Pre-allocate Time: 2321ms
// Lookup By Value Time: 150ms
// In nanosecs: 150937100ns
// Insert (Beginning) Time: 47400ns
// Insert (q1) Time: 18ms
// Insert (Middle) Time: 35ms
// Insert (q3) Time: 14ms
// Insert (End) Time: 13600ns
// Delete (Beginning) Time: 6000ns
// Delete (q1) Time: 48ms
// Delete (Middle) Time: 64ms
// Delete (q3) Time: 55ms
// Delete (End) Time: 20900ns
// Lookup By Value Time: 160ms
// In nanosecs: 160693700ns
// Insert (Beginning) Time: 3700ns
// Insert (q1) Time: 19ms
// Insert (Middle) Time: 37ms
// Insert (q3) Time: 10ms
// Insert (End) Time: 3400ns
// Delete (Beginning) Time: 1100ns
// Delete (q1) Time: 37ms
// Delete (Middle) Time: 67ms
// Delete (q3) Time: 64ms
// Delete (End) Time: 1500ns
// Heavy Time: 153ms
// Heavy Delete Time: 4265ms
// 10739913489293855
// Heavy Lookup Time: 73ms