#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Types.h"
#include "EventClock/EventClock.hpp"
#include "BK.h"
using namespace std;

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("Argument Error: %s <dataset> <k value>\n", argv[0]);
        return 0;
    }
    string dataset = argv[1];
    double k = stod(argv[2]);

    std::vector<EdgeType> edges;
    unsigned int N = 0, M = 0;
    ifstream ifs(dataset);
    for(string line; getline(ifs, line);) {
        stringstream ss(line);
        if(ss.peek() == '%') continue;
        if(N == 0 && M == 0) {
            ss >> N >> N >> M;
        } else {
            VertexType u, v;
            ss >> u >> v;
            edges.push_back({u, v});
        }
    }

    EventClock<TimeTicks::Microseconds> clock;

    clock.startClock("bk");
    BK bk(N, edges, k);
    auto cliques = bk.execute();
    clock.stopClock("bk");

    sort(cliques.begin(), cliques.end());

    ofstream output("MaximalCliques.txt");
    for(auto &clique : cliques) {
        for(auto &vertex : clique) {
            output << std::setw(3) <<  vertex << ' ';
        }
        output << endl;
    }

    output << "Size of result is " << cliques.size() << endl;
    clock.printEvent("bk");
    return 0;
}
