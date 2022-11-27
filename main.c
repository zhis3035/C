#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

/* Χǽ�Ŀ��� */
#define WIDTH  50   
#define HEIGHT 20

HANDLE g_hOut;              //�������̨��׼����ľ��
COORD g_coord = { 0,0 };   //�������̨����λ��


typedef struct POS          //���ڱ�������Ľṹ
{
    int x;
    int y;
}POS;

typedef struct SNAKE
{
    POS body[(WIDTH - 1) * (HEIGHT - 1)]; //������ͷ��body[0]Ԫ��
    int length;                     //������

    POS head;       //x,yȡ1��-1������������¼��ͷ�ƶ��ķ���ÿ���ƶ�һ����λ
    POS tail;       //������¼��β��λ��
}SNAKE;




/* ��ʼ���� */
void _InitializeSnake(SNAKE* snake)
{
    /* ��ʼ����ͷ */
    snake->body[0].x = (WIDTH - 2) / 2;
    snake->body[0].y = (HEIGHT - 2) / 2;

    /* ��ʼ������һ�ڳ��� */
    snake->body[1].x = (WIDTH - 2) / 2 - 1;
    snake->body[1].y = (HEIGHT - 2) / 2;

    snake->length = 2;    //�ߵ��ܳ���Ϊ2

    /*��ʼ��ʱ, ��ͷû���ƶ�*/
    snake->head.x = 1;          //��Ϸ��ʼ���߳����ƶ�
    snake->head.y = 0;

    /*��βλ��Ϊ:*/
    snake->tail.x = (WIDTH - 2) / 2 - 1;
    snake->tail.y = (HEIGHT - 2) / 2;
}

/*��ʼ��ʳ��*/
int  _InitialFood(SNAKE* snake, POS* food)
{
    int tmpx, tmpy;

    srand(time(NULL));

    /*����ʳ������꣬��ȷ�������ߵ������غ�*/
    while (1)
    {
        tmpx = (rand() % (WIDTH - 2)) + 1;  //��2����Ϊ���ߵ�ǽռ��2����λ�Ŀռ�
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

/*��ӡ�ߺ�ʳ��*/
void _ShowSnakeandFood(SNAKE* snake, POS* food)
{
    g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    g_coord.X = 0;
    g_coord.Y = 0;

    /*��ӡ��ͷ������*/
    for (int i = 0; i < snake->length; i++)  //�����ߵĳ��ȴ�ӡ��
    {
        g_coord.X = snake->body[i].x;
        g_coord.Y = snake->body[i].y;
        SetConsoleCursorPosition(g_hOut, g_coord);
        if (i == 0)
            putchar('*');  //��ͷ
        else
            putchar('+'); //����
    }

    /*��ӡʳ��*/
    g_coord.X = food->x;
    g_coord.Y = food->y;
    SetConsoleCursorPosition(g_hOut, g_coord);
    putchar('@');

}

/*�ƶ���*/
void _MoveSnake(SNAKE* snake)
{
    g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    g_coord.X = 0;
    g_coord.Y = 0;

    /*��¼��β*/
    snake->tail.x = snake->body[snake->length - 1].x;
    snake->tail.y = snake->body[snake->length - 1].y;

    /*��������,����β��ʼ������ÿһ�ڵ��������Ϊǰһ�ڵ�����
      ������ͷ���ƶ��������ɼ���������Ƶģ�������Ҫ��������*/
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i].x = snake->body[i - 1].x;
        snake->body[i].y = snake->body[i - 1].y;
    }


    /*������ͷ*/
    snake->body[0].x = snake->body[0].x + snake->head.x;
    snake->body[0].y = snake->body[0].y + snake->head.y;

    /*�����ƶ������β*/
    g_coord.X = snake->tail.x;
    g_coord.Y = snake->tail.y;
    SetConsoleCursorPosition(g_hOut, g_coord);
    putchar(' ');   //���ƶ���֮ǰ����β��������Ļ�ϣ���Ҫ����������������ֻᵼ������,����ÿո��滻��
}

/*�����˳��룬�˳���Ϸ*/
void _ExitGame(int exitcode)                 //exitcode=0������ESC���˳�
{                                           //exitcode=1,������ײǽ�����˳�                              
    system("cls");                         //exitcode=2,������ײ���Լ������˳�
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

/*�����ߵ��ƶ�������Ϸ����ͣ���˳�*/
void _ContrlSnake(SNAKE* snake)
{
    char ch = 0;
    while (_kbhit())  //_kbbit()�����������Ǽ�����̨���ڵİ����Ƿ񱻰���,�м����·��ط���ֵ�����򷵻�0
    {
        ch = _getch(); //�ǻ���ֱ�ӴӼ��̣��ǻ���������ȡ����
    }
    switch (ch)
    {
    case 'w':
        snake->head.x = 0;
        snake->head.y = -1;  //���ϣ�������-1
        break;
    case 'a':
        snake->head.x = -1;  //���󣬺�����-1
        snake->head.y = 0;
        break;
    case 's':
        snake->head.x = 0;
        snake->head.y = 1;   //���£�������+1
        break;
    case 'd':
        snake->head.x = 1;  //���ң�������+1
        snake->head.y = 0;
        break;
    case 27:                //����ESC�����˳���Ϸ
        _ExitGame(0);
    case 32:
        while (1)           //���¿ո���������������ѭ��
        {
            ch = _getch();
            if (ch == 32)
            {
                return;
            }
            else if (ch == 27)      //��Ϸ��ͣʱҲ���˳�
            {
                _ExitGame(0);
            }

        }

    }
}

/*�Ե�ʳ����ô����*/
void _EatFood(SNAKE* snake, POS* food){
    if (snake->body[0].x == food->x && snake->body[0].y == food->y)
    {
        /*ԭʳ����ʧ*/
        _InitialFood(snake, food);
        /*��������һ��*/
        snake->length += 1;
    }
}

/*��ײǽ*/
void _HitWall(SNAKE* snake)
{
    /*��ͷ�������������Χǽ��Χ�ڣ�˵��ײǽ��*/
    if (!(snake->body[0].x < WIDTH && snake->body[0].x>0 && snake->body[0].y < HEIGHT && snake->body[0].y>0))
    {
        _ExitGame(1);
    }
}



void _HitSelf(SNAKE* snake)
{
    for (int i = 1; i <= snake->length - 1; i++)
    {
        /*��ͷ�������غϣ���������������*/
        if (snake->body[0].x == snake->body[i].x && snake->body[0].y == snake->body[i].y)
        {
            _ExitGame(2);
        }

    }
}

void _Play(SNAKE* snake, POS* food)
{
    _InitializeSnake(snake);    //��ʼ����
    _InitialFood(snake, food);	//����ʼ��ʳ��	
    while (1)
    {
        /*������*/
        _ContrlSnake(snake);

        /*�ƶ���*/
        _MoveSnake(snake);

        /*��ײǽ��*/
        _HitWall(snake);

        /*ײ���Լ�*/
        _HitSelf(snake);

        /*�ߵ�λ�øı����Ҫ������ʾ*/
        _ShowSnakeandFood(snake, food);

        Sleep(300);      //�������ƶ����ٶ�

        /*�߳Ե�ʳ��*/
        _EatFood(snake, food);

    }
}

/* ��ӡΧǽ */
void _PrintWall()
{
    g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    g_coord.X = 0;
    g_coord.Y = 0;

    /*��ӡ�����ǽ*/
    for (int i = 0; i < WIDTH; i++)
        putchar('*');
    putchar('\n');

    /*��ӡ��ߵ�ǽ*/
    for (int j = 0; j < HEIGHT; j++)
    {
        g_coord.Y = j;
        SetConsoleCursorPosition(g_hOut, g_coord);
        printf("*\n");
    }

    /*��ӡ�ұߵ�ǽ*/
    g_coord.X = WIDTH - 1;
    g_coord.Y = 0;
    for (int j = 0; j < HEIGHT; j++)
    {
        g_coord.Y = j;
        SetConsoleCursorPosition(g_hOut, g_coord);
        printf("*\n");
    }

    /*��ӡ�±ߵ�ǽ*/
    g_coord.X = 0;
    g_coord.Y = HEIGHT - 1;
    SetConsoleCursorPosition(g_hOut, g_coord);
    for (int i = 0; i < WIDTH; i++)
        putchar('*');
    putchar('\n');
}

/*���ؿ���̨���*/
void _HideConsoleCursor()
{
    CONSOLE_CURSOR_INFO cci;   //��������Ϣ�Ľṹ
    cci.dwSize = sizeof(cci);
    cci.bVisible = FALSE;     
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

int main()
{
    char key = '\0';
    SNAKE* snake = (SNAKE*)malloc(sizeof(SNAKE)); //�����߲������ڴ�
    POS* food = (POS*)malloc(sizeof(POS));      //����ʳ�ﲢ�����ڴ�


    system("title ̰����");
    system("mode con cols=50 lines=30");

    _HideConsoleCursor();
    _PrintWall();

    g_coord.X = 0;
    g_coord.Y = HEIGHT + 2;
    SetConsoleCursorPosition(g_hOut, g_coord);
    printf("                   �ո����ͣ��Ϸ                   \n");
    printf("                   ESC���˳���Ϸ                    \n");


    while (1)
    {
        while (_kbhit())
        {
            key = _getch();
        }
        switch (key)
        {
        case 27:                    //����ESC�����˳���Ϸ
            _ExitGame(0);
        case 32:                    //���¿ո������Ϸ��ʼ
            _Play(snake, food);
            break;
        }
    }
    /*�ͷ��ڴ�*/
    free(snake);
    free(food);

    return 0;
}
