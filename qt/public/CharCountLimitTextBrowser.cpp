#include "CharCountLimitTextBrowser.h"

namespace {
const int DEFAULT_MAX_CHAR_COUNT = 1000;
}

CharCountLimitTextBrowser::CharCountLimitTextBrowser(QWidget* parent /*= nullptr*/) : QFrame(parent), m_nMaxCharCount(DEFAULT_MAX_CHAR_COUNT) {
    initUI();
    initConnect();
}

CharCountLimitTextBrowser::~CharCountLimitTextBrowser() {

}

void CharCountLimitTextBrowser::setMaxCharCount(int nMaxCount) {
    m_nMaxCharCount = nMaxCount;
}

void CharCountLimitTextBrowser::initUI() {
    ui.setupUi(this);
    updateCharCountLabel();
    ui.textBrowser->setReadOnly(false);
}

void CharCountLimitTextBrowser::initConnect() {
    connect(ui.textBrowser, &QTextBrowser::textChanged, this, &CharCountLimitTextBrowser::onTextBrowserTextChanged);
}

void CharCountLimitTextBrowser::onTextBrowserTextChanged() {
    updateCharCountLabel();
}

void CharCountLimitTextBrowser::updateCharCountLabel() {
    int nCurrentCount = ui.textBrowser->toPlainText().trimmed().size();
    QString strText = QString("%1/%2").arg(nCurrentCount).arg(m_nMaxCharCount);
    ui.charCountLabel->setText(strText);
}
