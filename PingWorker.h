#pragma once
#include"stdafx.h"
#include"ping.h"
#include"ResultHandler.h"
#include"GroupReader.h"
//ping���ν��������avg. max. min
class PingWorker
{
	PingReply reply;//ÿ��ping���
	CPing objPing;//ping����

	std::vector<DWORD>m_vResult;//�洢����dns���
	unsigned int m_nTimes;
	ResultHandler* m_pHandler;//���������
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

