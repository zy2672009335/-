/* ************************************************************************
 *       Filename:  main.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年07月31日 22时55分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
#include <unistd.h>
#include "start_mplayer.h"
#include "lrc.h"

void clock_show_lrc(char (*lrc_header)[LRC_SIZE],LLIST*list)
{
	clear_screen();//清屏
	cusor_hide();//隐藏光标
	show_lrc_header(lrc_header);//显示歌词前4行
	usleep(1000*1000);//延时,等待mplayer启动
	/*模拟时钟*/
	MYTIME t;
	t.minute =0;
	t.second =0;
	while(1)
	{
		sleep(1);
		t.second++;
		if(t.second >= 60)
		{
			t.second=0;
			t.minute++;
			if(t.minute>= 60)
				t.minute=0;
		}
		/*  通过当前模拟时钟的时间 和链表的每个节点比较时间*/
		cusor_moveto(35,12);//定位光标
		printf("%02d:%02d\n",t.minute,t.second);
		NODE *pcur = search_lrc_by_time(list,t.minute*60+t.second);
		if(pcur!= NULL)
			show_lrc(pcur,list);//显示 歌词
	}
	
}
int main(int argc, char *argv[])
{
	char lrc_header[4][LRC_SIZE]={0};//二维数组保存歌词前4行
	LLIST*list=NULL;//初始化list指针,用来维护链表
    init_linklist(&list);//初始化链表
	analysis_lrc(lrc_header,list,"简单爱.lrc");//解析歌词
	sort_linklist(list);//链表根据时间排序
	//print_linklist_head(list);//遍历链表
	mplayer_play("简单爱.mp3");//播放歌曲
	clock_show_lrc(lrc_header,list);//模拟时钟 显示歌词
	destroy_linklist(list);//销毁链表
	return 0;
}


