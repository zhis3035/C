#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void add(int sum1) //�����Ŀ
{
	int i;
	Sleep(2*1000);
	for(i=0; i<sum1;i++)
	{
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE,159*65535/1920,43*65535/1080,0,0);    //����꽹���Ƶ�����������ť����
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
		mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);   //ģ����굥��
	}
}

void input_less_100(int sum2)
{
	int i,j;
	
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 167*65535/1920,89*65535/1080,0,0);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);   //ģ����굥��
	Sleep(500);
	keybd_event(17,0,0,0); //����ctrl��
	keybd_event(16,0,0,0); //����shift��
	keybd_event(36,0,0,0); //����home��
	keybd_event(17,0,2,0); //�ɿ�ctrl��
	keybd_event(16,0,2,0); //�ɿ�shift��
	keybd_event(36,0,2,0); //�ɿ�home��
	Sleep(300);
	for(j=0; j<7; j++)
	{
		for(i=0; i<sum2; i++)
		{
			//���Ĺؼ�ģ�飬Sleep�����ǿ�������ٶȵĹؼ�����Ŀ�٣����Ƴ���δ��Ӧ�ĸ���С���ٶȿ����Կ�
			keybd_event(13,0,0,0);//����enter������������״̬
			keybd_event(13,0,2,0); //�ɿ�enter��
			Sleep(20); 
			keybd_event(113,0,0,0);//����f2��
			keybd_event(113,0,2,0);//�ɿ�f2��
			Sleep(20);
			keybd_event(40,0,0,0);//���·����¼�
			keybd_event(40,0,2,0);//�ɿ������¼�
			Sleep(20);
		}
		keybd_event(27,0,0,0); //����esc�����˳�����״̬
		keybd_event(27,0,2,0);
		Sleep(40);
		keybd_event(17,0,0,0); //����ctrl��
		keybd_event(16,0,0,0); //����shift��
		keybd_event(36,0,0,0); //����home��
		keybd_event(17,0,2,0); //�ɿ�ctrl��
		keybd_event(16,0,2,0); //�ɿ�shift��
		keybd_event(36,0,2,0); //�ɿ�home��
		Sleep(40);
		keybd_event(9,0,0,0);//����tab��
		keybd_event(9,0,2,0);//�ɿ�tab��
		Sleep(1000);	
	}

}
void input_more_100(int sum2)
{
	int i,j;
	
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 167*65535/1920,89*65535/1080,0,0);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);   //ģ����굥��
	Sleep(500);
	keybd_event(17,0,0,0); //����ctrl��
	keybd_event(16,0,0,0); //����shift��
	keybd_event(36,0,0,0); //����home��
	keybd_event(17,0,2,0); //�ɿ�ctrl��
	keybd_event(16,0,2,0); //�ɿ�shift��
	keybd_event(36,0,2,0); //�ɿ�home��
	Sleep(300);
	for(j=0; j<7; j++)
	{
		for(i=0; i<sum2; i++)
		{
			//���Ĺؼ�ģ�飬Sleep�����ǿ�������ٶȵĹؼ�����Ŀ�࣬���Ƴ���δ��Ӧ�ĸ��ʴ��ٶ������������Ƴ�����Ӧʱ��
			keybd_event(13,0,0,0);//����enter������������״̬
			keybd_event(13,0,2,0); //�ɿ�enter��
			Sleep(120);
			keybd_event(113,0,0,0);//����f2��
			keybd_event(113,0,2,0);//�ɿ�f2��
			Sleep(120);
			keybd_event(40,0,0,0);//���·����¼�
			keybd_event(40,0,2,0);//�ɿ������¼�
			Sleep(120);
		}
		keybd_event(27,0,0,0); //����esc�����˳�����״̬
		keybd_event(27,0,2,0);
		Sleep(40);
		keybd_event(17,0,0,0); //����ctrl��
		keybd_event(16,0,0,0); //����shift��
		keybd_event(36,0,0,0); //����home��
		keybd_event(17,0,2,0); //�ɿ�ctrl��
		keybd_event(16,0,2,0); //�ɿ�shift��
		keybd_event(36,0,2,0); //�ɿ�home��
		Sleep(40);
		keybd_event(9,0,0,0);//����tab��
		keybd_event(9,0,2,0);//�ɿ�tab��
		Sleep(1000);	
	}

}

int main(void)
{
	int i;
	printf("����^-^�������˫�ְɣ�\n");
	printf("������Ʒ��������������������������ַ��������˳�����\n");
	while(scanf("%d",&i)==1)
	{
		if(i==999) //һ��С�ʵ�
		{
			printf("ȥ��ķ�����Ӳ����ˣ�����\n");
			char str[40];
			time_t t1,t2;
			time(&t1);
			for(int j=1;j<16;j++)
			{
				time(&t2);
				if((t2-t1)==15) //15���˳�
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
			Sleep(1500);  //���������Ŀ�ĵȴ�ʱ�䣬�����Ŀ̫�࣬add()����ִ�����ˣ���ϵͳû��Ӧ�����Ļ�������ɴ��󣬵ȴ�ʱ��Ӧ�Գ�����Ŀ�ԵĻ����ȴ�ʱ������Զ�
			input_less_100(i);
		}
		else
		{
			add(i);
			Sleep(1000*10);  //���������Ŀ�ĵȴ�ʱ�䣬�����Ŀ̫�࣬add()����ִ�����ˣ���ϵͳû��Ӧ�����Ļ�������ɴ��󣬵ȴ�ʱ��Ӧ�Գ�
			input_more_100(i);
		}
			printf("��ϲ�㣬��Ʊ��Ʒ����ϸ��д��ɣ����һ�£�û����Ļ�ȥ��Ԥ��ɣ�\n");
			printf("��һƱ����׼�����˵Ļ�������Ʒ������������\n");
	}
}	
