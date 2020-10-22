#include "eightdigits.h"

EightDigits::EightDigits()
{

}
void EightDigits::BFS(int *start,int *end,bool &isFinished,vector<int *>&p,QString & text){
    Status * s= new Status(copyArray(start));
    Status * d= new Status(copyArray(end));
    clock_t start_clock = clock();
    if (!isReachable(s,d))
    {
        delete s->A;
        delete s;
        delete d->A;
        delete d;
        isFinished = true;
        text ="目标状态不可达";
        return;
    }
    Status *success = nullptr;
    vector<Status *> closed;
    vector<Status *> open;
    open.push_back(s);//初始化open表
    while (!open.empty())
    {
        Status *n = open.front();
        open.erase(open.begin());
        closed.push_back(n);//移动open表中的第一个状态n到closed表中
        if (isDestination(n,d))
        {
            success = n;
            break;//如果n是目标状态d，则退出
        }
        //i表示空格的四个移动方向(1-左，2-上，3-右，4-下)
        for (int i = 1; i <= 4; i++)
        {   //状态n中的空格向i方向移动生成子状态c
            Status *c = walk(n, i);
            if (nullptr == c)//c为空指针代表空格无法朝i方向移动
            {
                continue;
            }//search函数会返回closed表或open表中数码摆放和c相同的状态的下标，-1代表不存在
            if (-1ull==search(c, closed)&&-1ull==search(c, open))
            {
                open.push_back(c);//将子状态c放入open表
            }else{
                delete c->A;
                delete c;
            }
        }
    }
    text="";
    if (success != nullptr)
    {
        vector<Status *> path;
        Status *current = success;
        while (current->parent != nullptr)
        {
            path.push_back(current);
            current = current->parent;
        }
        text+=show(s);
        p.push_back(copyArray(s->A));
        for (int i = path.size() - 1; i >= 0; i--)
        {
            text+="       ||\n       \\/\n"+show(path.at(i));
            p.push_back(copyArray(path.at(i)->A));
        }
        text+="使用宽度优先算法移动"+QString::number(path.size())+"步到达目标状态\n";
    }
    clock_t stop_clock = clock();
    text+="程序执行时间是"+QString::number((stop_clock - start_clock))+"毫秒\n";
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
void EightDigits::GOS(int *start,int *end,bool &isFinished,hType h,vector<int *>&p,QString & text,int multiple){
    Status * s= new Status(copyArray(start));
    Status * d= new Status(copyArray(end));
    clock_t start_clock = clock();
    if (!isReachable(s,d))
    {
        delete s->A;
        delete s;
        delete d->A;
        delete d;
        isFinished = true;
        text ="目标状态不可达";
        return;
    }
    Status *success = nullptr;
    vector<Status *> closed;
    vector<Status *> open;
    s->calculateF(h,d,multiple);//使用启发函数h计算s状态相对于目标状态d的估价值f,multiple代表倍数
    open.push_back(s);//初始化open表
    while (!open.empty())
    {
        Status *n = open.front();
        open.erase(open.begin());//取出open表中第一个状态n
        if (isDestination(n,d))
        {
            success = n;
            break;//如果n是目标状态d，则退出
        }
        //i表示空格的四个移动方向(1-左，2-上，3-右，4-下)
        for (int i = 1; i <= 4; i++)
        {   //状态n中的空格向i方向移动生成子状态c
            Status *c = walk(n, i);
            if (nullptr == c)//c为空指针代表空格无法朝i方向移动
            {
                continue;
            }
            //使用启发函数h计算c状态相对于目标状态d的估价值f,multiple代表倍数
            c->calculateF(h,d,multiple);
            int indexInClosed = search(c, closed);
            int indexInOpen = search(c, open);
            //search函数会返回closed表或open表中数码摆放和c相同的状态的下标，-1代表不存在
            if (-1 == indexInClosed && -1 == indexInOpen)
            {
                open.push_back(c);//将c放入open表
            }else{
                delete c->A;
                delete c;
            }
        }
        closed.push_back(n);//将n放进closed表中
        sort(open.begin(), open.end(), compare);//将open表中的状态按照估价值f从小到大排序
    }
    text="";
    if (success != nullptr)
    {
        vector<Status *> path;
        Status *current = success;
        while (current->parent != nullptr)
        {
            path.push_back(current);
            current = current->parent;
        }
        text+=show(s);
        p.push_back(copyArray(s->A));
        for (int i = path.size() - 1; i >= 0; i--)
        {
            text+="       ||\n       \\/\n"+show(path.at(i));
            p.push_back(copyArray(path.at(i)->A));
        }
        text+="使用全局择优搜索算法移动"+QString::number(path.size())+"步到达目标状态\n";
    }
    clock_t stop_clock = clock();
    text+="程序执行时间是"+QString::number((stop_clock - start_clock))+"毫秒\n";
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
    return;

}
void EightDigits::Astar(int *start,int *end,bool &isFinished,hType h,vector<int *>&p,QString & text,int multiple){
    Status * s= new Status(copyArray(start));
    Status * d= new Status(copyArray(end));
    clock_t start_clock = clock();
    if (!isReachable(s,d))
    {
        delete s->A;
        delete s;
        delete d->A;
        delete d;
        isFinished = true;
        text ="目标状态不可达";
        return;
    }
    Status *success = nullptr;
    vector<Status *> closed;
    vector<Status *> open;
    s->calculateF(h,d,multiple);//使用启发函数h计算s状态相对于目标状态d的估价值f,multiple代表倍数
    open.push_back(s);//初始化open表
    while (!open.empty())
    {
        Status *n = open.front();
        open.erase(open.begin());//取出open表中第一个状态n
        if (isDestination(n,d))
        {
            success = n;
            break;//如果n是目标状态d，则退出
        }
        //i表示空格的四个移动方向(1-左，2-上，3-右，4-下)
        for (int i = 1; i <= 4; i++)
        {   //状态n中的空格向i方向移动生成子状态c
            Status *c = walk(n, i);
            if (nullptr == c)//c为空指针代表空格无法朝i方向移动
            {
                continue;
            }
            //使用启发函数h计算c状态相对于目标状态d的估价值f,multiple代表倍数
            c->calculateF(h,d,multiple);
            int indexInClosed = search(c, closed);
            int indexInOpen = search(c, open);
            //search函数会返回closed表或open表中数码摆放和c相同的状态的下标，-1代表不存在
            if (-1 == indexInClosed && -1 == indexInOpen)
            {
                open.push_back(c);//将c放入open表
            }
            else if (-1 != indexInOpen)
            {
                if (c->f < open.at(indexInOpen)->f)
                {   //刷新open表中对应状态的其它属性
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
                {   //删除closed表中对应的状态
                    delete closed.at(indexInClosed)->A;
                    delete closed.at(indexInClosed);
                    closed.erase(closed.begin() + indexInClosed);
                    open.push_back(c);//将c放入open表
                }
            }
        }
        closed.push_back(n);//将n放进closed表中
        sort(open.begin(), open.end(), compare);//将open表中的状态按照估价值f从小到大排序
    }
    text="";
    if (success != nullptr)
    {
        vector<Status *> path;
        Status *current = success;
        while (current->parent != nullptr)
        {
            path.push_back(current);
            current = current->parent;
        }
        text+=show(s);
        p.push_back(copyArray(s->A));
        for (int i = path.size() - 1; i >= 0; i--)
        {
            text+="       ||\n       \\/\n"+show(path.at(i));
            p.push_back(copyArray(path.at(i)->A));
        }
        text+="使用A*算法移动"+QString::number(path.size())+"步到达目标状态\n";
    }
    clock_t stop_clock = clock();
    text+="程序执行时间是"+QString::number((stop_clock - start_clock))+"毫秒\n";
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
Status * EightDigits::walk(Status *s, int dir){
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
    //数码"0"向左移动
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
        //数码"0"向上移动
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
        //数码"0"向右移动
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
        //数码"0"向下移动
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
int * EightDigits::copyArray(int *a){
    int *b = new int[9];
    for (int i = 0; i < 9; i++)
    {
        b[i] = a[i];
    }
    return b;
}
QString EightDigits::show(Status *s){
    int *a = s->A;
    return "---------------\n|"
            +QString::number(a[0])+"     "+QString::number(a[1])+"     "+QString::number(a[2])+"|\n"
            +"|"+QString::number(a[3])+"     "+QString::number(a[4])+"     "+QString::number(a[5])+"|\n"
            +"|"+QString::number(a[6])+"     "+QString::number(a[7])+"     "+QString::number(a[8])+"|\n"
            +"---------------\n";


}

bool EightDigits::isReverseOrderNumberEven(Status *s){
    int *b = new int[8];
    int j = 0;
    for (int i = 0; i < 9; i++)
    {
        if (0 != s->A[i])
        {
            b[j++] = s->A[i];
        }
    }
    int count = 0;//计算逆序数
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
    delete []b;
    return count % 2 == 0;
}
bool EightDigits::isReachable(Status *s,Status * d){
   return !(isReverseOrderNumberEven(s)^isReverseOrderNumberEven(d));
}

bool EightDigits::isDestination(Status *s,Status *d){
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
bool EightDigits::isTheSame(Status *s, Status *d){

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
unsigned long long EightDigits::search(Status *s, vector<Status *> &v){

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
bool EightDigits::compare(Status *s, Status *d){

    return s->f < d->f;

}
int EightDigits::h1(Status *s, Status *d){
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
int EightDigits::h2(Status *s, Status *d){
    int *dIndex = new int[9];
    for(int i = 0; i < 9; i++)
    {
        dIndex[d->A[i]]=i;
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
    delete [] dIndex;
    return count;

}
int EightDigits::h3(Status *s, Status *d){
    int *value = new int[9];
    for(int i = 0; i < 9; i++)
    {
        value[d->A[i]]=i;
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
    delete [] value;
    return count;
}
int EightDigits::h4(Status *s, Status *d){
    return h1(s,d) + 3 * h3(s,d);
}

int EightDigits::h5(Status *s, Status *d)
{
    return h2(s, d) + 3 * h3(s, d);
}

