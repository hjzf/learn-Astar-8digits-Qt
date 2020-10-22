#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eightdigits.h"
#include "searchthread.h"
#include <QMovie>
#include <QSound>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void timerEvent(QTimerEvent* );
    void refresh(int * b);
    void refreshOutput();
    void startGIF();
    void stopGIF();
    void allEnableTrue();
    void allEnableFalse();

    int static algorithmId;
    int static heuristicFuncId;
    int static multipleId;
    int static a[9];
    int static d[9];
    vector<int *> static path;
    bool static isFinished;
    QString static text;

private:
    Ui::MainWindow *ui;
    QString picturePath[9];
    int width;
    int startX;
    int startY;
    int timerId;
    unsigned long long pathIndex;
    bool mouseClick;
    QSound * clickSound;
    QMovie * movie;
};
#endif // MAINWINDOW_H
