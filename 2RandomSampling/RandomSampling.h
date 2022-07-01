#pragma once

#include "EcsInfo.h"
#include "CarInfo.h"

// 该解决方案的主要功能：
// 1.读入 1GenerateData 生成的大数据库
// 2.随机抽取五组车辆数据，每组车辆数据个数为 100, 500, 5000, 10000, 20000。且每组数据要抽取10次。
// 3.将随机抽取的数据保存到本地

/* 举例：假设现在进行实验一，我们要考察 小型车辆数为100时，算法获得的社会福利、执行时间、服务车辆数和资源利用率。
 * (1)我们要读入大数据库CarInfo_40000_40000_40000中的数据，即分别读入40000条小型车辆数据、40000条中型车辆数据和40000条大型车辆数据。
 * (2)从40000条小型车辆数据随机抽取 100 条小型车辆数据，并且要随机抽取10次。中型车辆数据和大型车辆数据亦然。
 * (3)那么，小型车辆数为100时，系统获得的社会福利 = （10组 100条小型车辆数据获得的社会福利 之和） / 10。
 */

//1.从文件夹 1GenerateData 中读入生成的数据
int count_S_ECS = 0, count_M_ECS = 0, count_L_ECS = 0;
double LoadData_RunTime = 0.00;
double Sampling_RunTime = 0.00;
double SaveData_RunTime = 0.00;

vector<EcsInfo> vEcsInfo;	//存放所有基站信息的容器

vector<CarInfo> T_vCarInfo;	//存放所有车辆信息的容器
vector<CarInfo> S_vCarInfo;	//存放小型车辆信息的容器
vector<CarInfo> M_vCarInfo;	//存放中型车辆信息的容器
vector<CarInfo> L_vCarInfo;	//存放大型车辆信息的容器

//(1)读入基站信息
void LoadEcsInfo(string EcsInfofile);
//(2)读入车辆任务信息
void LoadCarInfo(string CarInfofile, string CarCMfile, vector<CarInfo>& Car, int CarNum);

//2.随机抽取五组车辆数据，每组车辆数据个数为 100, 500, 5000, 10000, 20000。且每组数据要抽取10次。
// 供算法 OPT-TRAP 、OVMAP* 和 OTRAP 调入使用。
vector<CarInfo> RS_S_vCarInfo;	//存放随机抽取的小型车辆任务
vector<CarInfo> RS_M_vCarInfo;	//存放随机抽取的中型车辆任务
vector<CarInfo> RS_L_vCarInfo;	//存放随机抽取的大型车辆任务

//(1)随机抽取固定数量的车辆信息
//车辆任务总数：tCar = total Car
//随机抽取的车辆任务数：rsCar = random sampling Car
void RandomSampling(vector<CarInfo>& Car, vector<CarInfo>& rsCar, string type, int SamplingNum);

//3.将信息保存到本地
//(1)将基站信息保存到本地
void SaveEcsInfo();
//(2)将随机抽取的车辆数据保存到本地
//exenum 第几次执行代码
void SaveCarInfo();
//封装一个函数，用来保存“供算法输入使用”的车辆任务信息
void SaveCarInfoAsInput(vector<CarInfo>& rsCar, string type, int rscarnum);


