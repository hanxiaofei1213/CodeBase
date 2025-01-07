#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: BlockWidgetSignalsHelper.h
// Author: wangwenxi
// Date: 2023.07.07
// Comment: 阻塞widget以及子控件信号
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
