#include "PingWorker.h"

void PingWorker::run()
{

	int size = m_nTimes;
	while (size)
	{
		objPing.Ping(m_pReader->getAddr().c_str(), &reply);
		m_vResult.push_back(reply.m_dwRoundTripTime);
		--size;
	}
	
}

void PingWorker::calc()
{
	
	sort(m_vResult.begin(), m_vResult.end());//从小到大排序
	DWORD count = 0;
	bool status = true;
	for (auto& num : m_vResult)
	{
		if (num < 0 || num>DNS_TIMEOUT)
			status = false;
		else
			count += num;
	}

	if (status)
	{
		count /= m_nTimes;
		
	}
	m_pHandler->read(
		(DWORD)m_vResult[0],
		count,
		(DWORD)m_vResult[m_vResult.size() - 1]);
	m_vResult.clear();
}

