#pragma once
#include <vector>

class KeyboardEvent {
public:
    KeyboardEvent(int nKey);
    KeyboardEvent(std::vector<int> vecKeys);
    ~KeyboardEvent();

    void exec();

protected:
    void pressAllKeys();
    void releaseAllKeys();

private:
    std::vector<int> m_vecKeys;
};

