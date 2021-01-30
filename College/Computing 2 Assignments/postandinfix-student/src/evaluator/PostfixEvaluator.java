package evaluator;

import parser.ArithParser;
import stack.LinkedStack;

public class PostfixEvaluator extends Evaluator {

  private LinkedStack<Integer> stack = new LinkedStack<Integer>();

  /** return stack object (for testing purpose). */
  public LinkedStack<Integer> getStack() { 
    return stack; 
  }

  /** This method performs one step of evaluation of a postfix expression.
   *  The input is a token. Follow the postfix evaluation algorithm
   *  to implement this method. If the expression is invalid, throw an
   *  exception with the corresponding exception message.
   */
  public void evaluate_step(String token) throws Exception {
    if (isOperand(token)) {
      stack.push(Integer.parseInt(token));
    } else if (token.equals("!")){
    	if (stack.size < 1) {
      	  throw new Exception("too few operands");
        }
    	stack.push(-stack.pop());
    	return;
    } else {
      if (stack.size < 2) {
    	  throw new Exception("too few operands");
      }
      int operand2 = stack.pop();
      int operand1 = stack.pop();
      
      switch (token) {
      	
        case "+": 
          stack.push(operand2 + operand1); 
          break; 
              
        case "-": 
          stack.push(operand1 - operand2); 
          break; 
              
        case "/": 
          if (operand2 == 0) {
            throw new Exception("division by zero");
          }
          stack.push(operand1 / operand2); 
          break; 
              
        case "*": 
          stack.push(operand2 * operand1); 
          break; 
        default:
          throw new Exception("invalid operator");
      } 
    }
  }
  
  /** This method evaluates a postfix expression (defined by expr)
   *  and returns the evaluation result. It throws an Exception
   *  if the postfix expression is invalid.
   */
  public Integer evaluate(String expr) throws Exception {
    for (String token : ArithParser.parse(expr)) {
      evaluate_step(token);
    }
    // The stack should have exactly one operand after evaluation is done
    if (stack.size() > 1) {
      throw new Exception("too many operands");
    } else if (stack.size() < 1) {
      throw new Exception("too few operands");
    }
    return stack.pop(); 
  }

  public static void main(String[] args) throws Exception {
    System.out.println(new PostfixEvaluator().evaluate("50 25 ! / 3 +"));
  }
}