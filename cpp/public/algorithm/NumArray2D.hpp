#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: NumArray2D.hpp
// Author: wangwenxi
// Date: 2022.10.20
// Comment: 二维前缀和算法
//////////////////////////////////////////////////////////////////////////
#include <vector>

class NumArray2D {
public:
    NumArray2D(const std::vector<std::vector<int>>& matrix) {
        if (matrix.size() == 0) {
            return;
        }

        m_matrix.resize(matrix.size() + 1, std::vector<int>(matrix[0].size() + 1, 0));
        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < matrix[0].size(); ++col) {
                m_matrix[row + 1][col + 1] = matrix[row][col] + m_matrix[row][col + 1] + m_matrix[row + 1][col] - m_matrix[row][col];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return m_matrix[row2+1][col2+1] - m_matrix[row2+1][col1] - m_matrix[row1][col2+1] + m_matrix[row1][col1];
    }

private:
    std::vector<std::vector<int>> m_matrix;
};