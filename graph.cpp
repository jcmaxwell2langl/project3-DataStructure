//
//  graph.cpp
//  
//
//  Created by YingLi on 7/26/18.
//

#include <stdio.h>
#include <vector>
#include <iostream>
#include <limits>
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>



typedef pair<int, int> Pi;


using namespace std;

class vertexList
{
    bool head;
public:
    
    vertexList * next;
    int name;
    int weight;
    int edges = 0;
    vertexList() = default;
    vertexList(int name, bool isHead, int weight, vertexList *next)
    {
        this->name = name;
        head = isHead;
        this ->weight = weight;
        this->next = next;
    }
};


class Graphs_P3
{
private:
    
    
    const static int MaxVer = 51;
    vertexList v[MaxVer];
    int numV;
    int * vconverter = new int [MaxVer];
    const int a = numeric_limits<int>::max();  //infinit
    int Vertex[MaxVer];
    
    
    
public:
    
    Graphs_P3()
    {
        for(int i = 0; i < MaxVer; i++)
        {
            Vertex[i] = 0;
        }
    }
    
    
    void insertVertex(int vertex); //inserts new vertex in graph
    void insertEdge(int from, int to, int weight);  //inserts new edge in graph
    bool isEdge(int from, int to);  //returns true if there is an edge between the vertices from and to
    int getWeight(int from, int to);  //returns the weight of the edge between the vertices from and to
    vector<int> getAdjacent(int vertex);  //return an array of integers representing vertices adjacent to vertex
    void printDijkstra(int source);  //prints result of running Dijkstra algorithm with source vertex
    void printGraph(); //prints graph in a format sorted by ascending vertex and edge list
    
    
};


void Graphs_P3::insertVertex(int vertex) //inserts new vertex in graph
{
    v[vertex] = vertexList(vertex, true, -999, nullptr);
    Vertex[vertex] = 1;
    numV++;
}


void Graphs_P3::insertEdge(int from, int to, int weight)  //inserts new edge in graph
{
    
    
    vertexList *head = &v[from];
    vertexList *current = head;
    vertexList *newEdge = new vertexList(to, false, weight, nullptr);
    
    while (current->next != nullptr){
        current = current->next;
    }
    
    current->next = newEdge;
    head->edges = head->edges + 1;
    
}



bool Graphs_P3::isEdge(int from, int to)  //returns true if there is an edge between the vertices from and to
{
    vertexList *current = &v[from];
    
    while(current != nullptr){
        if(current->name == to){
            return true;
        }
        current = current->next;
    }
    
    return false;
}

int Graphs_P3::getWeight(int from, int to)  //returns the weight of the edge between the vertices from and to
{
    vertexList *temp = &v[from];
    
    while (temp != nullptr){
        if(temp->name == to){
            return temp->weight;
        }
        temp = temp->next;
    }
    
    return std::numeric_limits<int>::max();
}

vector<int> Graphs_P3::getAdjacent(int vertex) //return an array of integers representing vertices adjacent to vertex
{
    vector <int> adj;
    vertexList * temp = &v[vertex];
    temp = temp->next;
    while(temp)
    {
        adj.push_back(temp->name);
        temp = temp->next;
        
    }
    
    sort(adj.begin(), adj.end()); //sort the adjacency list
    
    return adj;
}



void Graphs_P3::printDijkstra(int source)  //prints result of running Dijkstra algorithm with source vertex
{
    priority_queue<Pi, vector<Pi>, greater<Pi>> minheap; //Minheap of pairs  <weight, vertex name)
    vector <int> d(MaxVer, a); //set all distance to infinity
    string path1 = to_string(source); //first path
    vector <string> paths (MaxVer, path1); //set all path from source
    
    
    minheap.push(make_pair(0, source)); //push first vertex and distance
    d[source] = 0;
    
    while (!minheap.empty())
    {
        int currentV = minheap.top().second; //currentV has smallest distance
        minheap.pop(); //remove first vertex from minheap
        vertexList * newTop = &v[currentV];
        vertexList * adjtop = newTop->next; //vertex connect to top
        
        while (adjtop != nullptr)
        {
            if (d[adjtop->name] > d[newTop->name] + adjtop->weight) //if find smaller distance
            {
                d[adjtop->name] = d[newTop->name] + adjtop->weight; //set new weight
                paths[adjtop->name] = paths[newTop->name] + "-" + to_string(adjtop->name); //add it to paths
                minheap.push(make_pair(d[adjtop->name], adjtop->name)); //add it to distance to be stored
            }
            adjtop = adjtop->next;
            
        }
        
    }
    
    
    
    
    int count = 1;
    cout << "V D P"; //format
    
    for (int n = 0; n < MaxVer; ++n)
    {
        
        if (n != source)
        {
            if (Vertex[n] == 1)
            {
                cout << "\n";
                cout << n << " " << d[n] << " " << paths[n];
                count ++;
            }
        }
        
    }
    
    
}




void Graphs_P3::printGraph() //prints graph in a format sorted by ascending vertex and edge list
{
    int count = 0;
    for (int i = 0; i < MaxVer; i ++){
        if (Vertex[i] == 1) {
            cout << v[i].name;
            vector<int> adj = getAdjacent(v[i].name);
            int size = adj.size();
            int j;
            j=0;
            while(j<size)
            {
                cout<< " " << adj[j];
                j++;
            }
            count++;
            if (count != numV) {
                cout << "\n";
            }
        }
    }
}








int main()
{
    //DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK
    int noOfLines, operation, vertex, to, fro, weight,source,j;
    vector<int> arr;
    int arrSize;
    Graphs_P3 g;
    cin>>noOfLines;
    for(int i=0;i<noOfLines;i++)
    {
        cin>>operation;
        switch(operation)
        {
            case 1:
                cin>>vertex;
                g.insertVertex(vertex);
                break;
            case 2:
                cin>>fro;
                cin>>to;
                cin>>weight;
                g.insertEdge(fro,to,weight);
                break;
            case 3:
                cin>>fro;
                cin>>to;
                cout<<g.isEdge(fro,to)<<"\n";
                break;
            case 4:
                cin>>fro;
                cin>>to;
                cout<<g.getWeight(fro,to)<<"\n";
                break;
            case 5:
                cin>>vertex;
                arr=g.getAdjacent(vertex);
                arrSize = arr.size();
                j=0;
                while(j<arrSize)
                {
                    cout<<arr[j]<<" ";
                    j++;
                }
                cout<<"\n";
                break;
            case 6:
                cin>>source;
                g.printDijkstra(source);
                cout<<"\n";
                break;
            case 7:
                g.printGraph();
                cout<<"\n";
                break;
        }
    }
}
