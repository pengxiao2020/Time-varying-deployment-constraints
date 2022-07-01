#pragma once
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>		//内建函数对象
#include <numeric>
using namespace std;

class CarInfo
{
public:
    //属性

    //车辆编号:1~tCarNum，
    int m_carId = 0;

    //车辆类型: s / m / l
    string type;

    //车辆初始位置（当前位置）服从均匀分布 U[0,L],  il = Initial Location
    int m_il = 0;

    //车辆速度: 以m/s为单位，范围: v = [10,20]m/s = [100,200]m/t
    int m_v = 0;

    //到达时间, 服从正态分布 N[T/2,(T/8)^2] 
    int m_at = 0;         //at = ArriveTime

    //任务完成截止时间 d[i]
    int m_dt = 0;         // dt = DeadlineTime

    //执行时间e[i]
    int m_et = 0;         // et = ExecutionTime

    //任务资源需求s[i]，共有四类资源：(CPU, GPU, Memory, Disk)
    //注意 m_c.size() == m_s.size()，二者对应元素的数量可以相加减（资源分配与回收）
    vector<int> m_s;

    //投标系数 mu[i] = [0.25, 4]
    //服从均匀分布 U[0.25, 4]
    double m_mu = 0.00;     //希腊字母 mu = BidCoefficient

    //投标b[i]
    double m_b = 0.00;      // b = Bid

    //车辆的可连接矩阵(ConnectableMatrix) = 时变部署约束矩阵
    vector<vector<bool>> m_cm;

    //付款p[i]
    double m_p = 0.00;       // p = Payment

};
