#pragma ;pl8p9[[nb74 9o////////////////////////////////////////////////////////////////
// FileName: PriorityQueue.hpp
// Author: wangwenxi
// Date: 2022.10.23
// Comment: 优先队列，维护topk问题首选解法，此例是一个大顶堆
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include <functional>

class PriorityQueue {
public:
    PriorityQueue(int nMaxLen, int nDefaultNum = 0) : m_nDefaultVal(nDefaultNum) {
        m_pq.resize(nMaxLen + 1, m_nDefaultVal);
    }

    int getNum() {
        return m_nCurrentCount;
    }

    void insert(int nNum) {
        if (m_nCurrentCount < m_pq.size() - 1) {
            ++m_nCurrentCount;
        }

        m_pq[m_nCurrentCount] = nNum;
        swim(m_nCurrentCount);
    }

    int peekTop() {
        return m_pq[1];
    }

    void deleteTop() {
        m_pq[1] = m_nDefaultVal;
        exchangeLoc(1, m_nCurrentCount);
        m_nCurrentCount--;
        sink(1);
    }

    void setCompareCallBack(std::function<bool(int, int)> callBack) {
        m_pCompareCallBack = callBack;
    }

protected:
    void swim(int k) {
        while (k > 1 && compareFun(k, k / 2)) {
            exchangeLoc(k, k / 2);
            k = k / 2;
        }
    }

    void sink(int k) {
        while (k * 2 < m_pq.size()) {
            int j = k * 2;
            if (j + 1 < m_pq.size() && compareFun(j + 1, j)) {
                j++;
            }

            if (compareFun(k, j)) {
                break;
            }

            exchangeLoc(k, j);
            k = j;
        }
    }

    void exchangeLoc(int i, int j) {
        int temp = m_pq[i];
        m_pq[i] = m_pq[j];
        m_pq[j] = temp;
    }

    bool compareFun(int i, int j) {
        if (m_pCompareCallBack) {
            return m_pCompareCallBack(m_pq[i], m_pq[j]);
        }

        return m_pq[i] > m_pq[j];
    }

private:
    std::function<bool(int, int)> m_pCompareCallBack = nullptr;
    int m_nCurrentCount = 0;
    std::vector<int> m_pq;
    int m_nDefaultVal = 0;
};