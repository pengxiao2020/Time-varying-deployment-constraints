#pragma once
#include "GlobalDefinition.h"

//�Զ���ṹ�壺��������
struct CarInfo
{
	int id;			//�������
	string type;	//������������
	int InitLoc;	//��ʼλ��
	int v;			//�����ٶ�

	//������������ theta_i
	int at = 0;		//��������ʱ��
	int dt = 0;		//�����ֹʱ��
	int et = 0;		//����ִ��ʱ��
	struct Resource TRD[R];	//������Դ���� Task Resource Demand = s[4] = {s1, s2, s3, s4} = {CPU, GPU, Memory, Disk}
	double mu = 0.00;	//����Ͷ��ϵ��
	double bid = 0.00;	//����Ͷ��
	//��vector�洢���󣬿����ڶ�����������֡�ջ�ռ䲻�㡱�����
	vector<vector<bool>> CM = vector<vector<bool>>(M, vector<bool>(T, false));	//���������Ӿ��� ConnectalbleMatrix
	//int CM[M][T];		//���������Ӿ��� ConnectalbleMatrix
	double pay = 0.00;	//��������

	//����״̬
	int bat = -1;		//�����õ������ʱ�� BeAllocatedTime����ֵΪʱ���
	bool alloc_flag = false;	//��� ���� �Ƿ�õ���վ����
	bool accom_flag = false;	//��� ���� �Ƿ�������� accom = accomplish 
	int ConnectTo = -1;			//��� �������ĸ���վ��ECS[j].id��ʵ�ʽ�������
	double dr = 0.00;		//������������Դ����
	double f = 0.00;		//��������Դ�ܶ�


	//���ظ�ֵ�������ʹ������������Ϣ�����໥����
	//lhs = left hand side, ��ֵ������Ŀ��
	//rhs = right hand side, ��ֵ������Դͷ
	CarInfo& operator= (const CarInfo& rhs)
	{
		this->id = rhs.id;
		this->type = rhs.type;
		this->InitLoc = rhs.InitLoc;
		this->v = rhs.v;

		this->at = rhs.at;
		this->dt = rhs.dt;
		this->et = rhs.et;
		this->TRD->cpu = rhs.TRD->cpu;	//��Դ����ֵ
		this->TRD->gpu = rhs.TRD->gpu;
		this->TRD->memory = rhs.TRD->memory;
		this->TRD->disk = rhs.TRD->disk;
		this->mu = rhs.mu;
		this->bid = rhs.bid;

		for (int j = 0; j < M; j++)
		{
			for (int t = 0; t < T; t++)
			{
				this->CM[j][t] = rhs.CM[j][t];	//�����Ӿ���ֵ
			}
		}
		this->pay = rhs.pay;

		this->bat = rhs.bat;
		this->alloc_flag = rhs.alloc_flag;
		this->accom_flag = rhs.accom_flag;
		this->ConnectTo = rhs.ConnectTo;
		this->dr = rhs.dr;
		this->f = rhs.f;


		return *this;
	}

};
