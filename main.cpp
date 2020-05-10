#include <queue>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int SIZE;

void printPath(string lookup[], int parents[], int size, int startv, int endv, const int endv2);
void bfs (string lookup[], vector<int> alists[], int size, int start, int target);
bool outputCityChoices(string c[], string input, int SIZE);
int getInput(string inputString, string look_up_table[]);
bool handleUserInput(string arrayOfCities[], string inputString, int SIZE);
bool tooShort(string inputString);
bool invalidInputInt(int inputInt, int SIZE);
string* createLookupTable();
vector<int>* createAdjacencyTable(string look_up_table[]);


int main () {

	// var declaration
	int i, j, from, to;
	string inputString;
	int inputInt;

	// creating look up and adjacency tables
	string* look_up_table = createLookupTable();
	vector<int>* alist = createAdjacencyTable(look_up_table);

	// UI
	do{
	cout << "Please enter a departing city name or \"quit\" to exit:" << endl;
	cin >> inputString;

	from = getInput(inputString, look_up_table);
	if(from == -2)
		break;
	if(from == -3)
		continue;
	cout << "Selected Departure: " << from << ": " << look_up_table[from] << endl;

	cout << "Please enter a destination city or \"quit\" to exit: ";
	cin >> inputString;

	to = getInput(inputString, look_up_table);
	if(to == -2)
		break;
	if(to == -3)
		continue;
	cout << "Selected Destination: " << to << ": " << look_up_table[to] << endl;

	cout << "Shortest Route: ";
	bfs(look_up_table, alist, SIZE, from, to);

	cout << "\nMake another search? (\"yes\" or \"no\"): ";
	cin >> inputString;

	if(inputString == "no")
		inputString = "quit";

	}while(inputString != "quit");

	return 0;
}



/*
 * function to output the the shortest path
 */
void printPath(string lookup[], int parents[], int size, int startv, int endv, const int endv2) {
	if (endv != startv) {
		printPath(lookup, parents, size, startv, parents[endv], endv2);
	}
	cout << lookup[endv];
	if(endv != endv2)
		cout << "  --->>   ";
}

/*
 * breadth first search function that
 */
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

string* createLookupTable(){
	cout << "Reading cities from file..." << endl;
	ifstream fin("connections.txt");   // input file
	if(!fin) {
		cout << "Error: Failure to open the input file!";
		cout << "Try putting the connections.txt into the same directory with this cpp file" << endl;
		exit(EXIT_FAILURE);
	} else{
		cout << "Creating a look up table..." << endl;
	}

	int i;
	string str;
	list<string> listOfCities;
	while(getline(fin, str)){
		str.erase(0, 7);
		listOfCities.push_back(str);
	}

	listOfCities.sort();
	listOfCities.unique();

	SIZE = listOfCities.size();
	string* look_up_table = new string[SIZE];

	// copy the list into an array
	i = 0;
	for (list<string>::iterator city=listOfCities.begin(); city!=listOfCities.end(); ++city) {
		look_up_table[i] = *city;
		i++;
	}

	fin.close();
	return look_up_table;
}

vector<int>* createAdjacencyTable(string look_up_table[]){
	int i, j, k;

	cout << "Creating an adjacency list..." << endl;

	ifstream fin("connections.txt");
	string str;

	vector<int>* alist = new vector<int>[SIZE];
	k = -1;
	while(getline(fin, str)){
		if (str.at(0) == 'F') {
			i = 0;
			j = 0;
			str.erase(0, 7);
			while (str != look_up_table[i] && i <= SIZE) {
				i++;
			}
		}else if(str.at(0) == 'T' || str.at(0) == ' ') {
			str.erase(0, 7);
			while(str != look_up_table[k] && k < SIZE) {
				k++;
			}
			alist[i].push_back(k);
			j++;
			k = -1;
		}
	}

	cout << "...FINISHED..." << endl;
	cout << "------------------------------------------------------------------------" << endl;

	fin.close();
	return alist;
}

int getInput(string inputString, string look_up_table[]){

	string tempInputString;
	int inputInt;
	bool citiesFound;

	transform(tempInputString.begin(), tempInputString.end(), tempInputString.begin(), ::tolower);
	if(tempInputString == "quit") {
		return -2; // code for break
	}
	if(tooShort(inputString)){
		return -3; // code for continue
	}
	citiesFound = handleUserInput(look_up_table, inputString, SIZE);
	if(!citiesFound){
		return -3; // code for continue
	}

	cout << "\nPlease select a departing city by entering a number from the list above: " << endl;
	cin >> inputInt;
	if(invalidInputInt(inputInt, SIZE)){
		return -3; // code for continue
	}

	return inputInt;
}