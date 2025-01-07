#pragma once
#include <vector>
#include <queue>
//////////////////////////////////////////////////////////////////////////
// FileName: MedianHelp.hpp
// Author: wangwenxi
// Date: 2022.12.18
// Comment: 求出中位数
//////////////////////////////////////////////////////////////////////////

class MedianHelp
{
public:
    MedianHelp() {}

    void addNum(int nNum) {
        m_nSize++;
        if (m_lessQueue.empty()) {
            m_lessQueue.push(nNum);
            return;
        }

        if (nNum > m_lessQueue.top()) {
            m_greaterQueue.push(nNum);
        } else {
            m_lessQueue.push(nNum);
        }

        balanceQueue();
    }

    double getMedian() {
        if (m_nSize == 0) {
            return 0;
        }

        if (m_nSize % 2 == 1) {
            return m_lessQueue.top();
        }

        return (m_lessQueue.top() + m_greaterQueue.top()) / 2.0;
    }

protected:

    void balanceQueue() {
        int nGreaterNeedSize = m_nSize / 2;
        if (m_greaterQueue.size() == nGreaterNeedSize) {
            return;
        }

        if (m_greaterQueue.size() < nGreaterNeedSize) {
            m_greaterQueue.push(m_lessQueue.top());
            m_lessQueue.pop();
        } else {
            m_lessQueue.push(m_greaterQueue.top());
            m_greaterQueue.pop();
        }
    }

private:
    int m_nSize = 0;
    std::priority_queue<int, std::vector<int>, std::less<int>> m_lessQueue;
    std::priority_queue<int, std::vector<int>, std::greater<int>> m_greaterQueue;
};