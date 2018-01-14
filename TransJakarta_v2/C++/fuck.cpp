#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int> > halteList[1000];
map<string, int> name_code;
map<int, string> code_name;
int dist[1000], prevPath[1000];
int route[1000][1000], st;

class Graph {
	private:
		int v;
	public:
		Graph() {
			memset(route, -1, sizeof(route));
		}
		void addEdge(int halteA, int halteB, int cost, int track) {
			halteList[halteA].push_back(make_pair(halteB, cost));
			halteList[halteB].push_back(make_pair(halteA, cost));
			route[halteA][halteB] = route[halteB][halteA] = track;
		}
		void findPath(int start, int dest) {
			priority_queue<pair<int, int> > pq;
			for(int i = 0; i < 1000; i++) dist[i] = 1000000000;
			pq.push(make_pair(0, start));
			dist[start] = 0;
			prevPath[0] = -1;
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
		void showPath(int dest) {
				if(dest == st) {
					cout<<code_name[st]<<endl;
					return;
				}
				else {
					showPath(prevPath[dest]);
					if(route[dest][prevPath[dest]] != route[prevPath[dest]][prevPath[prevPath[dest]]]) 
						cout<<"Move to line : "<<route[dest][prevPath[dest]]<<endl;
					cout << code_name[dest] << endl;
				}
		}
		void showHalteList() {
			cout << "Halte list:\n";
			for(map<int, string>::iterator i = code_name.begin(); i != code_name.end(); i++) cout << i->second << endl;
		}
		void nextShuttle() {
			int hour, min;
			time_t t = time(0);
			struct tm *timeNow = localtime(&t);
			hour = timeNow->tm_hour;
			min = timeNow->tm_min;
			(min < 10) ? cout << "Time now: " << hour << ":0" << min << endl : cout << "Time now: " << hour << ":" << min << endl;
			cout << "Your next bus will be on: ";
			if(min > 0 && min < 15) cout << hour << ":15" << endl;
			else if(min > 15 && min < 30) cout << hour << ":30" << endl;
			else if(min > 30 && min < 45) cout << hour << ":45" << endl;
			else if(min == 0 || min == 15 || min == 30 || min == 45) cout << "Your bus has arrived!\n";
			else cout << hour + 1 << ":00" << endl;
		}
};

Graph g;

void setup() {
	string halteInp, halteDestInp;
	int codeInp, dist, track;
	
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
	
	int choice;
	double totalDist;
	string halteStart, halteDest;
	setup();
				
	do {
		cout << "\n--TRANSJAKARTA--\n";
		cout << "1. List of all halte\n";
		cout << "2. Find route\n";
		cout << "3. Time\n";
		cout << "0. Exit\n";
		cin >> choice;
		cin.ignore();
		cout << endl;
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
					
				g.findPath(name_code[halteStart], name_code[halteDest]);
				totalDist = dist[name_code[halteDest]];
				cout << "Total Distance: ";
				(totalDist < 1000) ?  cout << totalDist << " m\n" : cout << totalDist / 1000 << " km\n";
				
				cout << "Path: " << endl;
				g.showPath(name_code[halteDest]);
				break;
			case 3:
				g.nextShuttle();
				break;
			default:
				cout << "Thank you for using our app :)\n";
		}	
	} while(choice != 0);
	
	return 0;
}
