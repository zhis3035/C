/* 
用C语言写一个控制台登陆程序：
输入用户名密码，验证是否正确，如果正确，显示“登陆成功”程序退出，
如果错误显示“登陆失败”，累积错误3次，提示后退出。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <stdbool.h>

#define MAX 10    

typedef struct User
{
	char name[20];     //用户名
	char password[16]; //用户密码
} USER;


/* 
功能：判断用户名是否存在,并保存
参数：name-用户名
	  usr[]-用户结构体数组
	  n-用户结构体数组元素数量
返回值：用户名存在，返回其所属结构体数组下标，否则返回-1
*/
int finduser(const char *name,USER usr[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(!strcmp(name,usr[i].name))     //strcmp函数比较两个字符串，相同则返回0；
		{
			return i;
		}
	}
	return -1;
}

/* 
功能：判断密码是否正确
参数：pwd-输入的密码
	  usr[]-用户结构体数组
	  pos-需要匹配的密码所属数组下标
返回值：密码正确，返回真值，否则返回假
*/
bool matchpassword(char *pwd,USER usr[],int pos)
{
	if(!strcmp(pwd,usr[pos].password))
		return true;
	return false;
}


int main()
{
	USER learner[MAX]={"user1", "123456",
						"user2", "1asfa465",
						"user3", "e2a36465",
						"user4", "1af36465",
						"user5", "1asf1325",
						"user6", "asfvre",
						"user7", "54asdf,",
						"user8", "312fasewqr",
						"user9", "asdfasvf",
						"user10", "12f!sfsad"};
	int count=0;
	int pos=-1;
	bool flag=false;
	char usr_name[20]={0};
	char usr_password[16]={0};
	
	while(1)
	{
		printf("请输入用户名：\n");
		scanf("%s",usr_name);
		
		printf("请输入密码：\n");
        scanf("%s",usr_password);
	
		pos=finduser(usr_name,learner,MAX);    //调用函数，查看输入的用户名是否在用户列表中
		
		if(pos==-1)							 //pos=-1，说明输入的用户名不在用户列表中
		{	
			count++;								//count+1，输入错误计数一次
			if(count==3)  break;					//count=3,直接跳出循环，结束程序
			printf("用户名不存在，请重新输入!\n\n");  
			continue;								//continue跳过后续的代码，重新开始输入			
		}
		
		flag=matchpassword(usr_password,learner,pos); //执行到这里输入的用户名没问题，匹配密码
		
		if(!flag)									//flag为假，说明密码匹配不上
		{
			count++;								//count+1，输入错误计数一次	
			if(count==3)  break;					//count=3,直接跳出循环，结束程序
			printf("密码错误，请重新输入!\n\n");
			continue;
		}
		
		printf("登陆成功!\n");					  //当用户名输入正确，且密码匹配上，才能执行到这里
		system("pause");
		return 0;
	}
		
	printf("错误次数过多，请稍后重试!\n");        //输入错误次数达到3次，直接退出程序
	system("pause");
	return 0;
}
