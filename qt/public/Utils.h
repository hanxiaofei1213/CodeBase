#pragma once

class Utils {
    // ʹ��QPainterģ����Ƴ���Ӱ
    static void drawShadow(QPainter& painter, const QRect& rect);
    static QRect getDesktopRect(const QWidget* widget);
};

