#ifndef GRAPHX_H
#define GRAPHX_H
#include <string>
#include <vector>

using namespace std;
class graph
{
  protected:
    struct properti{
        vector< vector<float> > adjacencyMatrix;
        vector< vector<float> > adjacencyTransversal;
        vector<int> visitedVertexLog;
        vector <int> shortest;
    }propGraph;
    int vertexCount;
    int source;
    int dest;
  public:
    graph();
    ~graph();
    virtual void proses(string, int, int, int) = 0;
    virtual void show() = 0;
    void lihatRelasi(bool);
    properti getData(){return propGraph;}
    void defaultMatrix();
    void addEdge(int, int, float);
    void removeEdge(int, int);
    static graph *graphAlgoritma(string pilihan);
};


class mstBobot: public graph{
    private:
        int lower;
        int minIndexBaris;
        int minIndexKolom;
    public:
        void show();
        void proses(string, int, int, int);
        void _prim(int);
};

class mst: public graph{
    private:
        queue<int> node;
        int topNode;
    public:
        void show();
        void proses(string, int, int, int);
        void _bfs(int);
        void _dfs(int);
};

class findPath: public graph{
    private:
        vector< pair<int, int> > dist;
        int minVal;
        int minIndex;
    public:
        void show();
        void proses(string, int, int, int);
        void _djikstra(int, int);
        void getDistance(vector< pair<int, int> > &dist);
        void getPath(vector< pair<int, int> > &dist, int, int);
        vector<int> getShortest();
        int minDistance(vector< pair<int, int> > &dist);


};

#endif // GRAPH_H
