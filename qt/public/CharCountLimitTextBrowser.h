#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: CharCountLimitTextBrowser.h
// Author: wangwenxi
// Date: 2023.07.07
// Comment: �������ָ����ĵ���
//////////////////////////////////////////////////////////////////////////


#include <QFrame>
#include "ui_CharCountLimitTextBrowser.h"

class CharCountLimitTextBrowser : public QFrame {
    Q_OBJECT

public:
    CharCountLimitTextBrowser(QWidget* parent = nullptr);
    ~CharCountLimitTextBrowser();

    void setMaxCharCount(int nMaxCount);

protected:
    void initUI();
    void initConnect();

    void onTextBrowserTextChanged();
    void updateCharCountLabel();

private:
    Ui::CharCountLimitTextBrowser ui;
    int m_nMaxCharCount = 0;

};

