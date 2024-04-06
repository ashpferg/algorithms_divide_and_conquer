# algorithms_divide_and_conquer

Divide and Conquer - Find Peak  

## DESCRIPTION  

Recursively find peak (highest number) of the given array using Divide and Conquer search algorithm.  
Returns values of the peak and it's index number.  

Assumptions: Input comes from file named input.txt. It is formatted to have one number per line.  
The numbers increase until it reaches the peak, and decrease afterwards.  


## EXAMPLES

Valid input sequence:	1, 2, 5, 12, 17 (peak), 15, 13, 5, 2, 1

Invalid input sequence: 1, 2, 5, 12, 17 (peak), 15, 16, 5, 2, 1

Invalid because each number after the peak should decrease. But we have 17 (peak), 15 (decrease), 16 (increase).
All numbers before the peak should be increasing. All numbers afterwards should be decreasing.
We could fix that input sequence by reordering: 17, 16, 15, etc...

## ALGORITHM  

Input sequence: 1, 2, 5, 12, 17, 15, 13, 5, 2, 1  
    
Subsequences below formatted as: [previous number], [current number], [next number]  

Recall the input is arranged to increase towards a peak number, then decrease afterwards.
We can search for the peak by testing the middle number in a given search range.
Compare this current number to it's neighbors. There are 3 outcomes from this test:  
    

		
1)  Peak found  
    12, 17, 15   
    The current number, 17, is higher than both it's neighbors. We've found the peak  
                
3)	Peak is to the left of current number  
    15, 13, 5  
    The current number is higher than the next number, but lower than the previous number.
    So we've passed the peak. Which means it's in the left half of the search range.
    Eliminate the right half and repeat the process until it's found.	

5)	Peak is to the right of the current number  
    2, 5, 12   
    The current number is lower than the next number. We haven't reached the peak yet.
    So eliminate the left half of the vector from the search range - we know the peak isn't there.
    Repeat the process until it's found.
