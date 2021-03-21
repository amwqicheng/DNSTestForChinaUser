#include"MyPing.h"
void MyPing::thread_ping(int num=1)
{
	for (int i = 0; i < num; ++i)
	{
		++current;
		if (current % 3 == 0)
			current = 0;
		objPing.Ping(groups[current][nFlagAddr].c_str(), &reply);
		result[current].nRoundTripTime[current] = reply.m_dwRoundTripTime;
	}
}
void MyPing::format_show(int i)
{
	//name|addr|t1=1secs|t2=2secs|t3=3secs|avg=|max=|min=;
	cout << groups[i][0] << "|";//name
	cout << groups[i][nFlagAddr] << "|";//addr
	for (size_t j = 0; j < 3; j++)
		cout << "T" << j + 1 << "=" << result[i].nRoundTripTime[i] << "|";
	#if ExtraInfo
		cout << "min=" << dns[i].min << "|";
		cout << "max=" << dns[i].max << "|";
		cout << "avg=" << dns[i].avg << "|";
	#endif // ExtraInfo
		cout << endl;

}
MyPing::MyPing(int num,int nFlagAddr)
{
	nFlagAddr = nFlagAddr;
	thread_ping();
}

void ping(int nFlagAddr)
{
	MyPing p(1,nFlagAddr);
}
//每个ping三次
void MyPing::thread_main()
{
	for (int j = 0; j < PING_TIMES; ++j)
		(thread_ping,j);
	//现在可计算该次
	for (auto& num :result[current].nRoundTripTime)
	{
		if (num <= 0 || num >= 460)
		{
			num = 460;
			result[current].bStatus = false;
		}
		else
			result[current].avg += num;
	}
	if (result[current].bStatus)
	{
		result[current].avg /= PING_TIMES;
		shell_sort(result[current].nRoundTripTime, PING_TIMES);
		result[current].min = result[current].nRoundTripTime[0];
		result[current].max = result[current].nRoundTripTime[PING_TIMES - 1];
	}
	else
		result[current].avg = -1;
}

