#include "eightdigits.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <thread>
using namespace std;
int mydata[50][9];
int pathSize[50];
long mytime[50];
Status *d = new Status(new int[9]{1, 2, 3, 8, 0, 4, 7, 6, 5});
void calculate(int start, int end, const char *text,const char *text1);
int main()
{
    Status *s = new Status;
    int *a = new int[9]{1, 2, 3, 8, 0, 4, 7, 6, 5};
    s->A = a;
    int SIZE = 50;
    for (int i = 0; i < SIZE; i++)
    {
        do
        {
            random_shuffle(a, a + 9);
        } while (!EightDigits::isReachable(s, d));
        for (int j = 0; j < 9; j++)
        {
            mydata[i][j] = s->A[j];
        }
    }
    thread t1(calculate, 0, 15, "result1.txt", "result11.txt");
    thread t2(calculate, 16, 32, "result2.txt","result22.txt");
    thread t3(calculate, 33, 49, "result3.txt","result33.txt");

    t1.join();
    t2.join();
    t3.join();

    cout << "finished!" << endl;
    return 0;
}

void calculate(int start, int end, const char *text,const char *text1)
{
    ofstream fout;
    fout.open(text);
    ofstream out;
    out.open(text1);
    bool isF = 0;
    vector<int *> p;
    for (int i = start; i <= end; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fout << mydata[i][j];
        }
        fout << "\t";
        // EightDigits::BFS(mydata[i], d->A, isF, p, pathSize[i], mytime[i]);
        // fout << mytime[i] << "\t";
        // EightDigits::GOS(mydata[i], d->A, isF, EightDigits::h1, p, pathSize[i], mytime[i], 1);
        // fout << mytime[i] << "\t";
        // out << pathSize[i] << "\t";
        // EightDigits::GOS(mydata[i], d->A, isF, EightDigits::h2, p, pathSize[i], mytime[i], 1);
        // fout << mytime[i] << "\t";
        // out << pathSize[i] << "\t";
        // EightDigits::GOS(mydata[i], d->A, isF, EightDigits::h3, p, pathSize[i], mytime[i], 1);
        // fout << mytime[i] << "\t";
        // out << pathSize[i] << "\t";
        // EightDigits::GOS(mydata[i], d->A, isF, EightDigits::h4, p, pathSize[i], mytime[i], 1);
        // fout << mytime[i] << "\t";
        // out << pathSize[i] << "\t";
        // EightDigits::Astar(mydata[i], d->A, isF, EightDigits::h1, p, pathSize[i], mytime[i], 1);
        // fout << mytime[i] << "\t";
        // out << pathSize[i] << "\t";
        // EightDigits::Astar(mydata[i], d->A, isF, EightDigits::h2, p, pathSize[i], mytime[i], 1);
        // fout << mytime[i] << "\t";
        // out << pathSize[i] << "\t";
        // EightDigits::Astar(mydata[i], d->A, isF, EightDigits::h3, p, pathSize[i], mytime[i], 1);
        // fout << mytime[i] << "\t";
        // out << pathSize[i] << "\t";
        // EightDigits::Astar(mydata[i], d->A, isF, EightDigits::h4, p, pathSize[i], mytime[i], 1);
        // fout << mytime[i] << "\t";
        // out << pathSize[i] << "\t";
        EightDigits::GOS(mydata[i], d->A, isF, EightDigits::h5, p, pathSize[i], mytime[i], 1);
        fout << mytime[i] << "\t";
        out << pathSize[i] << "\t";
        EightDigits::Astar(mydata[i], d->A, isF, EightDigits::h5, p, pathSize[i], mytime[i], 1);
        fout << mytime[i] << "\t";
        out << pathSize[i] << "\t";
        fout << endl;
        out<<endl;
    }
}
