#include <iostream>
#include <string>
#include <stdio.h>
#include <queue>
#include <stack>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <math.h>
#include <map>
#include "graphx.h"

using namespace std;
graph::graph()
{
   propGraph.adjacencyMatrix.resize(100, vector<float>(100, -1));
}

graph::~graph()
{
    //dtor
}

graph *graph::graphAlgoritma(string jenis){
    if (jenis == "mst")
        return new mst;
    else if (jenis == "mstBobot")
        return new mstBobot;
    else if (jenis == "findPath")
        return new findPath;
}

void graph::addEdge(int v1, int v2, float val){
    propGraph.adjacencyMatrix.at(v1).at(v2) = val;
    propGraph.adjacencyMatrix.at(v2).at(v1) = val;
}
void graph::removeEdge(int v1, int v2){
    propGraph.adjacencyMatrix.at(v1).at(v2) = -1;
    propGraph.adjacencyMatrix.at(v2).at(v1) = -1;
}

void graph::defaultMatrix(){
    propGraph.adjacencyTransversal.clear();
    propGraph.adjacencyTransversal.resize(vertexCount, vector<float>(vertexCount,-1));
    propGraph.visitedVertexLog.clear();
}

void graph::lihatRelasi(bool defaultMatrix){
    vector< vector<float> >& matrix = defaultMatrix ? propGraph.adjacencyMatrix: propGraph.adjacencyTransversal;
    //akses hanya sampai garis diagonal matrix atau batas pertemuan vertex yang sama pada matrix
    for (int i = 0; i < vertexCount; i++)
        for( int j = 0; j < i; j++)
            if ( matrix.at(i).at(j)!= -1 )
                cout << i <<"-"<< j << " ";
    cout << endl;

    }

///////FINDPATH
void findPath::show(){
    cout << "MINIMUM SPANNING TREE GRAPH TIDAK BERBOBOT" << endl << endl;
    cout << "Relasi antar node SEBELUM di proses" << endl;
    lihatRelasi(true);
    cout << endl << endl;
    cout << "Relasi antar node SETELAH di proses" << endl;
    lihatRelasi(false);
}

void findPath::proses(string jenisFindPath, int start, int dest, int vertex){
    vertexCount = vertex;
    defaultMatrix();
    dist.resize(vertexCount, make_pair(-1, INT_MAX));
    if (jenisFindPath == "djikstra")
        _djikstra(start, dest);

}

void findPath::_djikstra(int source, int dest){
    dist.at(source).second = 0;
    for (int i = 0; i < vertexCount; i++){
        int currVertex = minDistance(dist);
        propGraph.visitedVertexLog.push_back(currVertex);

        if (currVertex == dest){
            //printDistance(dist);
            getPath(dist, dest, source);
            return;
        }

        for( int j = 0; j < vertexCount; j++)
            if( find(propGraph.visitedVertexLog.begin(), propGraph.visitedVertexLog.end(), j) == propGraph.visitedVertexLog.end() && propGraph.adjacencyMatrix.at(currVertex).at(j)!= -1 &&  dist.at(currVertex).second + propGraph.adjacencyMatrix.at(currVertex).at(j) < dist.at(j).second )
                dist.at(j).second = dist.at(currVertex).second + propGraph.adjacencyMatrix.at(currVertex).at(j), dist.at(j).first = currVertex;

    }

}



vector <int>  findPath::getShortest(){
    getPath(dist,dest,source);
    return propGraph.shortest;
}

void findPath::getDistance(vector< pair<int, int> > &dist){
    cout << "Vertex   Distance from Source" << endl;
    for (int i = 0; i < vertexCount; i++)
        if(dist.at(i).first!= -1)
            cout << "vertex " << i + 1 << ": " << dist.at(i).second << ", Parent: " << dist.at(i).first + 1  << endl;
}

void findPath::getPath(vector< pair<int, int> > &dist, int dest, int source){
    if ( dist.at(dest).first == -1 ){
        cout << source << " ";
        propGraph.shortest.push_back(source);
        return;
    }
    propGraph.adjacencyTransversal.at(dist.at(dest).first).at(dest) = 1;
    propGraph.adjacencyTransversal.at(dest).at(dist.at(dest).first) = 1;
    getPath(dist, dist.at(dest).first, source );
    cout << dest << " ";
    propGraph.shortest.push_back(dest);
}

int findPath::minDistance(vector< pair<int, int> > &dist){
    int minVal = INT_MAX, minIndex;

    for (int i = 0; i < vertexCount; i++)
        if( find(propGraph.visitedVertexLog.begin(), propGraph.visitedVertexLog.end(), i) == propGraph.visitedVertexLog.end()  && dist.at(i).second <= minVal )
            minVal = dist.at(i).second, minIndex = i;

    return minIndex;
}


///////MINIMUM SPANNING TREE
void mst::show(){
    cout << "MINIMUM SPANNING TREE GRAPH TIDAK BERBOBOT" << endl << endl;
    cout << "Relasi antar node SEBELUM di proses" << endl;
    //lihatRelasi(true);
    cout << endl << endl;
    cout << "Relasi antar node SETELAH di proses" << endl;
    //lihatRelasi(false);
}

void mst::proses(string jenisMst, int start, int dest, int vertex){
    vertexCount = vertex;
    defaultMatrix();
    if (jenisMst == "bfs")
        _bfs(start);
    else if (jenisMst == "dfs")
        _dfs(start);

}

void mst::_bfs(int start){
    node.push(start);
    while(!node.empty()){
        topNode = node.front();
        for (int i = 0; i < vertexCount; i++){
            if ( propGraph.adjacencyMatrix.at(topNode).at(i)!= -1 && find(propGraph.visitedVertexLog.begin(), propGraph.visitedVertexLog.end(), i) == propGraph.visitedVertexLog.end() ){
                propGraph.adjacencyTransversal.at(topNode).at(i) = 1;
                propGraph.adjacencyTransversal.at(i).at(topNode) = 1;
                node.push(i);
                propGraph.visitedVertexLog.push_back(i);
            }
        }

        node.pop();
    }

}

void mst::_dfs(int topNode = 0){
        for (int i = 0; i < vertexCount; i++)
            if ( propGraph.adjacencyMatrix.at(topNode).at(i)!=-1 && find(propGraph.visitedVertexLog.begin(), propGraph.visitedVertexLog.end(), i) == propGraph.visitedVertexLog.end() ){
                    propGraph.adjacencyTransversal.at(topNode).at(i) = 1;
                    propGraph.adjacencyTransversal.at(i).at(topNode) = 1;
                    propGraph.visitedVertexLog.push_back(i);
                    _dfs(i);
            }
}



///////MINIMUM SPANNING TREE BERBOBOT
void mstBobot::show(){
    cout << "MINIMUM SPANNING TREE GRAPH BERBOBOT_PRIM" << endl << endl;
    cout << "Relasi antar node SEBELUM di proses" << endl;
    lihatRelasi(true);
    cout << endl << endl;
    cout << "Relasi antar node SETELAH di proses" << endl;
    lihatRelasi(false);

}

void mstBobot::proses(string jenisMstBobot, int start, int dest, int vertex){
    vertexCount = vertex;
    defaultMatrix();
    if (jenisMstBobot == "prim")
        _prim(start);
}

void mstBobot::_prim(int start){
    propGraph.visitedVertexLog.push_back(start);
    for( int n = 0; n < vertexCount-1; n++  ){
        for (int j = 0; j < vertexCount; j++)
            if( find(propGraph.visitedVertexLog.begin(), propGraph.visitedVertexLog.end(), j) != propGraph.visitedVertexLog.end())
                 for (int i = 0; i < vertexCount; i++ )
                    if ( propGraph.adjacencyMatrix.at(j).at(i) < lower && find(propGraph.visitedVertexLog.begin(), propGraph.visitedVertexLog.end(), i) == propGraph.visitedVertexLog.end()  && propGraph.adjacencyMatrix.at(j).at(i)!= -1)
                        lower = propGraph.adjacencyMatrix.at(j).at(i), minIndexBaris = j, minIndexKolom = i;

        propGraph.adjacencyTransversal.at(minIndexBaris).at(minIndexKolom) = 1;
        propGraph.adjacencyTransversal.at(minIndexKolom).at(minIndexBaris) = 1;
        propGraph.visitedVertexLog.push_back(minIndexKolom);
        lower = INT_MAX;
    }
}
