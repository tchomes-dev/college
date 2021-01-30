package stack;

/**
 * A {@link LinkedStack} is a generic stack that is implemented using
 * a Linked List structure to allow for unbounded size.
 */
public class LinkedStack<T> {
  public LLNode<T> top;
  public int size;
  /**
   * Remove and return the top element on this stack.
   * If stack is empty, return null (instead of throw exception)
   */
  
  public T pop() {
    if (top == null) {
      return null; 
    }
    T temp = top.info;
    size--;
    top = top.link;
    return temp;
  }

  /**
   * Return the top element of this stack (do not remove the top element).
   * If stack is empty, return null (instead of throw exception)
   */
  public T top() {
    if (top == null) { 
      return null; 
    }
    
    return top.info;
  }

  /**
   * Return true if the stack is empty and false otherwise.
   */
  public boolean isEmpty() {
    return top == null;
  }

  /**
   * Return the number of elements in this stack.
   */
  public int size() {
    return size;
  }

  /**
   * Pushes a new element to the top of this stack.
   */
  public void push(T elem) {
    LLNode<T> newNode = new LLNode<T>(elem);
    newNode.link = top;
    top = newNode;
    size++;
  }

}
