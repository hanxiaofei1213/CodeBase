#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: BlockWidgetSignalsHelper.h
// Author: wangwenxi
// Date: 2023.07.07
// Comment: ����widget�Լ��ӿؼ��ź�
//////////////////////////////////////////////////////////////////////////

#include <QWidget>

class BlockWidgetSignalsHelper {

public:
    BlockWidgetSignalsHelper(QWidget* pNeedBlockWidget);
    ~BlockWidgetSignalsHelper();

protected:
    void blockWidgetSignals(QWidget* pWidget, bool bBlock);

private:
    QWidget* m_pNeedBlockWidget = nullptr;
};
