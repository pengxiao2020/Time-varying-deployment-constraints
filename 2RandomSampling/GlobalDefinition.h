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

// 该解决方案的主要功能：
// (1)读入 1GenerateData 生成的大数据库
// (2)随机抽取五组车辆数据，每组车辆数据个数为 100, 500, 5000, 10000, 20000。且每组数据要抽取10次。
// (3)将随机抽取的数据保存到本地

/* 举例：假设现在进行实验一，我们要考察 小型车辆数为100时，算法获得的社会福利、执行时间、服务车辆数和资源利用率。
 * 1.我们要读入大数据库CarInfo_40000_40000_40000中的数据，即分别读入40000条小型车辆数据、40000条中型车辆数据和40000条大型车辆数据。
 * 2.从40000条小型车辆数据随机抽取 100 条小型车辆数据，并且要随机抽取10次。中型车辆数据和大型车辆数据亦然。
 * 3.那么，小型车辆数为100时，系统获得的社会福利 = （10组 100条小型车辆数据获得的社会福利 之和） / 10。
 */

const int SamplingNum = 10;	//随机抽取总次数,固定为10次
int ExeNum = 1;				//当前抽取次数,初始值为1

//读入文件定义
#define EcsInfoFile "../data/1GenerateData/exp3/EcsInfo_9_0_1/data_EcsInfo_9_0_1.txt"
//车辆 可连接矩阵 和 其余车辆属性 分开保存
#define CarInfoFile_S "../data/1GenerateData/exp3/EcsInfo_9_0_1/data_CarInfo_S_40000.txt"		//小型车辆任务信息
#define CarInfoFile_S_CM "../data/1GenerateData/exp3/EcsInfo_9_0_1/data_Car_CM_S_40000.txt"		//小型车辆可连接矩阵

#define CarInfoFile_M "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_CarInfo_M_40000.txt"		//中型车辆任务信息
#define CarInfoFile_M_CM "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_Car_CM_M_40000.txt"		//中型车辆可连接矩阵

#define CarInfoFile_L "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_CarInfo_L_40000.txt"		//大型车辆任务信息
#define CarInfoFile_L_CM "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_Car_CM_L_40000.txt"		//大型车辆可连接矩阵


#define RoadLength 10000	//道路长度
#define TTS 2160		//总时间槽 TTS = Total Time Slot

#define RESOURCE 4		//共有4种资源：CPU,GPU,Memory,Disk

#define S_EcsNum 9		//读入的小型基站数
#define M_EcsNum 0		//读入的中型基站数
#define L_EcsNum 1		//读入的大型基站数
#define tEcsNum (S_EcsNum+M_EcsNum+L_EcsNum)  //基站总数

#define RS_S_CarNum 10000		//随机抽取的小型车辆任务数 
#define RS_M_CarNum 0		//随机抽取的中型车辆任务数
#define RS_L_CarNum 0		//随机抽取的大型车辆任务数
#define RS_T_CarNum (RS_S_CarNum+RS_M_CarNum+RS_L_CarNum)  //随机抽取的车辆任务总数

#define S_tCarNum 40000	//小型车辆任务总数
#define M_tCarNum 40000	//中型车辆任务总数 
#define L_tCarNum 40000	//大型车辆任务总数 

const int T = TTS;			//时间槽
const int M = tEcsNum;		//基站总数
const int N = RS_T_CarNum;	//随机抽取的车辆任务总数
const int R = RESOURCE;		//RKNum = Resource Kind Number 资源种类数

const double gamma[R] = { 10, 40, 1, 0.03 };	//gamma是 4 类单位资源（CPU,GPU,Memory,Disk）的单位时间使用成本

//公用自定义结构体：资源
//可用作 基站资源容量，车辆任务资源请求
struct Resource
{
	int cpu = 0;	//资源:cpu
	int gpu = 0;	//资源:gpu
	int memory = 0;	//资源:memory
	int disk = 0;	//资源:disk
};