/* 2.实现输入10个数使用选择排序 */

#include <stdio.h>

int main()
{
    int i=0,j=0,min=0;
    float array[10];
    float tmp=0.0f;
    
    printf("请输入10个数：\n");
    for(i=0;i<10;i++)
        scanf("%f",&array[i]);
    
    printf("你输入的10个数是：\n");
    for(i=0;i<10;i++)
        printf("%.3f ",array[i]);
    
    printf("\n");
    
    /*选择排序*/
    for(i=0;i<10;i++)
    {
        min=i;
        for(j=i+1;j<10;j++)
        {
            if(array[j]<array[min])
            {
                tmp=array[j];
                array[j]=array[min];
                array[min]=tmp;
            }
        }
    }
    
    printf("使用选择排序以后的10个数：\n");
    for(i=0;i<10;i++)
        printf("%.3f ",array[i]);
    
    getchar();
    getchar();
    return 0;
}
