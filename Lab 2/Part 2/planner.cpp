#include "planner.h"
#include "dictionary.h"
#include "dictionary.cpp"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split(string text) {
	// Taken from DelftStack website.
    vector<string> words;

    istringstream iss(text);
    string word;

    while (iss >> word) {
    	words.push_back(word);
    }
    return words;
}

int main() {
	string query;
	Dictionary D;

	getline(std::cin, query);

	while (!query.empty()) {
		if (query.rfind("ADD", 0) == 0) {
			struct Journey *j = new struct Journey;

			vector<string> tokens = split(query);

			j->src.assign(tokens[1]);
		    j->dest.assign(tokens[3]);
			j->dept = stof(tokens[2]);
			j->arr = stof(tokens[4]);

			if (!D.put(*j))
				cout << "Could not add the given journey" << endl;
			else
				cout << "Added the journey" << endl;

		} else if (query.rfind("QUERY_JOURNEY", 0) == 0) {
			vector<string> tokens = split(query);

			string src, dest, intermediate;
			float start, minDir = 2500, minInter = 2500, interTime;

			src.assign(tokens[1]);
			start = stof(tokens[2]);
			dest.assign(tokens[3]);

			vector<struct Journey*> nextJourneys = D.get(src);

			if (nextJourneys.empty()) {
				cout << "No journeys available" << endl;
				continue;
			}

			for (auto &journey: nextJourneys) {
				// Direct vs Intermediate Cases
				if (journey->dept < start)
					continue;

				if (journey->dest.compare(dest) == 0) {
					minDir = min(minDir, journey->dept);
				} else {

					vector<struct Journey*> midJourneys = D.get(journey->dest);

					// Double loop :(
					for (auto &mid: midJourneys) {
						if (mid->dest.compare(dest) == 0 && mid->dept >= journey->arr) {
							intermediate.assign(journey->dest);
							minInter = journey->dept;
							interTime = mid->dept;
						}
					}
				}
			}

			if (minDir == 2500 && minInter == 2500)
				cout << "No trains available" << endl;
			else if (minDir <= minInter)
				cout << minDir << endl;
			else
				cout << minInter << " " << intermediate << " " << interTime << endl;

		} else if (query.rfind("QUERY_STATION", 0) == 0) {
			string station;
			float start;

			vector<string> tokens = split(query);
			station.assign(tokens[1]);
			start = stof(tokens[2]);

			vector<struct Journey*> nextJourneys = D.get(station);

			if (nextJourneys.empty())
				cout << "No trains available" << endl;
			else {
				for(auto &journey : nextJourneys) {
					// May output in random order
					if (journey->dept >= start)
						cout << journey->dept << " " << journey->dest << endl;
				}
			}

		} else if (query.rfind("EXIT", 0) == 0) {
			break;
		} else {
			cout << "NOT A VALID QUERY";
		}

		query.clear();
		getline(std::cin, query);
	}

	return 0;
}