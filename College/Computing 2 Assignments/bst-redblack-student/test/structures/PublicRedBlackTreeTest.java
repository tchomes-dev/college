package structures;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.concurrent.TimeUnit;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.Timeout;

public class PublicRedBlackTreeTest {

  private RedBlackTree<Integer> tree;

  @Rule
  public Timeout timeout = new Timeout(1L, TimeUnit.SECONDS);

  @Before
  public void before() {
    tree = new RedBlackTree<Integer>();
  }

  @Test
  public void testAdd() {
    tree.add(0);
    tree.add(1);
    tree.add(2);
    tree.add(3);
    assertEquals(2, tree.height());
    tree.add(4);
    assertEquals(2, tree.height());
  }

}
