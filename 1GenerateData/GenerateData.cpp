#include "GenerateData.h"


//第一部分 基站相关
//1.生成基站信息
void GenerateEcsInfo()
{
	//(1)生成小型基站数据
	for (int m = 0; m < S_EcsNum; m++)
	{
		//生成具体的小型基站对象 s_ei = Small EcsInfo
		EcsInfo s_ei;

		//生成基站编号(唯一)
		s_ei.m_ecsId = m + 1;

		//确定生成基站类型：小型基站
		s_ei.type = "S";

		//生成小型基站覆盖半径 m_cr
		s_ei.m_cr = S_ECS_CR;

		//生成基站位置 m_loc (唯一): 每隔 L / tEcsNum 米，建成一座基站
		s_ei.m_loc = CalcEcsLoc(s_ei);

		//基站覆盖范围
		//利用 m_loc 确定出基站的具体覆盖范围 m_arrCA : member_CoverageArea
		//m_arrCA[2] = [左区间，右区间] = [m_loc - m_cr, m_loc + m_cr]
		int* p = CalcEcsCA(s_ei);
		s_ei.m_aCA[0] = *p;
		s_ei.m_aCA[1] = *(p + 1);

		//生成基站资源容量 m_rc（固定）
		//s_ei.m_rc = Small_EcsInfo.m_rc 为：“小型基站”类对象的资源容量向量
		//s_ei.m_rc = (c_i1, c_i2, c_i3, c_i4) = (CPU, GPU, Memory, Disk)
		//注意 s_ei.size() = RFNum = 4
		for (int r = 0; r < RKNum; r++)
		{
			switch (r)
			{
			case 0:		//生成 CPU 的资源容量，即c_i1
				s_ei.m_rc.push_back(S_ECS_RC_CPU);
				break;
			case 1:		//生成 GPU 的资源容量，即c_i2
				s_ei.m_rc.push_back(S_ECS_RC_GPU);
				break;
			case 2:		//生成 Memory 的资源容量，即c_i3
				s_ei.m_rc.push_back(S_ECS_RC_MEMORY);
				break;
			case 3:		//生成 Disk 的资源容量，即c_i4
				s_ei.m_rc.push_back(S_ECS_RC_DISK);
				break;
			default:
				break;
			}
		}

		//生成一条小型基站信息后，要将该基站信息放入到小型基站容器 s_vEcsInfo 中
		s_vEcsInfo.push_back(s_ei);
		//把所有基站放入到同一个vector容器 vEcsInfo 中
		vEcsInfo.push_back(s_ei);
	}
	if (S_EcsNum == vEcsInfo.size())
		cout << "已成功生成 " << S_EcsNum << "条小型基站信息数据" << endl;
	else
		cout << "生成数据失败，生成的小型基站的数量 与 输入的 S_EcsNum = " << S_EcsNum << " 不相等!" << endl;

	//(2)生成中型基站数据
	for (int m = S_EcsNum; m < S_EcsNum + M_EcsNum; m++)
	{
		//生成具体的中型基站对象 m_ei = Medium EcsInfo
		EcsInfo m_ei;

		//生成基站编号(唯一)
		m_ei.m_ecsId = m + 1;

		//确定生成基站类型：中型基站
		m_ei.type = "M";

		//生成中型基站覆盖半径 m_cr
		m_ei.m_cr = M_ECS_CR;

		//生成基站位置 m_loc (唯一): 每隔 L / tEcsNum 米，建成一座基站
		m_ei.m_loc = CalcEcsLoc(m_ei);

		//基站覆盖范围
		//利用 m_loc 确定出基站的具体覆盖范围 m_arrCA : member_CoverageArea
		//m_arrCA[2] = [左区间，右区间] = [m_loc - m_cr, m_loc + m_cr]
		int* p = CalcEcsCA(m_ei);
		m_ei.m_aCA[0] = *p;
		m_ei.m_aCA[1] = *(p + 1);

		//生成基站资源容量 m_rc
		//m_ei.m_rc = Medium_EcsInfo.m_rc 为：“中型基站”类对象的资源容量向量
		//m_ei.m_rc = (c_i1, c_i2, c_i3, c_i4) = (CPU, GPU, Memory, Disk)
		//注意 m_ei.size() = RFNum = 4
		for (int r = 0; r < RKNum; r++)
		{
			switch (r)
			{
			case 0:		//生成 CPU 的资源容量，即c_i1
				m_ei.m_rc.push_back(M_ECS_RC_CPU);
				break;
			case 1:		//生成 GPU 的资源容量，即c_i2
				m_ei.m_rc.push_back(M_ECS_RC_GPU);
				break;
			case 2:		//生成 Memory 的资源容量，即c_i3
				m_ei.m_rc.push_back(M_ECS_RC_MEMORY);
				break;
			case 3:		//生成 Disk 的资源容量，即c_i4
				m_ei.m_rc.push_back(M_ECS_RC_DISK);
				break;
			default:
				break;
			}
		}

		//生成一条中型基站信息后，要将该基站信息放入到中型基站容器 m_vEcsInfo 中
		m_vEcsInfo.push_back(m_ei);
		//把所有基站放入到同一个vector容器 vEcsInfo 中
		vEcsInfo.push_back(m_ei);
	}
	if (M_EcsNum == vEcsInfo.size() - S_EcsNum)
		cout << "已成功生成 " << M_EcsNum << "条中型基站信息数据" << endl;
	else
		cout << "生成数据失败，生成的中型基站的数量 与 输入的 M_EcsNum = " << M_EcsNum << " 不相等!" << endl;

	//(3)生成大型基站数据
	for (int m = S_EcsNum + M_EcsNum; m < tEcsNum; m++)
	{
		//生成具体的大型基站对象 l_ei = Large EcsInfo
		EcsInfo l_ei;

		//生成基站编号(唯一)
		l_ei.m_ecsId = m + 1;

		//确定生成基站类型：大型基站
		l_ei.type = "L";

		//生成大型基站覆盖半径 m_cr
		l_ei.m_cr = L_ECS_CR;

		//生成基站位置 m_loc (唯一): 每隔 L / tEcsNum 米，建成一座基站
		l_ei.m_loc = CalcEcsLoc(l_ei);

		//基站覆盖范围
		//利用 m_loc 确定出基站的具体覆盖范围 m_arrCA : member_CoverageArea
		//m_arrCA[2] = [左区间，右区间] = [m_loc - m_cr, m_loc + m_cr]
		int* p = CalcEcsCA(l_ei);
		l_ei.m_aCA[0] = *p;
		l_ei.m_aCA[1] = *(p + 1);

		//生成基站资源容量 m_rc
		//l_ei.m_rc = Large_EcsInfo.m_rc 为：“大型基站”类对象的资源容量向量
		//l_ei.m_rc = (c_i1, c_i2, c_i3, c_i4) = (CPU, GPU, Memory, Disk)
		//注意 l_ei.size() = RFNum = 4
		for (int r = 0; r < RKNum; r++)
		{
			switch (r)
			{
			case 0:		//生成 CPU 的资源容量，即c_i1
				l_ei.m_rc.push_back(L_ECS_RC_CPU);
				break;
			case 1:		//生成 GPU 的资源容量，即c_i2
				l_ei.m_rc.push_back(L_ECS_RC_GPU);
				break;
			case 2:		//生成 Memory 的资源容量，即c_i3
				l_ei.m_rc.push_back(L_ECS_RC_MEMORY);
				break;
			case 3:		//生成 Disk 的资源容量，即c_i4
				l_ei.m_rc.push_back(L_ECS_RC_DISK);
				break;
			default:
				break;
			}
		}

		//生成一条大型基站信息后，要将该基站信息放入到大型基站容器 l_vEcsInfo 中
		l_vEcsInfo.push_back(l_ei);
		//把所有基站放入到同一个vector容器 vEcsInfo 中
		vEcsInfo.push_back(l_ei);
	}
	if (L_EcsNum == vEcsInfo.size() - S_EcsNum - M_EcsNum)
		cout << "已成功生成 " << L_EcsNum << "条大型基站信息数据" << endl;
	else
		cout << "生成数据失败，生成的大型基站的数量 与 输入的 L_EcsNum = " << L_EcsNum << " 不相等!" << endl;

	//判断 & 提示 生成基站数据成功
	if (tEcsNum == s_vEcsInfo.size() + m_vEcsInfo.size() + l_vEcsInfo.size())
	{
		cout << "已成功生成 tEcsNum = S_EcsNum + M_EcsNum + L_EcsNum = "
			<< s_vEcsInfo.size() << " + " << m_vEcsInfo.size() << " + " << l_vEcsInfo.size()
			<< " = " << tEcsNum << " 条基站信息数据" << endl;
	}
	cout << endl;

}
//生成基站位置的函数(改): 该函数过于冗杂，不需细看
int CalcEcsLoc(EcsInfo& ei)
{
	//第一步：计算每座基站之间的间隔 EcsItv （间隔相等）
	//均匀生成基站：每隔 (L / tECSNum) 的距离，生成一座基站
	int EcsItv = 0;
	EcsItv = L / tEcsNum;	//EcsItv = ECS interval

	//第二步：计算每种类型的基站因子 并对其进行四舍五入
	int temp = 0;
	int fct = 0;	//记录：哪种类型的基站数量最小（非0）
	
	if ((S_EcsNum == 0) || (M_EcsNum == 0) || (L_EcsNum == 0))
	{
		if (S_EcsNum == 0)
		{
			if (M_EcsNum == 0)
			{
				fct = L_EcsNum;
			}
			else if (L_EcsNum == 0)
			{
				fct = M_EcsNum;
			}
			else
			{
				fct = min(M_EcsNum, L_EcsNum);
			}
		}
		if (M_EcsNum == 0)
		{
			if (S_EcsNum == 0)
			{
				fct = L_EcsNum;
			}
			else if (L_EcsNum == 0)
			{
				fct = S_EcsNum;
			}
			else
			{
				fct = min(S_EcsNum, L_EcsNum);
			}
		}
		if (L_EcsNum == 0)
		{
			if (S_EcsNum == 0)
			{
				fct = M_EcsNum;
			}
			else if (M_EcsNum == 0)
			{
				fct = S_EcsNum;
			}
			else
			{
				fct = min(S_EcsNum, M_EcsNum);
			}
		}
	}
	else
	{
		temp = min(S_EcsNum, M_EcsNum);
		fct = min(temp, L_EcsNum);
	}

	////每个基站组中含有多少个该类型的基站（四舍五入）
	//int s_EcsDvs = int((double)S_EcsNum / (double)fct + 0.5);		//小型基站因子
	//int m_EcsDvs = int((double)M_EcsNum / (double)fct + 0.5);		//中型基站因子
	//int l_EcsDvs = int((double)L_EcsNum / (double)fct + 0.5);		//大型基站因子

	//每个基站组中含有多少个该类型的基站（未四舍五入，实验效果更好）
	int s_EcsDvs = int((double)S_EcsNum / (double)fct);		//小型基站因子
	int m_EcsDvs = int((double)M_EcsNum / (double)fct);		//中型基站因子
	int l_EcsDvs = int((double)L_EcsNum / (double)fct);		//大型基站因子

	//第三步，使用基站因子确定“基站组”，该组中包含确定数量的小中大基站
	//即一个基站组包含：s_EcsDvs个小基站，m_EcsDvs个小基站,l_EcsDvs个大基站
	//例如，设一共生成15个基站，其中，小基站数量为7，中基站数量为5，大基站数量为3。
	//则一个基站组包含的(小基站，中基站，大基站)个数为：(2.3, 1.6, 1)=(2,2,1)
	int EcsNumInSet = s_EcsDvs + m_EcsDvs + l_EcsDvs;	//一个基站组中所包含的小中大基站个数

	//应对 基站数量S : M : L = 10 : 5 : 2，基站因子：5 : 3 : 2 的例子(success)
	//应对 基站数量S : M : L = 7 : 5 : 3 ，基站因子：2 : 2 : 1 的例子(success)
	//应对 基站数量S : M : L = 5 : 3 : 2 ，基站因子：2 : 2 : 1 的例子(success)

	//第四步：确定基站组的“组数”
	//基站组的组数是由“数量最多的基站”和“数量最少的基站”共同确定的
	int EcsSetNum = 0;	//EcsSetNum 最终确定的基站组组数
	int int_EcsSetNum = tEcsNum / EcsNumInSet;	//int_EcsSetNum 基站组的组数(整型)
	double db_EcsSetNum = (double)tEcsNum / (double)EcsNumInSet;	//db_EcsSetNum 基站组的组数(双精度)

	//cdt:common divisor test
	//基站因子与基站数量是否呈整数倍关系
	bool cdt_s = false;
	bool cdt_m = false;
	bool cdt_l = false;

	//防止除数为1
	if (s_EcsDvs == 0 || m_EcsDvs == 0 || l_EcsDvs == 0)
	{
		if (s_EcsDvs == 0)
		{
			cdt_s = false;
		}
		else
		{
			cdt_s = ((double)S_EcsNum / (double)s_EcsDvs == (double)(S_EcsNum / s_EcsDvs));
		}
		if (m_EcsDvs == 0)
		{
			cdt_m = false;
		}
		else
		{
			cdt_m = ((double)M_EcsNum / (double)m_EcsDvs == (double)(M_EcsNum / m_EcsDvs));
		}
		if (l_EcsDvs == 0)
		{
			cdt_l = false;
		}
		else
		{
			cdt_l = ((double)L_EcsNum / (double)l_EcsDvs == (double)(L_EcsNum / l_EcsDvs));
		}
	}
	else
	{
		cdt_s = ((double)S_EcsNum / (double)s_EcsDvs == (double)(S_EcsNum / s_EcsDvs));
		cdt_m = ((double)M_EcsNum / (double)m_EcsDvs == (double)(M_EcsNum / m_EcsDvs));
		cdt_l = ((double)L_EcsNum / (double)l_EcsDvs == (double)(L_EcsNum / l_EcsDvs));
	}

	if ((double)int_EcsSetNum == db_EcsSetNum)
	{
		if (cdt_s && cdt_m && cdt_l)		//分别判断三种类型（小中大）的“基站数量与基站因子”是否为整数倍关系
		{
			EcsSetNum = int_EcsSetNum;
		}
		else
		{
			EcsSetNum = int(db_EcsSetNum + 1);
		}
	}
	else
	{
		EcsSetNum = int(db_EcsSetNum + 1);
	}

	int s_EcsLoc = 0;	//用来接收基站位置
	int m_EcsLoc = 0;	//用来接收基站位置
	int l_EcsLoc = 0;	//用来接收基站位置

	//判断该基站是哪种类型的基站（小中大）
	if (ei.type == "S")	//生成小基站位置
	{
		int id = ei.m_ecsId;

		//1.根据编号算出基站所在的组号：第几组(组数从0开始)
		//NoS = Number of Set : 基站所在的基站组号
		int NoS = (id - 1) / s_EcsDvs;		//基站 ei 所在组号 = (编号 - 1) / 基站因子
		//cout << "这是第 " << id << " 个小型基站，所在组号为：" << NoS << endl;

		//基站的数量最小的情况 包含于 编号=="因子的整数倍" 的情况
		//但在“基站数量最小的情况中”计算的位置需要多加 1 * EcsItv
		//NoS * (EcsNumInSet - 1) * EcsItv 是前面的基站组占据的位置
		//(NoS - 1) * EcsItv 是之前的基站组之间的间距
		if (id == s_EcsDvs * (id / s_EcsDvs))	//编号=="因子的整数倍"的情况
		{
			//cout << "第 " << id << "个小型基站的编号与其因子为整数倍关系" << endl;
			s_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % s_EcsDvs) + 1) * EcsItv;
		}
		else       //"编号!=因子的整数倍"的情况
		{
			s_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % s_EcsDvs) * EcsItv;
		}
	}

	else if (ei.type == "M")	//生成中基站位置
	{
		int id = ei.m_ecsId - S_EcsNum;

		int NoS = (id - 1) / m_EcsDvs;	//基站所在组号

		//分两种情况讨论，最后一组和不是最后一组
		if (NoS == EcsSetNum - 1)	//最后一组
		{
			//"编号==因子的整数倍"的特殊情况，((id - 1) % m_EcsDvs) + 1
			if (id == m_EcsDvs * (id / m_EcsDvs))
			{
				if (cdt_s)	//cdt_s 为真 : 小型基站的数量与其基站因子呈整数倍关系
				{
					//考虑以下因素
					//1.小基站在最后一组中安排一个完备组
					if (S_EcsNum / s_EcsDvs - 1 == NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % m_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs * EcsItv);
					}
					//2.小基站在前面的组中已经安排完
					else if (S_EcsNum / s_EcsDvs - 1 < NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % m_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs) * EcsItv;
					}
					else
						cout << "中型基站 " << ei.m_ecsId << " 的生成位置错误！" << endl;
				}
				else   //cdt_s 为假: 小型基站的数量与其基站因子不是整数倍关系
				{
					//考虑以下两个因素：
					//1.小基站在最后一组安排余数个基站
					if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % m_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs) * EcsItv;
					}
					//2.小基站在前面的组中已安排完
					else if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % m_EcsDvs) + 1) * EcsItv;
					}
					else
						cout << "中型基站 " << ei.m_ecsId << " 的生成位置错误！" << endl;
				}
			}
			//"编号!=因子的整数倍"的特殊情况: (id % m_EcsDvs)
			else
			{
				if (cdt_s)	//cdt_s 为真 : 小型基站的数量与其基站因子呈整数倍关系
				{
					//考虑以下因素
					//1.小基站在最后一组中安排一个完备组
					if (S_EcsNum / s_EcsDvs - 1 == NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (s_EcsDvs * EcsItv);
					}
					//2.小基站在前面的组中已经安排完
					else if (S_EcsNum / s_EcsDvs - 1 < NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs) * EcsItv;
					}
					else
						cout << "中型基站 " << ei.m_ecsId << " 的生成位置错误！" << endl;
				}
				else   //cdt_s 为假: 小型基站的数量与其基站因子不是整数倍关系
				{
					//考虑以下两个因素：
					//1.小基站在最后一组安排余数个基站
					if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs) * EcsItv;
					}
					//2.小基站在前面的组中已安排完
					else if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv;
					}
					else
						cout << "中型基站 " << ei.m_ecsId << " 的生成位置错误！" << endl;
				}
			}
		}
		//不是最后一组: (NoS == EcsSetNum - 1)
		else
		{
			//"编号==因子的整数倍"的特殊情况((id - 1) % m_EcsDvs) + 1
			if (id == m_EcsDvs * (id / m_EcsDvs))
			{
				if (cdt_s)	//cdt_s 为真 : 小型基站的数量与其基站因子呈整数倍关系
				{
					//考虑以下3个因素：
					//1.小基站在前面的组中已安排完
					if (S_EcsNum / s_EcsDvs - 1 < NoS)	//最后一组中已部署了一个完备组小型基站
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % m_EcsDvs) + 1) * EcsItv;
					}
					//2.小基站安排一个完备组，且在本组部署完。
					//3.小基站安排一个完备组，且下一组中仍需安排
					else if (S_EcsNum / s_EcsDvs - 1 >= NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % m_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs * EcsItv);
					}
					else
						cout << "中型基站 " << ei.m_ecsId << " 的生成位置错误！" << endl;
				}
				else   //cdt_s 为假: 小型基站的数量与其基站因子不是整数倍关系
				{
					//考虑以下3个因素：
					//1.小基站在前面的组中已安排完
					if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % m_EcsDvs) + 1) * EcsItv;
					}
					//2.小基站安排余数个基站，且在本组部署完。
					else if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % m_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs) * EcsItv;
					}
					//3.小基站安排一个完备组，且下一组中仍需安排。
					else if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % m_EcsDvs) + 1) * EcsItv
							+ s_EcsDvs * EcsItv;
					}
					else
						cout << "中型基站 " << ei.m_ecsId << " 的生成位置错误！" << endl;
				}
			}
			//"编号!=因子的整数倍"的特殊情况: (id % m_EcsDvs)
			else
			{
				if (cdt_s)	//cdt_s 为真 : 小型基站的数量与其基站因子呈整数倍关系
				{
					//考虑以下3个因素：
					//1.小基站在前面的组中已安排完
					if (S_EcsNum / s_EcsDvs - 1 < NoS)	//最后一组中已部署了一个完备组小型基站
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv;
					}
					//2.小基站安排一个完备组，且在本组部署完。
					//3.小基站安排一个完备组，且下一组中仍需安排
					else if (S_EcsNum / s_EcsDvs - 1 >= NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (s_EcsDvs * EcsItv);
					}
					else
						cout << "中型基站 " << ei.m_ecsId << " 的生成位置错误！" << endl;
				}
				else   //cdt_s 为假: 小型基站的数量与其基站因子不是整数倍关系
				{
					//考虑以下3个因素：
					//1.小基站在前面的组中已安排完
					if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv;
					}
					//2.小基站安排余数个基站，且在本组部署完。
					else if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs) * EcsItv;
					}
					//3.小基站安排一个完备组，且下一组中仍需安排。
					else if (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS)
					{
						m_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ s_EcsDvs * EcsItv;
					}
					else
						cout << "中型基站 " << ei.m_ecsId << " 的生成位置错误！" << endl;
				}
			}
		}
	}

	else if (ei.type == "L")
	{
		int id = ei.m_ecsId - S_EcsNum - M_EcsNum;

		int NoS = (id - 1) / l_EcsDvs;	//基站所在组号

		//分两种情况讨论，最后一组和不是最后一组
		if (NoS == EcsSetNum - 1)	//最后一组
		{
			//最后一组，且"编号==因子的整数倍"的情况 (((id - 1) % l_EcsDvs) + 1)
			if (id == l_EcsDvs * (id / l_EcsDvs))
			{
				//cdt_s : 小型基站数量 与 其基站因子 呈整数倍关系
				//cdt_m : 中型基站数量 与 其基站因子 呈整数倍关系
				if (cdt_s && cdt_m)	//cdt_s == T && cdt_m == T
				{
					//①小型基站 & 中型基站都安排一个完备组，且刚好安排完
					if (S_EcsNum / s_EcsDvs - 1 == NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//②小型基站安排一个完备组，刚好安排完；中型基站在前面的组中已经安排完.
					else if ((S_EcsNum / s_EcsDvs - 1 == NoS) && (M_EcsNum / m_EcsDvs - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小型基站在前面的组中已经安排完，中型基站安排一个完备组，且刚好安排完。
					else if (S_EcsNum / s_EcsDvs - 1 < NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//④小型基站 & 中型基站在前面的组中都已经安排完。
					else if (S_EcsNum / s_EcsDvs - 1 < NoS && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if (cdt_s && (!cdt_m)) // cdt_s == T && cdt_m == F
				{
					//10:5:2, 5:3:1
					//①小基站安排一个完备组，且刚好安排完。中型基站还要安排余数个基站。
					if (S_EcsNum / s_EcsDvs - 1 == NoS && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//7:3:5, 2:1:2
					//②小基站安排一个完备组，且刚好安排完。中型基站在前面的组中已经安排完。
					else if ((S_EcsNum / s_EcsDvs - 1 == NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + 0) * EcsItv;
					}
					//③小基站在前面的组中已安排完，中型基站还有余数个基站要安排。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//④小基站 & 中型基站都在前面的组中安排完。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + 0) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if ((!cdt_s) && cdt_m) // cdt_s == F && cdt_m == T
				{
					//①小型基站还有余数个基站要安排，中型基站安排一个完备组，刚好安排完。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && M_EcsNum / m_EcsDvs - 1 == NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//②小型基站还有余数个基站要安排，中型基站在前面的组中已经安排完。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小型基站在前面的组中已经安排完，中型基站安排一个完备组，刚好安排完。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (0 + m_EcsDvs) * EcsItv;
					}
					//④小型基站 & 中型基站都在前面的组中已经安排完。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (0 + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if ((!cdt_s) && (!cdt_m))	// cdt_s == F && cdt_m == F
				{
					//①小型基站 & 中型基站还有余数个基站要安排。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) &&
						(int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//②小型基站还有余数个基站要安排，中型基站在前面的组中已经安排完。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + 0) * EcsItv;
					}
					//③小型基站在前面的组中已经安排完，中型基站还有余数个基站要安排。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (0 + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//④小型基站 & 中型基站都在前面的组中已经安排完了。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (0 + 0) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
			}
			//最后一组，且 "编号!=因子的整数倍" (id % m_EcsDvs)
			else
			{
				//cdt_s : 小型基站数量 与 其基站因子 呈整数倍关系
				//cdt_m : 中型基站数量 与 其基站因子 呈整数倍关系
				if (cdt_s && cdt_m)	//cdt_s == T && cdt_m == T
				{
					//①小型基站 & 中型基站都安排一个完备组，且刚好安排完
					if (S_EcsNum / s_EcsDvs - 1 == NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//②小型基站安排一个完备组，刚好安排完；中型基站在前面的组中已经安排完.
					else if ((S_EcsNum / s_EcsDvs - 1 == NoS) && (M_EcsNum / m_EcsDvs - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小型基站在前面的组中已经安排完，中型基站安排一个完备组，且刚好安排完。
					else if (S_EcsNum / s_EcsDvs - 1 < NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//④小型基站 & 中型基站在前面的组中都已经安排完。
					else if (S_EcsNum / s_EcsDvs - 1 < NoS && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if (cdt_s && (!cdt_m)) // cdt_s == T && cdt_m == F
				{
					//10:5:2, 5:3:1
					//①小基站安排一个完备组，且刚好安排完。中型基站还要安排余数个基站。
					if (S_EcsNum / s_EcsDvs - 1 == NoS && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//7:3:5, 2:1:2
					//②小基站安排一个完备组，且刚好安排完。中型基站在前面的组中已经安排完。
					else if ((S_EcsNum / s_EcsDvs - 1 == NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (s_EcsDvs + 0) * EcsItv;
					}
					//③小基站在前面的组中已安排完，中型基站还有余数个基站要安排。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//④小基站 & 中型基站都在前面的组中安排完。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + 0) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if ((!cdt_s) && cdt_m) // cdt_s == F && cdt_m == T
				{
					//①小型基站还有余数个基站要安排，中型基站安排一个完备组，刚好安排完。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && M_EcsNum / m_EcsDvs - 1 == NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//②小型基站还有余数个基站要安排，中型基站在前面的组中已经安排完。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小型基站在前面的组中已经安排完，中型基站安排一个完备组，刚好安排完。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (0 + m_EcsDvs) * EcsItv;
					}
					//④小型基站 & 中型基站都在前面的组中已经安排完。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (0 + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if ((!cdt_s) && (!cdt_m))	// cdt_s == F && cdt_m == F
				{
					//①小型基站 & 中型基站还有余数个基站要安排。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) &&
						(int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//②小型基站还有余数个基站要安排，中型基站在前面的组中已经安排完。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + 0) * EcsItv;
					}
					//③小型基站在前面的组中已经安排完，中型基站还有余数个基站要安排。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (0 + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//④小型基站 & 中型基站都在前面的组中已经安排完了。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % m_EcsDvs) * EcsItv
							+ (0 + 0) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
			}
		}
		//不是最后一组
		else
		{
			//非最后一组，且"编号==因子的整数倍": (((id - 1) % l_EcsDvs) + 1)
			if (id == l_EcsDvs * (id / l_EcsDvs))
			{
				if (cdt_s && cdt_m)	//cdt_s == T && cdt_m == T
				{
					//①小基站在前面的组中已经安排完毕，中基站在前面的组中已经安排完毕。
					if (S_EcsNum / s_EcsDvs - 1 < NoS && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//②小基站在前面的组中已经安排完毕，中基站在本组安排一个完备组且刚好安排完毕。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//9:6:3, 3:2:1
					//③小基站在前面的组中已经安排完毕，中基站安排一个完备组且下一基站组仍然需要安装。
					else if (S_EcsNum / s_EcsDvs - 1 < NoS && M_EcsNum / m_EcsDvs - 1 > NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//④小基站安排一个完备组且刚好安排完毕，中基站在前面的组中已经安排完毕。
					// S_EcsNum / s_EcsDvs - 1 == NoS && M_EcsNum / m_EcsDvs - 1 < NoS
					//⑦小基站安排一个完备组且下一基站组仍然需要安装，中基站在前面的组中已经安排完毕。
					// S_EcsNum / s_EcsDvs - 1 > NoS && M_EcsNum / m_EcsDvs - 1 < NoS
					else if (S_EcsNum / s_EcsDvs - 1 >= NoS && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//⑤小基站安排一个完备组且刚好安排完毕，中基站在本组安排一个完备组且刚好安排完毕。
					// (S_EcsNum / s_EcsDvs - 1 == NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					//⑧小基站安排一个完备组且下一基站组仍然需要安装，中基站在本组安排一个完备组且刚好安排完毕。
					// (S_EcsNum / s_EcsDvs - 1 > NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					else if (S_EcsNum / s_EcsDvs - 1 >= NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑥小基站安排一个完备组且刚好安排完毕，中基站安排一个完备组且下一基站组仍然需要安装。
					// S_EcsNum / s_EcsDvs - 1 == NoS && M_EcsNum / m_EcsDvs - 1 > NoS
					//⑨小基站安排一个完备组且下一基站组仍然需要安装，中基站安排一个完备组且下一基站组仍需安排。
					// S_EcsNum / s_EcsDvs - 1 > NoS && M_EcsNum / m_EcsDvs - 1 > NoS
					else if (S_EcsNum / s_EcsDvs - 1 >= NoS && M_EcsNum / m_EcsDvs - 1 > NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if (cdt_s && (!cdt_m)) // cdt_s == T && cdt_m == F
				{
					//10:5:2, 5:3:1
					//①小基站在前面的组中已安排完(完备组)，中基站在前面的组中已安排完。
					// S_EcsNum / s_EcsDvs - 1 < NoS && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS)
					//④小基站在本组中安排一个完备组，刚好安排完；中基站在前面的组中已安排完。
					// S_EcsNum / s_EcsDvs - 1 == NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS)
					if (S_EcsNum / s_EcsDvs - 1 <= NoS && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + 0) * EcsItv;
					}
					//②小基站在前面的组中已安排完(完备组)，中基站在本组中安排余数个基站，刚好安排完。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小基站在前面的组中已安排完(完备组)，中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑤小基站在本组中安排一个完备组，刚好安排完；中基站在本组中安排余数个基站，刚好安排完
					// (S_EcsNum / s_EcsDvs - 1 == NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS)
					//⑧小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排余数个基站，刚好安排完。
					// (S_EcsNum / s_EcsDvs - 1 > NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS)
					else if ((S_EcsNum / s_EcsDvs - 1 >= NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//⑥小基站在本组中安排一个完备组，刚好安排完；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (S_EcsNum / s_EcsDvs - 1 == NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS)
					//⑨小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (S_EcsNum / s_EcsDvs - 1 > NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS)
					else if ((S_EcsNum / s_EcsDvs - 1 >= NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑦小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在前面的组中已安排完。
					else if ((S_EcsNum / s_EcsDvs - 1 > NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + 0) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if ((!cdt_s) && cdt_m) // cdt_s == F && cdt_m == T
				{
					//①小基站在前面的组中已安排完毕；中基站在前面的组中已安排完(完备组)。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (0 + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//②小基站在本组中安排余数个基站，刚好安排完；中基站在前面的组中已安排完(完备组)
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在前面的组中已安排完毕(完备组)。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS) && (M_EcsNum / m_EcsDvs - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//④小基站在前面的组中已安排完毕；中基站在本组中安排一个完备组，刚好安排完毕。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS)
					//⑦小基站在前面的组中已安排完毕；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 > NoS)
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 >= NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (0 + m_EcsDvs) * EcsItv;
					}
					//⑤小基站在本组中安排余数个基站，刚好安排完；中基站在本组中安排一个完备组，刚好安排完毕.
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS)
					//⑧小基站在本组中安排余数个基站，刚好安排完；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && (M_EcsNum / m_EcsDvs - 1 > NoS)
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && (M_EcsNum / m_EcsDvs - 1 >= NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑥小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排一个完备组，刚好安排完毕。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS)
					//⑨小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS) && (M_EcsNum / m_EcsDvs - 1 > NoS)
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS) && (M_EcsNum / m_EcsDvs - 1 >= NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if ((!cdt_s) && (!cdt_m))	// cdt_s == F && cdt_m == F
				{
					//①小基站在前面的组中已安排完毕；中基站在前面的组中已安排完毕。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) &&
						(int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (0 + 0) * EcsItv;
					}
					//②小基站在前面的组中已安排完毕；中基站在本组中安排余数个基站，刚好安排完。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (0 + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小基站在前面的组中已安排完毕；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (0 + m_EcsDvs) * EcsItv;
					}
					//④小基站在本组中安排余数个基站，刚好安排完；中基站在前面的组中已安排完毕。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + 0) * EcsItv;
					}
					//⑤小基站在本组中安排余数个基站，刚好安排完；中基站在本组中安排余数个基站，刚好安排完。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//⑥小基站在本组中安排余数个基站，刚好安排完；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑦小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在前面的组中已安排完毕。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + 0) * EcsItv;
					}
					//⑧小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排余数个基站，刚好安排完。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//⑨小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (((id - 1) % l_EcsDvs) + 1) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
			}
			//非最后一组，且"编号!=因子的整数倍": (id % l_EcsDvs)
			else
			{
				if (cdt_s && cdt_m)	//cdt_s == T && cdt_m == T
				{
					//①小基站在前面的组中已经安排完毕，中基站在前面的组中已经安排完毕。
					if (S_EcsNum / s_EcsDvs - 1 < NoS && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//②小基站在前面的组中已经安排完毕，中基站在本组安排一个完备组且刚好安排完毕。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//9:6:3, 3:2:1
					//③小基站在前面的组中已经安排完毕，中基站安排一个完备组且下一基站组仍然需要安装。
					else if (S_EcsNum / s_EcsDvs - 1 < NoS && M_EcsNum / m_EcsDvs - 1 > NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//④小基站安排一个完备组且刚好安排完毕，中基站在前面的组中已经安排完毕。
					// S_EcsNum / s_EcsDvs - 1 == NoS && M_EcsNum / m_EcsDvs - 1 < NoS
					//⑦小基站安排一个完备组且下一基站组仍然需要安装，中基站在前面的组中已经安排完毕。
					// S_EcsNum / s_EcsDvs - 1 > NoS && M_EcsNum / m_EcsDvs - 1 < NoS
					else if (S_EcsNum / s_EcsDvs - 1 >= NoS && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//⑤小基站安排一个完备组且刚好安排完毕，中基站在本组安排一个完备组且刚好安排完毕。
					// (S_EcsNum / s_EcsDvs - 1 == NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					//⑧小基站安排一个完备组且下一基站组仍然需要安装，中基站在本组安排一个完备组且刚好安排完毕。
					// (S_EcsNum / s_EcsDvs - 1 > NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					else if (S_EcsNum / s_EcsDvs - 1 >= NoS && M_EcsNum / m_EcsDvs - 1 == NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑥小基站安排一个完备组且刚好安排完毕，中基站安排一个完备组且下一基站组仍然需要安装。
					// S_EcsNum / s_EcsDvs - 1 == NoS && M_EcsNum / m_EcsDvs - 1 > NoS
					//⑨小基站安排一个完备组且下一基站组仍然需要安装，中基站安排一个完备组且下一基站组仍需安排。
					// S_EcsNum / s_EcsDvs - 1 > NoS && M_EcsNum / m_EcsDvs - 1 > NoS
					else if (S_EcsNum / s_EcsDvs - 1 >= NoS && M_EcsNum / m_EcsDvs - 1 > NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if (cdt_s && (!cdt_m)) // cdt_s == T && cdt_m == F
				{
					//10:5:2, 5:3:1
					//①小基站在前面的组中已安排完(完备组)，中基站在前面的组中已安排完。
					// S_EcsNum / s_EcsDvs - 1 < NoS && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS)
					//④小基站在本组中安排一个完备组，刚好安排完；中基站在前面的组中已安排完。
					// S_EcsNum / s_EcsDvs - 1 == NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS)
					if (S_EcsNum / s_EcsDvs - 1 <= NoS && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + 0) * EcsItv;
					}
					//②小基站在前面的组中已安排完(完备组)，中基站在本组中安排余数个基站，刚好安排完。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小基站在前面的组中已安排完(完备组)，中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					else if ((S_EcsNum / s_EcsDvs - 1 < NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑤小基站在本组中安排一个完备组，刚好安排完；中基站在本组中安排余数个基站，刚好安排完
					// (S_EcsNum / s_EcsDvs - 1 == NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS)
					//⑧小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排余数个基站，刚好安排完。
					// (S_EcsNum / s_EcsDvs - 1 > NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS)
					else if ((S_EcsNum / s_EcsDvs - 1 >= NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//⑥小基站在本组中安排一个完备组，刚好安排完；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (S_EcsNum / s_EcsDvs - 1 == NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS)
					//⑨小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (S_EcsNum / s_EcsDvs - 1 > NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS)
					else if ((S_EcsNum / s_EcsDvs - 1 >= NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑦小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在前面的组中已安排完。
					else if ((S_EcsNum / s_EcsDvs - 1 > NoS) && (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + 0) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if ((!cdt_s) && cdt_m) // cdt_s == F && cdt_m == T
				{
					//①小基站在前面的组中已安排完毕；中基站在前面的组中已安排完(完备组)。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (0 + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//②小基站在本组中安排余数个基站，刚好安排完；中基站在前面的组中已安排完(完备组)
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && M_EcsNum / m_EcsDvs - 1 < NoS)
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在前面的组中已安排完毕(完备组)。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS) && (M_EcsNum / m_EcsDvs - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//④小基站在前面的组中已安排完毕；中基站在本组中安排一个完备组，刚好安排完毕。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS)
					//⑦小基站在前面的组中已安排完毕；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 > NoS)
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) && (M_EcsNum / m_EcsDvs - 1 >= NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (0 + m_EcsDvs) * EcsItv;
					}
					//⑤小基站在本组中安排余数个基站，刚好安排完；中基站在本组中安排一个完备组，刚好安排完毕.
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS)
					//⑧小基站在本组中安排余数个基站，刚好安排完；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && (M_EcsNum / m_EcsDvs - 1 > NoS)
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS) && (M_EcsNum / m_EcsDvs - 1 >= NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑥小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排一个完备组，刚好安排完毕。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS) && (M_EcsNum / m_EcsDvs - 1 == NoS)
					//⑨小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					// (int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS) && (M_EcsNum / m_EcsDvs - 1 > NoS)
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS) && (M_EcsNum / m_EcsDvs - 1 >= NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
				else if ((!cdt_s) && (!cdt_m))	// cdt_s == F && cdt_m == F
				{
					//①小基站在前面的组中已安排完毕；中基站在前面的组中已安排完毕。
					if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS) &&
						(int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (0 + 0) * EcsItv;
					}
					//②小基站在前面的组中已安排完毕；中基站在本组中安排余数个基站，刚好安排完。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (0 + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//③小基站在前面的组中已安排完毕；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 < NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (0 + m_EcsDvs) * EcsItv;
					}
					//④小基站在本组中安排余数个基站，刚好安排完；中基站在前面的组中已安排完毕。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + 0) * EcsItv;
					}
					//⑤小基站在本组中安排余数个基站，刚好安排完；中基站在本组中安排余数个基站，刚好安排完。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//⑥小基站在本组中安排余数个基站，刚好安排完；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 == NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (S_EcsNum % s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					//⑦小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在前面的组中已安排完毕。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 < NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + 0) * EcsItv;
					}
					//⑧小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排余数个基站，刚好安排完。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 == NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + M_EcsNum % m_EcsDvs) * EcsItv;
					}
					//⑨小基站在本组中安排一个完备组，且下一基站组中仍需安排；中基站在本组中安排一个完备组，且下一基站组中仍需安排。
					else if ((int((double)S_EcsNum / (double)s_EcsDvs + 1) - 1 > NoS)
						&& (int((double)M_EcsNum / (double)m_EcsDvs + 1) - 1 > NoS))
					{
						l_EcsLoc = (NoS * (EcsNumInSet - 1) * EcsItv) + (NoS - 1) * EcsItv + (id % l_EcsDvs) * EcsItv
							+ (s_EcsDvs + m_EcsDvs) * EcsItv;
					}
					else
						cout << "大型基站 " << ei.m_ecsId << " 的位置生成错误！" << endl;
				}
			}

		}
	}
	else
	{
		cout << "基站 " << ei.m_ecsId << " 的类型判断错误，无法安排其位置！" << endl;
	}

	//s_EcsLoc, m_EcsLoc, l_EcsLoc当中，只有一个为正确数值，其他两个为0
	return s_EcsLoc + m_EcsLoc + l_EcsLoc;
}
//计算基站覆盖范围的函数
int* CalcEcsCA(EcsInfo & ei)
{
	//读入基站位置
	int loc = ei.m_loc;

	int r = ei.m_cr;

	//根据基站的位置算出其工作范围
	//左区间 = left section = lsct, 右区间 = right section = rsct
	int lsct = loc - r;	//基站覆盖范围左区间
	int rsct = loc + r;	//基站覆盖范围右区间
	if (lsct < 0 - r || rsct > L + r)
	{
		if (lsct <= 0 - r)
		{
			lsct = 0;
			cout << "基站: " << ei.m_ecsId << " 的位置在道路起点左边，故左覆盖范围无效。" << endl;
		}
		if (rsct >= L + r)
		{
			rsct = 0;
			cout << "基站: " << ei.m_ecsId << " 的位置在道路终点右边，故右覆盖范围无效。" << endl;
		}
	}

	//arrCA = Array Coverage Area
	//arrCA<左覆盖区间，右覆盖区间> = arrCA<lsct, rsct>
	int arrCA[2];
	arrCA[0] = lsct;
	arrCA[1] = rsct;

	return arrCA;
}


//第二部分：车辆相关
//1.生成车辆信息
void GenerateCarInfo()
{
	//生成并存放车辆初始位置
	UniformDistributionCarIL();
	vector<int>::iterator ILit = vCarIL.begin();
	//生成并存放车辆到达时间
	NormalDistributionCarAT();
	vector<int>::iterator ATit = vCarAT.begin();
	//生成并存放车辆投标系数
	UniformDistributionCarBC();
	vector<double>::iterator BCit = vCarBC.begin();

	//(1)生成小型车辆任务
	for (int n = 0; n < S_CarNum; n++)
	{
		//生成具体的小型车辆信息对象 s_ci = Small CarInfo
		CarInfo s_ci;

		//生成车辆编号
		s_ci.m_carId = n + 1;

		//标识车辆类型
		s_ci.type = "S";

		//生成车辆初始位置
		if (ILit != vCarIL.end())
		{
			s_ci.m_il = (*ILit);	//初始位置范围[0,L]
			ILit++;
		}

		//生成车辆速度
		s_ci.m_v = rand() % 101 + 100;		//车辆速度范围[100,200]m/t

		//生成到达时间
		if (ATit != vCarAT.end())
		{
			s_ci.m_at = (*ATit);	//到达时间范围[1,T]
			ATit++;
		}

		//生成截止时间 : et上限的2倍(FGCS p9) = 2 * 8
		s_ci.m_dt = GenerateCarDT(s_ci);

		//生成任务执行时间
		s_ci.m_et = rand() % 5 + 4;		//执行时间范围: [4,8]

		//生成任务资源需求向量 <vector>
		//s_ci.m_s = small_CarInfo.m_s 为：“小车辆任务”类对象的任务资源需求向量
		//s_ci.m_s = (s_i1, s_i2, s_i3, s_i4) = (CPU, GPU, Memory, Disk)
		//注意 s_ci.size() = RKNum = 4
		for (int r = 0; r < RKNum; r++)		//r: 资源种类个数
		{
			switch (r)
			{
			case 0:     //生成 CPU 的资源请求，即s_i1
				s_ci.m_s.push_back(rand() % 4 + 1);      //CPU的请求都控制在 [1,4] 的区间内
				break;
			case 1:     //生成 GPU 的资源请求，即s_i2
				s_ci.m_s.push_back(rand() % 2 + 1);          //GPU的请求都控制在 [1,2] 的区间内
				break;
			case 2:     //生成 Memory 的资源请求，即s_i3
				s_ci.m_s.push_back(rand() % 5 + 4);     //Memory请求都控制在 [4,8] 的区间内
				break;
			case 3:     //生成 Disk 的资源请求，即s_i4
				s_ci.m_s.push_back(rand() % 33 + 32);  //Disk请求都控制在 [32,64] 的区间内
				break;
			default:
				break;
			}
		}

		//生成投标系数
		if (BCit != vCarBC.end())
		{
			s_ci.m_mu = (*BCit);	//投标系数mu的范围[0.25,4]
			BCit++;
		}

		//计算投标
		s_ci.m_b = CalcCarBid(s_ci);

		//计算车辆的可连接矩阵（部署矩阵）
		s_ci.m_cm = CalcCarCM(s_ci);

		//生成一条小型车辆信息后，要将该基站信息放入到小型车辆容器 s_vCarInfo 中
		s_vCarInfo.push_back(s_ci);

		//存放车辆信息的容器 vCarInfo
		vCarInfo.push_back(s_ci);

	}
	if (S_CarNum == vCarInfo.size())
		cout << "已成功生成 " << S_CarNum << "条小型车辆任务数据" << endl << endl;
	else
		cout << "生成数据失败，生成的小型车辆任务的数量 与 输入的 S_CarNum = " << S_CarNum << " 不相等!" << endl << endl;

	//(2)生成中型车辆任务
	for (int n = S_CarNum; n < S_CarNum + M_CarNum; n++)
	{
		//生成具体的中型车辆信息对象 m_ci = Medium CarInfo
		CarInfo m_ci;

		//生成车辆编号
		m_ci.m_carId = n + 1;

		//标识车辆类型
		m_ci.type = "M";

		//生成车辆初始位置
		if (ILit != vCarIL.end())
		{
			m_ci.m_il = (*ILit);	//初始位置范围[0,L]
			ILit++;
		}

		//生成车辆速度
		m_ci.m_v = rand() % 101 + 100;		//车辆速度范围[100, 200] m / t

		//生成到达时间
		if (ATit != vCarAT.end())
		{
			m_ci.m_at = (*ATit);	//到达时间范围[1,T]
			ATit++;
		}

		//生成截止时间 : et上限的2倍(FGCS p9) = 2 * 16
		m_ci.m_dt = GenerateCarDT(m_ci);

		//生成任务执行时间
		m_ci.m_et = rand() % 9 + 8;		//执行时间范围: [8,16]

		//考虑用一个临时容器 vector<int> 存放“生成的任务资源需求向量”
		//生成任务资源需求向量 <vector>
		//m_ci.m_s = medium_CarInfo.m_s 为：“中型车辆任务”类对象的任务资源需求向量
		//m_ci.m_s = (s_i1, s_i2, s_i3, s_i4) = (CPU, GPU, Memory, Disk)
		for (int r = 0; r < RKNum; r++)		//r: 资源种类个数
		{
			switch (r)
			{
			case 0:     //生成 CPU 的资源请求，即s_i1
				m_ci.m_s.push_back(rand() % 5 + 4);      //CPU的请求都控制在 [4,8] 的区间内
				break;
			case 1:     //生成 GPU 的资源请求，即s_i2
				m_ci.m_s.push_back(rand() % 3 + 2);          //GPU的请求都控制在 [2,4] 的区间内
				break;
			case 2:     //生成 Memory 的资源请求，即s_i3
				m_ci.m_s.push_back(rand() % 9 + 8);     //Memory请求都控制在 [8,16] 的区间内
				break;
			case 3:     //生成 Disk 的资源请求，即s_i4
				m_ci.m_s.push_back(rand() % 65 + 64);  //Disk请求都控制在 [64,128] 的区间内
				break;
			default:
				break;
			}
		}

		//生成投标系数
		if (BCit != vCarBC.end())
		{
			m_ci.m_mu = (*BCit);	//投标系数mu的范围[0.25,4]
			BCit++;
		}

		//计算投标
		m_ci.m_b = CalcCarBid(m_ci);

		//计算车辆的可连接矩阵（部署矩阵）
		m_ci.m_cm = CalcCarCM(m_ci);

		//生成一条中型车辆信息后，要将该基站信息放入到中型车辆容器 m_vCarInfo 中
		m_vCarInfo.push_back(m_ci);

		//存放车辆信息的容器 vCarInfo
		vCarInfo.push_back(m_ci);
	}
	if (M_CarNum == vCarInfo.size() - S_CarNum)
		cout << "已成功生成 " << M_CarNum << "条中型车辆任务数据" << endl << endl;
	else
		cout << "生成数据失败，生成的中型车辆任务的数量 与 输入的 M_CarNum = " << M_CarNum << " 不相等!" << endl << endl;

	//(3)生成大型车辆任务
	for (int n = S_CarNum + M_CarNum; n < tCarNum; n++)
	{
		//生成具体的大型车辆信息对象 l_ci = Large CarInfo
		CarInfo l_ci;

		//生成车辆编号
		l_ci.m_carId = n + 1;

		//标识车辆类型
		l_ci.type = "L";

		//生成车辆初始位置
		if (ILit != vCarIL.end())
		{
			l_ci.m_il = (*ILit);	//初始位置范围[0,L]
			ILit++;
		}

		//生成车辆速度
		l_ci.m_v = rand() % 101 + 100;		//车辆速度范围[100,200]m/t

		//生成到达时间
		if (ATit != vCarAT.end())
		{
			l_ci.m_at = (*ATit);	//到达时间范围[1,T]
			ATit++;
		}

		//生成截止时间 : et上限的2倍(FGCS p9) = 2 * 32
		l_ci.m_dt = GenerateCarDT(l_ci);

		//生成任务执行时间
		l_ci.m_et = rand() % 17 + 16;		//执行时间范围: [16,32]

		//考虑用一个临时容器 vector<int> 存放“生成的任务资源需求向量”
		//生成任务资源需求向量 <vector>
		//l_ci.m_s = Large_CarInfo.m_s 为：“大型车辆任务”类对象的任务资源需求向量
		//l_ci.m_s = (s_i1, s_i2, s_i3, s_i4) = (CPU, GPU, Memory, Disk)
		for (int r = 0; r < RKNum; r++)		//r: 资源种类个数
		{
			switch (r)
			{
			case 0:     //生成 CPU 的资源请求，即s_i1
				l_ci.m_s.push_back(rand() % 9 + 8);			//CPU的请求都控制在 [8,16] 的区间内
				break;
			case 1:     //生成 GPU 的资源请求，即s_i2
				l_ci.m_s.push_back(rand() % 5 + 4);         //GPU的请求都控制在 [4,8] 的区间内
				break;
			case 2:     //生成 Memory 的资源请求，即s_i3
				l_ci.m_s.push_back(rand() % 17 + 16);		//Memory请求都控制在 [16,32] 的区间内
				break;
			case 3:     //生成 Disk 的资源请求，即s_i4
				l_ci.m_s.push_back(rand() % 129 + 128);		//Disk请求都控制在 [128，256] 的区间内
				break;
			default:
				break;
			}
		}

		//生成投标系数
		if (BCit != vCarBC.end())
		{
			l_ci.m_mu = (*BCit);	//投标系数mu的范围[0.25,4]
			BCit++;
		}

		//计算投标
		l_ci.m_b = CalcCarBid(l_ci);

		//计算车辆的可连接矩阵（部署矩阵）
		l_ci.m_cm = CalcCarCM(l_ci);

		//生成一条大型车辆信息后，要将该基站信息放入到大型车辆容器 l_vCarInfo 中
		l_vCarInfo.push_back(l_ci);

		//存放车辆信息的容器 vCarInfo
		vCarInfo.push_back(l_ci);

	}
	if (L_CarNum == vCarInfo.size() - S_CarNum - M_CarNum)
		cout << "已成功生成 " << L_CarNum << "条大型车辆任务数据" << endl << endl;
	else
		cout << "生成数据失败，生成的大型车辆任务的数量 与 输入的 L_CarNum = " << L_CarNum << " 不相等!" << endl << endl;

	cout << "已成功生成 tCarNum = S_CarNum + M_CarNum + L_CarNum = "
		<< S_CarNum << " + " << M_CarNum << " + " << L_CarNum << " = " << tCarNum << " 条车辆任务数据" << endl;
	cout << endl;
}
//(1)生成车辆当前位置的函数（均匀分布）
void UniformDistributionCarIL()
{
	int n = tCarNum;	//车辆总数 N
	int initloc = 0;
	int a = 0, b = L;
	//根据均匀分布随机生成[a,b]之间的随机数
	for (int i = 1; i <= n; i++)
	{
		initloc = a + rand() % (b - a + 1);
		vCarIL.push_back(initloc);
	}
	//打乱vCarIL中的元素顺序，实现随机排序
	random_shuffle(vCarIL.begin(), vCarIL.end());
}
//(2)生成车辆到达时间的函数（正态分布）
void NormalDistributionCarAT()
{
	/* 实现思路：
	 * ①初始化一个vector容器 vAT，存储符合 Normal Distribution 的随机数;
	 * ②打乱 存放车辆到达时间的容器vAT 中的元素顺序，再逐个赋值给ei.at.
	 */
	int n = tCarNum;	//车辆总数 N
	int t = T;	//时间槽 T

	//创建一个 mu(mean) =  T/2 , sigma(sd) = T/6 的正态分布
	double m = (double)t / (double)2;		//设置均值 mean
	double sd = (double)t / (double)6;			//设置标准差 standard deviation
	double mu{ m }, sigma{ sd };
	std::default_random_engine rn((unsigned int)time(NULL));	//随机数生成器 rn = random number
	//使用新标准生成随机数
	//rn.seed((unsigned int)time(NULL));
	std::normal_distribution<> normAT{ mu, sigma };

	//生成N辆车的到达时间 ci.at
	//并把生成的车辆到达时间装入 vCarAT 中
	for (int i = 0; i < n;)
	{
		int at = int(normAT(rn) + 0.5);	//对产生的随机到达时间进行四舍五入
		if (at >= 1 && at <= t)	//生成的到达时间 at 应当满足 1 <= at <= T
		{
			vCarAT.push_back(at);
			i++;
		}
	}

	////测试()
	////打印vCarAT中生成的所有随机数
	//cout << "正态分布normAT : X ~ N(mu,sigma) = X ~ N(" << mu << "," << sigma << ")" << endl;
	//for (vector<int>::iterator ATit = vCarAT.begin(); ATit != vCarAT.end(); ATit++)
	//{
	//	cout << (*ATit) << endl;
	//}
	//
	////计算 at = [mu - sigma, mu + sigma] 的占比，是否在66%左右
	////计算 at = [mu - 2*sigma, mu + 2*sigma] 的占比，是否在95%左右
	//int count = 0;
	//int atsize = vCarAT.size();
	//cout << "atsize = " << atsize << endl;
	//for (vector<int>::iterator ATit = vCarAT.begin(); ATit != vCarAT.end(); ATit++)
	//{
	//	if (((*ATit) > (int)(m - 2*sd)) && ((*ATit) < (int)(m + 2*sd)))
	//	{
	//		count++;
	//	}
	//}
	//cout << "count = " << count << endl;
	//double p = (double)count / (double)atsize;
	//cout << "随机生成的到达时间 at 的范围在 ["<< mu << " - " << sigma << ", "
	//	<< mu << " + "<< sigma << "] 的比例为：" << p << endl;

	//打乱vCarAT中的元素顺序，实现随机排序
	random_shuffle(vCarAT.begin(), vCarAT.end());

}
//(3)生成车辆截止时间的函数
int GenerateCarDT(CarInfo & ci)
{
	int t = T;			//记录最大时间槽
	int at = ci.m_at;	//记录车辆到达时间
	int dt = 0;		//初始化车辆任务截止时间

	//生成截止时间 : et上限的2倍(FGCS p9)
	//截止时间 = 到达时间 + 2 * 执行时间上限 
	//dt = at + 2 * ub(et)
	if (ci.type == "S")		//小型车辆任务的执行时间上限是 8
	{
		if (at + 2 * 8 < t)
			dt = at + 2 * 8;
		else
			dt = t;
	}
	else if (ci.type == "M")	//中型车辆任务的执行时间上限是 16
	{
		if (at + 2 * 16 < t)
			dt = at + 2 * 16;
		else
			dt = t;
	}
	else if (ci.type == "L")	//中型车辆任务的执行时间上限是 32
	{
		if (at + 2 * 32 < t)
			dt = at + 2 * 32;
		else
			dt = t;
	}
	else
		cout << "车辆类型错误，无法生成车辆截止时间！" << endl;

	return dt;
}
//(4)生成投标系数的函数（均匀分布）
void UniformDistributionCarBC()
{
	int n = tCarNum;	//车辆总数 N

	for (int i = 1; i <= n; i++)
	{
		int a = 0, b = 0;
		if (i <= (n / 2))		//一半车辆的投标系数取值在[0.25,1]之间：迫切程度低
		{
			a = 25, b = 100;
		}
		else
		{
			a = 100; b = 400;	//另一半车辆的投标系数取值在[1,4]之间：迫切程度高
		}
		double mu = (double)((double)(a + rand() % (b - a + 1)) / 100);
		vCarBC.push_back(mu);
	}

	//打乱vCarBC中的元素顺序，实现随机排序
	random_shuffle(vCarBC.begin(), vCarBC.end());
}
//(5)计算投标的函数
double CalcCarBid(CarInfo & ci)
{
	//生成投标
	//投标计算公式: bid =  mu_i * e_i * [sigma_(r=1~4) (gamma_r * s_i_r)]

	double mu = double(ci.m_mu);	//读入投标系数
	double et = double(ci.m_et);	//读入执行时间
	double temp = 0;			//单位时间内的所有资源的使用成本
	vector<int> trd(ci.m_s);	//使用 trd 记录车辆的任务资源需求向量

	for (int i = 0, r = 0; i < trd.size() && r < sizeof(gamma) / sizeof(double); i++, r++)
	{
		// i : 任务资源需求向量 m_s 的下标
		// r : 单位时间单位资源成本向量 gamma 的下标
		temp += trd[i] * gamma[r];
	}

	double bid = (double)(mu * et * temp);

	return bid;
}
//(6)计算单独一辆车的可连接矩阵 Calculate Single Car's Connectable Matrix
//车辆的可连接矩阵含义：车辆可以与哪些基站相连(但不一定连接)，从而完成任务。
//一旦 Car i 与 ECS j 相连，表示车辆一定能在 dt 前完成任务，且将资源归还给ECS j 
//那么，Car i 一旦与 ECS j 相连，则一定在 [at, dt-et+1] 的时间范围内做出决定
//为了统一，设可连接矩阵 CM_[M * T]，即 M 行 T 列，M个基站，T个时间槽
vector<vector<bool>> CalcCarCM(CarInfo & ci)
{
	int m = tEcsNum;			//矩阵的行数，有“基站数量”的行
	int t = T;					//矩阵的列数，有“时间槽个数”的列

	vector<vector<bool>> vCM(m, vector<bool>(t, false));

	////测试：初始化 二维vector 一共有 m 行 t 列
	//int r = cm.size();
	//int c = cm[0].size();
	//cout << "二维矩阵初始化为：" << endl;
	//for (vector<vector<bool>>::iterator rit = vCM.begin(); rit != vCM.end(); rit++)
	//{
	//	//遍历里面的vector<bool>，列：时间槽
	//	for (vector<bool>::iterator cit = (*rit).begin(); cit != (*rit).end(); cit++)
	//	{
	//		cout << (*cit) << " ";
	//	}
	//	cout << endl;
	//}
	//cout << "二维矩阵 vCM 的行数为：" << r << endl;
	//cout << "二维矩阵 vCM 的列数为：" << c << endl;
	//cout << endl;

	vector<EcsInfo>::iterator eit = vEcsInfo.begin();	//访问vEcsInfo 容器(存放EcsInfo信息)的迭代器
	vector<vector<bool>>::iterator rit = vCM.begin();	//访问 vCM 容器的迭代器，即按行访问矩阵

	//1.根据基站位置算出各基站工作范围(已完成)	
	//2.获取当前车辆位置，判断车辆是否在基站工作范围内
	int cl = ci.m_il;				//获取当前车辆位置
	int v = ci.m_v;					//获取车辆速度(匀速)
	int at = ci.m_at - 1;			//当前时间，矩阵下标从 0 开始，故 - 1
	int dt = ci.m_dt;				//任务截止时间，在截止时间点时，也可以执行任务，故不 - 1
	int et = ci.m_et;				//获取车辆任务的执行时间
	int lst = dt - et + 1;			//如果车辆和基站建立连接，必须在时间槽范围 last submit time = lst = [at, dt-et+1] 内建立连接

	//思路
	//对于矩阵的一行：考察车辆在不同时间槽能否连接基站
	if (at <= lst)	//还有机会完成任务，检查是否能连接基站
	{
		for (; rit != vCM.end() && eit != vEcsInfo.end(); rit++, eit++)
		{
			//从到达时间的时间槽开始，计算车辆的可连接矩阵
			//考虑两点：
			//1.车辆当前位置是否在基站覆盖范围内 if(条件)
			//2.若车辆成功连接基站，是否能在任务截止时间前(dt - et + 1)完成任务  cit != (*rit).begin() + (dt - et + 1)
			//cit++ == 列数++ == 时间槽++ == t++
			for (vector<bool>::iterator cit = (*rit).begin() + at; cit != (*rit).begin() + lst; cit++)
			{
				//cout << cit - (*rit).begin() << ' ' << at << ' ' << lst << endl;
				//2158 2158 2154; 2159 2158 2154; 2160 2158 2154
				//错误原因：at > lst
				if (cl >= eit->m_aCA[0] && cl <= eit->m_aCA[1] && cl <= L)
				{
					//想办法将 基站编号(eit->m_ecsId - 1) 与 矩阵行号 *rit 联系起来
					(*cit) = true;
				}
				else
				{
					(*cit) = false;
				}
				cl += v;	//车辆当前位置随着t的改变而改变
			}
			cl = ci.m_il;			//重置车辆位置 cl
			at = ci.m_at - 1;		//重置时间点
		}
	}
	else	//无法按时完成任务
	{
		for (; rit != vCM.end() && eit != vEcsInfo.end(); rit++, eit++)
		{
			for (vector<bool>::iterator cit = (*rit).begin() + at; cit != (*rit).begin() + T; cit++)
			{
				(*cit) = false;
			}
		}
	}

	////测试：打印车辆的部署矩阵
	//cout << "车辆 " << ci.m_carId << " 的可连接矩阵如下：" << endl;
	////遍历外面的vector<vector<bool>>，行：基站个数
	//for (vector<vector<bool>>::iterator rit = vCM.begin(); rit != vCM.end(); rit++)
	//{
	//	//遍历里面的vector<bool>，列：时间槽
	//	for (vector<bool>::iterator cit = (*rit).begin(); cit != (*rit).end(); cit++)
	//	{
	//		cout << (*cit) << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	//3.生成各车辆的可连接矩阵，再将可连接矩阵赋值给车辆中的属性：可连接矩阵 m_cm 
	return vCM;

}


//第三部分：保存到本地
//1.将基站信息保存到本地
//道路长度 L = 10000 m，一共设置10个基站
void SaveEcsInfo()
{
	ofstream ofs;
	//展示给用户看的基站信息汇总
	//string EcsInfoFile_show = "../data/1GenerateData/exp1_exp2/EcsInfo_10_0_0/EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";;
	string EcsInfoFile_show = "../data/1GenerateData/exp3/EcsInfo_9_0_1/EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";;
	ofs.open(EcsInfoFile_show, ios::out | ios::trunc);	//如果文件存在，先删除，再创建
	ofs << "ECS_Id" << '\t' << "Type" << '\t' << "CoverageRadius(m)" << '\t' << "Location(m)" << '\t' << "CoverageArea(m)" << '\t' << "ResourceCapacity" << endl;
	for (vector<EcsInfo>::iterator it = vEcsInfo.begin(); it != vEcsInfo.end(); it++)
	{
		ofs << it->m_ecsId << "\t";						//基站编号
		ofs << it->type << "\t";						//基站类型 S/M/L
		ofs << it->m_cr << "\t\t";						//基站工作半径 CoverageRadius	
		ofs << it->m_loc << "\t\t";						//基站位置 Location
		ofs << "[" << it->m_aCA[0] << "," << it->m_aCA[1] << "]\t";	//基站覆盖范围 CoverageArea
		ofs << "<";												//基站资源容量 ResourcesCapacity
		for_each(it->m_rc.begin(), it->m_rc.end(), [&](const int val) {WriteEcsRC(ofs, val); });
		ofs << ">\t" << endl;
	}
	ofs.close();

	//将所有基站的信息都输出到同一个.txt文件中保存，供算法输入使用
	//string EcsInfoFile_input = "../data/1GenerateData/exp1_exp2/EcsInfo_10_0_0/data_EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";
	string EcsInfoFile_input = "../data/1GenerateData/exp3/EcsInfo_9_0_1/data_EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";
	ofs.open(EcsInfoFile_input, ios::out | ios::trunc);
	for (vector<EcsInfo>::iterator it = vEcsInfo.begin(); it != vEcsInfo.end(); it++)
	{
		ofs << it->m_ecsId << " ";					//基站编号
		ofs << it->type << " ";						//基站类型 S/M/L
		ofs << it->m_cr << " ";						//基站工作半径 CoverageRadius
		ofs << it->m_loc << " ";					//基站位置 Location	
		ofs << it->m_aCA[0] << " " << it->m_aCA[1] << " ";	//基站覆盖范围 CoverageArea
		for_each(it->m_rc.begin(), it->m_rc.end(), [&](const int val) {WriteEcsRC(ofs, val); });	//基站资源容量 ResourcesCapacity
		ofs << endl;
	}
	ofs.close();

	cout << "已成功将 " << tEcsNum << "条基站信息写入EcsInfo.txt中。" << endl;
	cout << "其中，小型基站数量为：" << S_EcsNum << ","
		<< "中型基站数量为：" << M_EcsNum << ","
		<< "大型基站数量为：" << L_EcsNum << "." << endl;
	cout << endl;
}
//(1)封装一个函数用来输出资源容量向量
void WriteEcsRC(ofstream& ofs, int val)
{
	ofs << val << " ";
}
//2.将车辆信息保存到本地
void SaveCarInfo()
{
	ofstream ofs;
	//1. 展示给用户看的车辆信息
	//1.1 展示给用户看的车辆信息(除可连接矩阵CM)汇总
	//string CarInfoFile_show = "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/CarInfo_" + to_string(S_CarNum) + "_" + to_string(M_CarNum) + "_" + to_string(L_CarNum) + ".txt";
	string CarInfoFile_show = "../data/1GenerateData/exp3/EcsInfo_9_0_1/CarInfo_" + to_string(S_CarNum) + "_" + to_string(M_CarNum) + "_" + to_string(L_CarNum) + ".txt";
	ofs.open(CarInfoFile_show, ios::out | ios::trunc);	//如果文件存在，先删除，再创建
	ofs << "Car_Id" << '\t' << "Type" << '\t' << "InitLoc(m)" << '\t' << "v(m/t)" << '\t' << "AT" << '\t' << "DT" << '\t' << "ET" << '\t' << "TaskResourceDemand" << '\t' << "Bid" << '\t' << "BidCoefficient" << endl;
	//将每辆车的任务信息保存到 CarInfo.txt 中
	for (vector<CarInfo>::iterator it = vCarInfo.begin(); it != vCarInfo.end(); it++)
	{
		//数据格式：编号   类型   出发点   速度 到达时间 截止时间 执行时间 任务资源需求			投标	投标系数
		//数据格式：CarId  Type   InitLoc   v      at       dt       et    TaskResourceDemand   b		mu
		ofs << it->m_carId << "\t";		//车辆编号：表示这是第几辆车子 
		ofs << it->type << "\t";		//车辆/任务类型：S/M/L 
		ofs << it->m_il << "\t";		//车辆初始位置：Initial Location
		ofs << it->m_v << "\t";			//车辆行驶速度：Velocity
		ofs << it->m_at << "\t";		//车辆到达时间/产生任务时间：Arrival Time
		ofs << it->m_dt << "\t";		//任务截止时间：Deadline Time
		ofs << it->m_et << "\t";		//执行任务时间：Execution Time
		ofs << "<";						//任务资源请求：Task Resource Demand
		for_each(it->m_s.begin(), it->m_s.end(), [&](const int val) {WriteCarTR(ofs, val); });
		ofs << ">\t\t";
		ofs << it->m_b << "\t";
		ofs << it->m_mu << endl;		//投标系数<< endl;			//投标
	}
	ofs << endl;
	ofs.close();

	////1.2 展示给用户看的车辆 可连接矩阵 信息（数据量过大，不再展示）
	 
	//string Car_CM_show = "../data/1GenerateData/CarInfo_40000_40000_40000/Car_CM_" + to_string(S_CarNum) + "_" + to_string(M_CarNum) + "_" + to_string(L_CarNum) + "-" + to_string(ExeNum) + ".txt";
	//ofs.open(Car_CM_show, ios::out | ios::trunc);	//如果文件存在，先删除，再创建
	//for (vector<CarInfo>::iterator it = vCarInfo.begin(); it != vCarInfo.end(); it++)
	//{
	//	//数据格式：编号   类型   出发点   速度 到达时间 截止时间 执行时间 可连接矩阵
	//	//数据格式：CarId  Type   InitLoc   V      AT       DT       ET		   CM
	//	//			可连接矩阵
	//	ofs << "CarId:" << it->m_carId << " ";	//车辆编号：表示这是第几辆车子 
	//	ofs << "Type:" << it->type << " ";		//车辆/任务类型：S/M/L 
	//	ofs << "InitLoc(m):" << it->m_il << " ";	//车辆初始位置：Initial Location
	//	ofs << "V(m/s):" << it->m_v << " ";			//车辆行驶速度：Velocity
	//	ofs << "AT:" << it->m_at << " ";		//车辆到达时间/产生任务时间：Arrive Time
	//	ofs << "DT:" << it->m_dt << " ";		//完成任务截止时间：Deadline Time
	//	ofs << "ET:" << it->m_et << " ";		//执行任务时间：Execution Time
	//	ofs << "CM:" << endl;
	//	for (vector<vector<bool>>::iterator rit = it->m_cm.begin(); rit != it->m_cm.end(); rit++)
	//	{
	//		//遍历里面的vector<bool>，列：时间槽
	//		for (vector<bool>::iterator cit = (*rit).begin(); cit != (*rit).end(); cit++)
	//		{
	//			ofs << (*cit) << " ";
	//		}
	//		ofs << endl;
	//	}
	//	ofs << endl;
	//}
	//ofs.close();

	//2. 供算法调入使用的车辆信息
	//把车辆信息（包括可连接矩阵），按类型(S / M / L)分别写入不同的.txt文件中，供算法输入使用
	SaveCarInfoAsInput(s_vCarInfo, "S", s_vCarInfo.size());	//保存小型车辆任务信息
	SaveCarInfoAsInput(m_vCarInfo, "M", m_vCarInfo.size());	//保存中型车辆任务信息
	SaveCarInfoAsInput(l_vCarInfo, "L", l_vCarInfo.size());	//保存大型车辆任务信息

	cout << "已成功将 " << tCarNum << "个车辆任务写入CarInfo.txt中。" << endl;
	cout << "其中，小型车辆任务数目为：" << S_CarNum << ","
		<< "中型车辆任务数目为：" << M_CarNum << ","
		<< "大型车辆任务数目为：" << L_CarNum << "." << endl;
	cout << endl;

}
//(1)将任务资源需求向量写入文档中
void WriteCarTR(ofstream & ofs, int val)
{
	ofs << val << " ";
}
//(2)封装一个函数，把车辆的各个属性保存到同一个文件中，供算法调入使用
void SaveCarInfoAsInput(vector<CarInfo>& v, string type, int carnum)
{
	ofstream ofs;
	//保存车辆信息(除可连接矩阵CM)，供算法调入使用
	//string CarInfoFile = "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_CarInfo_" + type + "_" + to_string(carnum) + ".txt";	//实验一、实验二使用
	string CarInfoFile = "../data/1GenerateData/exp3/EcsInfo_9_0_1/data_CarInfo_" + type + "_" + to_string(carnum) + ".txt";	//实验三使用
	ofs.open(CarInfoFile, ios::out | ios::trunc);
	for (vector<CarInfo>::iterator it = v.begin(); it != v.end(); it++)
	{
		//数据格式：编号   类型   出发点   速度 到达时间 截止时间 执行时间 任务资源需求			投标	投标系数
		//数据格式：CarId  Type   InitLoc   v      at       dt       et    TaskResourceDemand   b		mu
		ofs << it->m_carId << " ";	//车辆编号：表示这是第几辆车子 
		ofs << it->type << " ";		//车辆/任务类型：S/M/L 
		ofs << it->m_il << " ";		//车辆初始位置：Initial Location
		ofs << it->m_v << " ";		//车辆行驶速度：Velocity
		ofs << it->m_at << " ";		//车辆到达时间/产生任务时间：Arrive Time
		ofs << it->m_dt << " ";		//任务截止时间：Deadline Time
		ofs << it->m_et << " ";		//执行任务时间：Execution Time			
		for_each(it->m_s.begin(), it->m_s.end(), [&](const int val) {WriteCarTR(ofs, val); });	//任务资源需求：TaskResourceDemand
		ofs << it->m_b << " ";		//投标：Bid
		ofs << it->m_mu << endl;	//投标系数：BidCoefficient
	}
	ofs.close();

	//保存车辆的 可连接矩阵：ConnectableMatrix，供算法调入使用
	//string CarCMFile = "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_Car_CM_" + type + "_" + to_string(carnum) + ".txt";	//实验一、实验二使用
	string CarCMFile = "../data/1GenerateData/exp3/EcsInfo_9_0_1/data_Car_CM_" + type + "_" + to_string(carnum) + ".txt";	//实验三使用
	ofs.open(CarCMFile, ios::out | ios::trunc);
	for (vector<CarInfo>::iterator it = v.begin(); it != v.end(); it++)
	{
		for (vector<vector<bool>>::iterator rit = it->m_cm.begin(); rit != it->m_cm.end(); rit++)
		{
			//遍历里面的vector<bool>，列：时间槽
			for (vector<bool>::iterator cit = (*rit).begin(); cit != (*rit).end(); cit++)
			{
				ofs << (*cit) << " ";
			}
			ofs << endl;
		}
		ofs << endl;
	}
	ofs.close();
	
}

void Modeling()
{
	cout << "一维道路长度为：L =  " << L << " m。时间槽[1, T] = [1, " << T << "]." << endl;
	cout << endl;
}

int main()
{
	//旧标准：搭配 rand 使用才有效
	srand((unsigned)time(NULL));
	
    Modeling(); //建模

	//清空使用过的容器
	vEcsInfo.clear(), s_vEcsInfo.clear(), m_vEcsInfo.clear(), l_vEcsInfo.clear();
	vCarInfo.clear(), s_vCarInfo.clear(), m_vCarInfo.clear(), l_vCarInfo.clear();
	vCarAT.clear();

	//第一部分：基站相关
	//1.生成基站信息
	GenerateEcsInfo();

	//第二部分：车辆相关
	//1.生成车辆信息
	GenerateCarInfo();

	//第三部分：保存到本地
	//1.将基站信息保存到本地
	SaveEcsInfo();
	//2.将车辆信息保存到本地
	SaveCarInfo();

    system("pause");
    return 0;
}
