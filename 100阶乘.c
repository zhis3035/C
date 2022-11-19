#include <stdio.h>

int main()
{
	int array[200] = { 0 };           //设置一个数组，用于保存结果
	int digits = 1;					  //结果位数
	int carry = 0;					  //进位	
	array[0] = 1;					  //arry[0]=1,即1！=1

	for (int i = 2; i <= 100; i++)    //i是乘数，从2开始
	{
		
		for (int j = 0; j < digits; j++)
		{
			int tmp = array[j] * i + carry;  //用第j位乘于乘数，加上进位
			array[j] = tmp % 10;			 //保留余数
			carry = tmp / 10;				 //更新进位
		}
		while (carry)						//被乘数的每一位都乘完以后，处理最后的进位
		{
			digits++;						//结果位数+1
			array[digits] = carry % 10;		//进位超过10，取余数
			carry /= 10;					//更新进位
		}
	}
	for (int i = digits-1; i >= 0; i--)	   //打印结果，结果逆序存放，数组从0开始，所以digits-1,
		printf("%d", array[i]);
}
