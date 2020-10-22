#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QObject>
#include <QThread>
#include "eightdigits.h"
#include "mainwindow.h"
#include "QtDebug"

class SearchThread : public QThread
{
    Q_OBJECT
public:
    explicit SearchThread(QObject *parent = nullptr);
protected:
    void run();

signals:
    void finished();

};


#endif // SEARCHTHREAD_H
