package structures;

interface BstNodeInterface<T extends Comparable<T>> {
  T getData();

  void setData(T data);

  BstNode<T> getLeft();

  void setLeft(BstNode<T> left);

  BstNode<T> getRight();

  void setRight(BstNode<T> right);
}
