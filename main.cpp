/*
 * main.cpp
 *
 *  Created on: Jul 26, 2018
 *      Author: louise0
 */
#include "dijstra.h"

#include <iostream>
#include <set>
using namespace std;
int main88()
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


