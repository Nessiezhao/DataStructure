#include"seqstack.h"

#define MAX_ROW 6
#define MAX_COL 6

typedef struct Maze
{
    int map[MAX_ROW][MAX_COL];
}Maze;
void MazeInit(Maze* maze)
{
    if(maze == NULL)
    {
        return;
    }
    int map[MAX_ROW][MAX_COL] = {
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,0,0},
        {0,1,0,1,1,0},
        {0,1,1,0,0,0},
        {0,0,1,0,0,0}
    };
    size_t i = 0;
    for(;i < MAX_ROW;++i)
    {
        size_t j = 0;
        for(;j < MAX_COL;++j)
        {
            maze->map[i][j] = map[i][j];
        }
    }
    return;
}
void MazePrint(Maze* maze)
{
    if(maze == NULL)
    {
        return;
    }
    size_t i = 0;
    for(;i < MAX_ROW;++i)
    {
        size_t j = 0;
        for(;j < MAX_COL;++j)
        {
            printf("%2d ",maze->map[i][j]);
        }
        printf("\n");
    }
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Round1 使用递归的方法解决迷宫问题
/////////////////////////////////////////////////////////////////////////////////////////////////////
//判断pt这个点是否能落脚
//如果能落脚，返回1，否则返回0
int CanStay(Maze* maze,Point pt)
{
    //1.如果pt这个点在地图外，肯定不能落脚
    if(pt.row < 0 || pt.row >= MAX_ROW || pt.col < 0 || pt.col >= MAX_COL)
    {
        return 0;
    }
    //2.如果pt在地图内，这个位置上的值是1，可以落脚
    //如果值是0，或者2，多不能落脚（0是墙，1是路，2是被标记的）
    int value = maze->map[pt.row][pt.col];
    if(value == 1)
    {
        return 1;
    }
    return 0;
}

void Mark(Maze* maze,Point cur)
{
    maze->map[cur.row][cur.col] = 2;
}

//如果是出口返回1.不是返回0
int IsExit(Maze* maze,Point cur,Point entry)
{
    (void) maze;//消除警告
    //1.当前点是不是入口点，如果是入口点那肯定不是出口
    if(cur.row == entry.row && cur.col == entry.col)
    {
        return 0;
    }
    //2.如果点在地图的边界上，也说明是出口
    if(cur.row == 0 || cur.col == MAX_ROW-1 || cur.col == 0 || cur.col == MAX_COL-1 )
    {
        return 1;
    }
    return 0;
}
//每次走到下一个点，都会递归的调用以下这个函数
void _GetPath(Maze* maze,Point cur,Point entry)
{
    //1.判断当前点，是否能落脚
    if(!CanStay(maze,cur))
    {
        return;
    }
    //2.如果能落脚，就给当前位置做一个标记
    Mark(maze,cur);
    //3.如果当前点是出口，说明就找到一条出路，探测就结束
    if(IsExit(maze,cur,entry))
    {
        //说明找到了这条出路
        printf("找到了一条路径\n");
    printf("cur :%d,%d\n",cur.row,cur.col);
        return;
    }
    //4.如果当前点不是出口，就按照顺时针探测四个相邻的点
    //  递归的调用函数本身，递归时，更新cur点（每次递归的时候，点都是下一次要走的点，这个点究竟能不能走，交给递归函数做判断）
    Point up = cur;
    up.row -= 1;
    _GetPath(maze,up,entry);

    Point right = cur;
    right.col += 1;
    _GetPath(maze,right,entry);

    Point down = cur;
    down.row += 1;
    _GetPath(maze,down,entry);

    Point left = cur;
    cur.col -= 1;
    _GetPath(maze,left,entry);
}
void GetPath(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        return;
    }
    //使用下面的函数辅助我们完成递归
    _GetPath(maze,entry,entry);//第一个entry为当前走到的点，第二个entry为入口点
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Round2 使用非递归的方法解决迷宫问题
/////////////////////////////////////////////////////////////////////////////////////////////////////
void GetPathByLoop(Maze* maze,Point entry)
{
    //1.创建一个栈，并且初始化，这个栈保存着走过的路径
    SeqStack stack;
    SeqStackInit(&stack);
    //2.判定入口能不能落脚，如果不能，说明参数非法
    if(!CanStay(maze,entry))
    {
        //入口点非法
        return;
    }
    //3.标记入口点，并且将入口点入栈
    Mark(maze,entry);
    SeqStackPush(&stack,entry);
    while(1)
    {
        //4.进入循环，获取到当前的栈顶元素（栈顶元素一定是能落脚）
        Point cur;
        int ret = SeqStackTop(&stack,&cur);
        if(ret == 0)
        {
            //栈为空说明回溯结束了
            return;
        }
        //5.判断这个点是不是出口，如果是出口，直接函数返回
        if(IsExit(maze,cur,entry))
        {   
               //说明找到了这条出路
               printf("找到了一条路径\n");
    printf("cur :%d,%d\n",cur.row,cur.col);
               return;
        }   
        //6.按照顺时针方向取相邻点，判断相邻点是否能落脚
        Point up = cur;
        up.row -= 1;
        if(CanStay(maze,up))
        {
            Mark(maze,up);
            SeqStackPush(&stack,up);
            continue;
        }
        Point right = cur;
        right.col += 1;
        if(CanStay(maze,right))
        {
            Mark(maze,right);
            SeqStackPush(&stack,right);
            continue;
        }
        Point down = cur;
        down.row += 1;
        if(CanStay(maze,down))
        {
            Mark(maze,down);
            SeqStackPush(&stack,down);
            continue;
        }
        Point left = cur;
        left.col -= 1;
        if(CanStay(maze,left))
        {
            Mark(maze,left);
            SeqStackPush(&stack,left);
            continue;
        }
     //  如果能落脚，就标记并且入栈，立刻进入下一轮循环
     //7.如果四个相邻的节点都不能落脚，就出栈当前点，相当于进行回溯
     SeqStackPop(&stack);
    }
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Round3 如果迷宫有多条路径，找到其中的最短路径
/////////////////////////////////////////////////////////////////////////////////////////////////////
void MazeInit2(Maze* maze)
{
    if(maze == NULL)
    {
        return;
    }
    int map[MAX_ROW][MAX_COL] = {
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,1,1},
        {1,1,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    };
    size_t i = 0;
    for(;i < MAX_ROW;++i)
    {
        size_t j = 0;
        for(;j < MAX_COL;++j)
        {
            maze->map[i][j] = map[i][j];
        }
    }
    return;
}
void _GetShortPath(Maze* maze,Point cur,Point entry,SeqStack* cur_path,SeqStack* short_path)
{
    //1.判断当前是否能落脚
    if(!CanStay(maze,cur))
    {
        return;
    }
    //2.如果能落脚，就对当前点进行标记，同时把当前点插入到cur_path
    Mark(maze,cur);
    SeqStackPush(cur_path,cur);
    //判断当前点是否是出口
    if(IsExit(maze,cur,entry))
    {
        //a）如果是出口，说明找到了一条路径，拿当前路径和short_path中的路径进行对比
        //，如果当前路径比short_path短，或short_path本身是一个空栈
        //  就用当前路径代替short_path
        printf("找到一条路经!\n");
        if(cur_path->size < short_path->size || short_path->size == 0)
        {
            printf("找到一条比较短的路径!\n");
            SeqStackAssgin(cur_path,short_path);
        }
        else
        {
            //b)如果当前路径没有short_path短，就继续再找其他路径（进行回溯）
            //  回溯之前要把cur_path栈顶元素出栈
            SeqStackPop(cur_path);
            return;
        }
    printf("cur :%d,%d\n",cur.row,cur.col);
    }
    //4.如果当前点不是出口，尝试探测四个方向（按照顺时针的方向探测）
    Point up = cur;
    up.row -= 1;
    _GetShortPath(maze,up,entry,cur_path,short_path);

    Point right = cur;
    right.col += 1;
    _GetShortPath(maze,right,entry,cur_path,short_path);

    Point down = cur;
    down.row += 1;
    _GetShortPath(maze,down,entry,cur_path,short_path);
    
    Point left = cur;
    left.col -= 1;
    _GetShortPath(maze,left,entry,cur_path,short_path);
    //5.如果四个方向都探测过了，就可以进行出栈（指当前函数栈帧结束
    //，同时cur_path,也要进行出栈），回溯到上一个点
    SeqStackPop(cur_path);
    return;
}
//找到所有路径，然后从所有的路径中筛选出一条最短的（递归）
void GetShortPath(Maze* maze,Point entry)
{
    //就像从一个数组中查找最小元素，一样，定义一个short_path保存最短路径
    SeqStack cur_path;//保存当前路径
    SeqStack short_path;//保存最短路径
    SeqStackInit(&cur_path);
    SeqStackInit(&short_path);
    _GetShortPath(maze,entry,entry,&cur_path,&short_path);
    SeqStackDebugPrint(&short_path,"最短路径");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Round4 针对一个复杂的迷宫地图找出其中的最短路径
//这里的复杂不单单指有多个出口，路径上也可能带环
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//        {0,2,0,0,0,0},
//        {0,3,4,5,0,0},
//        {0,4,0,6,7,8},
//        {6,5,6,7,0,0},
//        {0,0,7,0,0,0},
//        {0,0,8,0,0,0}
//实现递归版本
int CanStayWithCycle(Maze *maze,Point cur,Point pre)
{
    //当前点是否在地图上
    if(cur.row < 0 || cur.row > MAX_ROW || cur.col < 0 || cur.col > MAX_COL)
    {
        return 0;
    }
    //当前点不是墙
    int cur_value = maze->map[cur.row][cur.col];
    if(cur_value == 0)
    {
        return 0;
    }
    //如果当前点是1，就可以直接落脚
    if(cur_value == 1)
    {
        return 1;
    }
    //当前点若已经被标记就比较当前点对应的值和pre对应的值的大小
    //a）cur_path 7,pre_value 5,应该落脚
    //b）cur_path 6,pre_value 5,不应该落脚
    //c）cur_path 5,pre_value 5,不应该落脚
    //d）cur_path 4,pre_value 5,不应该落脚
    //总结以上的几种情况可以总结出：cur_path > pre_path + 1就应该落脚
    int pre_value = maze->map[pre.row][pre.col];
    if(cur_value > pre_value+1)
    {
        return 1;
    }
    return 0;
}
void MarkWithCycle(Maze* maze,Point cur,Point pre)
{
    if(pre.row == -1 && pre.col == -1)
    {
        maze->map[cur.row][cur.col] = 2;
        return;
    }
    int pre_value = maze->map[pre.row][pre.col];
    maze->map[cur.row][cur.col] = pre_value + 1;
}
void _GetShortPathWithCycle(Maze* maze,Point cur,Point pre,Point entry,SeqStack* cur_path,SeqStack* short_path)
{
    //判定当前是否能落脚（判定规则变了）
    printf("cur :%d,%d\n",cur.row,cur.col);
    if(!CanStayWithCycle(maze,cur,pre))
    {
        return;
    }
    //标记当前点，并且将当前点插入到cur_path
    MarkWithCycle(maze,cur,pre);
    SeqStackPush(cur_path,cur);
    //判断当前点是否是出口
    if(IsExit(maze,cur,entry))
    {
        printf("找到了一条路径！\n");
        //如果是出口，要拿cur_path和short_path进行比较，把比较短的路径保存到short_path中
        if(cur_path->size < short_path->size || short_path->size == 0)
        {
            printf("找到了一条比较短的路径！\n");
            SeqStackAssgin(cur_path,short_path);
        }
        //进行回溯，不管当前找到的这条路径是否是比较短的路径，都要进行回溯
        SeqStackPop(cur_path);
    printf("cur :%d,%d\n",cur.row,cur.col);
        return;
    }
    //如果不是出口，以当前点为基准点，探测周围的四个点
    Point up = cur;
    up.row -= 1;
    _GetShortPathWithCycle(maze,up,cur,entry,cur_path,short_path);
    Point right = cur;
    right.col += 1;
    _GetShortPathWithCycle(maze,right,cur,entry,cur_path,short_path);
    Point down = cur;
    down.row += 1;
    _GetShortPathWithCycle(maze,down,cur,entry,cur_path,short_path);
    Point left = cur;
    left.col -= 1;
    _GetShortPathWithCycle(maze,left,cur,entry,cur_path,short_path);
    //如果四个点都探测过了，就出栈回溯
    SeqStackPop(cur_path);
    return;
}
void GetShortPathWithCycle(Maze* maze,Point entry)
{
    SeqStack cur_path;
    SeqStack short_path;
    SeqStackInit(&cur_path);
    SeqStackInit(&short_path);
    Point pre = {-1,-1};
    _GetShortPathWithCycle(maze,entry,pre,entry,&cur_path,&short_path);
    SeqStackDebugPrint(&short_path,"最短路径为");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//以下为测试代码
/////////////////////////////////////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n=====================================%s=====================================\n",__FUNCTION__);
void TestInit()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    MazePrint(&maze);
}
void Test1()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    Point entry = {0,1};
    GetPath(&maze,entry);
    MazePrint(&maze);
}
void Test2()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    Point entry = {0,1};
    GetPath(&maze,entry);
    MazePrint(&maze);
}
void Test3()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    Point entry = {0,1};
    GetShortPath(&maze,entry);
    MazePrint(&maze);
}
void Test4()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    Point entry = {0,1};
    GetShortPathWithCycle(&maze,entry);
    MazePrint(&maze);
}
int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    return 0;
}
#endif
