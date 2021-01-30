package sorting;

import structures.Queue;

/**
 * A class containing methods to sort queues and merge sorted queues.
 * 
 * "Sorted" means in ascending order: the front of the queue is the smallest
 * element, and the rear of the queue is the largest.
 * 
 * e1 is less than or equal to e2 if and only if (e1.compareTo(e2) <= 0)
 *
 */
public class MergeSorter<T extends Comparable<T>> {
  /**
   * Returns a new queue containing the elements from the input queue in sorted
   * order.
   * 
   * Implement this method recursively:
   * 
   * In the base case, return the queue with no further work.
   *
   * Otherwise:
   * 
   * First, call divide to split the input queue into two smaller output queues.
   * 
   * Then, recursively mergeSort each of these two smaller queues.
   * 
   * Finally, return the result of merging these two queues.
   * 
   * @param queue an input queue
   * @return a sorted copy of the input queue
   */
  public Queue<T> mergeSort(Queue<T> queue) {
    Queue<T> input = new Queue<T>(queue);
    Queue<T> output1 = new Queue<T>(); // output queue 1
    Queue<T> output2 = new Queue<T>(); // output queue 2
    // TODO 1
    if (input.size() != 1 && !input.isEmpty()) {
      divide(input, output1, output2);
      return new Queue<T>(merge(mergeSort(output1), mergeSort(output2)));
    } else {
      return input;
    }
  }

  /**
   * Split elements from the input queue into the output queues, roughly half and
   * half.
   * 
   * @param input   a queue
   * @param output1 a queue into which about half of the elements in input should
   *                go
   * @param output2 a queue into which the other half of the elements in input
   *                should go
   */
  void divide(Queue<T> input, Queue<T> output1, Queue<T> output2) {
    // size is separate as the input.size is dynamic and changes as a dequeue is
    // called on input
    int size = input.size();
    // loop that exits if input is empty to prevent exceptions and determines which
    // output queue to enqueue from the first element in input
    for (int i = 0; i < size; i++) {
      if (!input.isEmpty()) {
        if (i < (size / 2)) {
          output1.enqueue(input.dequeue());
        } else {
          output2.enqueue(input.dequeue());
        }
      } else {
        break;
      }
    }
  }

  /**
   * Merge sorted input queues into an output queue in sorted order, and returns
   * that queue. To do so: while there are still elements in at least one of the
   * input queues, compare the front elements and pick the smaller among the two,
   * dequeue it, and enqueue it to the output queue. Remember, the Queue class has
   * a peek method which allows you to check the front element without removing
   * it.
   * 
   * @param input1 a sorted queue
   * @param input2 a sorted queue
   * @return a sorted queue consisting of all elements from input1 and input2
   */
  Queue<T> merge(Queue<T> input1, Queue<T> input2) {
    Queue<T> output = new Queue<T>();
    // assumes input1 and input 2 are not empty and compares the first elements of
    // the two queues and inserts the lower valued element to an output queue
    while (!input1.isEmpty() && !input2.isEmpty()) {
      if (input1.peek().compareTo(input2.peek()) <= 0) {
        output.enqueue(input1.dequeue());
      } else {
        output.enqueue(input2.dequeue());
      }
    }
    // if one of the input queues are empty, below will determine what input queue
    // to dequeue from without throwing an exception
    while (!input1.isEmpty()) {
      output.enqueue(input1.dequeue());
    }
    while (!input2.isEmpty()) {
      output.enqueue(input2.dequeue());
    }
    return output;
  }
}
