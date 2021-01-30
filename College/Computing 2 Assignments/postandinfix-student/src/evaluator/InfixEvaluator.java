package evaluator;

import parser.ArithParser;
import stack.LinkedStack;

public class InfixEvaluator extends Evaluator {

  private LinkedStack<String> operators = new LinkedStack<String>();
  private LinkedStack<Integer> operands  = new LinkedStack<Integer>();

  /** return stack object (for testing purpose). */
  public LinkedStack<String> getOperatorStack() { 
    return operators; 
  }
  
  public LinkedStack<Integer> getOperandStack() { 
    return operands;
  }
  public void process_operator() throws Exception {
	if (operators.top().equals("!")){
	  if (operands.size < 1) {
	    throw new Exception("too few operands");
	  }
      operands.push(-operands.pop());
      operators.pop();
	  return;
    } else if (operands.size < 2) {
	  throw new Exception("too few operands");
	} else {
	  int operand2 = operands.pop();
	  int operand1 = operands.pop();
	      
	  switch (operators.pop()) {
	      	
	    case "+": 
	      operands.push(operand2 + operand1); 
	      break; 
	              
	    case "-": 
	      operands.push(operand1 - operand2); 
	      break; 
	              
	    case "/": 
	      if (operand2 == 0) {
	        throw new Exception("division by zero");
	      }
	      operands.push(operand1 / operand2); 
	      break; 
	              
	    case "*": 
	      operands.push(operand2 * operand1); 
	      break; 
	      
	    default:
	      throw new Exception("invalid operator");
	  } 
	}
  }

  /** This method performs one step of evaluation of a infix expression.
   *  The input is a token. Follow the infix evaluation algorithm
   *  to implement this method. If the expression is invalid, throw an
   *  exception with the corresponding exception message.
   */
  public void evaluate_step(String token) throws Exception {
    if (isOperand(token)) {
    	operands.push(Integer.parseInt(token));
    } else {
    	if (token.equals("(")) {
    		operators.push(token);
    	} else if (operators.isEmpty() || precedence(operators.top()) < precedence(token)) {
    		operators.push(token);
    	} else if (token.equals(")")) {
    		boolean missing = true;
    		while (!operators.isEmpty() && missing == true) {
    			if (operators.top().equals("(")) {
    				missing = false;
    				operators.pop();
    			} else {
    				missing = true;
    				process_operator();
    			}
    		}
    		if (missing) {
    			throw new Exception("missing (");
    		}
    	} else {
    		while (!operators.isEmpty() && !(precedence(operators.top()) < precedence(token))) {
    			process_operator();
    		}
    		operators.push(token);
    	}
    }
  }
  
  /** This method evaluates an infix expression (defined by expr)
   *  and returns the evaluation result. It throws an Exception object
   *  if the infix expression is invalid.
   */
  public Integer evaluate(String expr) throws Exception {

    for (String token : ArithParser.parse(expr)) {
      evaluate_step(token);
    }

    while (!operators.isEmpty()) {
    	process_operator();
    }
    // The operand stack should have exactly one operand after the evaluation is done
    if (operands.size() > 1) {
      throw new Exception("too many operands");
    } else if (operands.size() < 1) {
      throw new Exception("too few operands");
    }

    return operands.pop();
  }

  public static void main(String[] args) throws Exception {
    System.out.println(new InfixEvaluator().evaluate("5+(5+2*(5+9))/!8"));
  }
}
