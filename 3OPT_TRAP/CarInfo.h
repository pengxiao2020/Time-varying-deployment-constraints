#pragma once
#include "GlobalDefinition.h"

//自定义结构体：车辆任务
struct CarInfo
{
	int id;			//车辆编号
	string type;	//车辆任务类型
	int InitLoc;	//生成位置
	int v;			//车辆速度

	//车辆任务请求 theta_i
	int at = 0;		//到达时间
	int dt = 0;		//任务截止时间
	int et = 0;		//任务执行时间
	struct Resource TRD[R];	//任务资源需求 TaskResourceDemand = TRD[4] = {s1, s2, s3, s4} = {CPU, GPU, Memory, Disk}
	double mu = 0.00;	//投标系数
	double bid = 0.00;	//投标
	//用vector存储矩阵，开辟在堆区，避免出现“栈空间不足”的情况
	vector<vector<bool>> CM = vector<vector<bool>>(M, vector<bool>(T, false));	//车辆可连接矩阵 ConnectalbleMatrix
	//int CM[M][T];		//时变部署约束矩阵 可连接矩阵 ConnectalbleMatrix 
	bool beAllocated = false;	//标记 车辆 i 是否得到分配
	double pay = 0.00;	//车辆付款

	///重载赋值运算符，使得两个车辆信息可以相互传递
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

		this->TRD->cpu = rhs.TRD->cpu;	//资源需求赋值
		this->TRD->gpu = rhs.TRD->gpu;
		this->TRD->memory = rhs.TRD->memory;
		this->TRD->disk = rhs.TRD->disk;

		this->mu = rhs.mu;
		this->bid = rhs.bid;

		for (int j = 0; j < M; j++)
		{
			for (int t = 0; t < T; t++)
			{
				this->CM[j][t] = rhs.CM[j][t];	//可连接矩阵赋值
			}
		}
		this->beAllocated = rhs.beAllocated;	//分配标识赋值
		this->pay = rhs.pay;

		return *this;
	}

};

struct CarInfo Car[N];	//该结构体数组存放车辆任务信息
CarInfo* carP = Car;	//carP 指向 Car[N]

//定义一个车辆结构体，暂存被踢出的车辆信息
struct CarInfo RemovedCar;



