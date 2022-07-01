#pragma once
#include "GlobalDefinition.h"
#include "EcsInfo.h"
#include "CarInfo.h"

//第一步：读入数据
vector<EcsInfo> vEcsInfo;	//存放所有基站信息的容器

vector<CarInfo> T_vCarInfo;	//存放所有车辆信息的容器

//vector<CarInfo> S_vCarInfo;	//存放小型车辆信息的容器
//vector<CarInfo> M_vCarInfo;	//存放中型车辆信息的容器
//vector<CarInfo> L_vCarInfo;	//存放大型车辆信息的容器

//读入基站信息，一次性读完。
void LoadEcsInfo(string EcsInfofile);
//读入车辆信息，分类型读入
void LoadCarInfo(string CarInfofile, string CarCMfile, vector<CarInfo> &vCar, int CarNum);

//第二步：每个时间槽执行一次OTRAP算法
vector<CarInfo> BeAllocatedCar;	//获得分配且正在执行任务的车辆集合
vector<CarInfo> UnAllocatedCar;	//未获得分配且处于任务有效期的车辆集合

vector<CarInfo> AllocResult;		//截止至[1,t]，获得分配的所有车辆集合
vector<CarInfo> cts_AllocResult;	//当前时间槽的分配结果 cts = current tims slot

vector<CarInfo> tmp_X;			//存放每次运行 OTRAP_ALLOC 后得到分配的车辆集合，下次运行 OTRAP_ALLOC 前清空

//1.OTRAP 算法框架
void OTRAP(int cts, vector<EcsInfo>& ECS, vector<CarInfo> &Car);		//OTRAP算法框架
void IsEcsRCEmpty();		//判断 所有基站容量 是否为空
bool EcsRCEmpty = false;	//标记 所有基站资源是否空，初始值为 false

//2.OTRAP 分配函数
void OTRAP_ALLOC(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& BACar, vector<CarInfo>& UACar);	//OTRAP 分配函数
bool EcsInDegreeAscend(const EcsInfo& ecs1, const EcsInfo& ecs2);	//按基站入度升序对基站排序
void Calc_CarValueDensity(CarInfo& car, EcsInfo& ecs);	//计算车辆的资源密度 Car[i].f
bool CarValueDensityDescend(const CarInfo& car1, const CarInfo& car2);	//按 车辆资源密度Car[i].f 降序对车辆排序

//3.OTRAP 支付函数（二分法）
void OTRAP_PAY(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& BACar, vector<CarInfo>& UACar, vector<CarInfo>& cts_AR);


//第三步：输出结果,保存到本地
void SaveResult();
void CalcUsageRatio();	//计算资源利用率
void CalcServedCarRatio();	//计算服务车辆比例
void CalcNormalPayRatio();	//计算正常付款的车辆比例
