#include <stdio.h>
#include"seqstack.h"

#define MAX_ROW 6
#define MAX_COL 6

typedef struct Maze
{
    int map[MAX_ROW][MAX_COL];
}Maze;
//#define FOR_MAZE
//#ifdef FOR_MAZE
//
//typedef struct Point
//{
//    int row;
//    int col;
//}Point;
//typedef Point SeqStackType;
//#else
//typedef char SeqStackType;
//#endif
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
    printf("cur :%d,%d\n",cur.row,cur.col);
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
#include"seqstack.h"
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
int main()
{
    TestInit();
    Test1();
    Test2();
    return 0;
}
#endif
