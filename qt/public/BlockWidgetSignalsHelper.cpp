
#include "BlockWidgetSignalsHelper.h"

BlockWidgetSignalsHelper::BlockWidgetSignalsHelper(QWidget* pNeedBlockWidget) {
    m_pNeedBlockWidget = pNeedBlockWidget;
    blockWidgetSignals(pNeedBlockWidget, true);
}

BlockWidgetSignalsHelper::~BlockWidgetSignalsHelper() {
    blockWidgetSignals(m_pNeedBlockWidget, false);
}

void BlockWidgetSignalsHelper::blockWidgetSignals(QWidget* pWidget, bool bBlock) {
    if (!pWidget) {
        return;
    }

    pWidget->blockSignals(bBlock);
    QList<QObject*> children = pWidget->children();
    for (QObject* pChild : children) {
        blockWidgetSignals(static_cast<QWidget*>(pChild), bBlock);
    }
}
