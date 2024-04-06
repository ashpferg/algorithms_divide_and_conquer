#include <iostream>
#include <fstream>
#include <vector>

/*	Divide and Conquer - Find Peak
	Asher Ferguson
	Last updated: 4/6/24
	
	Recursively find peak (highest number) of the given array using Divide and Conquer search algorithm.
	Returns value of the peak as well as its index number.

	Assumptions: Input comes from file named input.txt. It is formatted to have one number per line.
	The numbers are in increasing order until it reaches the peak, then decreasing order afterwards.
 
 	See README for examples of valid input and an explanation of the search algorithm.
 */

// A recursive search function using Divide and Conquer. Parameters explained below.
int findPeak(std::vector<int> input_vector, int range_start, int range_end, int midpoint) {

/*	Parameters

	input_vector:	Contains input values.

	range_start:	The lower index of the range to be tested. Starts at 0, the first element.
 					Narrows as search progresses

	range_end:		The higher index of range to be tested. Starts at n-1, the last element.
 					Narrows as search progresses

	midpoint:		The halfway point in our range. Determine if peak is to the left or
					right, then narrow our search range from there. 	
*/

	// Check if the midpoint is greater than the next number
	if(input_vector[midpoint] > input_vector[midpoint + 1]){

		// Check if midpoint is also greater than previous number.
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

	// Output error message if input.txt not found.
	input_stream.open("input.txt");
	if (input_stream.fail()) {
		std::cout << "No file found with that name. " << std::endl;
		exit(1);
	}

	// Read input from file into a vector.
	while (input_stream >> input_value) {
		input_vector.push_back(input_value);
	}

	// Close stream object.
	input_stream.close();

	int n = size(input_vector);			// Size of the range to be searched.
	int midpoint = floor((n - 1) / 2);	// The middle of range to be searched, which is half the size of the vector.
	int peak = 0;						// The index of the highest value in the input vector - this is our output.

	// Edge cases: check if array is size 1 or if the peak is first or last element.

	 // Edge case 1: Is array size 1?
	if (size(input_vector) == 1) {
		peak = input_vector[0];
	}

	// Edge case 2: is peak the first element? 
	else if (input_vector[0] > input_vector[1]) {
		peak = 0;
	}

	// Edge case 3: is peak the last element?
	else if (input_vector[n - 1] > input_vector[n - 2]) {
		peak = n - 1;
	}

	// If peak is not an edge case, then solve for it via Divide & Conquer.
	else {
		peak = findPeak(input_vector, 0, n - 1, midpoint);
	}

	// Output the peak.
	std::cout << "Peak is at index: " << peak << " with a value of: " << input_vector[peak] << std::endl;

	return 0;
}
