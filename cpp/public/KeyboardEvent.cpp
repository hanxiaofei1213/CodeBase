#include "KeyboardEvent.h"
#include <windows.h>

KeyboardEvent::KeyboardEvent(int nKey) {
    m_vecKeys.push_back(nKey);
}

KeyboardEvent::KeyboardEvent(std::vector<int> vecKeys) : m_vecKeys(vecKeys) {
    
}

KeyboardEvent::~KeyboardEvent() {

}

void KeyboardEvent::exec() {
    pressAllKeys();
    releaseAllKeys();
}

void KeyboardEvent::pressAllKeys() {
    for (int nIndex = 0; nIndex < m_vecKeys.size(); ++nIndex) {
        ::keybd_event(m_vecKeys[nIndex], 0, 0, 0);
    }
}

void KeyboardEvent::releaseAllKeys() {
    for (int nIndex = 0; nIndex < m_vecKeys.size(); ++nIndex) {
        ::keybd_event(m_vecKeys[nIndex], 0, 2, 0);
    }
}
