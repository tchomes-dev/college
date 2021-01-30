package filesystem;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.NoSuchElementException;

import structures.Queue;

/**
 * An iterator to perform a level order traversal of part of a filesystem. A
 * level-order traversal is equivalent to a breadth- first search.
 * 
 * @param <T>
 */
public class LevelOrderIterator<T> extends FileIterator<File> {
  private Queue<File> fileQueue = new Queue<>();
  private File[] onion;

  /**
   * Instantiate a new LevelOrderIterator, rooted at the rootNode.
   * 
   * @param rootNode
   * @throws FileNotFoundException if the rootNode does not exist
   */
  public LevelOrderIterator(File rootNode) throws FileNotFoundException {
    // TODO 1
    if (!rootNode.exists()) {
      throw new FileNotFoundException();
    }
    fileQueue.enqueue(rootNode);

  }

  @Override
  public boolean hasNext() {
    // TODO 2
    if (!fileQueue.isEmpty()) {
      return true;
    }
    return false;
  }

  @Override
  public File next() throws NoSuchElementException {
    // TODO 3
    if (fileQueue.isEmpty()) {
      throw new NoSuchElementException();
    }
    if (fileQueue.peek().isDirectory()) {
      File[] onion2 = fileQueue.peek().listFiles();
      Arrays.sort(onion2);
      for (File ring : onion2) {
        fileQueue.enqueue(ring);
      }
    }
    return fileQueue.dequeue();
  }

  @Override
  public void remove() {
    // Leave this one alone.
    throw new UnsupportedOperationException();
  }

}
