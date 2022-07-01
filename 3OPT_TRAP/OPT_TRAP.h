#pragma once
#include "GlobalDefinition.h"
#include "EcsInfo.h"
#include "CarInfo.h"

//第一步：读入数据
//读入基站信息，一次性读完。
void LoadEcsInfo(string EcsInfofile);	
//读取车辆信息，分类型读入
void LoadCarInfo(string CarInfofile, string CarCMfile,int CarNum, CarInfo * carp);


//第二步：分配函数，计算最优分配结果
int * TRAP_IP(CarInfo * carp);
int LessthanOrEqual(int a, int b);		//返回小于等于的整数左值
int GreaterthanOrEqual(int a, int b);	//返回大于等于的整数左值

//第三步：支付函数，计算各车辆付款
void TRAP_PAY(int* X);
//封装一个函数，把 Car[i] 踢出车辆集合Car[]。
//参数：env, model, cplex, 车辆数组[], 要踢出的车辆
void RemoveCar_i(CarInfo* carp, int id);
//封装一个函数，恢复 Car[i] 的信息
void RecoverCar_i(CarInfo* carp, int id);

//第四步：输出结果,保存到本地
void SaveResult();

void CalcUsageRatio();	//计算资源利用率

void CalcServedCarRatio();	//计算服务车辆比例

