#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int> > halteList[1000];
map<string, int> code_name;
map<int, string> name_code;
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
					cout<<name_code[st]<<endl;
					return;
				}
				else {
					showPath(prevPath[dest]);
					if(route[dest][prevPath[dest]] != route[prevPath[dest]][prevPath[prevPath[dest]]]) 
						cout<<"Move to line : "<<route[dest][prevPath[dest]]<<endl;
					cout << name_code[dest] << endl;
				}
		}
		void showHalteList() {
			cout << "Halte list:\n";
			for(map<int, string>::iterator i = name_code.begin(); i != name_code.end(); i++) cout << i->second << endl;
		}
		void nextShuttle() {
			int hour, min;
			time_t t = time(0);
			struct tm *timeNow = localtime(&t);
			hour = timeNow->tm_hour;
			min = timeNow->tm_min;
			(min < 0) ? cout << "Time now: " << hour << ":0" << min << endl : cout << "Time now: " << hour << ":" << min << endl;
			if(min > 0 && min < 15) cout << "Your next shuttle will be on: " << hour << ":15" << endl;
			else if(min > 15 && min < 30) cout << "Your next shuttle will be on: " << hour << ":30" << endl;
			else if(min > 30 && min < 45) cout << "Your next shuttle will be on: " << hour << ":45" << endl;
			else if(min == 0 || min == 15 || min == 30 || min == 45) cout << "Your shuttle has arrived!\n";
			else cout << "Your next shuttle will be on: " << hour + 1 << ":00" << endl;
		}
};

Graph g;

void setup() {
	string halteInp;
	int codeInp;
	
	/*ifstream inFile("data.txt");
	while(getline(inFile, halteInp) && inFile >> codeInp) {
		code_name.insert(pair<string, int>(halteInp, codeInp));
	}*/
	code_name.insert(pair<string, int>("Halte 1", 100));
	code_name.insert(pair<string, int>("Halte 2", 101));
	code_name.insert(pair<string, int>("Halte 3", 102));
	code_name.insert(pair<string, int>("Halte 4", 103));
	code_name.insert(pair<string, int>("Halte 5", 104));
	code_name.insert(pair<string, int>("Halte 6", 105));
	code_name.insert(pair<string, int>("Halte 7", 106));
	code_name.insert(pair<string, int>("Halte 8", 107));
	
	
	name_code.insert(pair<int, string>(100, "Halte 1"));
	name_code.insert(pair<int, string>(101, "Halte 2"));
	name_code.insert(pair<int, string>(102, "Halte 3"));
	name_code.insert(pair<int, string>(103, "Halte 4"));
	name_code.insert(pair<int, string>(104, "Halte 5"));
	name_code.insert(pair<int, string>(105, "Halte 6"));
	name_code.insert(pair<int, string>(106, "Halte 7"));
	name_code.insert(pair<int, string>(107, "Halte 8"));
	
	
	g.addEdge(code_name["Halte 1"], code_name["Halte 2"], 103, 1);
	g.addEdge(code_name["Halte 2"], code_name["Halte 3"], 487, 2);
	g.addEdge(code_name["Halte 2"], code_name["Halte 5"], 691, 1);
	g.addEdge(code_name["Halte 3"], code_name["Halte 4"], 326, 3);
	g.addEdge(code_name["Halte 3"], code_name["Halte 6"], 549, 2);
	g.addEdge(code_name["Halte 5"], code_name["Halte 7"], 221, 1);
	g.addEdge(code_name["Halte 4"], code_name["Halte 8"], 1035, 3);
	g.addEdge(code_name["Halte 7"], code_name["Halte 8"], 947, 1);
}

int main() {
	
	int choice;
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
				st = code_name[halteStart];
				cout << "Your destination: ";
				getline(cin, halteDest);
					
				g.findPath(code_name[halteStart], code_name[halteDest]);
				cout << "Total Distance: " << dist[code_name[halteDest]] << " km" << endl;
				cout << "Path: " << endl;
				g.showPath(code_name[halteDest]);
				break;
			case 3:
				g.nextShuttle();
				break;
			default:
				cout << "Thank you for using our app :)\n";
		}
			
				
	}while(choice != 0);
	
//	setup();
//	
//	string halteStart, halteDest;
//	cout << "Halte List:\n";
//	g.showHalteList();
//	cout << "Your location: ";
//	getline(cin, halteStart); 
//	st = code_name[halteStart];
//	cout << "Your destination: ";
//	getline(cin, halteDest);
//	
//	g.findPath(code_name[halteStart], code_name[halteDest]);
//	cout << "Total Distance: " << dist[code_name[halteDest]] << endl;
//	cout << "Path: "<<endl;
//	g.showPath(code_name[halteDest]);
	
	return 0;
	
}
