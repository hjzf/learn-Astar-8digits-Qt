#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
const int L = 1;
const int U = 2;
const int R = 3;
const int D = 4;
class Status
{
public:
    Status(int *A = nullptr, Status *parent = nullptr);
    ~Status();
    int *A;
    Status *parent;
};
Status *walk(Status *s, int dir);
int *copyArray(int *a);
void show(Status *s);
bool isReachable(Status *s);
bool isDestination(Status *s);
bool isTheSame(Status *s, Status *d); 
bool isExist(Status *s, vector<Status *> v);
int main()
{
    clock_t start_clock = clock();

    Status *s = new Status(new int[9]{1, 3, 2, 4, 0, 5, 6, 7, 8});
    if (!isReachable(s))
    {
        cout << "目标状态不可达" << endl;
        return 0;
    }
    Status *success = nullptr;
    vector<Status *> closed;
    vector<Status *> open;
    open.push_back(s);
    while (!open.empty())
    {
        Status *n = open.front();
        open.erase(open.begin());
        closed.push_back(n);
        if (isDestination(n))
        {
            success = n;
            break;
        }
        for (int i = 1; i <= 4; i++)
        {
            Status *c = walk(n, i);
            if (c != nullptr && !(isExist(c, closed) || isExist(c, open)))
            {
                open.push_back(c);
            }
        }
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
            cout << "        ||" << endl;
            cout << "        \\/" << endl;
            show(path.at(i));
        }
        cout << "最少移动" << path.size() << "步到达目标状态" << endl;
    }

    clock_t stop_clock = clock();
    cout << "\nThe running time of the program is  ";
    cout << (double)((stop_clock - start_clock) / CLOCKS_PER_SEC);
    cout << "  seconds" << endl;
    return 0;
}

Status::Status(int *A, Status *parent)
{
    this->A = A;
    this->parent = parent;
}

Status::~Status()
{
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
            d = new Status(b, s);
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
            d = new Status(b, s);
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
            d = new Status(b, s);
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
            d = new Status(b, s);
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
    cout << "------------------" << endl;
    cout << "|" << a[0] << "\t" << a[1] << "\t" << a[2] << "|" << endl;
    cout << "|" << a[3] << "\t" << a[4] << "\t" << a[5] << "|" << endl;
    cout << "|" << a[6] << "\t" << a[7] << "\t" << a[8] << "|" << endl;
    cout << "------------------" << endl;
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

bool isExist(Status *s, vector<Status *> v)
{
    bool flag = false;
    for (int i = 0; i < v.size(); i++)
    {
        if (isTheSame(s, v.at(i)))
        {
            flag = true;
            break;
        }
    }
    return flag;
}