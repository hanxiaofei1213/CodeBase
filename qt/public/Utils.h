#pragma once

class Utils {
    // 使用QPainter模拟绘制出阴影
    static void drawShadow(QPainter& painter, const QRect& rect);
    static QRect getDesktopRect(const QWidget* widget);
};

