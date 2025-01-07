#include "ThreadTemplate.h"
#include <windows.h>
#include <QDebug>



ThreadTemplate::ThreadTemplate() {
    initConnect();

    moveToThread(&m_thread);
    m_thread.start();

}

ThreadTemplate::~ThreadTemplate() {
    m_thread.quit();
    m_thread.wait();
}

void ThreadTemplate::initConnect() {
    connect(this, &ThreadTemplate::signalTrigger1, this, &ThreadTemplate::slotDoSomething1);
    connect(this, &ThreadTemplate::signalTrigger2, this, &ThreadTemplate::slotDoSomething2);
    connect(this, &ThreadTemplate::signalTrigger3, this, &ThreadTemplate::slotDoSomething3);
}

void ThreadTemplate::slotDoSomething1() {
    qDebug() << "do something1 begin";
    Sleep(2000);
    qDebug() << "do something1 end";
}

void ThreadTemplate::slotDoSomething2(const QMap<QString, QString>& myMap) {
    qDebug() << "do something2 begin";
    Sleep(2000);
    qDebug() << "do something2 end";
}

void ThreadTemplate::slotDoSomething3(const QVariant& var) {
    qDebug() << "do something3 begin";
    Sleep(2000);
    qDebug() << "do something3 end";
}
