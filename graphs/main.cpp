#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

template <typename Vertex, typename Label>
struct Edge {
    Vertex from;
    Vertex to;
    Label lbl;
    Edge(const Vertex& from, const Vertex& to, const Label& l)
        :from(from), to(to), lbl(l) { }
};

template <typename Vertex, typename Label>
class Graph {
    using E = Edge<Vertex,Label>;
private:
    unordered_map<Vertex, vector<pair<Vertex, Label>>> adjacencyList;
public:
    void addVertex(const Vertex& v) {
        adjacencyList[v];
    }
    void addEdge(const Vertex& from,
                  const Vertex& to,
                   const Label& lbl) {
        addVertex(from);
        addVertex(to);
        adjacencyList[from].push_back(make_pair(to, lbl));
    }
    vector<E> listEdges() {
        vector<E> edges;
        for (auto const& entry: adjacencyList) {
                // entry.first is the key (vertex from)
                // entry.second is the vector of neighbors
            for (auto const& outgoing: entry.second) {
                // outgoing is a single edge <vertex to, label>
                edges.push_back(E(entry.first,
                                   outgoing.first,
                                    outgoing.second));
            }
        }
        return edges;
    }

    vector<Vertex> noIncomingEdges() {
        vector<Vertex> result;
        for (auto const& entry: adjacencyList) {
            bool found = false;
            for (auto const& it: adjacencyList) {
                for (auto const& edge: it.second) {
                    if (entry.first == edge.first) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            if (!found) {
                result.push_back(entry.first);
            }
        }
    }
};

int main()
{
    Graph<string, int> g;
    g.addVertex("Plovdiv");
    g.addVertex("Sofia");
    g.addEdge("Plovdiv", "Sofia", 150);
    cout << "Hello world!" << endl;
    return 0;
}
