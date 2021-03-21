#pragma once
#include"stdafx.h"
#include"ping.h"
#include"ResultHandler.h"
#include"GroupReader.h"
//ping三次结果并计算avg. max. min
class PingWorker
{
	PingReply reply;//每次ping结果
	CPing objPing;//ping对象

	std::vector<DWORD>m_vResult;//存储本次dns结果
	unsigned int m_nTimes;
	ResultHandler* m_pHandler;//结果管理器
	GroupReader*m_pReader;
	void run();
	void calc();
public:
	PingWorker(GroupReader&reader,ResultHandler& handler,int times = 3) {
		m_pReader = &reader;
		m_nTimes = times;
		m_pHandler = &handler;
	}
	void start(){
		if (m_nTimes < 3|| m_nTimes >10)
			m_nTimes = 3;
		run();
		calc();
	}
};

