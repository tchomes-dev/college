package structures;

public class RedBlackTree<T extends Comparable<T>> extends BinarySearchTree<T> {

  /** 
   * printTree.
   */
  public void printTree() {
    System.out.println("------------------------");
    if (root != null) {
      root.printSubtree(0);
    }
  }

  private boolean isRed(BstNode<T> node) {
    if (node == null) {
      return false;
    }
    return node.getColor() == BstNode.RED;
  }

  private boolean isBlack(BstNode<T> node) {
    if (node == null) {
      return false;
    }
    return node.getColor() == BstNode.BLACK;
  }

  private void rotateLeft(BstNode<T> node) {
    BstNode<T> r = node.getRight();
    node.setRight(r.getLeft());

    if (r.getLeft() != null) {
      r.getLeft().setParent(node);
    }
    r.setParent(node.getParent());
    if (node.getParent() == null) {
      this.root = r;
    } else {
      if (node.getParent().getLeft() == node) {
        node.getParent().setLeft(r);
      } else {
        node.getParent().setRight(r);
      }
    }

    r.setLeft(node);
    node.setParent(r);
  }

  private void rotateRight(BstNode<T> node) {
    BstNode<T> l = node.getLeft();
    node.setLeft(l.getRight());

    if (l.getRight() != null) {
      l.getRight().setParent(node);
    }
    l.setParent(node.getParent());
    if (node.getParent() == null) {
      this.root = l;
    } else {
      if (node == node.getParent().getRight()) {
        node.getParent().setRight(l);
      } else {
        node.getParent().setLeft(l);
      }
    }

    l.setRight(node);
    node.setParent(l);
  }

  // After inserting node, color it red and check BST property as followed,
  // 1. If node is root, make it black.
  // 2. if parent node is black, do nothing.
  // 3. if parent node is red, keep doing recursively for BST property by following,
  //   3.1 If uncle is RED, set color properly based on the instruction. 
  //       Then check for BST property on grandparent node.
  //   3.2 If uncle is black, and node is inside node, 
  //       do rotation on parent node to make a outside node case.
  //       If target node is the right child of parent node and 
  //       parent node is the left child of grandparent node, do left rotation.
  //       If target node is the left child of parent node and 
  //       parent node is the right child of grandparent node, do right rotation.
  //       After the rotation, checking for BST property on parent node.
  //   3.3 If uncle is black, and node is outside node, 
  //       make parent black and grandparent red,
  //       then do rotation on grandparent node.
  //       If target node is the right child of parent node and 
  //       parent node is the right child of grandparent node, do left rotation.
  //       If target node is the left child of parent node and 
  //       parent node is the left child of grandparent node, do right rotation.
  // HINT: It's helpful if you build getGrandparent and getUncle method first
  @Override
  public void add(T t) {


    // TODO
  }
}
