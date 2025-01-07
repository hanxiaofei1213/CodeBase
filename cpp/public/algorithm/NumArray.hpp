#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: NumArray.hpp
// Author: wangwenxi
// Date: 2022.10.20
// Comment: Ç°×ººÍËã·¨
//////////////////////////////////////////////////////////////////////////
#include <vector>

class NumArray {
public:
    NumArray(const std::vector<int>& num) {
        m_num.resize(num.size(), 0);
        for (int index = 0; index < num.size(); ++index) {
            if (index == 0) {
                m_num[index] = num[index];
                continue;
            }

            m_num[index] = num[index] + m_num[index - 1];
        }
    }

    ~NumArray() {

    }

    int getSum(int nLeft, int nRight) {
        if (m_num.size() == 0) {
            return 0;
        }

        if (nRight >= m_num.size()) {
            nRight = m_num.size() - 1;
        }

        if (nLeft <= 0) {
            return m_num[nRight];
        }

        return m_num[nRight] - m_num[nLeft - 1];
    }

private:
    std::vector<int> m_num;
};