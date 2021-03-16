/**********************************************************************
 *  Linear Feedback Shift Register (part A) ps1a-readme.txt template
 **********************************************************************/

Name: Tony Choma
Hours to complete assignment: 4
/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.

 **********************************************************************/
The assignment had instructions to simulate a linear feedback shift register. 
To do so it was required to make a function that simulates one step and returns 
1 or 0 based on a XOR comparison between the largest bit and the tap. The generate 
function simulates k steps and returns an integer in k-bits.

/**********************************************************************
 *  Explain the representation you used for the register bits 
 *  (how it works, and why you selected it)
 **********************************************************************/
I used an array of integers as I had complications using another data structure 
like valarray.
 
/**********************************************************************
 * Discuss what's being tested in your two additional Boost unit tests
  **********************************************************************/
The first test consists of a rudimentary test that checks if the seed is all zero or one 
then it returns the appropiate integers. The second test simply tests a few specific results 
to make sure that anything other than the basic cases work. 

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
stoi() gave me a bad number for some reason so I had to implement my own way 
to convert the string into an array of integers.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
