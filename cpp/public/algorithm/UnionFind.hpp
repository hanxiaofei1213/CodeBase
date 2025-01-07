#pragma once
#include <vector>


class UnionFind {
public:
    UnionFind(int N) : m_nCount(N) {
        for (int i = 0; i < N; ++i) {
            m_vecUnionFind.push_back(i);
        }
    }

    virtual ~UnionFind() {

    }

    int count() {
        return m_nCount;
    }

    virtual int find(int p) = 0;

    virtual void makeUnion(int p, int q) = 0;

    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

protected:
    std::vector<int> m_vecUnionFind;
    int m_nCount = 0;
};

class QuickFindUF : public UnionFind {
public:
    QuickFindUF(int N) : UnionFind(N) {

    }

    virtual int find(int p) override {
        return m_vecUnionFind[p];
    }

    virtual void makeUnion(int p, int q) override {
        int nPid = find(p);
        int nQid = find(q);
        if (nPid == nQid) {
            return;
        }

        for (int i = 0; i < m_vecUnionFind.size(); ++i) {
            if (m_vecUnionFind[i] == nPid) {
                m_vecUnionFind[i] = nQid;
            }
        }

        m_nCount--;
    }
};

class QuickUnionUF : public UnionFind {
public:
    QuickUnionUF(int N) : UnionFind(N) {

    }

    virtual int find(int p) override {
        while (p != m_vecUnionFind[p]) {
            p = m_vecUnionFind[p];
        }

        return p;
    }

    virtual void makeUnion(int p, int q) override {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot) {
            return;
        }

        m_vecUnionFind[pRoot] = qRoot;
        m_nCount--;
    }
};

class WeightedQuickUnionUF : public QuickUnionUF {
public:
    WeightedQuickUnionUF(int N) : QuickUnionUF(N), m_ufSize(N, 1) {
        
    }

    virtual void makeUnion(int p, int q) override {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot) {
            return;
        }

        if (m_ufSize[pRoot] < m_ufSize[qRoot]) {
            m_vecUnionFind[pRoot] = qRoot;
            m_ufSize[qRoot] += m_ufSize[pRoot];
        } else {
            m_vecUnionFind[qRoot] = pRoot;
            m_ufSize[pRoot] += m_ufSize[qRoot];
        }

        m_nCount--;
    }

private:
    std::vector<int> m_ufSize;
};