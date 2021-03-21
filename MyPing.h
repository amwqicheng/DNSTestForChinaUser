#pragma once
#include"stdafx.h"
#include"ping.h"
#include"Sort.h"
#include<vector>
#ifndef MYPING_H
#define MYPING_H
using namespace std;
#define PING_TIMES 3 //每次ping次数
#define PING_GROUP 9 //ping的总数
#define ExtraInfo false
int MyPing::current =-1;
dnsResult result[PING_GROUP];
struct dnsResult {
	int nRoundTripTime[PING_TIMES] = { 0 },
		max = 0,
		min = 0,
		avg = 0;
	bool bStatus = true;
};

class 

{
private:
	
	PingReply reply;//每次ping结果
	CPing objPing;//ping对象
	int nFlagAddr;
	static int current;
	
	
	void format_show(int i);//输出
	void thread_ping(int);//ping
	void thread_main();//计算平均值...
	friend void ping(int);
public:
	MyPing(int ,int );
	
	friend class thread;
	void show() {
		for (size_t i = 0; i < 9; i++)
			format_show(i);
	}
};

#endif // !MYPING_H


