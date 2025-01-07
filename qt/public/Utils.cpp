#include <QPainter>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>
#include "Utils.h"

void Utils::drawShadow(QPainter& painter, const QRect& rect) {
    painter.save();

    QColor borderColor("#dddddd");
    painter.setPen(borderColor);
    painter.drawRect(rect);

    int nShodowColorAlpha = 24;
    QColor shadowColor(210, 210, 210, nShodowColorAlpha);
    int shadowSize = 8;
    for (int i = 1; i <= shadowSize; ++i) {
        QRect shadowRect = rect.adjusted(-i, -i, i, i);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(shadowColor, Qt::SolidPattern));
        painter.drawRect(shadowRect);
        shadowColor.setAlpha(shadowColor.alpha() - nShodowColorAlpha / shadowSize);
    }

    painter.restore();
}

QRect Utils::getDesktopRect(const QWidget* widget) {
    QDesktopWidget* desktopWidget = QApplication::desktop();
    if (!desktopWidget || !widget)
        return {};

    QRect deskRect = desktopWidget->availableGeometry(widget);
    return deskRect;
}
