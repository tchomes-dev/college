package structures;

/**
 * A node in a BST.
 * Note that BSTNode MUST implement BSTNodeInterface; removing this will resulit
 * in your program failing to compile for the autograder.
 * 
 * @author liberato
 *
 * @param <T> : generic type.
 */
public class BstNode<T extends Comparable<T>> implements BstNodeInterface<T> {
  private T data;
  private BstNode<T> left;
  private BstNode<T> right;
  private BstNode<T> parent;

  public static final boolean RED   = true;
  public static final boolean BLACK = false;
  private boolean color;

  /** constructor.
   * 
   * @param data : data
   * @param left : left subtree
   * @param right : right subtree
   */
  public BstNode(T data, BstNode<T> left, BstNode<T> right) {
    this.data = data;
    this.left = left;
    this.right = right;
    parent = null;
  }

  /** constructor.
   * 
   * @param data : data
   * @param left : left subtree
   * @param right : right subtree
   */
  public BstNode(T data, BstNode<T> left, BstNode<T> right, boolean color) {
    this.data = data;
    this.left = left;
    this.right = right;
    this.color = color;
    parent = null;
  }

  public T getData() {
    return data;
  }

  public void setData(T data) {
    this.data = data;
  }

  public boolean getColor() {
    return color;
  }

  public void setColor(boolean color) {
    this.color = color;
  }

  public BstNode<T> getLeft() {
    return left;
  }

  public void setLeft(BstNode<T> left) {
    this.left = left;
  }

  public BstNode<T> getRight() {
    return right;
  }

  public void setRight(BstNode<T> right) {
    this.right = right;
  }

  public BstNode<T> getParent() {
    return parent;
  }

  public void setParent(BstNode<T> p) {
    this.parent = p;
  }

  /** print sub-tree.
   * 
   * @param spaces : formatting space
   */
  public void printSubtree(int spaces) {
    if (right != null) {
      right.printSubtree(spaces + 5);
    }
    for (int i = 0; i < spaces; i++) {
      System.out.print(" ");
    }
    System.out.print(data);
    System.out.print('-');
    System.out.println(color);
    if (left != null) {
      left.printSubtree(spaces + 5);
    }
  }
}