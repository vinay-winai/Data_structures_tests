import java.util.Collections;
import java.util.Random;
import java.util.concurrent.TimeUnit;
import java.util.ArrayList;
class arraylists {
    public static void main(String[] args) {
        ArrayList<Integer> data = new ArrayList<>();
        Random random = new Random();

        // Insertion benchmark
        long startInsert = System.nanoTime();
        for (int i = 0; i < 1000000; ++i) {
            int value = random.nextInt();
            int index = Collections.binarySearch(data, value); // Find insertion point
            if (index < 0) index = -(index + 1); // Handle not found case
            data.add(index, value);
        }
        long endInsert = System.nanoTime();

        // Deletion benchmark
        long startDelete = System.nanoTime();
        while (!data.isEmpty()) {
            int index = random.nextInt(data.size());
            data.remove(index);
        }
        long endDelete = System.nanoTime();

        // Print timings
        long insertTime = TimeUnit.NANOSECONDS.toMillis(endInsert - startInsert);
        long deleteTime = TimeUnit.NANOSECONDS.toMillis(endDelete - startDelete);

        System.out.println("Insertion Time: " + insertTime + "ms");
        System.out.println("Deletion Time: " + deleteTime + "ms");
    }
}

