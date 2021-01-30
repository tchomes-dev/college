package bigo;

import java.util.Scanner;

interface Algorithm {
	long run(long N);
	String name();
}

class Method1 implements Algorithm{
	public String name() { return "Print Even Squares"; }
	public long run(long N) {
		long count = 0;
		for(long i=0; i<N; i+=2) {
			System.out.println(i+"^2="+(i*i));
			count++;
		}
		return count;
	}
}

class Method2 implements Algorithm{
	public String name() { return  "Print Savings"; }
	public long run(long N) {
		long count = 0;
		for(double i=1.0; i<=N; i=i+(i/10.0)) {
			System.out.printf("Year %d, $%.2f\n", count, i);
			count++;
		}
		return count;
	}
}

class Method3 implements Algorithm{
	public String name() { return  "Print Odd-Even Pairs"; }
	public long run(long N) {
		long count = 0;
		for(long i = 1; i < N; i += 2) {
			for(long k = i+1; k < N; k += 2) {
				System.out.println("("+i+","+k+")");
				count++;
			}
		}
		return count;
	}
}

class Method4 implements Algorithm{
	public String name() { return  "Print Powers"; }
	public long run(long N) {
		long count = 0;
		for(long i = 1; i < N; i <<= 1) {
			for(long k = 0; k < i; k ++) {
				System.out.println("("+i+","+k+")");
				count++;
			}
		}
		return count;
	}
}

class Method5 implements Algorithm{
	private long count = 0;
	public String name() { return  "Print Primes"; }
	private boolean isPrime(long x) {
		boolean is_prime = true;
		for(long k=2;k*k<x;k++) {
			if(x%k==0) is_prime = false;
			count++;
		}
		return is_prime;
	}
	public long run(long N) {
		count = 0;
		for (long i=2; i<=N; i++) {
			if(isPrime(i)) System.out.println(i);
		}
		return count;
	}
}

public class BigO {
  public BigO() {}
  public static void main(String[] args) {
	  Scanner scanner = new Scanner(System.in);
	  int method = 0;
	  Algorithm[] methods = {new Method1(), new Method2(), new Method3(), new Method4(), new Method5()};
	  while(method==0) {
		  System.out.println("Choose the method you want to evaluate (1 to 5):");
		  method = scanner.nextInt();
		  if(method<1 || method>5)
			  method=0;
	  }
	  System.out.println("Method chosen: "+method+" ("+methods[method-1].name()+")");
	  while(true) {
		  System.out.println("Enter problem size N (enter 0 to quit):");
		  int N = scanner.nextInt();
		  if(N>0) {
			  long cost = methods[method-1].run(N);
			  System.out.println("N="+N+", cost="+cost);
		  } else
			  break;
	  }
	  System.out.println("The end.");
	  scanner.close();
  }
}