#pragma once
#include "GlobalDefinition.h"
struct EcsInfo
{
	int id;				//��վ���
	string type;		//��վ����
	int CR;				//���ǰ뾶
	int loc;			//��վλ��
	int CA[2];			//���Ƿ�Χ

	Resource RC[R];		//��Դ����
};
struct EcsInfo ECS[M];	//�ýṹ�������Ż�վ��Ϣ



