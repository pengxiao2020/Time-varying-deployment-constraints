#pragma once
#include "GlobalDefinition.h"

//�Զ���ṹ�壺��������
struct CarInfo
{
	int id;			//�������
	string type;	//������������
	int InitLoc;	//����λ��
	int v;			//�����ٶ�

	//������������ theta_i
	int at = 0;		//����ʱ��
	int dt = 0;		//�����ֹʱ��
	int et = 0;		//����ִ��ʱ��
	struct Resource TRD[R];	//������Դ���� TaskResourceDemand = TRD[4] = {s1, s2, s3, s4} = {CPU, GPU, Memory, Disk}
	double mu = 0.00;	//Ͷ��ϵ��
	double bid = 0.00;	//Ͷ��
	//��vector�洢���󣬿����ڶ�����������֡�ջ�ռ䲻�㡱�����
	vector<vector<bool>> CM = vector<vector<bool>>(M, vector<bool>(T, false));	//���������Ӿ��� ConnectalbleMatrix
	//int CM[M][T];		//ʱ�䲿��Լ������ �����Ӿ��� ConnectalbleMatrix 
	bool beAllocated = false;	//��� ���� i �Ƿ�õ�����
	double pay = 0.00;	//��������

	///���ظ�ֵ�������ʹ������������Ϣ�����໥����
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
		this->beAllocated = rhs.beAllocated;	//�����ʶ��ֵ
		this->pay = rhs.pay;

		return *this;
	}

};

struct CarInfo Car[N];	//�ýṹ�������ų���������Ϣ
CarInfo* carP = Car;	//carP ָ�� Car[N]

//����һ�������ṹ�壬�ݴ汻�߳��ĳ�����Ϣ
struct CarInfo RemovedCar;



