#pragma once
#include "GlobalDefinition.h"
#include "CarInfo.h"
struct EcsInfo
{
	int id;				//基站编号
	string type;		//基站类型
	int CR;				//覆盖半径
	int loc;			//基站位置
	int CA[2];			//覆盖范围

	Resource RC[R];		//资源容量

	int InDegree = 0;	//基站入度
	
	vector<CarInfo> AbleConnectToECS;	//存放：能够与 ECS j 建立连接的车辆 

	EcsInfo& operator= (const EcsInfo& rhs)
	{
		this->id = rhs.id;
		this->type = rhs.type;
		this->CR = rhs.CR;
		this->loc = rhs.loc;
		this->CA[0] = rhs.CA[0];
		this->CA[1] = rhs.CA[1];

		this->RC->cpu = rhs.RC->cpu;
		this->RC->gpu = rhs.RC->gpu;
		this->RC->memory = rhs.RC->memory;
		this->RC->disk = rhs.RC->disk;

		this->InDegree = rhs.InDegree;

		return *this;
	}
};