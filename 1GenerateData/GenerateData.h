#pragma once
#include "CarInfo.h"
#include "EcsInfo.h"

#include <random>
#include <tchar.h>
#include <windows.h>
using namespace std;


//该解决方案的主要功能：生成实验所用的大数据库并将数据保存到本地


//实验思路：
// (1)测试代码阶段
// 基站数量：10
// 车辆数：30
// (2)实验阶段
// 八车道昼夜车流量：45000~80000；每小时车流量：1666~3333；时间段：04:00am ~ 10:00am
// 早高峰的车辆到达时间遵循正态分布 at~N[T/2,(T/6)^2]，即95%的车辆的到达时间都应集中在[05:00am, 09:00am]
// 为了满足随机性，我们生成一个大的数据集，再随机抽取固定数量数据，进行实验。
// 我们生成 120,000 个车辆数据参与实验，即，生成小中大 车辆任务信息各 40,000 个，供算法调用。
// 道路长度 ： L = 10000
// 时间槽：T = 2160， 1t = 10s
// 车辆速度 v = [100,200]t/s = [10,20]m/s = [36,72]km/h; 
// 基站工作半径(4G标准) S: 1000m, M: 2000m, L: 3000
// 基站数：10
// 车辆数：小型车辆任务 40000， 中型车辆任务 40000， 大型车辆任务 40000	

#define RoadLength 10000	//一维道路长度
#define TTS 2160	//TTS = Total Time Slot
#define RKNum 4	    //资源种类个数the Number of Resources' Kind，分别指代 CPU, GPU, Memory, Disk

#define S_EcsNum 9		//小型基站数
#define M_EcsNum 0		//中型基站数
#define L_EcsNum 1		//大型基站数
#define tEcsNum (S_EcsNum+M_EcsNum+L_EcsNum)  //基站总数

#define S_CarNum 40000			//小型车辆任务数
#define M_CarNum 0			//中型车辆任务数
#define L_CarNum 0			//大型车辆任务数
#define tCarNum (S_CarNum+M_CarNum+L_CarNum)  //车辆任务总数

//gamma是 4 类单位资源（CPU,GPU,Memory,Disk）的单位时间使用成本
const double gamma[4] = { 10, 40, 1, 0.03 };

#define S_ECS_CR 1000 //小型基站覆盖半径
#define M_ECS_CR 2000 //小型基站覆盖半径
#define L_ECS_CR 3000 //小型基站覆盖半径

#define S_ECS_RC_CPU 20			//小型基站CPU容量		40		50		100
#define S_ECS_RC_GPU 10			//小型基站GPU容量		20		50		100
#define S_ECS_RC_MEMORY	40		//小型基站MEMORY容量	80		200		400
#define S_ECS_RC_DISK 250		//小型基站DISK容量		500		1600	3200

#define M_ECS_RC_CPU 40 		//中型基站CPU容量			
#define M_ECS_RC_GPU 20			//中型基站GPU容量
#define M_ECS_RC_MEMORY	80		//中型基站MEMORY容量
#define M_ECS_RC_DISK 500		//中型基站DISK容量

#define L_ECS_RC_CPU 80			//大型基站CPU容量
#define L_ECS_RC_GPU 40			//大型基站GPU容量
#define L_ECS_RC_MEMORY	160		//大型基站MEMORY容量
#define L_ECS_RC_DISK 1000		//大型基站DISK容量

const int L = RoadLength;
const int T = TTS;

//第一部分：基站相关
//1.生成基站信息
void GenerateEcsInfo();
//创造vector容器，用来存放生成的基站信息
vector<EcsInfo> vEcsInfo;
//创造vector容器，分别用来存放不同类型基站的信息
vector<EcsInfo> s_vEcsInfo;	//存放小型基站的容器 s_vEcsInfo = small vEcsInfo
vector<EcsInfo> m_vEcsInfo;	//存放中型基站的容器 m_vEcsInfo = medium vEcsInfo
vector<EcsInfo> l_vEcsInfo;	//存放大型基站的容器 l_vEcsInfo = large vEcsInfo
//封装一个函数用来生成基站位置
int CalcEcsLoc(EcsInfo& ei);
//使用数组arrCA[2]来存放基站覆盖范围
int* CalcEcsCA(EcsInfo& ei);

//第二部分：车辆相关
//1.生成车辆信息
void GenerateCarInfo();
//存放车辆信息的容器：vector<CarInfo>
vector<CarInfo> vCarInfo;
//创造vector容器，分别用来存放不同类型的车辆信息
vector<CarInfo> s_vCarInfo;	//存放小型车辆的容器 s_vCarInfo = small vCarInfo
vector<CarInfo> m_vCarInfo;	//存放中型车辆的容器 m_vCarInfo = medium vCarInfo
vector<CarInfo> l_vCarInfo;	//存放大型车辆的容器 l_vCarInfo = large vCarInfo

vector<int> vCarIL;		//存放车辆初始位置 InitLoc 的容器
vector<int> vCarAT;		//存放车辆到达时间 ArrivalTime 的容器
vector<double>vCarBC;	//存放车辆投标系数 BidCoefficient 的容器 
						//一半车辆的投标系数为[0.25,1],另一半车辆的投标系数为[1,4]
						
//(1)生成车辆初始位置(当前位置)的函数 InitialLocation(CurrentLocation)
void UniformDistributionCarIL();
//(2)生成车辆到达时间的函数
//产生符合 Normal Distribution 的随机数，用以生成车辆到达时间
void NormalDistributionCarAT();
//(3)生成车辆截止时间的函数
int GenerateCarDT(CarInfo& ci);
//(4)生成车辆投标系数的函数
//产生符合 Uniform Distribution 的随机数，用以生成车辆投标系数：
void UniformDistributionCarBC();
//(5)计算投标的函数
double CalcCarBid(CarInfo& ci);
//(6)计算车辆的时变部署约束矩阵，也叫可连接矩阵 Calculate Car's Connectable Matrix
vector<vector<bool>> CalcCarCM(CarInfo& ci);

//第三部分：将生成的数据保存到本地
//1.将基站信息保存到本地供用户查看
void SaveEcsInfo();
////(1)封装一个函数，把基站各个属性保存到不同文件中，供算法调入使用
//void SaveEcsInfoAsInput(vector<EcsInfo>& v, string type, int ecsnum);
//(2)封装一个函数用来输出资源容量向量
void WriteEcsRC(ofstream& ofs, int val);
//2.将车辆信息(除可连接矩阵外)保存到本地
void SaveCarInfo();
//封装一个函数，把车辆的各个属性保存到不同文件中，供算法调入使用
void SaveCarInfoAsInput(vector<CarInfo>& v, string type, int carnum);
//(1)封装一个函数用来输出车辆的任务资源需求向量
void WriteCarTR(ofstream& ofs, int val);