#pragma once
#include <QObject>
#include <QSize>
#include <QPoint>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>

class PaintButton : public QObject{
    Q_OBJECT
public:

    enum BtnStatus {
        Normal,
        Hoverd,
        Pressed
    };

    PaintButton(QObject* parent);
    virtual ~PaintButton();

    void move(const QPoint& pos);
    void resize(const QSize& size);
    void setVisible(bool bVisible);

    QPoint pos() const;
    QSize size() const;
    QRect geometry();
    BtnStatus getCurrentStatus() const;
    bool isVisible() const;
    

    void setNormalPic(const QPixmap& pixmap);
    void setHoverdPic(const QPixmap& pixmap);
    void setPressedPic(const QPixmap& pixmap);
    void setTriStatusPic(const QPixmap& pixmap);

    bool mousePressEvent(QMouseEvent* event);
    bool mouseMoveEvent(QMouseEvent* event);
    bool mouseReleaseEvent(QMouseEvent* event);
    void paint(QPainter& painter);

signals:
    void signalBtnStatusChanged(BtnStatus status);
    void signalBtnClicked();

protected:
    void changeCurrentBtnStatus(BtnStatus status);
    bool isBtnContainsPos(const QPoint& pos);
    QPixmap getStatusPixmap(BtnStatus status);

private:
    QPoint m_pos;
    QSize m_size;
    QPixmap m_normalStatusPixmap;
    QPixmap m_hoverdStatusPixmap;
    QPixmap m_pressedStatusPixmap;
    BtnStatus m_currentBtnStatus = BtnStatus::Normal;
    bool m_bIsVisible = true;
};

