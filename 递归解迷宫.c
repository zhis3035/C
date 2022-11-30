#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowMaze(char szMaze[][30],int nRow)
{
    for(int i=0;i<nRow;i++)
    {
        puts(szMaze[i]);
    }
}

void Maze(char szMaze[][30],int x,int y,int nRow)
{
    system("cls");
    ShowMaze(szMaze,nRow);
    system("pause");
   
    
    if(szMaze[x][y]=='$')
    {
         system("cls");
         ShowMaze(szMaze,nRow);
         puts("通关");
         system("pause");
         exit(0);
    }
    szMaze[x][y]='>';   //>代表路可以走
    
    
    /*如果一条路能走通，那么就继续走（递归调用）
      如果路走不通，那么就返回，返回时做好标记 */
    
    if(szMaze[x+1][y]=='0' ||szMaze[x+1][y]=='$')  //上
    {
        Maze(szMaze,x+1,y,nRow);
    }
     if(szMaze[x][y-1]=='0' ||szMaze[x][y-1]=='$') //左
    {
        Maze(szMaze,x,y-1,nRow);
    }
      if(szMaze[x][y+1]=='0' ||szMaze[x][y+1]=='$') //右
    {
        Maze(szMaze,x,y+1,nRow);
    }
      if(szMaze[x-1][y]=='0' ||szMaze[x-1][y]=='$') //下
    {
        Maze(szMaze,x-1,y,nRow);
    }
    szMaze[x][y]='x';   //在函数返回时才会打印，x代表路不通
    system("cls");
    ShowMaze(szMaze,nRow);
    system("pause");
    
    
    return;
    
}
int main()
{
    char szMaze[][30]={
        "1111111111111111111111111111",
        "1011111000000000000111000111",
        "100000000111000111011001$111",
        "1101100001110101111110111111",
        "1100001101000101110000111111",
        "1101111101011101110111111111",
        "1100000101011100110111111111",
        "1111110000011110000111111111",
        "1111111111111111111111111111",
    };
    int nRow=sizeof(szMaze)/sizeof(szMaze[0]);
    Maze(szMaze,1,1,nRow);
    return 0;
}
