/*
 * Dijstra.cpp
 *
 *  Created on: Aug 6, 2018
 *      Author: louise0
 */



#include <limits>
#include <vector>
#include <set>
#include <iostream>
#include <queue>
using namespace std;
//vertex data structure

class Vertex{
public:
	bool headNode;

	int weight;
	int name;
	Vertex* next;
	Vertex(int n,bool head, int w, Vertex* next):name(n), headNode(head), weight(w), next(next){};
};
//Graphs dataStructures

void printPath(int index, int* p, vector<Vertex>v, int* vC){
	//base case: when p[i]=0;

	if (p[index]==0){//correct
		cout<<v[index].name;
	}
	else{
		printPath(vC[p[index]]-1, p,v, vC);//here
		cout<<"-"<<v[index].name;
	}
}

int getMinIndex(int* d, set<int> s, int numVertices){//find min of the array that's not in the set
	int min = numeric_limits<int>::max();
	int minIndex = 0;
	for (int i = 0; i<numVertices; ++i){
		if(min>d[i] && s.count(i)!=1){
			min = d[i];
			minIndex = i;
		}
	}
	return minIndex;
}

int arraySize(int* a){
	//getting arraysize
	int count=0;
	do{
		//	cout<<*a++<<endl;
		a++;
		++count;

	}while(*a && *a<50 && *a>=0);
	return count;
}

class Graphs_P3
{
private:
	// Graph data structure here
	const static int MAXNUMVERTICES = 50;
	int numVertices;
	int vertexConverter[MAXNUMVERTICES];
	std::vector<Vertex> theVertices;
public:
	Graphs_P3(){
		numVertices = 0;
	}

	void insertVertex(int vertex); //inserts new vertex in graph
	void insertEdge(int from, int to, int weight);  //inserts new edge in graph
	bool isEdge(int from, int to);  //returns true if there is an edge between the vertices from and to
	int getWeight(int from, int to);  //returns the weight of the edge between the vertices from and to
	vector<int> getAdjacent(int vertex);  //return an array of integers representing vertices adjacent to vertex
	void printDijkstra(int source);  //prints result of running Dijkstra algorithm with source vertex
	void printGraph(); //prints graph in a format sorted by ascending vertex and edge list
};

void Graphs_P3::insertVertex(int vertex){
	Vertex* newVertex = new Vertex(vertex, true, numeric_limits<int>::max(), NULL);
	theVertices.push_back(*newVertex);
	vertexConverter[vertex]=++(numVertices);
}
//void insertEdge()
void Graphs_P3::insertEdge(int from, int to, int weight){
	//inserts new edge in graph
	int index = vertexConverter[from]-1;
	Vertex* theHead = &theVertices[index];
	Vertex* current = theHead;
	Vertex *newEdge = new Vertex(to, false, weight, NULL);
	while(current->next)
		current = current->next;
	current->next= newEdge;
}


bool Graphs_P3::isEdge(int from, int to){ //returns true if there is an edge between the vertices from and to
	int index = vertexConverter[from]-1;
	Vertex* f=&theVertices[index];
	while(f){
		if(f->name == to){
			return true;
		}
		f=f->next;
	}
	return false;
}

int Graphs_P3::getWeight(int from, int to){ //returns the weight of the edge between the vertices from and to
	int index=vertexConverter[from]-1;
	if (isEdge(from, to)){
		Vertex* f = &theVertices[index];

		while(f){
			if(f->next->name == to){
				return f->next->weight;
			}
			f=f->next;
		}
	}
	return -1;
}

vector<int> Graphs_P3::getAdjacent(int vertex){  //return an array of integers representing vertices adjacent to vertex{
	queue<int> q;
	int index = vertexConverter[vertex]-1;
	Vertex* v = &theVertices[index];
	while(v){
		if (v->next){
			q.push(v->next->name);
		}
		v = v->next;
	}
	int size = q.size();
	vector<int> output;
	for(int i = 0; i != size; ++i){
		output.push_back(q.front());
		q.pop();
	}
	return output;
}

void Graphs_P3::printDijkstra(int source){
	//prints result of running Dijkstra algorithm with source vertex
	set<int> s;//finalized list
	int* d = new int[numVertices]; //distances list
	int* p = new int[numVertices]; //prior nodes list
	//initialize all distance list
	for (int i = 0; i!= numVertices; i++){
		d[i]= numeric_limits<int>::max() ;
		p[i]=0;
	}
	//init the first thing to traverse(source)
	int index = vertexConverter[source]-1;
	vector<int> adj;
	d[index]=0;
	p[index]=0;
	int newSum = 0;
	int size;
	int j=0;
	//traverse the vertices
	while (s.size() != numVertices){
		//insert source into the finalized list
		s.insert(index);
		//get adjency list
		adj = getAdjacent(theVertices[index].name);//need to be checked
		//traverse adj list;
		j=0;
		while(j!=adj.size()){
			/*if statement: the distance to adjacent node+vertex distance to start < the stored value distance
	inside then change to the smaller value and then update the p list
			 */
			newSum = getWeight(theVertices[index].name, adj[j])+d[index];
			if (newSum < d[vertexConverter[adj[j]]-1]){
				d[vertexConverter[adj[j]]-1] = newSum;
				p[vertexConverter[adj[j]]-1] = theVertices[index].name;
			}
			j++;
		}
		//Traverse the dlist and find the min
		index=getMinIndex(d,s,numVertices);//return the index of the min distance
	}
	//some ways to print out stuff but save it to the last.
	cout<<"V\ D\ P";
	for (int i=0;i<numVertices;i++){
		if(theVertices[i].name!= source){
		cout<<"\n";
		cout<<theVertices[i].name<<"\ ";
		cout<<d[i]<<"\ ";
		printPath(i,p,theVertices,vertexConverter);
		}
	}
}
void Graphs_P3::printGraph(){
	Vertex* v;
	for(int i =0; i<numVertices; i++){
		v= &theVertices[i];
		while(v){
			cout<<v->name;
			if(v->next)
				cout<<" ";
			v = v->next;
		}
		cout<<"\n";
	}
}

int mainfasdf()
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

