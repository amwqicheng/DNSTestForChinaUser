#pragma once
#include "stdafx.h"
#define DNS_TIMEOUT 460
#define MIN_DNS_INDEX 0
#define AVG_DNS_INDEX 1
#define MAX_DNS_INDEX 2
#include"GroupReader.h"
#include<iterator>
#include <iomanip>
#include<vector>
#include<algorithm>
typedef unsigned long DWORD;
#define ADDR(m_nFlag) DWORD*addr=result.mainaddr;if(m_nFlag==2)addr=result.subaddr
#define ExtraInfo 1
#define DNS_SHOW_NUM 3 
#define Index(pointer,index,flag) \
		if(dns.mainaddr[index]==*(pointer+flag)||\
		dns.subaddr[index]==*(pointer+flag))\
		*(pointer+flag) = i;
struct DNS_RESULT
{
	DWORD mainaddr[3] = { 0,0,0 },
		subaddr[3] = { 0,0,0 };
	
	std::string dnsName;
};
class ResultHandler
{
	std::vector<DNS_RESULT>v;//存储所有结果
	DNS_RESULT  result;
	GroupReader* m_pReader;
	int handle_num = 0;//每次处理一组dns
	/*
	* 0 min
	* 1 avg
	* 2 max
	*/
	public:
		void read(DWORD min, DWORD avg, DWORD max) {
		
			ADDR(m_pReader->getFlag());
			addr[0] = (min<0||min>DNS_TIMEOUT)? DNS_TIMEOUT:min;//最快
			addr[1] = (avg<0 || avg>DNS_TIMEOUT) ? DNS_TIMEOUT : avg;//平均
			addr[2] = (max<0 || max>DNS_TIMEOUT) ? DNS_TIMEOUT : max;//最慢
			store();
		};
		void store() {
			handle_num++;
			if (handle_num && handle_num % 2 == 0)
			{
				
				handle_num = 0;
				result.dnsName = m_pReader->getName();
				v.push_back(result);
				//show(v.end()-1, v.end());
			}
		};
		ResultHandler(GroupReader& reader) {
			m_pReader = &reader;
		};
		void show(std::vector<DNS_RESULT>::iterator iter,
			std::vector<DNS_RESULT>::iterator end,
			int* arr = NULL) {
			using std::cout;
			int pos = m_pReader->getPos();
			if(NULL!=arr)
			m_pReader->setPos(*(arr)++);
			else
			{
				static int iPos = 0;
				CHECK_POS(iPos);
				m_pReader->setPos(iPos);
				++iPos;
				
			}
			for (; iter!=end;++iter)
			{
				
				cout << m_pReader->getName()
					<< std::endl
					<< "|主地址="
					<<std::left
					<< std::setw(16)
					<<std::setfill(' ')
					<<m_pReader->getMainAddr()
					<< "|最小=" << iter->mainaddr[0]
					<< "|平均=" << iter->mainaddr[1]
					<< "|最大=" << iter->mainaddr[2]
					<< std::endl
					<< "|副地址="
					<< std::left
					<< std::setw(16)
					<< std::setfill(' ')
					<< m_pReader->getSubAddr()
					<< "|最小=" << iter->mainaddr[0]
					<< "|平均=" << iter->mainaddr[1]
					<< "|最大=" << iter->mainaddr[2]
					<< std::endl;
				m_pReader->nextPos();
				
			}
			m_pReader->setPos(pos);
		}
		//获取前n个dns的下标
		void getIndex(int *&arr, std::vector<DNS_RESULT>list,int nFlag) {
			int i = 0;
			for (auto& dns : list)
				for(int i=0;i< DNS_SHOW_NUM;++i)
					Index(arr,nFlag, i);
		}
		//显示某条信息
		void showInfo(std::vector<DNS_RESULT>::iterator & iter,int nFlag=0) {
			using std::cout;
			if (nFlag == 0)
				cout << "最快|";
			if (nFlag == 1)
				cout << "平均|";
			if (nFlag == 2)
				cout << "最慢|";
			cout << std::endl;
			cout << (*iter).dnsName << "|";
		
		}
		void shell_sort(int arr[], int len) {
			int gap, i, j;
			int temp;
			for (gap = len >> 1; gap > 0; gap >>= 1)
				for (i = gap; i < len; i++) {
					temp = arr[i];
					for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
						arr[j + gap] = arr[j];
					arr[j + gap] = temp;
				}
		}
		void output(int arr[],int showFlag) {
		
			shell_sort(arr,DNS_SHOW_NUM);
			std::vector<DNS_RESULT>::iterator iter = v.begin();
			for (int n=0; n < DNS_SHOW_NUM;++n)
			{
				iter = v.begin()+arr[n];
				showInfo(iter, showFlag);
			}
		}
		
		//提取数组前n个
		void collect(int*& arr,std::vector<DWORD> &dnsList) {
			std::vector<DWORD>::iterator iter = dnsList.begin();
			for (int i = 0; i < DNS_SHOW_NUM; ++i)
				*(arr+i)= *(iter)++;
		}
		//待优化
		void getFastestDNS(int nFlag,bool isMainaddr=true)
		{
			int i, j,len=DNS_GROUPS-1; 
			int pos[DNS_GROUPS - 1];
			for(int i=0;i< DNS_GROUPS - 1;++i)
				pos[i]=i;
			DNS_RESULT temp;
			for (i = 0; i < len - 1; i++)
			{
				int min = i;
				for (j = i + 1; j < len; j++)
				{
					
					if (isMainaddr&&v[j].mainaddr[nFlag] < v[min].mainaddr[nFlag])
						min = j;
					if (!isMainaddr && v[j].subaddr[nFlag] < v[min].subaddr[nFlag])
						min = j;
				} //紀錄最小值
				
				std::swap(v[min],v[i]);    //做交換
				std::swap(pos[min], pos[i]);
			}
			show(v.begin(),v.end(),pos);
		}
};

