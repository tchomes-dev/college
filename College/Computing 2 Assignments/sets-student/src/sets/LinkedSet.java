package sets;

import java.util.Iterator;

/**
 * A LinkedList-based implementation of Set
 */

/********************************************************
 * NOTE: Before you start, check the Set interface in
 * Set.java for detailed description of each method.
 *******************************************************/

/********************************************************
 * NOTE: for this project you must use linked lists
 * implemented by yourself. You are NOT ALLOWED to use
 * Java arrays of any type, or any Collection-based class 
 * such as ArrayList, Vector etc. You will receive a 0
 * if you use any of them.
 *******************************************************/ 

/********************************************************
 * NOTE: you are allowed to add new methods if necessary,
 * but do NOT add new files (as they will be ignored).
 *******************************************************/

public class LinkedSet<E> implements Set<E> {
  private LinkedNode<E> head = null;
  private LinkedNode<E> tail = null;
  private Iterator<E> iter = iterator();

  // Constructors
  public LinkedSet() {
  }

  public LinkedSet(E e) {
    this.head = new LinkedNode<E>(e, null);
  }

  private LinkedSet(LinkedNode<E> head) {
    this.head = head;
  }

  @Override
  public int size() {
	int size = 0;
	for (E item : this) {
		size++;
	}
    return size;
  }

  @Override
  public boolean isEmpty() {
	  if (head == null) {
		  return true;
	  }
    return false;
  }

  @Override
  public Iterator<E> iterator() {
    return new LinkedNodeIterator<E>(this.head);
  }

  @Override
  public boolean contains(Object o) {
	  for (E item : this) {
		  if (item.equals(o)) return true;
	  }
    return false;
  }

  @Override
  public boolean isSubset(Set<E> that) {
	  for (E item : this) {
		  if (!that.contains(item)) return false;
	  }
    return true;
  }

  @Override
  public boolean isSuperset(Set<E> that) {
	  for (E item : that) {
		  if (!this.contains(item)) return false;
	  }
    return true;
  }

  @Override
  public Set<E> adjoin(E e) {
	  LinkedSet<E> newSet = new LinkedSet<>(head);
	  LinkedNode<E> input = new LinkedNode<>(e, head);
	  newSet.head = input;
	return newSet;
  }

  @Override
  public Set<E> union(Set<E> that) {
	  LinkedSet<E> newSet = new LinkedSet<>();
	  for (E item : that) {
		  if (!this.contains(item)) {
			  newSet.adjoin(item);
		  }
	  }
    return newSet;
  }

  @Override
  public Set<E> intersect(Set<E> that) {
	  LinkedSet<E> newSet = new LinkedSet<>();
	   for (E item : that) {
		   if (this.contains(item)) {
			   newSet.adjoin(item);
		   }
	   }
    return newSet;
  }

  @Override
  public Set<E> subtract(Set<E> that) {
	  LinkedSet<E> newSet = new LinkedSet<>();
	  for (E item : this) {
		  if (!that.contains(item)) {
			  newSet.adjoin(item);
		  }
	  }
    return newSet;
  }

  @Override
  public Set<E> remove(E e) {
	  LinkedSet<E> newSet = new LinkedSet<>();
	  
	  for (E item : this) {
		  if (item != e) {
			  newSet.adjoin(item);
		  }
	  }
    return newSet;
  }

  @Override
  @SuppressWarnings("unchecked")
  public boolean equals(Object o) {
    if (! (o instanceof Set)) {
      return false;
    }
    Set<E> that = (Set<E>)o;
    return this.isSubset(that) && that.isSubset(this);
  }

  @Override
  public int hashCode() {
    int result = 0;
    for (E e : this) {
      result += e.hashCode();
    }
    return result;
  }
}
