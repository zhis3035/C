#include <stdio.h>
#include <math.h>
/*
功能：用数组来实现乘法，结果逆序保存在原数组内（被乘数也是按位逆序保存在数组的）
参数：x - 乘数 	
	  res[] - 数组
	  res_size - 数组大小
返回值：数组的大小

原理：
		1234
	 *     9
	 --------
	     (3)6     4*9+进位0,保留6（中间结果模10得到），进位3(中间结果整除10得到）
		(3)0      3*9+进位3，保留0，进位3
       ...
*/
int multiply(int x,int res[],int res_size)
{
	int carry=0;					//保存进位
	for(int i=0;i<res_size;i++)
	{
		int tmp=res[i]*x+carry;		 //按位相乘得到的结果，包含了进位结果
		res[i]=tmp%10;				//数组第i个元素保存进位后的结果
		carry=tmp/10;				//更新进位
	}
	while(carry)					//处理最后的进位，直到不产生进位为止
	{
		res[res_size]=carry%10;	   //进位大于10，保存结果，继续进位
		carry=carry/10;			   //更新进位
		res_size++;				   //位数加一
	}
	return res_size;
}

/*
功能：计算n!阶乘结果的位数
参数：n
返回值：n！阶乘结果的位数

原理：log10(x)向上取整，就是十进制数x的位数
	  log10(x*y*z*...n)=log10(x)+log10(y)+log10(z)+...+log10(n)
	  log10(1*2*3*...*n)即log10(1)+log10(2)+log10(3)+...+log10(n)  
*/
int calcDigits(int n)        
{
	double digits_res=0; 
	if(n==1)			//n=1直接返回1
		return 1;
	else
	{
		for(int i=1;i<=n;i++)
			digits_res+=log10(i);
	}
	return ceil(digits_res);
	
}

/*
功能：计算n的阶乘，并打印
参数：n
无返回值
*/
void factorial(int n)
{
	int max=calcDigits(n);			 //获取结果位数
	int res[max];					//创建一个数组,变长数组需要c99标准支持
	
	res[0]=1;					   //数组第一个元素设为1；
	int res_size=1;					
	
	for(int x=2;x<=n;x++)		  			//计算n!阶乘
		res_size=multiply(x,res,res_size);  //保存结果的位数，即数组元素的个数
	
	for(int i=res_size-1;i>=0;i--)			//打印结果	
		printf("%d",res[i]);			   
}



int main()
{
	int digits,n;
	printf("请输入需要计算的阶乘数：");
	while(scanf("%d",&n))
	{
		digits=calcDigits(n);
		printf("%d阶乘的结果有%d位数字，其阶乘结果如下：\n",n,digits);
		factorial(n);
		printf("\n请输入需要计算的阶乘数：");
	}
	
	getchar();
	return 0;
}


