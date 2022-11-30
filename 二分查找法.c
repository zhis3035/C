/*3.对以上两题排序排完后进行折半查找*/

#include <stdio.h>
#include <math.h>

/*选择排序*/
void _SelectionSort(float array[],int n)
{
    int min=0;
    float tmp=0.0f;
    for(int i=0;i<n;i++)
    {
        min=i;
        for(int j=i+1;j<n;j++)
        {
            if(array[j]<array[min])
            {
                tmp=array[j];
                array[j]=array[min];
                array[min]=tmp;
            }
        }
    }
    return;
}

/*冒泡排序*/
void _BubbleSort(float array[],int n)
{  
     float tmp=0.0f;
     for(int i=0;i<n;i++)
     {
         for(int j=i+1;j<n;j++)
         {
             if(array[i]>array[j])
             {
                 tmp=array[i];
                 array[i]=array[j];
                 array[j]=tmp;
             }
         }
     }
     return;
}

/*折半查找*/
int _Bisearch(float array[],int narray,float num)
{
    int left=0;
    int right=narray-1;
    int mid=0;
    
    while(left<=right)
    {
        mid=(left+right)/2;
        if(fabs(array[mid]-num)<1e-6)  //判断浮点数是否相等
        {
            return mid;
        }
        else if(array[mid]<num)
        {
            left=mid+1;
        }
        else if(array[mid]>num)
        {
            right=mid-1;
        }
        
    }
    return -1;
}
int main()
{
    int i=0,j=0,option=0,index=0;
    float array[10];
    float tmp=0.0f,min=0.0f,num=0.0f;
    
    /*输入10个数*/
    printf("请输入10个数：\n");
    for(i=0;i<10;i++)
        scanf("%f",&array[i]);
    printf("你输入的10个数是：\n");
    for(i=0;i<10;i++)
        printf("%.3f ",array[i]);
    printf("\n");
    
    /*选择排序方式*/
    printf("请选择排序方式：1.选择  2.冒泡\n");
    scanf("%d",&option);
    if(option==1)
    {
        _SelectionSort(array,10);
    }
    else if(option==2)
    {
        _BubbleSort(array,10);
    }
    else
    {
        return 0;
    }
    
    printf("排序以后的10个数：\n");
    for(i=0;i<10;i++)
        printf("%.3f ",array[i]);
    printf("\n");
    
    /*折半查找*/
    printf("请输入要查找的数：\n");
    scanf("%f",&num);
    index=_Bisearch(array,10,num);
    if(index==-1)
    {
        printf("输入的数不在数组中\n");
        getchar();
        getchar();
        return 0;
    }
    else
    {
        printf("输入是下标为%d的数,即第%d个数\n",index,index+1);
        getchar();
        getchar();
        return 0;
    }
}
