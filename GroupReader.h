#pragma once
#include"stdafx.h"
#define CHECK_POS(pos) if(pos>(DNS_GROUPS-2)||pos<0)pos=0;

class GroupReader
{
	int m_nFlag;
	int m_nPos;
public:
	
	GroupReader(int pos=0) {
		CHECK_POS(pos);
		GroupReader::m_nPos = pos;
		m_nFlag = 1;
	}
	const std::string getName() {
		return groups[m_nPos][0];
	}
	const std::string getMainAddr() {
		return groups[m_nPos][1];
	}
	const std::string getSubAddr() {
		return groups[m_nPos][2];
	}
	const std::string getAddr() {
		return m_nFlag ==1? groups[m_nPos][1]:groups[m_nPos][2];
	}
	const int getPos() {
		return m_nPos;
	}
	const int getFlag() {
		return m_nFlag;
	}
	void switchAddr() {
		m_nFlag = m_nFlag == 1 ? 2:1;
	}
	void nextPos() {
		++m_nPos;
		if (m_nPos % (DNS_GROUPS-1) == 0)
			GroupReader::m_nPos = 0;
	}
	void setPos(int pos = 0) {
		CHECK_POS(pos);
		GroupReader::m_nPos = pos; m_nPos = pos;
	}
};

