#include <iostream>
#include "eightdigits.h"
using namespace std;
int main()
{
    // Status *s = new Status;
    // s->A = new int[9];
    // cout << "输入起点：";
    // for (int i = 0; i < 9; i++)
    // {
    //     cin >> s->A[i];
    // }
    // Status *d = new Status;
    // d->A = new int[9];
    // cout << "输入终点：";
    // for (int i = 0; i < 9; i++)
    // {
    //     cin >> d->A[i];
    // }

    Status *s = new Status;
    s->A = new int[9]{1, 3, 2, 4, 0, 5, 6, 7, 8};
    Status *d = new Status;
    d->A = new int[9]{1, 2, 3, 8, 0, 4, 7, 6, 5};

    cout << "选择算法：" << endl;
    cout << "1.宽度优先搜索" << endl;
    cout << "2.全局择优搜索" << endl;
    cout << "3.A*算法" << endl;
    int select = -1;
    cout<<"输入算法编号: ";
    cin>>select;
    bool isF = 0;
    int pathSize;
    long mytime;
    vector<int *> p;
    switch (select)
    {
    case 1:
        EightDigits::BFS(s->A, d->A, isF, p, pathSize, mytime);
        break;
    case 2:
        EightDigits::GOS(s->A, d->A, isF, EightDigits::h1, p, pathSize, mytime, 1);
        break;
    case 3:
        EightDigits::Astar(s->A, d->A, isF, EightDigits::h1, p, pathSize, mytime, 1);
        break;
    default:
        break;
    }
    return 0;
}