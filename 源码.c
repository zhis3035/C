#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void add(int sum1) //添加条目
{
	int i;
	Sleep(2*1000);
	for(i=0; i<sum1;i++)
	{
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE,159*65535/1920,43*65535/1080,0,0);    //将鼠标焦点移到“新增”按钮上面
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
		mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);   //模拟鼠标单击
	}
}

void input_less_100(int sum2)
{
	int i,j;
	
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 167*65535/1920,89*65535/1080,0,0);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);   //模拟鼠标单击
	Sleep(500);
	keybd_event(17,0,0,0); //按下ctrl键
	keybd_event(16,0,0,0); //按下shift键
	keybd_event(36,0,0,0); //按下home键
	keybd_event(17,0,2,0); //松开ctrl键
	keybd_event(16,0,2,0); //松开shift键
	keybd_event(36,0,2,0); //松开home键
	Sleep(300);
	for(j=0; j<7; j++)
	{
		for(i=0; i<sum2; i++)
		{
			//填充的关键模块，Sleep函数是控制填充速度的关键，项目少，复制程序未响应的概率小，速度可以稍快
			keybd_event(13,0,0,0);//按下enter键，进入输入状态
			keybd_event(13,0,2,0); //松开enter键
			Sleep(20); 
			keybd_event(113,0,0,0);//按下f2键
			keybd_event(113,0,2,0);//松开f2键
			Sleep(20);
			keybd_event(40,0,0,0);//按下方向下键
			keybd_event(40,0,2,0);//松开方向下键
			Sleep(20);
		}
		keybd_event(27,0,0,0); //按下esc键，退出输入状态
		keybd_event(27,0,2,0);
		Sleep(40);
		keybd_event(17,0,0,0); //按下ctrl键
		keybd_event(16,0,0,0); //按下shift键
		keybd_event(36,0,0,0); //按下home键
		keybd_event(17,0,2,0); //松开ctrl键
		keybd_event(16,0,2,0); //松开shift键
		keybd_event(36,0,2,0); //松开home键
		Sleep(40);
		keybd_event(9,0,0,0);//按下tab键
		keybd_event(9,0,2,0);//松开tab键
		Sleep(1000);	
	}

}
void input_more_100(int sum2)
{
	int i,j;
	
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 167*65535/1920,89*65535/1080,0,0);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);   //模拟鼠标单击
	Sleep(500);
	keybd_event(17,0,0,0); //按下ctrl键
	keybd_event(16,0,0,0); //按下shift键
	keybd_event(36,0,0,0); //按下home键
	keybd_event(17,0,2,0); //松开ctrl键
	keybd_event(16,0,2,0); //松开shift键
	keybd_event(36,0,2,0); //松开home键
	Sleep(300);
	for(j=0; j<7; j++)
	{
		for(i=0; i<sum2; i++)
		{
			//填充的关键模块，Sleep函数是控制填充速度的关键，项目多，复制程序未响应的概率大，速度稍慢，给复制程序响应时间
			keybd_event(13,0,0,0);//按下enter键，进入输入状态
			keybd_event(13,0,2,0); //松开enter键
			Sleep(120);
			keybd_event(113,0,0,0);//按下f2键
			keybd_event(113,0,2,0);//松开f2键
			Sleep(120);
			keybd_event(40,0,0,0);//按下方向下键
			keybd_event(40,0,2,0);//松开方向下键
			Sleep(120);
		}
		keybd_event(27,0,0,0); //按下esc键，退出输入状态
		keybd_event(27,0,2,0);
		Sleep(40);
		keybd_event(17,0,0,0); //按下ctrl键
		keybd_event(16,0,0,0); //按下shift键
		keybd_event(36,0,0,0); //按下home键
		keybd_event(17,0,2,0); //松开ctrl键
		keybd_event(16,0,2,0); //松开shift键
		keybd_event(36,0,2,0); //松开home键
		Sleep(40);
		keybd_event(9,0,0,0);//按下tab键
		keybd_event(9,0,2,0);//松开tab键
		Sleep(1000);	
	}

}

int main(void)
{
	int i;
	printf("哈哈^-^，来解放双手吧！\n");
	printf("请输入品名总数（输入数字以外的其他字符，将会退出程序）\n");
	while(scanf("%d",&i)==1)
	{
		if(i==999) //一个小彩蛋
		{
			printf("去你的分项，老子不做了！！！\n");
			char str[40];
			time_t t1,t2;
			time(&t1);
			for(int j=1;j<16;j++)
			{
				time(&t2);
				if((t2-t1)==15) //15秒退出
				{
				   break;
				 }
				sprintf(str,"color %x%x",j,16-j);
				system(str);
				Sleep(10);
				if(j==15)
				{
				   j=1;
				}
				
			}
			return 0;
		}
		getchar();
		if(i<=100)
		{	add(i);
			Sleep(1500);  //控制添加项目的等待时间，如果项目太多，add()函数执行完了，但系统没反应过来的话，会造成错误，等待时间应稍长，项目稍的话，等待时间可以稍短
			input_less_100(i);
		}
		else
		{
			add(i);
			Sleep(1000*10);  //控制添加项目的等待时间，如果项目太多，add()函数执行完了，但系统没反应过来的话，会造成错误，等待时间应稍长
			input_more_100(i);
		}
			printf("恭喜你，这票的品名明细填写完成，检查一下，没问题的话去发预配吧！\n");
			printf("下一票分项准备好了的话，输入品名总数继续吧\n");
	}
}	
