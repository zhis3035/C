/*2.写程序查看float定义数据的内存。*/

#include <stdio.h>

/*
功能：指定地址中的内容按照16进制打印出来
参数：addr-内存起始地址
	  n-打印多少字节
*/
void printHex(const unsigned char* addr, int n)     //使用unsigned char*，避免字节里>=8的补1导致打印f
{
	for (int i = n - 1; i >= 0; i--)   				//i初始值设为n-1,适用小端机器
		printf("%02x ", *(addr + i));
}

int main()
{
	float fl;
	printf("请输入一个小数：");
	while(scanf("%f",&fl))
	{
		printf("%f在内存中的形式为：",fl);
		printHex((unsigned char*)&fl,sizeof(float));
		printf("\n");
		printf("请输入一个小数：");
	}
	
	getchar();
	return 0;
}
