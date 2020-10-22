#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#define abs(x) ((x) >= 0 ? (x) : -(x))
using namespace std;
ofstream fout;
const int L = 1;
const int U = 2;
const int R = 3;
const int D = 4;
class Status
{
public:
    int *A;
    Status *parent;
    int f;
    int d;
    Status(int *A = nullptr, Status *parent = nullptr, int d = 0, int f = 0)
    {
        this->A = A;
        this->parent = parent;
        this->f = f;
        this->d = d;
    }
    ~Status() {}
    void calculateF(int (*h)(Status *s))
    {
        this->f = this->d + (*h)(this);
    }
};
typedef int (*hType)(Status *s);
void eightDigital(hType h);
Status *walk(Status *s, int dir);
int *copyArray(int *a);
void show(Status *s);
bool isReachable(Status *s);
bool isDestination(Status *s);
bool isTheSame(Status *s, Status *d);
int search(Status *s, vector<Status *> v);
bool compare(Status *s, Status *d);
int h1(Status *s);
int h2(Status *s);
int h3(Status *s);
int h4(Status *s);
int main()
{
    fout.open("result.txt");
    cout << "使用启发函数h1:" << endl;
    eightDigital(h1);
    cout << "使用启发函数h2:" << endl;
    eightDigital(h2);
    cout << "使用启发函数h3,倍数取1:" << endl;
    eightDigital(h3);
    cout << "使用启发函数h4:" << endl;
    eightDigital(h4);
    return 0;
}

void eightDigital(hType h)
{
    clock_t start_clock = clock();
    Status *s = new Status(new int[9]{1, 3, 2, 4, 0, 5, 6, 7, 8});
    if (!isReachable(s))
    {
        cout << "目标状态不可达" << endl;
        return;
    }
    Status *success = nullptr;
    vector<Status *> closed;
    vector<Status *> open;
    s->calculateF(h); //根据启发函数h计算f的值
    open.push_back(s);
    while (!open.empty())
    {
        Status *n = open.front();
        open.erase(open.begin());
        if (isDestination(n))
        {
            success = n;
            break;
        }
        for (int i = 1; i <= 4; i++)
        {
            Status *c = walk(n, i);
            if (nullptr == c)
            {
                continue;
            }
            c->calculateF(h);
            int indexInClosed = search(c, closed);
            int indexInOpen = search(c, open);
            if (-1 == indexInClosed && -1 == indexInOpen)
            {
                open.push_back(c);
            }
            else if (-1 != indexInOpen)
            {
                if (c->f < open.at(indexInOpen)->f)
                {
                    open.at(indexInOpen)->f = c->f;
                    open.at(indexInOpen)->d = c->d;
                    open.at(indexInOpen)->parent = c->parent;
                }
            }
            else if (-1 != indexInClosed)
            {
                if (c->f < closed.at(indexInClosed)->f)
                {
                    closed.erase(closed.begin() + indexInClosed);
                    open.push_back(c);
                }
            }
        }
        closed.push_back(n);
        sort(open.begin(), open.end(), compare);
    }
    if (success != nullptr)
    {
        vector<Status *> path;
        Status *current = success;
        while (current->parent != nullptr)
        {
            path.push_back(current);
            current = current->parent;
        }
        show(s);
        for (int i = path.size() - 1; i >= 0; i--)
        {
            fout << "        ||" << endl;
            fout << "        \\/" << endl;
            show(path.at(i));
        }
        fout << "*****************************************" << endl;
        cout << "最少移动" << path.size() << "步到达目标状态" << endl;
    }

    clock_t stop_clock = clock();
    cout << "程序运行的时间是  "
         << (stop_clock - start_clock)
         << "  毫秒\n"
         << endl;
}

Status *walk(Status *s, int dir)
{
    Status *d = nullptr;
    int *a = s->A;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (0 == a[i])
        {
            break;
        }
    }
    int n = i / 3;
    int m = i % 3;
    switch (dir)
    {
    case L:
        if (0 == m)
        {
            break;
        }
        else
        {
            int *b = copyArray(a);
            b[i] = b[i - 1];
            b[i - 1] = 0;
            d = new Status(b, s, s->d + 1);
            break;
        }
    case U:
        if (0 == n)
        {
            break;
        }
        else
        {
            int *b = copyArray(a);
            b[i] = b[i - 3];
            b[i - 3] = 0;
            d = new Status(b, s, s->d + 1);
            break;
        }
    case R:
        if (2 == m)
        {
            break;
        }
        else
        {
            int *b = copyArray(a);
            b[i] = b[i + 1];
            b[i + 1] = 0;
            d = new Status(b, s, s->d + 1);
            break;
        }
    case D:
        if (2 == n)
        {
            break;
        }
        else
        {
            int *b = copyArray(a);
            b[i] = b[i + 3];
            b[i + 3] = 0;
            d = new Status(b, s, s->d + 1);
            break;
        }
    default:
        break;
    }
    return d;
}
int *copyArray(int *a)
{
    int *b = new int[9];
    for (int i = 0; i < 9; i++)
    {
        b[i] = a[i];
    }
    return b;
}
void show(Status *s)
{
    int *a = s->A;
    fout << "------------------" << endl;
    fout << "|" << a[0] << "\t" << a[1] << "\t" << a[2] << "|" << endl;
    fout << "|" << a[3] << "\t" << a[4] << "\t" << a[5] << "|" << endl;
    fout << "|" << a[6] << "\t" << a[7] << "\t" << a[8] << "|" << endl;
    fout << "------------------" << endl;
}

bool isReachable(Status *s)
{
    int *b = new int[8];
    int j = 0;
    for (int i = 0; i < 9; i++)
    {
        if (0 != s->A[i])
        {
            b[j++] = s->A[i];
        }
    }
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (b[j] > b[i])
            {
                count++;
            }
        }
    }
    return count % 2 == 1;
}

bool isDestination(Status *s)
{
    int d[] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    bool flag = true;
    for (int i = 0; i < 9; i++)
    {
        if (s->A[i] != d[i])
        {
            flag = false;
            break;
        }
    }
    return flag;
}

bool isTheSame(Status *s, Status *d)
{
    bool flag = true;
    for (int i = 0; i < 9; i++)
    {
        if (s->A[i] != d->A[i])
        {
            flag = false;
            break;
        }
    }
    return flag;
}

int search(Status *s, vector<Status *> v)
{
    int index = -1;
    for (int i = 0; i < v.size(); i++)
    {
        if (isTheSame(s, v.at(i)))
        {
            index = i;
            break;
        }
    }
    return index;
}

int h1(Status *s)
{ //           0, 1, 2, 3, 4, 5, 6, 7, 8
    int d[] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if (s->A[i] != d[i])
        {
            count++;
        }
    }
    return count;
}

int h2(Status *s)
{ //                0, 1, 2, 3, 4, 5, 6, 7, 8
    int dIndex[] = {4, 0, 1, 2, 5, 8, 7, 6, 3};
    int count = 0;
    int j = 0;
    for (int i = 0; i < 9; i++)
    {
        j = dIndex[s->A[i]];
        if (j != i)
        {
            count = count + abs(i / 3 - j / 3) + abs(i % 3 - j % 3);
        }
    }
    return count;
}

int h3(Status *s)
{
    //计算相对逆序数
    int dIndex[] = {4, 0, 1, 2, 5, 8, 7, 6, 3};
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (dIndex[s->A[j]] > dIndex[s->A[i]])
            {
                count++;
            }
        }
    }
    return count;
}

int h4(Status *s)
{
    return h1(s) + 3 * h3(s);
}

bool compare(Status *s, Status *d)
{
    return s->f < d->f;
}