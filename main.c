#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

/* 围墙的宽、高 */
#define WIDTH  50   
#define HEIGHT 20

HANDLE g_hOut;              //保存控制台标准输出的句柄
COORD g_coord = { 0,0 };   //保存控制台光标的位置


typedef struct POS          //用于保存坐标的结构
{
    int x;
    int y;
}POS;

typedef struct SNAKE
{
    POS body[(WIDTH - 1) * (HEIGHT - 1)]; //蛇身，蛇头是body[0]元素
    int length;                     //蛇身长度

    POS head;       //x,y取1或-1，可以用来记录蛇头移动的方向，每次移动一个单位
    POS tail;       //用来记录蛇尾的位置
}SNAKE;




/* 初始化蛇 */
void _InitializeSnake(SNAKE* snake)
{
    /* 初始化蛇头 */
    snake->body[0].x = (WIDTH - 2) / 2;
    snake->body[0].y = (HEIGHT - 2) / 2;

    /* 初始化蛇身，一节长度 */
    snake->body[1].x = (WIDTH - 2) / 2 - 1;
    snake->body[1].y = (HEIGHT - 2) / 2;

    snake->length = 2;    //蛇的总长度为2

    /*初始化时, 蛇头没有移动*/
    snake->head.x = 1;          //游戏开始，蛇朝右移动
    snake->head.y = 0;

    /*蛇尾位置为:*/
    snake->tail.x = (WIDTH - 2) / 2 - 1;
    snake->tail.y = (HEIGHT - 2) / 2;
}

/*初始化食物*/
int  _InitialFood(SNAKE* snake, POS* food)
{
    int tmpx, tmpy;

    srand(time(NULL));

    /*生成食物的坐标，并确保不与蛇的坐标重合*/
    while (1)
    {
        tmpx = (rand() % (WIDTH - 2)) + 1;  //减2是因为两边的墙占据2个单位的空间
        tmpy = (rand() % (HEIGHT - 2)) + 1;

        for (int i = 0; i < snake->length; i++)
        {
            if (tmpx != snake->body[i].x && tmpy != snake->body[i].y)
            {
                food->x = tmpx;
                food->y = tmpy;
                return 1;
            }
        }

    }
}

/*打印蛇和食物*/
void _ShowSnakeandFood(SNAKE* snake, POS* food)
{
    g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    g_coord.X = 0;
    g_coord.Y = 0;

    /*打印蛇头和蛇身*/
    for (int i = 0; i < snake->length; i++)  //根据蛇的长度打印蛇
    {
        g_coord.X = snake->body[i].x;
        g_coord.Y = snake->body[i].y;
        SetConsoleCursorPosition(g_hOut, g_coord);
        if (i == 0)
            putchar('*');  //蛇头
        else
            putchar('+'); //蛇身
    }

    /*打印食物*/
    g_coord.X = food->x;
    g_coord.Y = food->y;
    SetConsoleCursorPosition(g_hOut, g_coord);
    putchar('@');

}

/*移动蛇*/
void _MoveSnake(SNAKE* snake)
{
    g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    g_coord.X = 0;
    g_coord.Y = 0;

    /*记录蛇尾*/
    snake->tail.x = snake->body[snake->length - 1].x;
    snake->tail.y = snake->body[snake->length - 1].y;

    /*处理蛇身,从蛇尾开始处理，将每一节的坐标更新为前一节的坐标
      由于蛇头的移动方向是由键盘输入控制的，所以需要单独处理*/
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i].x = snake->body[i - 1].x;
        snake->body[i].y = snake->body[i - 1].y;
    }


    /*处理蛇头*/
    snake->body[0].x = snake->body[0].x + snake->head.x;
    snake->body[0].y = snake->body[0].y + snake->head.y;

    /*处理移动后的蛇尾*/
    g_coord.X = snake->tail.x;
    g_coord.Y = snake->tail.y;
    SetConsoleCursorPosition(g_hOut, g_coord);
    putchar(' ');   //蛇移动后，之前的蛇尾还留在屏幕上，需要处理掉，设置清屏又会导致闪屏,因此用空格替换掉
}

/*根据退出码，退出游戏*/
void _ExitGame(int exitcode)                 //exitcode=0，代表按ESC键退出
{                                           //exitcode=1,代表蛇撞墙导致退出                              
    system("cls");                         //exitcode=2,代表蛇撞到自己导致退出
    g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    g_coord.X = WIDTH / 2 - 12;
    g_coord.Y = 0;
    SetConsoleCursorPosition(g_hOut, g_coord);
    if (exitcode == 0)
    {
        puts("Exit game!");
    }
    else if (exitcode == 1)
    {
        puts("You hit a wall. Game over!");
    }
    else if (exitcode == 2)
    {
        puts("You hit yourself. Game over!");
    }
    getchar();
    exit(0);
}

/*控制蛇的移动方向，游戏的暂停与退出*/
void _ContrlSnake(SNAKE* snake)
{
    char ch = 0;
    while (_kbhit())  //_kbbit()函数的作用是检查控制台窗口的按键是否被按下,有键按下返回非零值，否则返回0
    {
        ch = _getch(); //非回显直接从键盘（非缓冲区）获取输入
    }
    switch (ch)
    {
    case 'w':
        snake->head.x = 0;
        snake->head.y = -1;  //向上，纵坐标-1
        break;
    case 'a':
        snake->head.x = -1;  //向左，横坐标-1
        snake->head.y = 0;
        break;
    case 's':
        snake->head.x = 0;
        snake->head.y = 1;   //向下，纵坐标+1
        break;
    case 'd':
        snake->head.x = 1;  //向右，横坐标+1
        snake->head.y = 0;
        break;
    case 27:                //按下ESC键，退出游戏
        _ExitGame(0);
    case 32:
        while (1)           //按下空格键，程序进入无限循环
        {
            ch = _getch();
            if (ch == 32)
            {
                return;
            }
            else if (ch == 27)      //游戏暂停时也能退出
            {
                _ExitGame(0);
            }

        }

    }
}

/*吃到食物怎么处理*/
void _EatFood(SNAKE* snake, POS* food){
    if (snake->body[0].x == food->x && snake->body[0].y == food->y)
    {
        /*原食物消失*/
        _InitialFood(snake, food);
        /*蛇身增加一节*/
        snake->length += 1;
    }
}

/*蛇撞墙*/
void _HitWall(SNAKE* snake)
{
    /*蛇头的坐标如果不在围墙范围内，说明撞墙了*/
    if (!(snake->body[0].x < WIDTH && snake->body[0].x>0 && snake->body[0].y < HEIGHT && snake->body[0].y>0))
    {
        _ExitGame(1);
    }
}



void _HitSelf(SNAKE* snake)
{
    for (int i = 1; i <= snake->length - 1; i++)
    {
        /*蛇头和蛇身重合，则碰到了蛇自身*/
        if (snake->body[0].x == snake->body[i].x && snake->body[0].y == snake->body[i].y)
        {
            _ExitGame(2);
        }

    }
}

void _Play(SNAKE* snake, POS* food)
{
    _InitializeSnake(snake);    //初始化蛇
    _InitialFood(snake, food);	//初初始化食物	
    while (1)
    {
        /*控制蛇*/
        _ContrlSnake(snake);

        /*移动蛇*/
        _MoveSnake(snake);

        /*蛇撞墙了*/
        _HitWall(snake);

        /*撞到自己*/
        _HitSelf(snake);

        /*蛇的位置改变后，需要重新显示*/
        _ShowSnakeandFood(snake, food);

        Sleep(300);      //控制蛇移动的速度

        /*蛇吃到食物*/
        _EatFood(snake, food);

    }
}

/* 打印围墙 */
void _PrintWall()
{
    g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    g_coord.X = 0;
    g_coord.Y = 0;

    /*打印上面的墙*/
    for (int i = 0; i < WIDTH; i++)
        putchar('*');
    putchar('\n');

    /*打印左边的墙*/
    for (int j = 0; j < HEIGHT; j++)
    {
        g_coord.Y = j;
        SetConsoleCursorPosition(g_hOut, g_coord);
        printf("*\n");
    }

    /*打印右边的墙*/
    g_coord.X = WIDTH - 1;
    g_coord.Y = 0;
    for (int j = 0; j < HEIGHT; j++)
    {
        g_coord.Y = j;
        SetConsoleCursorPosition(g_hOut, g_coord);
        printf("*\n");
    }

    /*打印下边的墙*/
    g_coord.X = 0;
    g_coord.Y = HEIGHT - 1;
    SetConsoleCursorPosition(g_hOut, g_coord);
    for (int i = 0; i < WIDTH; i++)
        putchar('*');
    putchar('\n');
}

/*隐藏控制台光标*/
void _HideConsoleCursor()
{
    CONSOLE_CURSOR_INFO cci;   //保存光标信息的结构
    cci.dwSize = sizeof(cci);
    cci.bVisible = FALSE;     
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

int main()
{
    char key = '\0';
    SNAKE* snake = (SNAKE*)malloc(sizeof(SNAKE)); //创建蛇并分配内存
    POS* food = (POS*)malloc(sizeof(POS));      //创建食物并分配内存


    system("title 贪吃蛇");
    system("mode con cols=50 lines=30");

    _HideConsoleCursor();
    _PrintWall();

    g_coord.X = 0;
    g_coord.Y = HEIGHT + 2;
    SetConsoleCursorPosition(g_hOut, g_coord);
    printf("                   空格键暂停游戏                   \n");
    printf("                   ESC键退出游戏                    \n");


    while (1)
    {
        while (_kbhit())
        {
            key = _getch();
        }
        switch (key)
        {
        case 27:                    //按下ESC键，退出游戏
            _ExitGame(0);
        case 32:                    //按下空格键，游戏开始
            _Play(snake, food);
            break;
        }
    }
    /*释放内存*/
    free(snake);
    free(food);

    return 0;
}
