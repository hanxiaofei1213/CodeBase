#pragma once
#include <vector>

class Graph {
public:
    Graph(int v) : m_nVertexCount(v) {
        m_adjList.resize(v);
    }

    void addEdge(int start, int end) {
        m_adjList[start].push_back(end);
        m_adjList[end].push_back(start);
        m_nEdgeCount++;
    }

    std::vector<int> adjPoint(int v) {
        return m_adjList[v];
    }

    int getVertexCount() {
        return m_nVertexCount;
    }

    int getEdgeCount() {
        return m_nEdgeCount;
    }

private:
    int m_nVertexCount = 0;
    int m_nEdgeCount = 0;
    std::vector<std::vector<int>> m_adjList;
};

class DfsSearchGraph {
public:
    DfsSearchGraph(Graph graph, int nStart) {
        m_bMarked.resize(graph.getVertexCount(), false);
        dfs(graph, nStart);
    }

    void dfs(Graph graph, int nStart) {
        m_bMarked[nStart] = true;
        m_nCount++;
        for (auto it : graph.adjPoint(nStart)) {
            if (!m_bMarked[it]) {
                dfs(graph, it);
            }
        }
    }

    bool marked(int nEnd) {
        return m_bMarked[nEnd];
    }

    int getCount() {
        return m_nCount;
    }

private:
    std::vector<bool> m_bMarked;
    int m_nCount = 0;
};