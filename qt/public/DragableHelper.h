#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: DragableHelper.h
// Author: wangwenxi
// Date: 2022.01.04
// Comment: 帮助无边框控件进行拖拽
//////////////////////////////////////////////////////////////////////////


#include <QPoint>
#include <QMouseEvent>
#include <QRect>

// 点击窗口任意位置均可移动
#define UI_DRAGABLE UI_DRAGABLE_WITH_TITLE_HEIGHT(-1)

// 点击窗口标题栏，才可移动
// @param nHeight 标题栏的高度，当nHeight为-1时，表示点击任意位置均可移动
#define UI_DRAGABLE_WITH_TITLE_HEIGHT(nHeight)                     \
protected:                                                         \
virtual void mousePressEvent(QMouseEvent* event) override {        \
    QRect headTitleRect(0, 0, width(), (nHeight));                 \
    if ((nHeight) != -1 && !headTitleRect.contains(event->pos()))  return;    \
    m_bBeginDrag_macro = true;                                     \
    m_dragPoint_macro = event->globalPos();                        \
}                                                                  \
virtual void mouseMoveEvent(QMouseEvent* event) override {         \
    if (!m_bBeginDrag_macro) return;                               \
                                                                   \
    int dx = event->globalX() - m_dragPoint_macro.x();             \
    int dy = event->globalY() - m_dragPoint_macro.y();             \
    m_dragPoint_macro = event->globalPos();                        \
    move(x() + dx, y() + dy);                                      \
}                                                                  \
virtual void mouseReleaseEvent(QMouseEvent* event) override {      \
    if (!m_bBeginDrag_macro) return;                               \
                                                                   \
    int dx = event->globalX() - m_dragPoint_macro.x();             \
    int dy = event->globalY() - m_dragPoint_macro.y();             \
    m_dragPoint_macro = event->globalPos();                        \
    move(x() + dx, y() + dy);                                      \
    m_bBeginDrag_macro = false;                                    \
}                                                                  \
private:                                                           \
bool m_bBeginDrag_macro = false;                                   \
QPoint m_dragPoint_macro;                                          \
