tony_choma@student.uml.edu

In this assignment my degree of success was of 100% completion. 
It was a simple but not so simple adder of two unsigned integers.
To achieve this the starter code converted the ascii input into binary.
Then all was needed was to simply add the two. However, converting into
ASCII proved to be trickier. First the combined number had to be split into 
single digits. To do so I divided the number by 10 using div, incremented
the stack pointer for seamless popping into the transmitter buffer and adding 
48 to convert to ASCII. Then the added number would be displayed in the 
terminal. For overflow detection theres a simple jump if negative after adding
the two numbers. All in all the most frustrating part was not realizing that div
doesn't increment the stack pointer and return just the remainder and the quotient.