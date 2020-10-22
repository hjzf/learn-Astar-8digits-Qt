#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
int MainWindow::algorithmId=0;
int MainWindow::heuristicFuncId=0;
int MainWindow::multipleId=0;
int MainWindow::a[9]={1,3,2,4,0,5,6,7,8};
int MainWindow::d[9]={1,2,3,8,0,4,7,6,5};
bool  MainWindow::isFinished = true;
vector<int *>  MainWindow::path;
QString  MainWindow::text = "";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("八数码问题");
    setWindowIcon(QIcon(":/res/icon.ico"));
    clickSound = new QSound(":/res/click.wav");
    movie = new QMovie(":/res/loading.gif");
    ui->label->setMovie(movie);
    movie->start();
    ui->label->setVisible(false);
    width = 104;
    startX = 26;
    startY = 30;
    picturePath[0]=":/res/0.png";
    picturePath[1]=":/res/1.png";
    picturePath[2]=":/res/2.png";
    picturePath[3]=":/res/3.png";
    picturePath[4]=":/res/4.png";
    picturePath[5]=":/res/5.png";
    picturePath[6]=":/res/6.png";
    picturePath[7]=":/res/7.png";
    picturePath[8]=":/res/8.png";
    mouseClick = true;
    connect(ui->btnInput,&QPushButton::clicked,[=](){
        bool isOK = false;
        QString text = QInputDialog::getText(NULL,
                                             "输入起点",
                                             "输入八数码的摆放状态,示例: 132405678",
                                             QLineEdit::Normal,
                                             "132405678",
                                             &isOK,
                                             Qt::Drawer);
        if(isOK) {
            int * b =new  int [9];
            int j = 0;
            int repeat = 0^1^2^3^4^5^6^7^8;
            for (int i=0;i<9;i++) {
                int x = text.mid(i,1).toInt();
                if(x>=0&&x<=8){
                    b[j++]=x;
                    repeat =repeat^x;
                }
            }
            if(j==9&&repeat==0){
                refresh(b);
            }else {
                QMessageBox::information(NULL,
                                         "提示",
                                         "无效的输入,必须是0~8这9个数字的排列",
                                         QMessageBox::Yes);
            }
            delete [] b;
        }
    });

    connect(ui->btnInput2,&QPushButton::clicked,[=](){
        bool isOK = false;
        QString text = QInputDialog::getText(NULL,
                                             "输入终点",
                                             "输入八数码的摆放状态,示例: 123804765",
                                             QLineEdit::Normal,
                                             "123804765",
                                             &isOK,
                                             Qt::Drawer);
        if(isOK) {
            int * b =new  int [9];
            int j = 0;
            int repeat = 0^1^2^3^4^5^6^7^8;
            for (int i=0;i<9;i++) {
                int x = text.mid(i,1).toInt();
                if(x>=0&&x<=8){
                    b[j++]=x;
                    repeat =repeat^x;
                }
            }
            if(j==9&&repeat==0){
                QString  s;
                s+="终点为：";
                for (int i=0;i<9;i++) {
                   d[i]=b[i];
                   s+=QString::number(d[i]);
                }
               ui->output->setText(s);
               path.clear();
            }else {
                QMessageBox::information(NULL,
                                         "提示",
                                         "无效的输入,必须是0~8这9个数字的排列",
                                         QMessageBox::Yes);
            }
            delete [] b;
        }
    });

    connect(ui->btnRandom,&QPushButton::clicked,[=](){
        int * b =EightDigits::copyArray(a);
        random_shuffle(b, b + 9);
        refresh(b);
        delete [] b;
    });

    connect(ui->btnSearch,&QPushButton::clicked,[=](){
        algorithmId = ui->cbAlgorithm->currentIndex();
        heuristicFuncId = ui->cbHeuristicFunc->currentIndex();
        multipleId = ui->cbMultiple->currentIndex();
        isFinished = false;
        mouseClick = false;
        path.clear();
        text = "";
        refreshOutput();
        startGIF();
        allEnableFalse();
        SearchThread * searchThread = new SearchThread(this);
        connect(searchThread,&SearchThread::finished,this,&MainWindow::refreshOutput);
        searchThread->start();
    });

    connect(ui->btnDisplay,&QPushButton::clicked,[=](){
        if(!path.empty()){
            Status * s = new Status(path.at(0));
            Status * d = new Status(a);
            if(EightDigits::isTheSame(s,d)){
                pathIndex = 0;
                mouseClick = false;
                allEnableFalse();
                timerId  = startTimer(300);
            }else{
                QMessageBox::information(NULL,
                                         "提示",
                                         "当前状态不是解路径中的起点状态，请重新搜索求解",
                                         QMessageBox::Yes);
            }
            delete d;
            delete s;
        }else{
            QMessageBox::information(NULL,
                                     "提示",
                                     "没有可以演示的解路径，请先进行搜索求解",
                                     QMessageBox::Yes);
        }
    });
    void (QComboBox:: *change)(int index) = &QComboBox::currentIndexChanged;//解决重载问题
    connect(ui->cbAlgorithm,change,[=](int index){
        if(2==index){
           ui->cbHeuristicFunc->clear();
           ui->cbHeuristicFunc->addItem("无启发");
           ui->cbHeuristicFunc->setEnabled(false);
           ui->cbMultiple->clear();
           ui->cbMultiple->addItem("无倍数");
           ui->cbMultiple->setEnabled(false);
        }else{
            ui->cbHeuristicFunc->clear();
            ui->cbHeuristicFunc->addItems(QStringList()<<tr("启发函数1")<<tr("启发函数2")<<tr("启发函数3")<<tr("启发函数4"));
            ui->cbHeuristicFunc->setEnabled(true);
            ui->cbMultiple->clear();
            ui->cbMultiple->addItems(QStringList()<<tr("1倍")<<tr("2倍")<<tr("3倍")<<tr("4倍")<<tr("5倍")<<tr("6倍"));
            ui->cbMultiple->setEnabled(true);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.translate(startX,startY);
    painter.drawPixmap(0,0,width,width,QPixmap(picturePath[a[0]]));
    painter.drawPixmap(width,0,width,width,QPixmap(picturePath[a[1]]));
    painter.drawPixmap(width*2,0,width,width,QPixmap(picturePath[a[2]]));
    painter.drawPixmap(0,width,width,width,QPixmap(picturePath[a[3]]));
    painter.drawPixmap(width,width,width,width,QPixmap(picturePath[a[4]]));
    painter.drawPixmap(width*2,width,width,width,QPixmap(picturePath[a[5]]));
    painter.drawPixmap(0,width*2,width,width,QPixmap(picturePath[a[6]]));
    painter.drawPixmap(width,width*2,width,width,QPixmap(picturePath[a[7]]));
    painter.drawPixmap(width*2,width*2,width,width,QPixmap(picturePath[a[8]]));
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if(mouseClick){
        int m= ((e->x())-startX)/width;
        int n=((e->y())-startY)/width;
        if(m>=0&&m<=2&&n>=0&&n<=2){
            if(n-1>=0&&n-1<=2&&a[(n-1)*3+m]==0){
                a[(n-1)*3+m] = a[n*3+m];
                a[n*3+m]=0;
                clickSound->play();
                update();
            }else if(n+1>=0&&n+1<=2&&a[(n+1)*3+m]==0){
                a[(n+1)*3+m] = a[n*3+m];
                a[n*3+m]=0;
                clickSound->play();
                update();

            }else if(m-1>=0&&m-1<=2&&a[n*3+(m-1)]==0){
                a[n*3+(m-1)] = a[n*3+m];
                a[n*3+m]=0;
                clickSound->play();
                update();

            }else if(m+1>=0&&m+1<=2&&a[n*3+(m+1)]==0){
                a[n*3+(m+1)] = a[n*3+m];
                a[n*3+m]=0;
                clickSound->play();
                update();
            }
        }
    }

}

void MainWindow::timerEvent(QTimerEvent*){
    if(pathIndex<path.size()){
        refresh(path.at(pathIndex++));
    }else{
        killTimer(timerId);
        mouseClick = true;
        allEnableTrue();
    }
}

void MainWindow:: refresh(int * b){
    for (int i=0;i<9;i++) {
        a[i]=b[i];
    }
    update();
}

void MainWindow:: refreshOutput(){
    stopGIF();
    ui->output->setText(text);
    mouseClick = true;
    allEnableTrue();
}

void MainWindow:: startGIF(){
    ui->label->setVisible(true);
}
void MainWindow:: stopGIF(){
    ui->label->setVisible(false);
}

void MainWindow:: allEnableTrue(){
    ui->btnInput->setEnabled(true);
    ui->btnRandom->setEnabled(true);
    ui->btnSearch->setEnabled(true);
    ui->btnDisplay->setEnabled(true);
    ui->cbMultiple->setEnabled(true);
    ui->cbAlgorithm->setEnabled(true);
    ui->cbHeuristicFunc->setEnabled(true);
   ui->btnInput2->setEnabled(true);
}
void MainWindow:: allEnableFalse(){
    ui->btnInput->setEnabled(false);
    ui->btnRandom->setEnabled(false);
    ui->btnSearch->setEnabled(false);
    ui->btnDisplay->setEnabled(false);
    ui->cbMultiple->setEnabled(false);
    ui->cbAlgorithm->setEnabled(false);
    ui->cbHeuristicFunc->setEnabled(false);
    ui->btnInput2->setEnabled(false);
}


