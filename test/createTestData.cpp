#include "eightdigits.h"
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
ofstream fout;
Status *d = new Status(new int[9]{1, 2, 3, 8, 0, 4, 7, 6, 5});
void foo();
int main()
{
    fout.open("textdata.txt");
    foo();
    return 0;
}
void foo()
{
    Status *s = new Status;
    int *a = new int[9]{1, 2, 3, 8, 0, 4, 7, 6, 5};
    s->A = a;
    for (int i = 0; i < 50; i++)
    {
        do
        {
            random_shuffle(a, a + 9);
        } while (!EightDigits::isReachable(s, d));
        for (int i = 0; i < 9; i++)
        {
            fout << s->A[i];
        }
         fout <<endl;
        // if (i % 5 == 4)
        //     fout << endl;
    }
}