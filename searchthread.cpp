#include "searchthread.h"

SearchThread::SearchThread(QObject *parent) : QThread(parent)
{

}
void SearchThread::run(){
    switch(MainWindow::algorithmId){
    case 0:
        switch (MainWindow::heuristicFuncId) {
        case 0:
            EightDigits::Astar(MainWindow::a,MainWindow::d,MainWindow::isFinished,EightDigits::h1,MainWindow::path,MainWindow::text,MainWindow::multipleId+1);
            break;
        case 1:
            EightDigits::Astar(MainWindow::a,MainWindow::d,MainWindow::isFinished,EightDigits::h2,MainWindow::path,MainWindow::text,MainWindow::multipleId+1);
            break;
        case 2:
            EightDigits::Astar(MainWindow::a,MainWindow::d,MainWindow::isFinished,EightDigits::h3,MainWindow::path,MainWindow::text,MainWindow::multipleId+1);
            break;
        case 3:
            EightDigits::Astar(MainWindow::a,MainWindow::d,MainWindow::isFinished,EightDigits::h4,MainWindow::path,MainWindow::text,MainWindow::multipleId+1);
            break;
        default: break;
        }
        break;
    case 1:
        switch (MainWindow::heuristicFuncId) {
        case 0:
            EightDigits::GOS(MainWindow::a,MainWindow::d,MainWindow::isFinished,EightDigits::h1,MainWindow::path,MainWindow::text,MainWindow::multipleId+1);
            break;
        case 1:
            EightDigits::GOS(MainWindow::a,MainWindow::d,MainWindow::isFinished,EightDigits::h2,MainWindow::path,MainWindow::text,MainWindow::multipleId+1);
            break;
        case 2:
            EightDigits::GOS(MainWindow::a,MainWindow::d,MainWindow::isFinished,EightDigits::h3,MainWindow::path,MainWindow::text,MainWindow::multipleId+1);
            break;
        case 3:
            EightDigits::GOS(MainWindow::a,MainWindow::d,MainWindow::isFinished,EightDigits::h4,MainWindow::path,MainWindow::text,MainWindow::multipleId+1);
            break;
        default: break;
        }
        break;
    case 2:
        EightDigits::BFS(MainWindow::a,MainWindow::d,MainWindow::isFinished,MainWindow::path,MainWindow::text);
        break;
    default:break;
    }
    emit finished();
}
