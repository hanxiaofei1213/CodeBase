#include "PaintButton.h"

PaintButton::PaintButton(QObject* parent) : QObject(parent) {

}

PaintButton::~PaintButton() {

}

void PaintButton::move(const QPoint& pos) {
    m_pos = pos;
}

void PaintButton::resize(const QSize& size) {
    m_size = size;
}

void PaintButton::setVisible(bool bVisible) {
    m_bIsVisible = bVisible;
}

QPoint PaintButton::pos() const {
    return m_pos;
}

QSize PaintButton::size() const {
    return m_size;
}

QRect PaintButton::geometry() {
    return QRect(m_pos, m_size);
}

PaintButton::BtnStatus PaintButton::getCurrentStatus() const {
    return m_currentBtnStatus;
}

bool PaintButton::isVisible() const {
    return m_bIsVisible;
}

void PaintButton::setNormalPic(const QPixmap& pixmap) {
    m_normalStatusPixmap = pixmap;
}

void PaintButton::setHoverdPic(const QPixmap& pixmap) {
    m_hoverdStatusPixmap = pixmap;
}

void PaintButton::setPressedPic(const QPixmap& pixmap) {
    m_pressedStatusPixmap = pixmap;
}

void PaintButton::setTriStatusPic(const QPixmap& pixmap) {
    if (pixmap.isNull()) {
    	return;
    }

    int nWidth = pixmap.width();
    int nEachPixmapWidth = nWidth / 3.0;
    m_normalStatusPixmap = pixmap.copy(0, 0, nEachPixmapWidth, pixmap.height());
    m_hoverdStatusPixmap = pixmap.copy(nEachPixmapWidth, 0, nEachPixmapWidth, pixmap.height());
    m_pressedStatusPixmap = pixmap.copy(nEachPixmapWidth * 2, 0, nEachPixmapWidth, pixmap.height());
}

bool PaintButton::mousePressEvent(QMouseEvent* event) {
    if (!event) {
    	return false;
    }

    QPoint mousePos = event->pos();
    if (isBtnContainsPos(mousePos)) {
        changeCurrentBtnStatus(Pressed);
        return true;
    }

    return false;
}

bool PaintButton::mouseMoveEvent(QMouseEvent* event) {
    if (!event) {
    	return false;
    }

    if (event->button() != Qt::NoButton) {
        return false;
    }

    if (isBtnContainsPos(event->pos())) {
        changeCurrentBtnStatus(Hoverd);
        return true;
    } 
        
    changeCurrentBtnStatus(Normal);
    return false;
}

bool PaintButton::mouseReleaseEvent(QMouseEvent* event) {
    if (!event) {
        return false;
    }

    bool bRet = false;
    if (isBtnContainsPos(event->pos())) {
        if (m_currentBtnStatus == Pressed) {
            emit signalBtnClicked();
        }

        bRet = true;
    }

    changeCurrentBtnStatus(Normal);
    return bRet;
}

void PaintButton::paint(QPainter& painter) {
    if (!m_bIsVisible) {
        return;
    }

    painter.save();
    
    painter.setRenderHint(QPainter::Antialiasing);
    QPixmap pixmap = getStatusPixmap(m_currentBtnStatus);
    painter.drawPixmap(geometry(), pixmap);

    painter.restore();
}

void PaintButton::changeCurrentBtnStatus(BtnStatus status) {
    m_currentBtnStatus = status;
    emit signalBtnStatusChanged(m_currentBtnStatus);
}

bool PaintButton::isBtnContainsPos(const QPoint& pos) {
    return geometry().contains(pos);
}

QPixmap PaintButton::getStatusPixmap(BtnStatus status) {
    if (status == Hoverd && !m_hoverdStatusPixmap.isNull()) {
        return m_hoverdStatusPixmap;
    }

    if (status == Pressed && !m_pressedStatusPixmap.isNull()) {
        return m_pressedStatusPixmap;
    }

    return m_normalStatusPixmap;
}

