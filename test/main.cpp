#include <iostream>
#include "eightdigits.h"
using namespace std;
int main()
{
    // Status *s = new Status;
    // s->A = new int[9];
    // cout << "������㣺";
    // for (int i = 0; i < 9; i++)
    // {
    //     cin >> s->A[i];
    // }
    // Status *d = new Status;
    // d->A = new int[9];
    // cout << "�����յ㣺";
    // for (int i = 0; i < 9; i++)
    // {
    //     cin >> d->A[i];
    // }

    Status *s = new Status;
    s->A = new int[9]{1, 3, 2, 4, 0, 5, 6, 7, 8};
    Status *d = new Status;
    d->A = new int[9]{1, 2, 3, 8, 0, 4, 7, 6, 5};

    cout << "ѡ���㷨��" << endl;
    cout << "1.�����������" << endl;
    cout << "2.ȫ����������" << endl;
    cout << "3.A*�㷨" << endl;
    int select = -1;
    cout<<"�����㷨���: ";
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