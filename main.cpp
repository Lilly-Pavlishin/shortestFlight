#include <queue>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;





// traces parent pointers back from endv to startv
void printPath(string lookup[], int parents[], int size, int startv, int endv, const int endv2) {
	if (endv != startv) {
		printPath(lookup, parents, size, startv, parents[endv], endv2);
	}
	cout << lookup[endv];
	if(endv != endv2)
		cout << "  --->>   ";
}

void bfs (string lookup[], vector<int> alists[], int size, int start, int target) {
	int * parents = new int[size];
	for (int i = 0; i< size; i++) parents[i] = -1;
	parents[start] = start;
	queue<int> q;
	q.push(start);
	bool found = false;

	while (!q.empty() && !found) {
		int v = q.front();
		q.pop();
		if (v == target)
			found = true;
		else for (int i = 0; i < alists[v].size(); i++) {
				int w = alists[v][i];

				if (parents[w] == -1) {
					parents[w] = v;
					q.push(w);
				}
			}
	}

	if (found)
		printPath(lookup, parents, size, start, target, target);
	else
		cout << "Not found";
	cout << endl;
	delete [] parents;
}

bool outputCityChoices(string c[], string input, int SIZE){
	int flag = false;
	int found = -1;
	int i = 0;
	string tempInput, tempCity;
	tempInput  = input;
	transform(input.begin(), input.end(), tempInput.begin(), ::tolower);
	while(i < SIZE){
		tempCity = c[i];
		transform(tempCity.begin(), tempCity.end(), tempCity.begin(), ::tolower);
		found = tempCity.find(tempInput);
		if(found != -1) {
			cout << i << ": " << c[i] << endl;
			flag = true;
		}
		i++;
	}
	if(!flag){
		cout << "Sorry, there are no  cities with: \"" << input << "\" substring in them!" << endl;
		cout << "Please try again!\n" << endl;
		return flag;
	}
	return flag;
}

bool handleUserInput(string arrayOfCities[], string inputString, int SIZE){
	if(inputString == "quit")
		return false;

	// flag is false if no cities found
	return outputCityChoices(arrayOfCities, inputString, SIZE);
}

bool tooShort(string inputString){
	if(inputString.size() < 2){
		cout << "Please use at least two characters!" << endl;
		return true;
	}
	return false;
}

bool invalidInputInt(int inputInt, int SIZE){
	if(inputInt < 0 || inputInt > SIZE-1){
		cout << "ERROR: invalid departure number entry!" << endl;
		return true;
	}
	return false;
}

int main () {
	cout << "Reading cities from file..." << endl;
	ifstream fin("connections.txt");   // input file
	if(!fin) {
		cout << "Error: Failure to open the input file!";
		cout << "Try putting the connections.txt into the same directory with this cpp file" << endl;
		return -1;
	} else{
		cout << "Creating a look up table..." << endl;
	}

	/*
	 * CREATING A LOOKUP TABLE
	 */
	// read the file into a list
	int i, j, from, to;
	string str;
	bool citiesFound;
	list<string> listOfCities;
	while(getline(fin, str)){
		str.erase(0, 7);
		listOfCities.push_back(str);
	}

	fin.clear();
	fin.seekg (0, fin.beg);

	listOfCities.sort();
	listOfCities.unique();

	int SIZE = listOfCities.size();

	string arrayOfCities[SIZE];

	// copy the list into an array
	i = 0;
	for (list<string>::iterator city=listOfCities.begin(); city!=listOfCities.end(); ++city) {
		arrayOfCities[i] = *city;
		i++;
	}

	cout << "Creating an adjacency list..." << endl;

	/*
	 * Creating an adjacency list
	 */
	vector<int> alist[SIZE];
	i = 0;
	j = 0;
	int k = -1;
	while(getline(fin, str)){
		if (str.at(0) == 'F') {

			i = 0;
			j = 0;
			str.erase(0, 7);

			while (str != arrayOfCities[i] && i <= SIZE) {
				i++;
			}
			}else if(str.at(0) == 'T' || str.at(0) == ' ') {
			str.erase(0, 7);
			while(str != arrayOfCities[k] && k < SIZE) {
				k++;
			}
			alist[i].push_back(k);
			j++;
			k = -1;
		}
	}

	cout << "...FINISHED..." << endl;

	/**
	TODO
	 * format the print function to produce valid output
	 * create an output.txt for submission
	*/

	/*
	 * USER INTERFACE
	 */

	string inputString, tempInputString;
	int inputInt;

	cout << "...Finished..." << endl;
	cout << "--------------------------------------------------------------------" << endl;
	do{
	cout << "Please enter a departing city name or \"quit\" to exit:" << endl;
	cin >> inputString;
	transform(tempInputString.begin(), tempInputString.end(), tempInputString.begin(), ::tolower);
	if(tempInputString == "quit") {
		break;
	}
	if(tooShort(inputString)){
		continue;
	}
	citiesFound = handleUserInput(arrayOfCities, inputString, SIZE);
	if(!citiesFound){
		continue;
	}

	cout << "\nPlease select a departing city by entering a number from the list above: " << endl;
	cin >> inputInt;
	if(invalidInputInt(inputInt, SIZE)){
		continue;
	}

	cout << "Selected Departure: " << inputInt << ": " << arrayOfCities[inputInt] << endl;
	from = inputInt;

	cout << "Please enter a destination city or \"quit\" to exit: ";
	cin >> inputString;
	transform(tempInputString.begin(), tempInputString.end(), tempInputString.begin(), ::tolower);
	if(tempInputString == "quit") {
		break;
	}
	if(tooShort(inputString)){
		continue;
	}
	citiesFound = handleUserInput(arrayOfCities, inputString, SIZE);
	if(!citiesFound){
		continue;
	}

	cout << "Please select a destination by entering a number from the list above: ";
	cin >> inputInt;
	if(invalidInputInt(inputInt, SIZE)){
		continue;
	}

	cout << "Selected Destination: " << inputInt << ": " << arrayOfCities[inputInt] << endl;
	to = inputInt;

	cout << "Shortest Route: ";
	bfs(arrayOfCities, alist, SIZE, from, to);

	cout << "\nMake another search? (\"yes\" or \"no\"): ";
	cin >> inputString;

	if(inputString == "no")
		inputString = "quit";


	}while(inputString != "quit");


	fin.close();
	return 0;
}





