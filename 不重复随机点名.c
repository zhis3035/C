//*7,	随机点名，支持两种随机方式。1，可以重复；2，不可重复。


//注意：
//		*学员名单需要和本软件放在同一目录, 编码需要为ANSI编码
//		*学员名单最后一行不能有换行符


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
#include<stdbool.h>

/*
功能：将字符串中的\n替换成\0
参数：字符串地址
无返回值
*/
void replace_n(char *buffer)
{
	
	for(int i=0;i<=strlen(buffer);i++)
		if(buffer[i]=='\n')
			buffer[i]='\0';
}

/*
功能：判断一个数字否是为数组中前n个元素之一
参数：数组，数组前n个元素，需要判断的数字
返回值：数字是元素中的数组返回1，不是返回-1
*/
int is_array_num(int *array,int n, int num)
{
	for(int i=0;i<=n;i++)
	{
		if(num==array[i])
			return true;
	}
	return false;
}


int main()
{
	FILE* fp = fopen("学员名单.txt", "r");
	if (fp == NULL)
	{
		printf("请确认学员名单是否存在！\n");
		return 0;
	}
	
	//获取学员名单文件中的学员数
	int num= 0;
	char ch,buffer[30]={0};
	ch = fgetc(fp);
	if(ch==EOF)								//判断名单中是否有数据，暂不判断数据是否是有效的名字
	{
		printf("学员名单中没有数据\n");
		return 0;
	}
	while (ch != EOF)
	{
		if (ch == '\n')
			++num;
		ch=fgetc(fp);
	}
	const int cr45_num=num+1;				//学员人数=换行符，规定最后一行不能有换行符的原因
	
	rewind(fp);								//让文件指针指向文件开头
	
	//将学员名单加载到内存中
	char learner[cr45_num][30];  		   //创建一个二维数组，用来保存学员名字
	
	for (int i = 0; i <cr45_num; i++)
	{
		
		fgets(buffer, 30, fp);
		replace_n(buffer);
		strcpy(learner[i], buffer);
	}

	
	printf("请选择点名模式：\n");
	printf("1.重复模式\n");
	printf("2.不重复模式\n");
	printf("请选择：\n");

	int option;
	
	scanf("%d", &option);
	
	//重复点名
	if (option == 1)
	{
		int i=0;
		srand((unsigned)time(0));
		
		while ((ch = getchar()) != 'q')
		{
			i=rand()%cr45_num;		//学员二维数组的行下标为0~cr45_num-1,随机数也应在此范围
			printf("学员：%6s, 在否？", learner[i]);
			printf("请按回车键继续(q退出)：");
		}
	}
	else if(option==2)
	{
		
		//1.定义一个元素数量为学员人数的数组，生成学员总数范围内的不重复随机数将数组填充
		//2.利用上述数组的元素作为学员数组的下标按顺序进行点名
		//3.index数组的元素是随机的，用其元素作为学员元素的下标来进行顺序点名，也相当与随机点名
		
		int index[cr45_num];       //定义index数组
		int i=0,j=0,count=0;
		int tmp;
		srand((unsigned)time(0));
		
		while (1)
		{
			tmp=rand()%cr45_num;
			if(!is_array_num(index,i,tmp))   //判断tmp是否是数组中的元素
			{
				index[i]=tmp;
				++i;
				if(i==cr45_num)				//随机数全部生成成功，跳出循环
					break;
			}
			
		}
		
		while ((ch = getchar()) != 'q' && count<cr45_num)   //用index数组中的元素作为下标，打印学员数组中的元素
		{
			j=index[count];
			printf("学员：%6s, 在否？", learner[j]);
			printf("请按回车键继续(q退出)：");
			++count;
			if(count>=cr45_num)
				printf("\n%d位学员都已点到，程序将退出！\n",count);
		}
	}
	
	
	getchar();
	return 0;
}

