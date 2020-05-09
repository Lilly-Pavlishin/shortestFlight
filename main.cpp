#include <queue>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;





// traces parent pointers back from endv to startv
void printPath(int parents[], int size, int startv, int endv) {
	if (endv != startv) {
		printPath(parents, size, startv, parents[endv]);
	}
	cout << endv << " ";
}



//

void bfs (vector<int> alists[], int size, int start, int target) {
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
		printPath(parents,size,start,target);
	else
		cout << "Not found";
	cout << endl;
	delete [] parents;
}

int main () {
	ifstream fin("connections.txt");   // input file
	if(!fin) {
		cout << "Error: Failure to open the input file!";
		cout << "Try putting the connections.txt into the same directory with this cpp file" << endl;
		return -1;
	}

	// read the file into a list
	int i, j;
	string str;
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

//	cout << "size of the listOfCities is: "<< listOfCities.size() << endl;
//	cout << "size of arrayOfCities is : " << arrayOfCities->size() << endl;
//
//	i= 0;
//	for (list<string>::iterator city=listOfCities.begin(); city!=listOfCities.end(); ++city) {
//		cout << "list of cities at index " << i << ": " << *city << endl;
//		cout << "array of cities at index " << i << ": " << arrayOfCities[i] << endl << endl;
//		i++;
//	}


	vector<string> alist[SIZE];



	i = 0;
	j = 0;
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
			alist[i].push_back(str);
			j++;
		}
	}

//	check if alist works
//	i = 0;
//	for(i = 0; i < SIZE; i++){
//		j = 0;
//		while(j < alist[i].size()){
//			cout << "\n From the city of: " << arrayOfCities[i] << endl;
//			cout << "The value of an array is at index [" << i << "][" << j << "]: "<< alist[i][j] << endl;
//			j++;
//		}
//
//	}

	// output the contents of array for check
//	for(i = 0; i < listOfCities.size(); i++)
//		cout << arrayOfCities[i] << "\n";


	/**
	TODO
	 * create user interface
	 	* Take input from the user
	 	* search through a look up table and output the list of choices
	 * take the info from the user and find the shortest path
	 * modify the print function to produce valid output
	*/



	const int size = 10;
	vector<int> alists[size]; // Adjacency lists for a sample graph
	int parents[size];

	// I WILL HAVE TO DECIDE WHAT TO PUSH BASED ON THE TXT

//       alists[0].push_back(1);
	alists[0].push_back(2);		// from 0 I can go to 2
	alists[1].push_back(0);		// from 1 I can go to 0
	alists[1].push_back(3);		// from 1 I can go to 3
	alists[2].push_back(0);
	alists[2].push_back(4);
	alists[3].push_back(1);
	alists[3].push_back(4);
	alists[3].push_back(5);
	alists[3].push_back(6);
	alists[4].push_back(2);
	alists[4].push_back(7);
//       alists[5].push_back(3);
	alists[5].push_back(6);
	alists[5].push_back(8);
	alists[6].push_back(3);
	alists[6].push_back(5);
	alists[7].push_back(4);
	alists[7].push_back(8);
	alists[8].push_back(5);
	alists[8].push_back(7);
	alists[9].push_back(6);
	alists[9].push_back(7);
	bfs(alists,size,0,9);
	bfs(alists,size,9,0);
	bfs(alists,size,0,1);
	bfs(alists,size,1,0);

	fin.close();
	return 0;
}





