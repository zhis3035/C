/* 1.实现输入10个数使用冒泡法进行排序 */

#include <stdio.h>

int main()
{
    int i=0,j=0;
    float array[10];
    float tmp=0.0f;
    
    printf("请输入10个数：\n");
    for(i=0;i<10;i++)
        scanf("%f",&array[i]);
    
    printf("你输入的10个数是：\n");
    for(i=0;i<10;i++)
        printf("%.3f ",array[i]);
    
    printf("\n");
    
    /*冒泡排序*/
    for(i=0;i<10;i++)
    {
        for(j=i+1;j<10;j++)
        {
            if(array[i]>array[j])
            {
                tmp=array[i];
                array[i]=array[j];
                array[j]=tmp;
            }
        }
    }
    
    printf("使用冒泡排序以后的10个数：\n");
    for(i=0;i<10;i++)
        printf("%.3f ",array[i]);
    
    getchar();
    getchar();
    return 0;
}
