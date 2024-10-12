/*
 * This function determines the prefer city to start a circular journey based on the fuel available
 * and the distance between neighboring cities. We are given two arrays:
 *
 * 1. An array `cityDist[]` representing the distances between neighboring cities.
 *    - The value at index `i` in `cityDist` is the distance from city `i` to city `i+1`.
 *    - The last element in the array represents the distance from the last city to the first city, completing the circle.
 *
 * 2. An array `fuel[]` representing the fuel available at each city `i`.
 *    - The value at index `i` in `fuel[]` is the fuel available at city `i`, which can be used to travel to the next city.
 *
 * The goal is to find the preferable city to start the journey such that you can visit all cities in a circular path without running out of fuel.
 * The car has a given fuel efficiency of `mpg` (miles per gallon), which means for each gallon of fuel, the car can travel `mpg` miles.
 *
 */
#include <iostream>
using namespace std;

int bestCity(int cityDist[], int fuel[], int mpg, int size) {
	// Start each variable need to calculate the current fuel, total fuel, and best city.
	int currentFuel = 0;
	int totalFuel = 0;
	int preferCityToStart = 0;

	for(int i = 0; i < size; i++) {
		//Calculate the current fuel we have at the current city.
		currentFuel = (fuel[i] * mpg) - cityDist[i];
		//Calculate the total fuel we have in the journey.
		totalFuel = (fuel[i] * mpg) - cityDist[i];

		// When the current fuel become negative we reset the current fuel
		// and the next city become the best city where we can start the journey.
		if (currentFuel < 0) {
			preferCityToStart = i + 1;
			currentFuel = 0;
		}
	}
	// If total fuel is a positive value or zero (>= 0) return the index of the best city to start
	// otherwise return -1 meaning we could not find a valid city.
	return (totalFuel >= 0) ? preferCityToStart : -1;
}

int main() {

	int city_distances[] = {5,25,15,10,15};
	int fuel[] = {1,2,1,0,3};
	int mpg = 10;
	// Find the total size of the city_distances assuming that the fuel and distances cities have the same size.
	int size = sizeof(city_distances) / sizeof(city_distances[0]);
	int whichCity = bestCity(city_distances, fuel, mpg, size);
	cout << "The best to start is: " << whichCity << endl;
	return 0;
}
