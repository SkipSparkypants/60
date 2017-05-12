// Author: Sean Davis
#ifndef maxfinderH
#define maxfinderH
#include "NetDriver.h"
//#include <vector>
#include <cstring>
//#include <algorithm>
//#include "LinearProbing.cpp"
#include "Hash.cpp"
#include "vector.h"

class MaxFinder
{
public:
  MaxFinder(const Computer *computers, int numComputers, int numTerminals);
  int calcMaxFlow(Edge *edges, int numEdges);
  int edKarp(int src, int sink);
  int breadthFirstSearch(int start, int end);
  int terminals;
  int capacities[15000][15000];
  int flows[15000][15000];
  int sources[15000];
  int currentCap[15000]; 
  int sourceTerminals[500];
  int sinkNode;
  vector<int> graph[20000];
  //int sourceGraph[20000];
  //int destinationGraph[20000];
  HashMap ipHash;
}; // class MaxFinder

struct ipHash
{
    short data;
};

#endif
