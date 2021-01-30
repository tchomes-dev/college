package structures;

import java.util.Iterator;

public class RecursiveList<T> implements ListInterface<T> {
  private Node<T> head;
  private Node<T> tail = head;
  private int numElements = 0;

  @Override
  public int size() {
    return numElements;
  }

  @Override
  public Iterator<T> iterator() {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public ListInterface<T> insertFirst(T elem) throws NullPointerException {
    if (elem == null) {
      throw new NullPointerException();
    }
    if (isEmpty()) {
      head = new Node<T>(elem, null);
      tail = head;
    } else {
      Node<T> newNode = new Node<T>(elem, head);
      head = newNode;
    }
    numElements++;
    return this;
  }

  @Override
  public ListInterface<T> insertLast(T elem) throws NullPointerException {
    if (elem == null) {
      throw new NullPointerException();
    }
    if (isEmpty()) {
      head = new Node<T>(elem, null);
      tail = head;
    } else {
      tail.next = new Node<T>(elem, null);
      tail = tail.next;
    }
    numElements++;
    return this;
  }

  @Override
  public ListInterface<T> insertAt(int index, T elem) throws NullPointerException, IndexOutOfBoundsException {
    // TODO Auto-generated method stub
    if (elem == null) {
      throw new NullPointerException();
    }
    if (index < 0 || index > size()) {
      throw new IndexOutOfBoundsException();
    }
    Node<T> curr = head;
    Node<T> prev = null;
    insertAt(index, elem, curr, prev, 0);
    return this;
  }

  public void insertAt(int index, T elem, Node<T> curr, Node<T> prev, int pointer) {
    if (pointer != index) {
      insertAt(index, elem, curr.next, prev = curr, pointer += 1);
    } else {
      Node<T> newNode = new Node<>(elem, null);
      if (prev == null) {
        insertFirst(elem);
      } else {
        if (curr == null) {
          insertLast(elem);
        } else {
          newNode.next = curr;
          prev.next = newNode;
          numElements++;
        }
      }
      return;
    }
  }

  @Override
  public T removeFirst() throws IllegalStateException {
    if (isEmpty()) {
      throw new IllegalStateException();
    }
    T temp = head.data;
    head = head.next;
    numElements--;
    return temp;
  }

  @Override
  public T removeLast() throws IllegalStateException {
    // TODO Auto-generated method stub
    if (isEmpty()) {
      throw new IllegalStateException();
    }
    T temp = tail.data;
    Node<T> curr = head;
    Node<T> prev = null;
    removeLast(curr, prev);
    return temp;
  }

  public void removeLast(Node<T> curr, Node<T> prev) {
    if (curr.next != null) {
      removeLast(curr.next, prev = curr);
    } else {
      if (prev == null) {
        head = head.next;
        tail = head;
      } else {
        tail = prev;
        prev.next = null;
      }
      numElements--;
    }
  }

  @Override
  public T removeAt(int i) throws IndexOutOfBoundsException {
    // TODO Auto-generated method stub
    if (i < 0 || i >= size()) {
      throw new IndexOutOfBoundsException();
    }
    Node<T> curr = head;
    Node<T> prev = null;
    return removeAt(i, curr, prev, 0);
  }

  public T removeAt(int index, Node<T> curr, Node<T> prev, int pointer) {
    T temp = curr.data;
    if (index != pointer) {
      temp = removeAt(index, curr.next, prev = curr, pointer += 1);
    } else {
      if (prev == null) {
        removeFirst();
      } else {
        if (curr.next == null) {
          removeLast();
        } else {
          prev.next = curr.next;
          numElements--;
        }
      }
    }
    return temp;
  }

  @Override
  public T getFirst() throws IllegalStateException {
    if (isEmpty()) {
      throw new IllegalStateException();
    }
    return head.data;
  }

  @Override
  public T getLast() throws IllegalStateException {
    if (isEmpty()) {
      throw new IllegalStateException();
    }
    return tail.data;
  }

  @Override
  public T get(int i) throws IndexOutOfBoundsException {
    if (i < 0 || i >= size()) {
      throw new IndexOutOfBoundsException();
    }
    Node<T> curr = head;
    return get(i, curr, 0);
  }

  public T get(int i, Node<T> curr, int pointer) {
    if (pointer == i) {
      return curr.data;
    }
    return get(i, curr.next, pointer += 1);
  }

  @Override
  public boolean remove(T elem) throws NullPointerException {
    // TODO Auto-generated method stub
    if (elem == null) {
      throw new NullPointerException();
    }
    Node<T> curr = head;
    Node<T> prev = null;
    return remove(elem, curr, prev);
  }

  public boolean remove(T elem, Node<T> curr, Node<T> prev) {
    if (curr != null) {
      if (curr.data.equals(elem)) {
        if (prev == null) {
          head = head.next;
          numElements--;
        } else {
          if (curr.next == null) {
            removeLast();
          } else {
            prev.next = curr.next;
            numElements--;
          }
        }
        return true;
      } else {
        remove(elem, curr.next, prev = curr);
      }
    }
    return (curr != null);
  }

  @Override
  public int indexOf(T elem) throws NullPointerException {
    // TODO Auto-generated method stub
    if (elem == null) {
      throw new NullPointerException();
    }
    Node<T> curr = head;
    return indexOf(elem, 0, curr);
  }

  public int indexOf(T elem, int pointer, Node<T> curr) {
    if (curr != null) {
      if (curr.data.equals(elem)) {
        return pointer;
      }
      return indexOf(elem, pointer += 1, curr.next);
    }
    return -1;
  }

  @Override
  public boolean isEmpty() {
    // TODO Auto-generated method stub
    return head == null;
  }

  class Node<T> {
    public T data;
    public Node<T> next;

    public Node(T data) {
      this.data = data;
    }

    public Node(T data, Node<T> next) {
      this.data = data;
      this.next = next;
    }
  }

}
