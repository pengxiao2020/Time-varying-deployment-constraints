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

//本项目 已注释 非必要显示的测试代码，若要检查代码功能，请自行取消注释

const int count_OVMAP_mod = 10;			// OVMAP_mod 运行次数，设为 10
int ExeNum = 1;							// 第几次运行程序，初始值为 1


// 根据实验要求，每次实验之前都要根据“使用的基站信息”来修改 文件路径 和 文件名
#define EcsInfoFile "../data/2RandomSampling/exp3/EcsInfo_5_0_5/data_EcsInfo_5_0_5.txt"	//基站信息

//根据不用的实验要求，需要修改存放“车辆任务信息”的路径和文件名，如：
//车辆 可连接矩阵 和 其余车辆属性 分开保存（读入的车辆信息小于 20000 条）
//实验一：仅修改小型车辆读取文件路径：/exp1/data_RS_CarInfo_S_xxxxx-
//实验二：要修改“小型车辆读取文件路径 和 大型车辆读取文件路径”或“小型车辆读取文件路径 和 中型车辆读取文件路径”:/exp2/data_CarInfo_5%_9500_0_500/data_RS_CarInfo_S_9500-

#define RS_CarInfoFile_S "../data/2RandomSampling/exp3/EcsInfo_5_0_5/data_RS_CarInfo_S_10000-" + to_string(ExeNum) + ".txt"	//小型车辆任务信息
#define RS_CarInfoFile_S_CM "../data/2RandomSampling/exp3/EcsInfo_5_0_5/data_RS_Car_CM_S_10000-" + to_string(ExeNum) + ".txt"	//小型车辆可连接矩阵(时变部署约束矩阵)

#define RS_CarInfoFile_M "../data/2RandomSampling/exp1/data_RS_CarInfo_M_10000-" + to_string(ExeNum) + ".txt"	//中型车辆任务信息
#define RS_CarInfoFile_M_CM "../data/2RandomSampling/exp1/data_RS_Car_CM_M_10000-" + to_string(ExeNum) + ".txt"	//中型车辆可连接矩阵(时变部署约束矩阵)

#define RS_CarInfoFile_L "../data/2RandomSampling/exp2/data_CarInfo_5%_9500_0_500/data_RS_CarInfo_L_500-" + to_string(ExeNum) + ".txt"	//大型车辆任务信息
#define RS_CarInfoFile_L_CM "../data/2RandomSampling/exp2/data_CarInfo_5%_9500_0_500/data_RS_Car_CM_L_500-" + to_string(ExeNum) + ".txt"	//大型车辆可连接矩阵(时变部署约束矩阵)


#define RoadLength 10000	//道路长度
#define TTS 2160		//总时间槽 TTS = Total Time Slot

#define RESOURCE 4		//共有4种资源：CPU,GPU,Memory,Disk

#define S_EcsNum 5		//读入的小型基站数
#define M_EcsNum 0		//读入的中型基站数
#define L_EcsNum 5		//读入的大型基站数
#define tEcsNum (S_EcsNum+M_EcsNum+L_EcsNum)  //基站总数

//根据读入的文件名不同，每次运行需要设置不同的数字（车辆任务数）
//实验二读入的中型、大型车辆任务信息比例为：0%, 5%, 10%, 20%, 50% 
#define S_CarNum 10000		//读入的小型车辆任务数 
#define M_CarNum 0			//读入的中型车辆任务数
#define L_CarNum 0		//读入的大型车辆任务数
#define tCarNum (S_CarNum+M_CarNum+L_CarNum)  //车辆任务总数

const int T = TTS;		//时间槽
const int M = tEcsNum;	//基站总数
const int N = tCarNum;	//车辆任务总数
const int R = RESOURCE;	//RKNum = Resource Kind Number 资源种类数

const double gamma[R] = { 10, 40, 1, 0.03 };	//gamma是 4 类单位资源（CPU,GPU,Memory,Disk）的单位时间使用成本

const double epsilon = 0.000001;	//定义一个较小的数字，OVMAP_mod_PAY 确定付款使用

double TotalSocialWelfare = 0.00;	//截止至[1,t], 求解的社会福利
double cts_SocialWelfare = 0.00;	//当前时间槽求得的社会福利 cts = current tims slot

double RunTime = 0.00;					//OVMAP_mod 算法的运行时间
double PreWork_RunTime = 0.00;			//1. OVMAP_mod 算法准备工作所花的时间
double ReturnResource_RunTime = 0.00;	//1.1 完成任务的 Cars 归还 ECS 资源所花的时间
double DelOvertimeTask_RunTime = 0.00;	//1.2 删除 UnAllocatedCar 中的过期车辆任务所花的时间
double AddArrivedCar_RunTime = 0.00;	//1.3 将新到达的车辆任务添加进集合 UnAllocatedCar 所花的时间 

double ALLOC_RunTime = 0.00;			//2.OVMAP_mod_ALLOC 分配函数运行时间

double PAY_RunTime = 0.00;				//3.OVMAP_mod_PAY 支付函数运行时间

//公用自定义结构体：资源
//可用作 基站资源容量，车辆任务资源请求
struct Resource
{
	//资源向量中包含四种资源
	int cpu = 0;	//资源:cpu
	int gpu = 0;	//资源:gpu
	int memory = 0;	//资源:memory
	int disk = 0;	//资源:disk
};

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

double NPR_t_Car = 0.00;	//正确付款的车辆比例 NPR = Normal Pay Ratio
double NPR_s_Car = 0.00;	//正确付款的小型车辆比例
double NPR_m_Car = 0.00;	//正确付款的中型车辆比例
double NPR_l_Car = 0.00;	//正确付款的大型车辆比例