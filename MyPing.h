#pragma once
#include"stdafx.h"
#include"ping.h"
#include"Sort.h"
#include<vector>
#ifndef MYPING_H
#define MYPING_H
using namespace std;
#define PING_TIMES 3 //ÿ��ping����
#define PING_GROUP 9 //ping������
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
	
	PingReply reply;//ÿ��ping���
	CPing objPing;//ping����
	int nFlagAddr;
	static int current;
	
	
	void format_show(int i);//���
	void thread_ping(int);//ping
	void thread_main();//����ƽ��ֵ...
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


