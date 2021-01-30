package structures;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.Iterator;
import java.util.concurrent.TimeUnit;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.Timeout;

public class PublicBinarySearchTreeTest {

  private BstInterface<Integer> emptyTree;
  private BstInterface<String> oneNodeTree;
  private BstInterface<Integer> tree;
  private static final String FOO = "foo";

  @Rule
  public Timeout timeout = new Timeout(1L, TimeUnit.SECONDS);

  /**
   * setting.
   */
  @Before
  public void before() {
    emptyTree = new BinarySearchTree<Integer>();
    oneNodeTree = new BinarySearchTree<String>();
    tree = new BinarySearchTree<Integer>();
    oneNodeTree.add(FOO);
  }

  @Test
  public void testEmpty() {
    assertTrue(emptyTree.isEmpty());
  }

  @Test
  public void testNotEmpty() {
    assertFalse(oneNodeTree.isEmpty());
  }

  @Test
  public void testSize() {
    assertEquals(0, emptyTree.size());
    assertEquals(1, oneNodeTree.size());
  }

  @Test
  public void testContains() {
    assertTrue(oneNodeTree.contains(FOO));
  }

  @Test
  public void testRemove() {
    assertFalse(emptyTree.remove(0));
  }

  @Test
  public void testGet() {
    assertEquals(FOO, oneNodeTree.get(FOO));
  }

  @Test
  public void testAdd() {
    emptyTree.add(1);
    assertFalse(emptyTree.isEmpty());
    assertEquals(1, emptyTree.size());
  }

  @Test
  public void testGetMinimum() {
    assertEquals(null, emptyTree.getMinimum());
  }

  @Test
  public void testGetMaximum() {
    assertEquals(FOO, oneNodeTree.getMaximum());
  }

  @Test
  public void testHeight() {
    assertEquals(-1, emptyTree.height());
    assertEquals(0, oneNodeTree.height());
    tree.add(2);
    tree.add(1);
    tree.add(3);
    assertEquals(1, tree.height());
  }

  @Test
  public void testPreorderIterator() {
    Iterator<String> i = oneNodeTree.preorderIterator();
    while (i.hasNext()) {
      assertEquals(FOO, i.next());
    }
  }

  @Test
  public void testInorderIterator() {
    Iterator<String> i = oneNodeTree.inorderIterator();
    while (i.hasNext()) {
      assertEquals(FOO, i.next());
    }
  }

  @Test
  public void testPostorderIterator() {
    Iterator<Integer> i = emptyTree.postorderIterator();
    assertFalse(i.hasNext());
  }

  @Test
  public void testEquals() {
    BstInterface<String> tree = new BinarySearchTree<String>();
    assertFalse(oneNodeTree.equals(tree));
    tree.add(new String("foo"));
    assertTrue(oneNodeTree.equals(tree));
  }

  @Test
  public void testSameValues() {
    BstInterface<Integer> tree = new BinarySearchTree<Integer>();
    assertTrue(emptyTree.sameValues(tree));

    emptyTree.add(1);
    emptyTree.add(2);

    tree.add(2);
    tree.add(1);

    assertTrue(emptyTree.sameValues(tree));
  }

  @Test
  public void testIsBalanced() {
    // disabled due to late change of isBalanced() specification
    // assertTrue(emptyTree.isBalanced());
    emptyTree.add(1);
    assertTrue(emptyTree.isBalanced());
    emptyTree.add(2);
    assertTrue(emptyTree.isBalanced());
    emptyTree.add(3);
    assertFalse(emptyTree.isBalanced());
  }

  @Test
  public void testBalance() {
    emptyTree.add(2);
    emptyTree.add(3);
    emptyTree.add(5);
    emptyTree.add(6);
    emptyTree.add(7);
    emptyTree.add(8);
    emptyTree.add(9);
    assertFalse(emptyTree.isBalanced());
    emptyTree.balance();
    assertTrue(emptyTree.isBalanced());
  }
}
