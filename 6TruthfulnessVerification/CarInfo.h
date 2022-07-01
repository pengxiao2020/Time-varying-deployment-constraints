#pragma once
#include "GlobalDefinition.h"

//自定义结构体：车辆任务
struct CarInfo
{
	int id;			//车辆编号
	string type;	//车辆任务类型
	int InitLoc;	//初始位置
	int v;			//车辆速度

	//车辆任务类型 theta_i
	int at = 0;		//到达时间
	int dt = 0;		//任务截止时间
	int et = 0;		//任务执行时间
	struct Resource TRD[R];	//任务资源需求 TaskResourceDemand = s[4] = {s1, s2, s3, s4} = {CPU, GPU, Memory, Disk}
	double bid = 0.00;	//投标
	double mu = 0.00;	//投标系数
	//用vector存储矩阵，开辟在堆区，避免出现“栈空间不足”的情况
	vector<vector<bool>> CM = vector<vector<bool>>(M, vector<bool>(T, false));	//车辆可连接矩阵 ConnectalbleMatrix
	//int CM[M][T];		//车辆可连接矩阵 ConnectalbleMatrix

	double pay = 0.00;	//车辆付款

	//车辆状态
	int bat = -1;		//车辆得到分配的时间 BeAllocatedTime，赋值为时间槽
	bool alloc_flag = false;	//标记 车辆 是否得到基站分配
	bool accom_flag = false;	//标记 车辆 是否完成任务 accom = accomplish 
	int ConnectTo = -1;			//标记 车辆与哪个基站（ECS[j].id）实际建立连接
	double dr = 0.00;		//车辆的主导资源比例
	double f = 0.00;		//车辆的资源密度


	//重载赋值运算符，使得两个车辆信息可以相互传递
	//lhs = left hand side, 赋值操作的目标
	//rhs = right hand side, 赋值操作的源头
	CarInfo& operator= (const CarInfo& rhs)
	{
		this->id = rhs.id;
		this->type = rhs.type;
		this->InitLoc = rhs.InitLoc;
		this->v = rhs.v;

		this->at = rhs.at;
		this->dt = rhs.dt;
		this->et = rhs.et;
		this->TRD->cpu = rhs.TRD->cpu;
		this->TRD->gpu = rhs.TRD->gpu;
		this->TRD->memory = rhs.TRD->memory;
		this->TRD->disk = rhs.TRD->disk;
		this->bid = rhs.bid;
		this->mu = rhs.mu;

		for (int j = 0; j < M; j++)
		{
			for (int t = 0; t < T; t++)
			{
				this->CM[j][t] = rhs.CM[j][t];	//可连接矩阵赋值
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
