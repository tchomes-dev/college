package structures;

import java.util.NoSuchElementException;

/**************************************************************************************
 * NOTE: before starting to code, check support/structures/UnboundedQueueInterface.java
 * for detailed explanation of each interface method, including the parameters, return
 * values, assumptions, and requirements
 ***************************************************************************************/
public class Queue<T> implements UnboundedQueueInterface<T> {

	public Queue() {		
            // TODO 1
    }
	
	public Queue(Queue<T> other) {
            // TODO 2
	}
	
	@Override
	public boolean isEmpty() {
            // TODO 3
            return false;
	}

	@Override
	public int size() {
            // TODO 4
            return 0;
	}

	@Override
	public void enqueue(T element) {
            // TODO 5
	}

	@Override
	public T dequeue() throws NoSuchElementException {
            // TODO 6
            return null;
	}

	@Override
	public T peek() throws NoSuchElementException {
            // TODO 7
            return null;
	}

	
	@Override
	public UnboundedQueueInterface<T> reversed() {
            // TODO 8
            return null;
	}
}

class Node<T> {
	public T data;
	public Node<T> next;
	public Node(T data) { this.data=data;}
	public Node(T data, Node<T> next) {
		this.data = data; this.next=next;
	}
}

