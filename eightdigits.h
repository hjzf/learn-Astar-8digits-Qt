#ifndef EIGHTDIGITAL_H
#define EIGHTDIGITAL_H
#include <algorithm>
#include <vector>
#include <ctime>
#include <QString>
#include <QDebug>
#define abs(x) ((x) >= 0 ? (x) : -(x))
#define L_DIR 1
#define U_DIR 2
#define R_DIR 3
#define D_DIR 4
using namespace std;
class Status
{
public:
    int *A;         //一维向量，描述该状态的数码摆放情况
    Status *parent; //该状态的父状态指针
    int f;          //状态的估价函数值
    int d;          //状态的深度
    Status(int *A = nullptr, Status *parent = nullptr, int d = 0, int f = 0)
    {
        this->A = A;
        this->parent = parent;
        this->f = f;
        this->d = d;
    }
    ~Status() {}
    //利用启发函数 h 计算估价函数值f,multiple是 启发函数h扩大的倍数，默认为1
    void calculateF(int (*h)(Status *s,Status *d),Status* d,int multiple=1)
    {
        this->f = this->d + ((*h)(this,d))*multiple;
    }
};
//根据启发函数h的形式给h定义一个类型hType
typedef int (*hType)(Status *s,Status *d);
class EightDigits
{
public:
    EightDigits();
    //状态s中的"0"数码向dir方向移动之后得到一个新状态，返回新状态
    Status static *walk(Status *s, int dir);
    int  static * copyArray(int *a);
    QString static  show(Status *s);
    bool static isReverseOrderNumberEven(Status *s);
    bool static isReachable(Status *s,Status *d);
    bool static isDestination(Status *s,Status *d);
    bool static isTheSame(Status *s, Status *d);
    unsigned long long static search(Status *s, vector<Status *> &v);
    bool static compare(Status *s, Status *d);
    int static h1(Status *s,Status *d);
    int static h2(Status *s,Status *d);
    int static h3(Status *s,Status *d);
    int static h4(Status *s,Status *d);
    int static h5(Status *s,Status *d);
    void static BFS(int *start,int *end,bool &isFinished,vector<int *>&p,QString & text);
    void static GOS(int *start,int *end,bool &isFinished,hType h,vector<int *>&p,QString & text,int multiple=1);
    void static Astar(int *start,int *end,bool &isFinished,hType h,vector<int *>&p,QString & text,int multiple=1);
};

#endif // EIGHTDIGITAL_H
