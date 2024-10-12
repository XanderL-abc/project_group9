// Algorithm 1 Code done by Xander Lahti

// include iostream as always, and include vector for dynamic arrays
#include<iostream>
#include<vector>
// use namespace std for standard C++ conventions :)
using namespace std;



// ================================================================================
//							minSwaps function 
// ================================================================================
// INPUT: vector of int type as input and is passed by reference. 
// OUTPUT: int swaps: num of swaps done to match all partners up with their pair
// ================================================================================
int minSwaps(vector<int>& row) {

	// number of individuals is 2n, n is thus pairs 
	// (as described in the algorithm 1 description)
	// take size of row and divide by 2 to get pairs n
	int n = row.size() / 2;

	// define vector position to track current position of each person, 
	// thus multiple pairs by 2 to get num of individuals
	vector<int> position(n * 2);

	// loop through and fill vector position 
	// with current index of each individual
	for (int i = 0; i < n * 2; i++) {

		// set the position of the ID of a person 
		// sitting in a specified seat to be equal 
		position[row[i]] = i;
	}

	// define int swaps; starts at 0
	int swaps = 0;

	// loop through every couple; i += 2 because 
	// there are 2 people per couple/pair
	for (int i = 0; i < n * 2; i += 2) {

		// set person in current seat to matching row person ID
		int currentPerson = row[i];

		// get partner of currentPerson using XOR (^) operator
		int partner = currentPerson ^ 1;

		// now check if the next person (thus i + 1 to move one 
		// person up in index) is not alredy a couple, and 
		// if they are not, then execute following code to do a swap
		if (row[i + 1] != partner){

			// add 1 value to swaps int since there will be a swap done
			swaps++;

			// find position of partner and set currentPosition to this position
			int partnerPosition = position[partner];

			// swap the next person up in index (row[i + 1]) with the partner
			swap(row[i + 1], row[partnerPosition]);

			// now update the positions of the swapped people:
			// update position of the one swapped
			position[row[partnerPosition]] = partnerPosition;
			// update position of the partner
			position[partner] = i + 1;
		}

	}

	// return number swaps done/the output
	return swaps;

}



// main function
int main() {
	
	// define rows to test out minSwaps function
	vector<int> row1 = { 0, 2, 1, 3 };
	vector<int> row2 = { 3, 2, 0, 1 };
	vector<int> row3 = { 3, 1, 0, 5, 2, 4 };
	vector<int> row4 = { 1, 5, 3, 2, 6, 4, 0, 7 };
	
	// print out info of the min swaps needed for the different row examples
	cout << "Minimum swaps needed for... " << endl;
	cout << "a row of {0, 2, 1, 3}: " << minSwaps(row1) << endl;
	cout << "a row of {3, 2, 0, 1}: " << minSwaps(row2) << endl;
	cout << "a row of { 3, 1, 0, 5, 2, 4 }: " << minSwaps(row3) << endl;
	cout << "a row of { 1, 5, 3, 2, 6, 4, 0, 7 }: " << minSwaps(row4) << endl;

}