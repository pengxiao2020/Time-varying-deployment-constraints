#pragma once

#include "GlobalDefinition.h"
#include "CarInfo.h"
struct EcsInfo
{
	int id;				//��վ���
	string type;		//��վ����
	int CR;				//���ǰ뾶
	int loc;			//��վλ��
	int CA[2];			//���Ƿ�Χ

	Resource RC[R];		//��Դ����

	int InDegree = 0;	//��վ���

	vector<CarInfo> AbleConnectToECS;	//��ţ��ܹ��� ECS j �������ӵĳ��� 

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