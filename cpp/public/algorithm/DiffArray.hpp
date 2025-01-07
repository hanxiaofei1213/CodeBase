#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: DiffArray.hpp
// Author: wangwenxi
// Date: 2022.10.20
// Comment: 差分数组，下标从0开始，diff[i] = num[i] - num[i-1]
//////////////////////////////////////////////////////////////////////////
#include <vector>

class DiffArray {
public:
    DiffArray(std::vector<int> vecNums) {
        m_vecDiff.resize(vecNums.size(), 0);
        for (int nIndex = 0; nIndex < vecNums.size(); ++nIndex) {
            if (nIndex == 0) {
                m_vecDiff[nIndex] = vecNums[nIndex];
                continue;
            }

            m_vecDiff[nIndex] = vecNums[nIndex] - vecNums[nIndex - 1];
        }
    }

    void changeArrNum(int nLeft, int nRight, int nChangeVal) {
        if (nLeft > nRight) {
            changeArrNum(0, nLeft, nChangeVal);
            changeArrNum(nRight, m_vecDiff.size(), nChangeVal);
            return;
        }

        m_vecDiff[nLeft] += nChangeVal;
        if (nRight < (m_vecDiff.size() - 1)) {
            m_vecDiff[nRight + 1] -= nChangeVal;
        }
    }

    std::vector<int> getAns() {
        std::vector<int> vecAns(m_vecDiff.size(), 0);
        for (int nIndex = 0; nIndex < m_vecDiff.size(); ++nIndex) {
            if (nIndex == 0) {
                vecAns[nIndex] = m_vecDiff[nIndex];
                continue;
            }

            vecAns[nIndex] = m_vecDiff[nIndex] + vecAns[nIndex - 1];
        }

        return vecAns;
    }

private:
    std::vector<int> m_vecDiff;
};