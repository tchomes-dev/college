package structures;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Before;
import org.junit.Test;

public class PublicListInterfaceTest {

  private ListInterface<String> list;

  @Before
  public void setup() {
    list = new RecursiveList<String>();
  }

  @Test(timeout = 500)
  public void testInsertFirstIsEmptySizeAndGetFirst1() {
    assertTrue("Newly constructed list should be empty.", list.isEmpty());
    assertEquals("Newly constructed list should be size 0.", 0, list.size());
    assertEquals("Insert First should return instance of self", list, list.insertFirst("hello"));
    assertFalse("List should now have elements.", list.isEmpty());
    assertEquals("List should now have 1 element.", 1, list.size());
    assertEquals("First element should .equals \"hello\".", "hello", list.getFirst());
    list.insertFirst("world");
    assertEquals(2, list.size());
    list.insertFirst("foo");
    assertEquals(3, list.size());
    assertEquals("First element should .equals \"foo\".", "foo", list.getFirst());
  }

  @Test
  public void testInsertLastRemoveAt() {
    assertTrue("Newly constructed list should be empty.", list.isEmpty());
    assertEquals("Newly constructed list should be size 0.", 0, list.size());
    assertEquals("Insert First should return instance of self", list, list.insertFirst("hello"));
    assertFalse("List should now have elements.", list.isEmpty());
    assertEquals("List should now have 1 element.", 1, list.size());
    assertEquals("First element should .equals \"hello\".", "hello", list.getFirst());
    list.insertFirst("world");
    assertEquals(2, list.size());
    list.insertFirst("foo");
    assertEquals(3, list.size());
    list.insertLast("frank");
    assertEquals(4, list.size());
    list.removeFirst();
    assertEquals(3, list.size());
    list.insertAt(1, "god");
    assertEquals("Index at 1 should .equals \"god\".", "god", list.get(1));
    assertEquals("First element should .equals \"world\".", "world", list.getFirst());
    assertEquals("Should return world", "world", list.removeAt(0));
    list.insertFirst("world");
    list.remove("god");
    assertEquals("Index 1 should equal hello", "hello", list.get(1));
    assertEquals("Index of world should be 0", 0, list.indexOf("world"));

  }

  @Test
  public void testInsertLastRemoveLastandIsEmpty() {
    list.insertAt(0, "1"); // 1
    assertEquals("1", list.get(0));
    assertEquals(1, list.size());
    list.insertAt(0, "2"); // 2,1
    assertEquals("2", list.getFirst());
    assertEquals(2, list.size());
    list.removeAt(0); // 1
    assertEquals("1", list.get(0));
    assertEquals(1, list.size());
    list.removeLast(); //
    assertEquals(true, list.isEmpty());
    list.insertAt(0, "1"); // 1
    assertEquals("1", list.get(0));
    assertEquals(1, list.size());
    list.insertAt(0, "2"); // 2, 1
    assertEquals("2", list.getFirst());
    assertEquals(2, list.size());
    list.removeFirst(); // 1
    assertEquals("1", list.getFirst());
    assertEquals(1, list.size());
    list.insertAt(1, "fri"); // 1 , fri
    assertEquals("fri", list.get(1));
    assertEquals(2, list.size());
    list.insertFirst("first"); // first , 1, fri
    assertEquals("fri", list.get(2));
    list.insertLast("last"); // first, 1, fri, last
    assertEquals("last", list.getLast());
    assertEquals(4, list.size());
    list.removeAt(1);
    assertEquals(3, list.size());
    assertEquals("fri", list.get(1));
  }

  @Test
  public void testInsertAt() {
    list.insertFirst("three");
    list.insertFirst("one");
    list.insertAt(1, "two");
    assertEquals("one", list.getFirst());
    assertEquals("three", list.getLast());
  }

  @Test
  public void testInsertLast() {
    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    assertEquals("one", list.getFirst());
    assertEquals("three", list.getLast());
  }

  @Test
  public void testRemoveFirst() {
    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    assertEquals("one", list.removeFirst());
  }

  @Test
  public void testRemoveAt() {
    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    assertEquals("two", list.removeAt(1));
  }

  @Test
  public void testRemoveLast() {
    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    assertEquals("three", list.removeLast());
  }

  @Test
  public void testGetAt() {
    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    assertEquals("three", list.get(2));
  }

  @Test
  public void testRemoveData() {
    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    assertEquals(true, list.remove("three"));
  }

  @Test
  public void testIndexOf() {
    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    assertEquals(2, list.indexOf("three"));
  }

  @Test
  public void testIndexOf2() {
    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    assertEquals(0, list.indexOf("one"));
  }

  @Test
  public void testRemoveAndIndex() {
    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    assertEquals(true, list.remove("two"));
    assertEquals(1, list.indexOf("three"));

  }

  @Test
  public void mytestInsertsRemoveAndIndexOf() {
    list.insertFirst("foo");
    assertEquals("foo is index 0", 0, list.indexOf("foo"));
    list.insertFirst("bar");
    assertEquals("bar is index 0", 0, list.indexOf("bar"));
    assertEquals(true, list.remove("bar"));
    assertEquals("foo is index 0", 0, list.indexOf("foo"));

  }

  @Test(expected = IndexOutOfBoundsException.class)
  public void testExceptions() {

    list.insertFirst("two");
    list.insertFirst("one");
    list.insertLast("three");
    list.insertAt(-1, "foobar");
  }
}
