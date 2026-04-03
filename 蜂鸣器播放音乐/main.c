#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "Key.h"

sbit Buzzer=P2^5;

//宏定义播放速率，方便阅读修改
#define SPEED    1000

//宏定义音符，方便写谱
#define P    0
#define L1   1
#define L1_  2
#define L2   3
#define L2_  4
#define L3   5
#define L4   6
#define L4_  7
#define L5   8
#define L5_  9
#define L6   10
#define L6_  11
#define L7   12
#define M1   13
#define M1_  14
#define M2   15
#define M2_  16
#define M3   17
#define M4   18
#define M4_  19
#define M5   20
#define M5_  21
#define M6   22
#define M6_  23
#define M7   24
#define H1   25
#define H1_  26
#define H2   27
#define H2_  28
#define H3   29
#define H4   30
#define H4_  31
#define H5   32
#define H5_  33
#define H6   34
#define H6_  35
#define H7   36 
#define G1   37
#define G1_  38
#define G2   39
#define G2_  40
#define G3   41
#define G4   42
#define G4_  43
#define G5   44
#define G5_  45
#define G6   46
#define G6_  47
#define G7   48 
#define E1   49
#define E1_  50
#define E2   51
#define E2_  52
#define E3   53
#define E4   54
#define E4_  55
#define E5   56
#define E5_  57
#define E6   58
#define E6_  59
#define E7   60

//音符数组
unsigned int code FreqTable[]={						
		0,61719,61939,62135,62331,62506,62679,62833,62985,63132,63263,63390,63512,
		63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64524,
		64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,
		65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,
		65297,65310,65323,65335,65346,65357,65367,65377,65385,65394,65402,65409
};

//乐谱数组：花海
unsigned char code Music[]={					

	G1,2,G2,2,G3,2,G5,1,G5,9,G3,2,G2,2,G1,2,G2,1,G3,9,G1,2,G2,2,G3,2,G7,1,E1,7,
	E1,2,G7,2,E1,1,G7,3,G5,1,G6,3,G5,6,G1,2,G2,2,G3,2,G5,1,G5,9,G3,2,G2,2,G1,2,G2,1,G1,9,
	G1,2,G2,2,G3,2,G5,1,G1,6,G1,2,G1,2,H7,2,H6,2,H7,2,G1,12,G1,1,G3,3,G3,8,G3,2,G2,2,G1,2,
	G2,4,G3,2+4,P,4,G1,1,G3,2+1,G3,4+4,G4,2,G3,2,G5,4,G1,4+4,P,4,G1,1,G4,2+1,G4,4+4,G4,2,G3,2,
	G1,2,H5,2+2,G3,4+2,P,4,G1,1,G3,2+1,G2,4,G1,1,G3,2+1,G2,4,G1,1,G3,2+1,G2,4+4+4,G1,1,G3,3,G3,4+4,
	G3,2,G2,2,G1,2,G2,4,G5,6,P,4,G1,1,G3,3,G3,8,G4,2,G3,2,G5,4,G1,4+4,P,4,G1,1,G3,3,G4,8,G4,2,G3,2,
	G1,2,G5,4,G3,2,E1,8,P,2,G5,2,G4,2,G3,2,G1,2,G1,2,H7,4,G1,10,G1,2,G2,2,G3,2,G5,1,G5,9,G3,2,G2,2,
	G1,2,G2,1,G3,9,	G1,2,G2,2,G3,2,E1,1,E1,7,E1,2,G7,2,G6,1,G5,3,G6,1,G6,3,G5,6,G1,2,G2,2,G3,2,G5,1,	
	G5,9,G3,2,G2,2,G1,2,G2,1,G1,9,G1,2,G2,2,G3,2,G5,2,G5,2,G4,2,G4,2,G3,2,E1,2,G3,2,G3,4,G2,2,P,4,G1,2,
	G2,2,G3,2,G5,1,G5,9,G3,2,G2,2,G1,2,G2,1,G3,9,G1,2,G2,2,G3,2,E1,1,E1,7,E1,2,G7,2,G6,1,G5,3,G6,1,	
	G6,3,G5,6,G1,2,G2,2,G3,2,G5,1,G5,9,G3,2,G2,2,G1,2,G2,1,G1,9,G1,2,G2,2,G3,2,G5,1,G1,9,G1,2,H7,2,	
	H6,2,H7,1,G1,13,G3,12,
	0xFF
};
	
	
unsigned char FreqSelect,MusicSelect,KeyNum;
	
void main()
{
	Timer0Init();										//定时器初始化
	while(1)
	{	
		//读入键码
		KeyNum=Key();
		
		//播放音乐（音乐结束判断）
		if(Music[MusicSelect]!=0)
	{		
		FreqSelect=Music[MusicSelect];
		MusicSelect++;
		Delay(SPEED/4*Music[MusicSelect]);
		MusicSelect++;
		TR0=0;
		Delay(5);
		TR0=1;
	}
	else{
			TR0=0;
			while(1);
		}
	
		//判断键码
		if(KeyNum==1)									//按下按键1，音乐重头播放	
	{	
		TR0=0;
		FreqSelect=0;
		MusicSelect=0;
		KeyNum=0;
	}
		if(KeyNum==2)									//按下按键2，音乐关闭，关闭后按键1无法响应
	{
		TR0=0;
		while(Key()!=3);								//按下按键3，音乐继续播放
		TR0=1;	
	}
	}
}



void Timer0_Routine() interrupt 1
{
	if(FreqTable[FreqSelect])
{
	TL0 = FreqTable[FreqSelect]%256;	//设置定时初值
	TH0 = FreqTable[FreqSelect]/256;		//设置定时初值
	Buzzer=!Buzzer;
}
}