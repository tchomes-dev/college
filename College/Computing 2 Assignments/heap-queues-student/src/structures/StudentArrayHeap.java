package structures;

import java.util.Comparator;

public class StudentArrayHeap<P, V> extends AbstractArrayHeap<P, V> {
  private Comparator<P> comparator = getComparator();

  public StudentArrayHeap(Comparator<P> comparator) {
    super(comparator);
    // TODO Auto-generated constructor stub
  }

  @Override
  protected int getLeftChildOf(int index) {
    // TODO Auto-generated method stub
    if (index < 0) {
      throw new IndexOutOfBoundsException();
    }
    return (2 * index) + 1;
  }

  @Override
  protected int getRightChildOf(int index) {
    // TODO Auto-generated method stub
    if (index < 0) {
      throw new IndexOutOfBoundsException();
    }
    return (2 * index) + 2;
  }

  @Override
  protected int getParentOf(int index) {
    // TODO Auto-generated method stub
    if (index < 1) {
      throw new IndexOutOfBoundsException();
    }
    return (index - 1) / 2;
  }

  @Override
  protected void bubbleUp(int index) {
    // TODO Auto-generated method stub
    Entry<P, V> elem = heap.get(index);
    int parent = (index - 1) / 2;
    while ((index > 0) && comparator.compare(elem.getPriority(), heap.get(parent).getPriority()) > 0) {
      heap.set(index, heap.get(parent));
      index = parent;
      parent = (parent - 1) / 2;
    }
    heap.set(index, elem);
  }

  @Override
  protected void bubbleDown(int index) {
    // TODO Auto-generated method stub
    int largerChild;
    Entry<P, V> elem = heap.get(index);
    while (index < size() / 2) { // has at least 1 child
      int left = 2 * index + 1;
      int right = 2 * index + 2;
      if (right < size() && // right child exists
          comparator.compare(heap.get(left).getPriority(), heap.get(right).getPriority()) < 0) {
        largerChild = right;
      } else {
        largerChild = left;
      }
      if (comparator.compare(elem.getPriority(), heap.get(largerChild).getPriority()) >= 0) {
        break;
      }
      heap.set(index, heap.get(largerChild));
      index = largerChild;
    }
    heap.set(index, elem);
  }
}
