#include <iostream>
#include <fstream>
#include <vector>

/*	Divide and Conquer - Find Peak
	Asher Ferguson
	Last updated: 4/6/24

	*** DESCRIPTION ***
	
		Recursively find peak (highest number) of the given array using Divide and Conquer search algorithm.
		Returns values of the peak as well as its index number.

		Assumptions: Input comes from file named input.txt. It is formatted to have one number per line.
		The numbers increase until it reaches the peak, and decrease afterwards.


	*** EXAMPLES ***

		Valid input sequence	-	1, 2, 5, 12, 17 (peak), 15, 13, 5, 2, 1

		Invalid input sequence	-	1, 2, 5, 12, 17 (peak), 15, 16, 5, 2, 1

		Invalid because each number after the peak should decrease. But we have 17 (peak), 15 (decrease), 16 (increase).
		All numbers before the peak should be increasing. All numbers afterwards should be decreasing.
		We could fix that input sequence by reordering: 17, 16, 15, etc...
 */

// A recursive search function using Divide and Conquer. Parameters + algorithm explained below.
int findPeak(std::vector<int> input_vector, int range_start, int range_end, int midpoint) {

	/*
		*** PARAMETERS ***
		
			input_vector:	Contains input values.

			range_start:	The lower index of the range to be tested. Starts at 0, the first element.

			range_end:		The higher index of range to be tested. Starts at n-1, the last element.

			midpoint:		The halfway point in our range. Determine if peak is to the left or
							right, then narrow our search range from there. 	


		*** ALGORITHM ***
		 
			Recall the input is arranged to increase towards a peak number, then decrease afterwards.
			We can search for this number by testing the middle number in the search range.
			Compare this current number to it's neighbors. There are 3 outcomes from this test:

			Input sequence: 1, 2, 5, 12, 17, 15, 13, 5, 2, 1

			Subsequences below formatted as: [previous number], [current number], [next number]
		
			1)	12, 17, 15	
				The current number, 17, is higher than both it's neighbors. We've found the peak
			

			2)	15, 13, 5
				The current number is higher than the next number, but lower than the previous number.
				So we've passed the peak. Which means it's in the left half of the search range.
				Eliminate the right half and repeat the process until it's found.
			

			3)	2, 5, 12	
				The current number is lower than the next number. We haven't reached the peak yet.
				So eliminate the left half of the vector from the search range - we know the peak isn't there.
				Repeat the process until it's found.
	*/

	// Check if the current number is greater than the next number
	if(input_vector[midpoint] > input_vector[midpoint + 1]){

		// Check if current number is also greater than previous number.
		if (input_vector[midpoint] > input_vector[midpoint - 1]) {

			// Case 1: we've found the peak.
			return midpoint;
		}

		// Case 2: eliminate right half of the search range.
		range_end = midpoint;
		midpoint -= floor((range_end - range_start) / 2);
		return findPeak(input_vector, range_start, range_end, midpoint);
	}

	else {

		// Case 3: eliminate left half of the search range.
		range_start = midpoint;
		midpoint += floor((range_end - range_start) / 2);
		return findPeak(input_vector, range_start, range_end, midpoint);
	}
}

int main() {

	std::vector<int> input_vector;	// Vector to be filled with input, then searched for peak.
	std::ifstream input_stream;		// Stream object for reading input file.
	int input_value;				// Current input element.

	/* Create ifstream object to read in data from input.txt. Output error message if input.txt not found. */
	input_stream.open("input.txt");
	if (input_stream.fail()) {
		std::cout << "No file found with that name. " << std::endl;
		exit(1);
	}

	/* Read input from file into a vector. */
	while (input_stream >> input_value) {
		input_vector.push_back(input_value);
	}

	/* Close stream object. */
	input_stream.close();

	int n = size(input_vector);			// Size of the range to be searched.
	int midpoint = floor((n - 1) / 2);	// The middle of range to be searched, which is half the size of the vector.
	int peak = 0;						// The index of the highest value in the input vector - this is our output.

	/* Edge cases: if the peak is the first or last element, then we should check for that and quit immediately.
	 * It doesn't make sense to repeatedly check for this inside a recursive function. If its false once,
	 * it'll always be false. We'd just be adding extra work to the function. */

	 /* Edge case 1: Is array size 1? */
	if (size(input_vector) == 1) {
		peak = input_vector[0];
	}

	/* Edge case 2: is peak the first element? */
	else if (input_vector[0] > input_vector[1]) {
		peak = 0;
	}

	/* Edge case 3: is peak the last element? */
	else if (input_vector[n - 1] > input_vector[n - 2]) {
		peak = n - 1;
	}

	/* If peak is not an edge case, then solve for it via Divide & Conquer. */
	else {
		peak = findPeak(input_vector, 0, n - 1, midpoint);
	}

	/* Output the peak. */
	std::cout << "Peak is at index: " << peak << " with a value of: " << input_vector[peak] << std::endl;

	return 0;
}