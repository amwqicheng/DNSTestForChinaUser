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
	std::cout << "���ڲ���...";
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
		std::cout << "ѡ��ģʽ(";
		ismain ? std::cout << "��" : std::cout << "��";
		std::cout<<"��ַ):\n0 |��С�ӳ�\n1 |ƽ���ӳ�\n2 |����ӳ�\n3 |�л�������ַ\n";
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