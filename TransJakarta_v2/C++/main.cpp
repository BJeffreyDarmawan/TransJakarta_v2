/*
	Analysis Algorithms - COMP6340
	Class: L3AC
	Lecturer/Supervisor: Yaya Heryadi & Sani Muhammad Isa
	Project Name: Transjakarta Route/Path Finder
	
	Team:
	1. Archel Taneka
	2. Bernardus Jeffrey Darmawan
	3. Mikha Putri
	4. Mirna Sumopawiro
	5. Muhammad Firman
	6. Wilson Fransicius
*/

#include<bits/stdc++.h>
using namespace std;

// global variables
vector<pair<int, int> > halteList[1000]; // vector data type to store between vertices and connected edges
map<string, int> name_code; // store bus stop name and its code
map<int, string> code_name; // store bus stop code and its name

/* dist --> an array to store the distance for adjacent vertices
   prevPath --> for backtracking/tracing the path taken from one to another bus stop
   route --> indicator for line/route transfer
   st --> store a bus stop where we want to start from
*/
int dist[1000], prevPath[1000];
int route[1000][1000], st;

// Graph class
class Graph {
	public:
		// default constructor --> restore the value of array route to -1
		Graph() {
			memset(route, -1, sizeof(route));
		}
		// connect between 2 bus stops according to the route/line
		void addEdge(int halteA, int halteB, int cost, int track) {
			halteList[halteA].push_back(make_pair(halteB, cost));
			halteList[halteB].push_back(make_pair(halteA, cost));
			route[halteA][halteB] = route[halteB][halteA] = track;
		}
		// finding the route using djikstra algorithm
		void findPath(int start, int dest) {
			priority_queue<pair<int, int> > pq;
			for(int i = 0; i < 1000; i++) dist[i] = 1000000000;
			pq.push(make_pair(0, start));
			dist[start] = 0; // store the distance to 0 --> because this index is where we start(no cost added)
			prevPath[start] = -1; // store the prevPath index 0 to -1 --> start vertice don't have previous bus stop
			while(!pq.empty()) {
				pair<int, int> temp = pq.top();
				pq.pop();
				int currentCost = temp.first;
				int currentPos = temp.second;
				for(int i = 0; i < halteList[currentPos].size(); i++) {
					int nextPos = halteList[currentPos][i].first;
					int cost = halteList[currentPos][i].second;
					if(dist[nextPos] > currentCost + cost) {
						dist[nextPos] = currentCost + cost;
						prevPath[nextPos] = currentPos;
						pq.push(make_pair(dist[nextPos], nextPos));
					}
				}
			}
		}
		// show the tracing path
		void showPath(int dest) {
			// check if the current bus stop is the destination we want to go
				if(dest == st) { // if it has arrived according to the destination
					cout<<code_name[st]<<endl; // print the last bus stop
					return;
				}
				// if it is hasn't reached the destination
				else {
					showPath(prevPath[dest]); // recursively call the function and move on to the next bus stop
					// check if the current bus stop and the previous bus stop is the same line/route
					if(route[dest][prevPath[dest]] != route[prevPath[dest]][prevPath[prevPath[dest]]])
						// tells user if they have to transfer/transit between routes/lines
						cout<<"Move to line : "<<route[dest][prevPath[dest]]<<endl;
					// if not, then just print the bus stop
					cout << code_name[dest] << endl;
				}
		}
		// show the list of all bus stops
		void showHalteList() {
			cout << "Halte list:\n";
			for(map<int, string>::iterator i = code_name.begin(); i != code_name.end(); i++) cout << i->second << endl;
		}
		// function to tells user time and when the next bus will be coming
		void nextShuttle() {
			// declare variables to store number of hours and minutes
			int hour, min;
			// get current time from the system
			time_t t = time(0);
			struct tm *timeNow = localtime(&t);
			// store current number of hours and minutes
			hour = timeNow->tm_hour;
			min = timeNow->tm_min;
			/*
				Here, we follow the government's policy which the bus will eventually come every 15 minutes for 24 hours.
				
				--Printing Format--
				1. Whenever the number of minutes is below 10, add '0' to the front after ':'
				2. Notify user about when the next bus will be coming. From a whole hour, the bus will be arriving on: :15, :30, :45, and :00
			*/
			(min < 10) ? cout << "Time now: " << hour << ":0" << min << endl : cout << "Time now: " << hour << ":" << min << endl;
			if(min > 0 && min < 15) cout << "Your next bus will be on: " << hour << ":15" << endl;
			else if(min > 15 && min < 30) cout << "Your next bus will be on: " << hour << ":30" << endl;
			else if(min > 30 && min < 45) cout << "Your next bus will be on: " << hour << ":45" << endl;
			else if(min == 0 || min == 15 || min == 30 || min == 45) cout << "Your bus has arrived!\n";
			else cout << hour + 1 << ":00" << endl;
		}
};

// creates Graph object and declares it as a global variable
Graph g;

// setting up the environment --> bus stops, distance, and routes
void setup() {
	// variables for reading from input file
	string halteInp, halteDestInp, logo;
	int codeInp, dist, track;
	
	// read logo from txt file
	ifstream logoFile("logo.txt");
	while(getline(logoFile, logo)) {
		cout << logo << endl;
	}
	
	/*
		The main idea from this function is to read input .txt files
		which we can be said that as a "database" in the program.
	*/
	
	ifstream inFile("name_code.txt");
	while(inFile >> halteInp >> codeInp) {
		name_code.insert(pair<string, int>(halteInp, codeInp));
	}
	
	ifstream inFile2("code_name.txt");
	while(inFile2 >> codeInp >> halteInp) {
		code_name.insert(pair<int, string>(codeInp, halteInp));
	}	
	
	ifstream inFile3("add_edge.txt");
	while(inFile3 >> halteInp >> halteDestInp >> dist >> track)  {
		g.addEdge(name_code[halteInp], name_code[halteDestInp], dist, track);
	}
}

int main() {
	
	int choice; // input variable for choosing the menu
	double totalDist; // storing the total distance from start to the destination
	string halteStart, halteDest; // input for start and destination bus stop
	
	setup(); // setup function
	
	// prompt user to press any key to continue to the main program
	cout << "Press any key to proceed.\n";
	cin.ignore();
	cin.get();
	
	do {
		cout << "\n--MAIN MENU--\n";
		cout << "1. List of all halte\n";
		cout << "2. Find route\n";
		cout << "3. Time\n";
		cout << "0. Exit\n";
		cin >> choice;
		cin.ignore();
		cout << endl;
		// switch cases to iterate through the menu
		switch(choice) {
			case 1:
				g.showHalteList();
				break;
			case 2:
				cout << "Your location: ";
				getline(cin, halteStart);
				st = name_code[halteStart];
				cout << "Your destination: ";
				getline(cin, halteDest);
				
				// find the shortest route
				g.findPath(name_code[halteStart], name_code[halteDest]);
				totalDist = dist[name_code[halteDest]]; // store the total distance
				cout << "Total Distance: ";
				// display the total distance in km or m format depending on the distance itself
				(totalDist < 1000) ?  cout << totalDist << " m\n" : cout << totalDist / 1000 << " km\n";
				
				cout << "Route: " << endl;
				g.showPath(name_code[halteDest]); // display the route
				break;
			case 3:
				// display the current time and when the next bus will be coming
				g.nextShuttle();
				break;
			default:
				cout << "Thank you for using our app :)\n";
		}	
	} while(choice != 0);
	
	return 0;
}
