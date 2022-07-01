#pragma once
#include "GlobalDefinition.h"
struct EcsInfo
{
	int id;				//基站编号
	string type;		//基站类型
	int CR;				//覆盖半径
	int loc;			//基站位置
	int CA[2];			//覆盖范围

	Resource RC[R];		//资源容量
};
struct EcsInfo ECS[M];	//该结构体数组存放基站信息



