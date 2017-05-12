// Author: Faiyz and Alex

#include <iostream>

#include "NetDriver.h"
#include "maxfinder.h"
#include "QueueAr.h"
#include "vector.h"


int ipInt(const char *c) //convert ip address to int
{
    int x = 0;
    int temp;
    int count = 0;
    int mult = 1;
    for(int i = 0; i < 16; i++)
    {
        if(count > 8)
        {
            break;
        }
        if(c[i] != '\0')
        {
            if(c[i] != '.')
            {
                temp = c[i] -'0';
                x += (temp * mult);
                mult *= 10;
                ++count;
            }
        }
        else
        {
            break;
        }
    }
    return x;
}

MaxFinder::MaxFinder(const Computer *computers, int numComputers,
  int numTerminals)  
{
    terminals = numTerminals;  //save stuff and hash ips
    for(int i = 0; i < numComputers; i++)
    {
        if(i < terminals)  
        {
            sourceTerminals[i] = ipInt(computers[i].address);
        }
        if(i == numComputers - 1)
        {
            sinkNode = ipInt(computers[i].address);
        }
        //std::cout << computers[i].address << std::endl;
        ipHash.put(ipInt(computers[i].address), i + 1);
        //std::cout << ipHash.get(ipInt(computers[i].address)) << " " << ipInt(computers[i].address)<< std::endl;
    }
    /*for(int i = 0; i < numComputers; i++)
    {
        std::cout << ipHash.get(ipInt(computers, i)) << std::endl;
    }*/
} // MaxFinder()

int MaxFinder::calcMaxFlow(Edge *edges, int numEdges)//construct graph and calculate max
{
    int maximum = 0;
    for(int i = 0; i < numEdges; i++) 
    {
        //std::cout << "new edge" << std::endl;
        int source = ipHash.get(ipInt(edges[i].src));
        int destination = ipHash.get(ipInt(edges[i].dest));
        
        //std::cout <<source << " " << destination << std::endl;
        capacities[source][destination] = edges[i].capacity;
        //std::cout << capacities[source][destination] << std::endl;
        //graph[source].resize(size());
        //graph[source].resize(graph[destination].size()+1);
        graph[source].push_back();      
        sourceGraph[source] = source;
        //graph[destination].resize(source.size);
        //graph[destination].resize(graph[source].size()+1);
        graph[destination].push_back();
    }
    int sink = ipHash.get(sinkNode);
    for(int i = 0; i < terminals; i++)
    {
        int sr = ipHash.get(sourceTerminals[i]);
        //std::cout << ipHash.get(sourceTerminals[i]) << std::endl;
        //std::cout << edKarp(sr, sink) << std::endl;
        maximum += edKarp(sr, sink);
    }
    //std::cout << maximum << std::endl;
    return maximum;  // bad result :(
} // calcMaxFlow()

int MaxFinder::edKarp(int src, int sink)
{
    int maxFlow = 0;
    while(true)
    {
        int flow = breadthFirstSearch(src, sink);
        //std::cout << "flow:" << flow << std::endl;
        if(flow == 0)
        {
            break;
        }
        maxFlow += flow;
        int currentPos = sink;
        while(currentPos != src)
        {
            int prevPos = sources[currentPos];
            flows[prevPos][currentPos] += flow;
            flows[currentPos][prevPos] -= flow;
            currentPos = prevPos;
        }
    }
    return maxFlow;
}
 int MaxFinder::breadthFirstSearch(int source, int end)
 {
     memset(sources, -1, sizeof(sources));
     memset(currentCap, 0, sizeof(currentCap));
     
     Queue <int> ar(10000);
     ar.enqueue(source);
     
     sources[source] = -2;
     currentCap[source] = 100;
     
     while(!ar.isEmpty())
     {
         int currentPos = ar.getFront();
         ar.dequeue();
         
         for(int i = 0; i < 5000; i++)
         {
             int next = sourceGraph[currentPos];
             
             
             if(sources[next] == -1)
             {
                 if(capacities[currentPos][next] - flows[currentPos][next] > 0)
                 {
                     sources[next] = currentPos;
                     currentCap[next] = std::min(currentCap[currentPos], capacities[currentPos][next] - flows[currentPos][next]);
                     if(next == end)
                     {
                         return currentCap[end];
                     }
                     ar.enqueue(next);
                 }
             }
         }
     }
     return 0;
 }
 

