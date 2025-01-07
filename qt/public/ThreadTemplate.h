#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: ThreadTemplate.h
// Author: wangwenxi
// Date: 2022.02.17
// Comment: Ïß³ÌÄ£°å
//////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QThread>
#include <QMap>
#include <QString>
#include <QVariant>



class ThreadTemplate : public QObject {
    Q_OBJECT
public:
    ThreadTemplate();
    ~ThreadTemplate();

    void initConnect();

    void slotDoSomething1();
    void slotDoSomething2(const QMap<QString, QString>& myMap);
    void slotDoSomething3(const QVariant& var);

signals:
    void signalTrigger1();
    void signalTrigger2(const QMap<QString, QString>& myMap);
    void signalTrigger3(const QVariant& var);
    

private:
    QThread m_thread;

};

