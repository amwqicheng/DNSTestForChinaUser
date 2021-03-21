#pragma once
#include"PingWorker.h"
using namespace std;
GroupReader  reader;
ResultHandler  handler(reader);
PingWorker worker(reader, handler);
void ping() 
{
	//ping main
	worker.start();
	reader.switchAddr();
	worker.start();
	reader.switchAddr();
	reader.nextPos();
}
void not_thread() {
	int num = 0;
	while (num < (DNS_GROUPS - 1))
	{
		ping();
		num++;
	}
}
int main() 
{
	std::cout << "正在测试...";
	not_thread();
	int menu[] = 
	{ 
		MIN_DNS_INDEX,
		AVG_DNS_INDEX,
		MAX_DNS_INDEX,
	};
	int in;
	bool ismain = true;
	while (1)
	{
		system("cls");
		std::cout << "选择模式(";
		ismain ? std::cout << "主" : std::cout << "副";
		std::cout<<"地址):\n0 |最小延迟\n1 |平均延迟\n2 |最差延迟\n3 |切换主副地址\n";
		cin >> in;
		if (in == 4)return 0;
		if (in == 3) { ismain= ismain?false:true; continue; }
		for (auto& num : menu)
			if (num == in)
				handler.getFastestDNS(in,ismain);
		system("pause");
	}
	return 0;
}