#include "eightdigits.h"

EightDigits::EightDigits()
{
}
void EightDigits::BFS(int *start, int *end, bool &isFinished, vector<int *> &p, int &pathSize, long &time)
{
    Status *s = new Status(copyArray(start));
    Status *d = new Status(copyArray(end));
    clock_t start_clock = clock();
    if (!isReachable(s, d))
    {
        delete s->A;
        delete s;
        delete d->A;
        delete d;
        isFinished = true;
        cout << "Ŀ��״̬���ɴ�" << endl;
        return;
    }
    Status *success = nullptr;
    vector<Status *> closed;
    vector<Status *> open;
    open.push_back(s); //��ʼ��open��
    while (!open.empty())
    {
        Status *n = open.front();
        open.erase(open.begin());
        closed.push_back(n); //�ƶ�open���еĵ�һ��״̬n��closed����
        if (isDestination(n, d))
        {
            success = n;
            break; //���n��Ŀ��״̬d�����˳�
        }
        //i��ʾ�ո���ĸ��ƶ�����(1-��2-�ϣ�3-�ң�4-��)
        for (int i = 1; i <= 4; i++)
        { //״̬n�еĿո���i�����ƶ�������״̬c
            Status *c = walk(n, i);
            if (nullptr == c) //cΪ��ָ�����ո��޷���i�����ƶ�
            {
                continue;
            } //search�����᷵��closed���open��������ڷź�c��ͬ��״̬���±꣬-1��������
            if (-1ull == search(c, closed) && -1ull == search(c, open))
            {
                open.push_back(c); //����״̬c����open��
            }
            else
            {
                delete c->A;
                delete c;
            }
        }
    }
    clock_t stop_clock = clock();
    if (success != nullptr)
    {
        vector<Status *> path;
        Status *current = success;
        while (current->parent != nullptr)
        {
            path.push_back(current);
            current = current->parent;
        }
        pathSize = path.size();
        show(s);
        for (int i = path.size() - 1; i >= 0; i--)
        {
            cout << "        ||" << endl;
            cout << "        \\/" << endl;
            show(path.at(i));
        }
        cout << "*****************************************" << endl;
        cout << "�����ƶ�" << path.size() << "������Ŀ��״̬\n"
             << endl;
    }
    time = (stop_clock - start_clock);
    cout << "�������е�ʱ����  "
         << (stop_clock - start_clock)
         << "  ����"
         << endl;
    for (int i = open.size() - 1; i >= 0; i--)
    {
        delete open.at(i)->A;
        delete open.at(i);
    }
    for (int i = closed.size() - 1; i >= 0; i--)
    {
        delete closed.at(i)->A;
        delete closed.at(i);
    }
    isFinished = true;
    delete d->A;
    delete d;
    return;
}
void EightDigits::GOS(int *start, int *end, bool &isFinished, hType h, vector<int *> &p, int &pathSize, long &time, int multiple)
{
    Status *s = new Status(copyArray(start));
    Status *d = new Status(copyArray(end));
    clock_t start_clock = clock();
    if (!isReachable(s, d))
    {
        delete s->A;
        delete s;
        delete d->A;
        delete d;
        isFinished = true;
        cout << "Ŀ��״̬���ɴ�" << endl;
        return;
    }
    Status *success = nullptr;
    vector<Status *> closed;
    vector<Status *> open;
    s->calculateF(h, d, multiple); //ʹ����������h����s״̬�����Ŀ��״̬d�Ĺ���ֵf,multiple������
    open.push_back(s);             //��ʼ��open��
    while (!open.empty())
    {
        Status *n = open.front();
        open.erase(open.begin()); //ȡ��open���е�һ��״̬n
        if (isDestination(n, d))
        {
            success = n;
            break; //���n��Ŀ��״̬d�����˳�
        }
        //i��ʾ�ո���ĸ��ƶ�����(1-��2-�ϣ�3-�ң�4-��)
        for (int i = 1; i <= 4; i++)
        { //״̬n�еĿո���i�����ƶ�������״̬c
            Status *c = walk(n, i);
            if (nullptr == c) //cΪ��ָ�����ո��޷���i�����ƶ�
            {
                continue;
            }
            //ʹ����������h����c״̬�����Ŀ��״̬d�Ĺ���ֵf,multiple������
            c->calculateF(h, d, multiple);
            int indexInClosed = search(c, closed);
            int indexInOpen = search(c, open);
            //search�����᷵��closed���open��������ڷź�c��ͬ��״̬���±꣬-1��������
            if (-1 == indexInClosed && -1 == indexInOpen)
            {
                open.push_back(c); //��c����open��
            }
            else
            {
                delete c->A;
                delete c;
            }
        }
        closed.push_back(n);                     //��n�Ž�closed����
        sort(open.begin(), open.end(), compare); //��open���е�״̬���չ���ֵf��С��������
    }
    clock_t stop_clock = clock();
    if (success != nullptr)
    {
        vector<Status *> path;
        Status *current = success;
        while (current->parent != nullptr)
        {
            path.push_back(current);
            current = current->parent;
        }
        pathSize = path.size();
        show(s);
        for (int i = path.size() - 1; i >= 0; i--)
        {
            cout << "        ||" << endl;
            cout << "        \\/" << endl;
            show(path.at(i));
        }
        cout << "*****************************************" << endl;
        cout << "�����ƶ�" << path.size() << "������Ŀ��״̬\n"
             << endl;
    }

    time = (stop_clock - start_clock);
    cout << "�������е�ʱ����  "
         << (stop_clock - start_clock)
         << "  ����"
         << endl;
    for (int i = open.size() - 1; i >= 0; i--)
    {
        delete open.at(i)->A;
        delete open.at(i);
    }
    for (int i = closed.size() - 1; i >= 0; i--)
    {
        delete closed.at(i)->A;
        delete closed.at(i);
    }
    isFinished = true;
    delete d->A;
    delete d;
    return;
}
void EightDigits::Astar(int *start, int *end, bool &isFinished, hType h, vector<int *> &p, int &pathSize, long &time, int multiple)
{
    Status *s = new Status(copyArray(start));
    Status *d = new Status(copyArray(end));
    clock_t start_clock = clock();
    if (!isReachable(s, d))
    {
        delete s->A;
        delete s;
        delete d->A;
        delete d;
        isFinished = true;
        cout << "Ŀ��״̬���ɴ�" << endl;
        return;
    }
    Status *success = nullptr;
    vector<Status *> closed;
    vector<Status *> open;
    s->calculateF(h, d, multiple); //ʹ����������h����s״̬�����Ŀ��״̬d�Ĺ���ֵf,multiple������
    open.push_back(s);             //��ʼ��open��
    while (!open.empty())
    {
        Status *n = open.front();
        open.erase(open.begin()); //ȡ��open���е�һ��״̬n
        if (isDestination(n, d))
        {
            success = n;
            break; //���n��Ŀ��״̬d�����˳�
        }
        //i��ʾ�ո���ĸ��ƶ�����(1-��2-�ϣ�3-�ң�4-��)
        for (int i = 1; i <= 4; i++)
        { //״̬n�еĿո���i�����ƶ�������״̬c
            Status *c = walk(n, i);
            if (nullptr == c) //cΪ��ָ�����ո��޷���i�����ƶ�
            {
                continue;
            }
            //ʹ����������h����c״̬�����Ŀ��״̬d�Ĺ���ֵf,multiple������
            c->calculateF(h, d, multiple);
            int indexInClosed = search(c, closed);
            int indexInOpen = search(c, open);
            //search�����᷵��closed���open��������ڷź�c��ͬ��״̬���±꣬-1��������
            if (-1 == indexInClosed && -1 == indexInOpen)
            {
                open.push_back(c); //��c����open��
            }
            else if (-1 != indexInOpen)
            {
                if (c->f < open.at(indexInOpen)->f)
                { //ˢ��open���ж�Ӧ״̬����������
                    open.at(indexInOpen)->f = c->f;
                    open.at(indexInOpen)->d = c->d;
                    open.at(indexInOpen)->parent = c->parent;
                    delete c->A;
                    delete c;
                }
            }
            else if (-1 != indexInClosed)
            {
                if (c->f < closed.at(indexInClosed)->f)
                { //ɾ��closed���ж�Ӧ��״̬
                    delete closed.at(indexInClosed)->A;
                    delete closed.at(indexInClosed);
                    closed.erase(closed.begin() + indexInClosed);
                    open.push_back(c); //��c����open��
                }
            }
        }
        closed.push_back(n);                     //��n�Ž�closed����
        sort(open.begin(), open.end(), compare); //��open���е�״̬���չ���ֵf��С��������
    }
    clock_t stop_clock = clock();
    if (success != nullptr)
    {
        vector<Status *> path;
        Status *current = success;
        while (current->parent != nullptr)
        {
            path.push_back(current);
            current = current->parent;
        }
        pathSize = path.size();
        show(s);
        for (int i = path.size() - 1; i >= 0; i--)
        {
            cout << "        ||" << endl;
            cout << "        \\/" << endl;
            show(path.at(i));
        }
        cout << "*****************************************" << endl;
        cout << "�����ƶ�" << path.size() << "������Ŀ��״̬\n"
             << endl;
    }

    time = (stop_clock - start_clock);
    cout << "�������е�ʱ����  "
         << (stop_clock - start_clock)
         << "  ����"
         << endl;
    for (int i = open.size() - 1; i >= 0; i--)
    {
        delete open.at(i)->A;
        delete open.at(i);
    }
    for (int i = closed.size() - 1; i >= 0; i--)
    {
        delete closed.at(i)->A;
        delete closed.at(i);
    }
    isFinished = true;
    delete d->A;
    delete d;
    return;
}
Status *EightDigits::walk(Status *s, int dir)
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
    //����"0"�����ƶ�
    case L_DIR:
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
        //����"0"�����ƶ�
    case U_DIR:
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
        //����"0"�����ƶ�
    case R_DIR:
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
        //����"0"�����ƶ�
    case D_DIR:
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
int *EightDigits::copyArray(int *a)
{
    int *b = new int[9];
    for (int i = 0; i < 9; i++)
    {
        b[i] = a[i];
    }
    return b;
}

void EightDigits::show(Status *s)
{
    int *a = s->A;
    cout << "------------------" << endl;
    cout << "|" << a[0] << "\t" << a[1] << "\t" << a[2] << "|" << endl;
    cout << "|" << a[3] << "\t" << a[4] << "\t" << a[5] << "|" << endl;
    cout << "|" << a[6] << "\t" << a[7] << "\t" << a[8] << "|" << endl;
    cout << "------------------" << endl;
}

bool EightDigits::isReverseOrderNumberEven(Status *s)
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
    int count = 0; //����������
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
    delete[] b;
    return count % 2 == 0;
}
bool EightDigits::isReachable(Status *s, Status *d)
{
    return !(isReverseOrderNumberEven(s) ^ isReverseOrderNumberEven(d));
}

bool EightDigits::isDestination(Status *s, Status *d)
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
bool EightDigits::isTheSame(Status *s, Status *d)
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
unsigned long long EightDigits::search(Status *s, vector<Status *> &v)
{

    unsigned long long index = -1;
    for (unsigned long long i = 0; i < v.size(); i++)
    {
        if (isTheSame(s, v.at(i)))
        {
            index = i;
            break;
        }
    }
    return index;
}
bool EightDigits::compare(Status *s, Status *d)
{

    return s->f < d->f;
}
int EightDigits::h1(Status *s, Status *d)
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if (s->A[i] != d->A[i])
        {
            count++;
        }
    }
    return count;
}
int EightDigits::h2(Status *s, Status *d)
{
    int *dIndex = new int[9];
    for (int i = 0; i < 9; i++)
    {
        dIndex[d->A[i]] = i;
    }
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
    delete[] dIndex;
    return count;
}
int EightDigits::h3(Status *s, Status *d)
{
    int *value = new int[9];
    for (int i = 0; i < 9; i++)
    {
        value[d->A[i]] = i;
    }
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (value[s->A[j]] > value[s->A[i]])
            {
                count++;
            }
        }
    }
    delete[] value;
    return count;
}
int EightDigits::h4(Status *s, Status *d)
{
    return h1(s, d) + 3 * h3(s, d);
}

int EightDigits::h5(Status *s, Status *d)
{
    return h2(s, d) + 3 * h3(s, d);
}
