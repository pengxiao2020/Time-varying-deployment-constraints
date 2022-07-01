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

//EcsInfo 类用来定义基站信息

//基站信息 用“类 class”来表示
//基站 j 的资源容量向量 c[i] 使用“容器 vector”存储

class EcsInfo
{
public:
	//属性
	//基站编号 1~tEcsNum
	int m_ecsId = 0;

	//基站类型 S M L 
	string type;	//type = S/M/L;

	//基站位置：一维道路中，用点m_loc标识；二维道路需要用make_pair表示
	int m_loc = 0;

	//基站覆盖半径 coverage radius：100m, 200m, 300m
	int m_cr = 0;

	//基站覆盖范围
	//利用 m_loc 确定出基站的具体覆盖范围 m_aCA : member_arrayCoverageArea
	//m_aCA[2] = [左区间，右区间] = [m_loc - m_cr, m_loc + m_cr]
	int m_aCA[2];

	//资源容量向量 m_c，共有四类资源：(CPU, GPU, Memory, Disk)
	//注意 m_c.size() == m_s.size()，二者对应元素的数量可以相加减（资源分配与回收）
	vector<int> m_rc;

};
