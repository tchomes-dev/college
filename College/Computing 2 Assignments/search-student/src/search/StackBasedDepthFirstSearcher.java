package search;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

/**
 * An implementation of a Searcher that performs an iterative search, storing
 * the list of next states in a Stack. This results in a depth-first search.
 * 
 */
public class StackBasedDepthFirstSearcher<T> extends Searcher<T> {
  /**
   * StackBasedDepthFirstSearcher.
   * 
   * @param searchProblem : search problem
   */
  public StackBasedDepthFirstSearcher(SearchProblem<T> searchProblem) {
    super(searchProblem);
  }

  @Override
  public List<T> findSolution() {
    // TODO
    if (solution != null) {
      return solution;
    }
    final List<T> path = new ArrayList<T>();
    Stack<T> stack = new Stack<>();
    T state = searchProblem.getInitialState();
    visited.add(state);
    stack.push(state);
    while (!stack.isEmpty()) {
      T s = stack.pop();
      path.add(s);
      for (T successor : searchProblem.getSuccessors(s)) {
        if (!visited.contains(successor)) {
          stack.push(successor);
          visited.add(successor);
        }
      }
    }
    if (path.size() > 0) {
      if (!isValidSolution(path)) {
        throw new RuntimeException("searcher should never find an invalid solution!");
      }
    }
    return path;
  }
}
