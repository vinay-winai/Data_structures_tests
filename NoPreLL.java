import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;

public class NoPreLL {
    public static void main(String[] args) {
        try {
            // Read numbers from file and insert into linked list
            BufferedReader numbersFile = new BufferedReader(new FileReader("numbers.txt"));
            LinkedList<Integer> numbers = new LinkedList<>();
            long startTime = System.nanoTime();
            String line;
            while ((line = numbersFile.readLine()) != null) {
                int num = Integer.parseInt(line);
                int index = 0;
                for (Integer n : numbers) {
                    if (n >= num) {
                        break;
                    }
                    index++;
                }
                numbers.add(index, num);
            }
            numbersFile.close();
            long endTime = System.nanoTime();
            long duration = (endTime - startTime) / 1000000;
            System.out.println("Total time taken to insert " + numbers.size() + " numbers: " + duration + " ms");

            // Delete elements from linked list by value
            BufferedReader deleteFile = new BufferedReader(new FileReader("delete.txt"));
            startTime = System.nanoTime();
            while ((line = deleteFile.readLine()) != null) {
                int idx = numbers.indexOf(Integer.parseInt(line));
                numbers.remove(idx);
            }
            deleteFile.close();
            endTime = System.nanoTime();
            duration = (endTime - startTime) / 1000000;
            System.out.println("Deleted, " + numbers.size() + " numbers left. Time: " + duration + " ms");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

// Results 100k
// best after jit warm-up
// Total time taken to insert 100000 numbers: 68827 ms
// Deleted, 0 numbers left. Time: 70944 ms
// avg
// Total time taken to insert 100000 numbers: 78942 ms     
// Deleted, 0 numbers left. Time: 86152 ms