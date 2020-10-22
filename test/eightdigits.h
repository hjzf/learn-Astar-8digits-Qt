#ifndef EIGHTDIGITS_H
#define EIGHTDIGITS_H

#include <algorithm>
#include <vector>
#include <ctime>
#include <iostream>
#define abs(x) ((x) >= 0 ? (x) : -(x))
#define L_DIR 1
#define U_DIR 2
#define R_DIR 3
#define D_DIR 4
using namespace std;
class Status
{
public:
    int *A;         //һά������������״̬������ڷ����
    Status *parent; //��״̬�ĸ�״ָ̬��
    int f;          //״̬�Ĺ��ۺ���ֵ
    int d;          //״̬�����
    Status(int *A = nullptr, Status *parent = nullptr, int d = 0, int f = 0)
    {
        this->A = A;
        this->parent = parent;
        this->f = f;
        this->d = d;
    }
    ~Status() {}
    //������������ h ������ۺ���ֵf,multiple�� ��������h����ı�����Ĭ��Ϊ1
    void calculateF(int (*h)(Status *s,Status *d),Status* d,int multiple=1)
    {
        this->f = this->d + ((*h)(this,d))*multiple;
    }
};
//������������h����ʽ��h����һ������hType
typedef int (*hType)(Status *s,Status *d);
class EightDigits
{
public:
    EightDigits();
    //״̬s�е�"0"������dir�����ƶ�֮��õ�һ����״̬��������״̬
    Status static *walk(Status *s, int dir);
    int  static * copyArray(int *a);
    void static  show(Status *s);
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
    void static BFS(int *start,int *end,bool &isFinished,vector<int *>&p,int &pathSize,long &time);
    void static GOS(int *start,int *end,bool &isFinished,hType h,vector<int *>&p,int &pathSize,long &time,int multiple=1);
    void static Astar(int *start,int *end,bool &isFinished,hType h,vector<int *>&p,int &pathSize,long &time,int multiple=1);
};
#endif // EIGHTDIGITS_H
