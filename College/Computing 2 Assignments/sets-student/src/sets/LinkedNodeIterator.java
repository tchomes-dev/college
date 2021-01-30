package sets;

import java.util.Iterator;
import java.util.NoSuchElementException;

class LinkedNodeIterator<E> implements Iterator<E> {
  // TODO (1) define data variables
	LinkedNode<E> head;
	LinkedNode<E> cur;

  // Constructors
  public LinkedNodeIterator(LinkedNode<E> head) {
    // TODO (2) choose appropriate parameters and do the initialization
	  this.head = head;
	  cur = head;
  }

  @Override
  public boolean hasNext() {
    // TODO (3)
	  if (head == null) {
		  return false;
	  }
	  if (cur != null) {
		  return true;
	  }
    return false;
  }

  @Override
  public E next() {
    // TODO (4)
	  if (cur == null) {
		  throw new NoSuchElementException();
	  } else {
		   E thing = cur.getData();
		   cur = cur.getNext();
		   return thing;
		  
	  }
    
  }

  @Override               
  public void remove() {
    // Nothing to change for this method
    throw new UnsupportedOperationException();
  }
}
