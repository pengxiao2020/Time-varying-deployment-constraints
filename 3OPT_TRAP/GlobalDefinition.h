#pragma once
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>		//内建函数对象
#include <numeric>
using namespace std;

#include <ilcplex/ilocplex.h>

//本项目 已注释 非必要显示的测试代码，若要检查代码功能，请自行取消注释

// /../表示：当前目录上一层

const int count_OPT_TRAP = 10;		// OPT_TRAP 运行次数，设为 10
int ExeNum = 1;						// 第几次运行程序，初始值为 1
int count_TRAP_IP = 1;				// 记录最优分配算法 TRAP-IP() 被调用的次数，初始值为 1

// 根据实验要求，每次运行代码之前都要根据“使用的基站信息”来修改 文件路径 和 文件名，如
// ../data/2RandomSampling/exp1/data_RS_CarInfo_S_100-
// ../data/2RandomSampling/exp1/data_RS_CarInfo_S_500-
#define EcsInfoFile "../data/2RandomSampling/exp1/data_EcsInfo_10_0_0.txt"	//基站信息	

// 根据不用的实验要求，每次运行代码之前都要修改存放“车辆任务信息”的路径和文件名，如：
//车辆 可连接矩阵 和 其余车辆属性 分开保存
#define RS_CarInfoFile_S "../data/2RandomSampling/exp1/data_RS_CarInfo_S_500-" + to_string(ExeNum) +".txt"		//小型车辆任务信息
#define RS_CarInfoFile_S_CM "../data/2RandomSampling/exp1/data_RS_Car_CM_S_500-" + to_string(ExeNum) +".txt"		//小型车辆可连接矩阵

#define RS_CarInfoFile_M "../data/2RandomSampling/exp1/data_RS_CarInfo_M_500-" + to_string(ExeNum) +".txt"		//中型车辆任务信息
#define RS_CarInfoFile_M_CM "../data/2RandomSampling/exp1/data_RS_Car_CM_M_500-" + to_string(ExeNum) +".txt"		//中型车辆可连接矩阵

#define RS_CarInfoFile_L "../data/2RandomSampling/exp1/data_RS_CarInfo_L_500-" + to_string(ExeNum) +".txt"		//大型车辆任务信息
#define RS_CarInfoFile_L_CM "../data/2RandomSampling/exp1/data_RS_Car_CM_L_500-" + to_string(ExeNum) +".txt"		//大型车辆可连接矩阵

#define RoadLength 10000	//道路长度
#define TTS 2160		//总时间槽 TTS = Total Time Slot

#define RESOURCE 4		//共有4种资源：CPU,GPU,Memory,Disk

#define S_EcsNum 10		//读入的小型基站数
#define M_EcsNum 0		//读入的中型基站数
#define L_EcsNum 0		//读入的大型基站数
#define tEcsNum (S_EcsNum+M_EcsNum+L_EcsNum)  //基站总数

//根据读入的文件名不同，每次运行需要设置不同的数字（车辆任务数）
#define S_CarNum 500     //读入的小型车辆任务数 
#define M_CarNum 0     //读入的中型车辆任务数
#define L_CarNum 0     //读入的大型车辆任务数
#define tCarNum (S_CarNum+M_CarNum+L_CarNum)  //车辆任务总数

const int T = TTS;		//时间槽
const int M = tEcsNum;	//读入的基站总数
const int N = tCarNum;	//读入的车辆任务总数
const int R = RESOURCE;	//RKNum = Resource Kind Number 资源种类数

//公用自定义结构体：资源
//可用作 基站资源容量，车辆任务资源请求
struct Resource
{
	//资源向量中包含四种资源
	int cpu = 0;	//资源 : cpu
	int gpu = 0;	//资源 : gpu
	int memory = 0; //资源 : memory
	int disk = 0;	//资源 : disk
};

string Status;					//求得的解的性质：Optimal表示最优解
double SocialWelfare = 0.00;	//求解的最大社会福利
double RunTime = 0.00;			//TRAP-IP算法的运行时间

int AllocResult[N];			//存放分配结果的数组
double Payment[N];			//存放车辆付款的数组

//定义一个三维数组cnt[i][j][t]，存放整个系统的连接结果 cnt = connectivity
//cnt[i][j][t] = cplex.getValue(x[i][j][t]);
int cnt[N][M][T];
//定义一个三维数组tmp_cnt[i][j][t]，暂存整个系统的连接结果，用作备份恢复
int tmp_cnt[N][M][T];

struct Resource UsedResource;	//整个系统使用的资源
struct Resource TotalResource;	//整个系统的资源总量

double UR_t_cpu = 0.00;			//总CPU利用率
double UR_t_gpu = 0.00;			//总GPU利用率
double UR_t_memory = 0.00;		//总Memory利用率
double UR_t_disk = 0.00;		//总Disk利用率

double SR_t_Car = 0.00;		//服务车辆比例
double SR_s_Car = 0.00;		//小型车辆任务服务比例
double SR_m_Car = 0.00;		//小型车辆任务服务比例
double SR_l_Car = 0.00;		//小型车辆任务服务比例