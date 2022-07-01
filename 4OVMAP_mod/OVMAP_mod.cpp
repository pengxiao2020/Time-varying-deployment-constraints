// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "OVMAP_mod.h"

//第一步：读入数据
void LoadEcsInfo(string EcsInfofile)
{
	ifstream ifs_ECS(EcsInfofile);	//一次性读入所有类型的基站信息	
	for (int j = 0; j < M; j++)	//读入基站信息：资源容量
	{
		EcsInfo* ecs = new EcsInfo;	//临时 EcsInfo 对象
		//先读入具体值到对象的属性中，再将该对象放入vector中
		ifs_ECS >> ecs->id;
		ifs_ECS >> ecs->type;
		ifs_ECS >> ecs->CR;
		ifs_ECS >> ecs->loc;
		ifs_ECS >> ecs->CA[0];
		ifs_ECS >> ecs->CA[1];
		ifs_ECS >> ecs->RC->cpu;
		ifs_ECS >> ecs->RC->gpu;
		ifs_ECS >> ecs->RC->memory;
		ifs_ECS >> ecs->RC->disk;
		vEcsInfo.push_back(*ecs);
		delete ecs;
	}
	ifs_ECS.close();

	int count_S_ECS = 0, count_M_ECS = 0, count_L_ECS = 0;
	for (vector<EcsInfo>::iterator ecsit = vEcsInfo.begin(); ecsit != vEcsInfo.end(); ecsit++)
	{
		if (ecsit->type == "S")
			count_S_ECS++;
		else if (ecsit->type == "M")
			count_M_ECS++;
		else if (ecsit->type == "L")
			count_L_ECS++;
		else
			cout << "读入的基站类型错误, 请重新运行程序，再读入基站信息文件！" << endl;
	}
	if (count_S_ECS != 0)
	{
		cout << "成功读入小型基站信息：" << count_S_ECS << " 条！" << endl;
	}
	if (count_M_ECS != 0)
	{
		cout << "成功读入中型基站信息：" << count_M_ECS << " 条！" << endl;
	}
	if (count_L_ECS != 0)
	{
		cout << "成功读入大型基站信息：" << count_L_ECS << " 条！" << endl;
	}
}

void LoadCarInfo(string CarInfofile, string CarCMfile, vector<CarInfo>& Car, int CarNum)
{
	ifstream ifs_Car(CarInfofile);		//读入车辆任务信息
	ifstream ifs_Car_CM(CarCMfile);		//读入车辆可连接矩阵
	for (int i = 0; i < CarNum; i++)	//读入车辆信息
	{
		CarInfo* car = new CarInfo;
		ifs_Car >> car->id;
		ifs_Car >> car->type;
		ifs_Car >> car->InitLoc;
		ifs_Car >> car->v;
		ifs_Car >> car->at;
		ifs_Car >> car->dt;
		ifs_Car >> car->et;
		ifs_Car >> car->TRD->cpu;
		ifs_Car >> car->TRD->gpu;
		ifs_Car >> car->TRD->memory;
		ifs_Car >> car->TRD->disk;
		ifs_Car >> car->bid;
		ifs_Car >> car->mu;
		for (int j = 0; j < M; j++)
		{
			for (int t = 0; t < T; t++)
			{
				bool tmp;
				ifs_Car_CM >> tmp;
				car->CM[j][t] = tmp;
			}
		}
		Car.push_back(*car);
		delete car;
	}
	ifs_Car.close();
	ifs_Car_CM.close();

	/*int count_S_Car = 0, count_M_Car = 0, count_L_Car = 0;
	for (vector<CarInfo>::iterator carit = Car.begin(); carit != Car.end(); carit++)
	{
		if (carit->type == "S")
			count_S_Car++;
		else if (carit->type == "M")
			count_M_Car++;
		else if (carit->type == "L")
			count_L_Car++;
		else
			cout << "读入的车辆类型错误，请重新运行程序，再读入正确的车辆任务信息！" << endl;
	}
	if (count_S_Car != 0)
	{
		cout << "成功读入小型车辆任务信息：" << count_S_Car << " 条！" << endl;
	}
	if (count_M_Car != 0)
	{
		cout << "成功读入中型车辆任务信息：" << count_M_Car << " 条！" << endl;
	}
	if (count_L_Car != 0)
	{
		cout << "成功读入大型车辆任务信息：" << count_L_Car << " 条！" << endl;
	}*/
}

//第二步：每个时间槽执行一次 OVMAP_mod 算法
void OVMAP_mod(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& Car)
{
	//测试：记录每次运行 OTRAP 的准备工作 所用时间
	time_t tPreWork_begin, tPreWork_end;
	tPreWork_begin = clock();	//准备工作开始计时

	//0.每次运行 OTRAP 前的准备工作
	cts_AllocResult.clear();

	//1.回收完成任务的车辆使用的资源
	time_t tReturnResource_begin, tReturnResource_end;	//统计 归还资源 所用的时间
	tReturnResource_begin = clock();

	if (!BeAllocatedCar.empty())
	{
		//对于 et = 1 的车辆，在下一个时间槽 cts+1 将其 accom_flag 置 ture 并回收资源
		//对于 et > 1 的车辆，在当前时间槽 cts 将其 accom_flag 置 ture 并回收资源
		//for (int i = 0; i < BeAllocatedCar.size(); i++)
		for (vector<CarInfo>::iterator BACit = BeAllocatedCar.begin(); BACit != BeAllocatedCar.end();)
		{
			//若按照算法中 使用 == 来判断，则不能及时回收 et = 1 的车辆使用的资源，故使用 >=
			if (cts >= (BACit->bat + BACit->et - 1))	//如果车辆完成任务
			{
				////测试：是否正确根据 判断条件 回收“完成任务的车辆”使用的资源(成功)
				//cout << "车辆 BeAllocatedCar[" << i << "].id = " << BeAllocatedCar[i].id
				//	<< " type = " << BeAllocatedCar[i].type
				//	<< " at = " << BeAllocatedCar[i].at
				//	<< " dt = " << BeAllocatedCar[i].dt
				//	<< " et = " << BeAllocatedCar[i].et
				//	<< " TR = [" << BeAllocatedCar[i].TR->cpu << ", " << BeAllocatedCar[i].TR->gpu << ", " << BeAllocatedCar[i].TR->memory << ", " << BeAllocatedCar[i].TR->disk << "]"
				//	<< " bid = " << BeAllocatedCar[i].bid
				//	<< " bat = " << BeAllocatedCar[i].bat
				//	<< " ConnectTo = " << BeAllocatedCar[i].ConnectTo << endl;
				//cout << "因为当前时间槽 t >= bat + et - 1 <=> " << cts <<" >= "<< BeAllocatedCar[i].bat << " + " << BeAllocatedCar[i].et << " - 1 ";
				//cout << "故车辆 BeAllocatedCar[" << i << "] 已完成任务，向 ECS[" << BeAllocatedCar[i].ConnectTo << "] 归还资源并离开集合 BeAllocatedCar[] " << endl;
				BACit->accom_flag = true;	//完成标志置1
				//for (int j = 0; j < ECS.size(); j++)	//找出 i 与哪个基站相连
				for (auto ECSit = ECS.begin(); ECSit != ECS.end(); ECSit++)
				{
					if (BACit->ConnectTo == ECSit->id)	//归还资源
					{
						////测试 : 是否正确归还资源（成功）
						//cout << "归还资源前：";
						//cout << "ECS[" << ECS[j].id << "].RC->cpu = " << ECS[j].RC->cpu;
						//cout << " ECS[" << ECS[j].id << "].RC->gpu = " << ECS[j].RC->gpu;
						//cout << " ECS[" << ECS[j].id << "].RC->memory = " << ECS[j].RC->memory;
						//cout << " ECS[" << ECS[j].id << "].RC->disk = " << ECS[j].RC->disk;
						//cout << endl;

						ECSit->RC->cpu += BACit->TRD->cpu;
						ECSit->RC->gpu += BACit->TRD->gpu;
						ECSit->RC->memory += BACit->TRD->memory;
						ECSit->RC->disk += BACit->TRD->disk;

						/*cout << "归还资源后：";
						cout << "ECS[" << ECS[j].id << "].RC->cpu = " << ECS[j].RC->cpu;
						cout << " ECS[" << ECS[j].id << "].RC->gpu = " << ECS[j].RC->gpu;
						cout << " ECS[" << ECS[j].id << "].RC->memory = " << ECS[j].RC->memory;
						cout << " ECS[" << ECS[j].id << "].RC->disk = " << ECS[j].RC->disk;
						cout << endl;*/
						break;
					}
				}
				BACit = BeAllocatedCar.erase(BACit);		//踢出完成任务的车辆
			}
			else
			{
				BACit++;
			}
		}
	}

	tReturnResource_end = clock();
	ReturnResource_RunTime += static_cast<double>(tReturnResource_end - tReturnResource_begin) / CLOCKS_PER_SEC * 1000;

	//2.清除过期的车辆任务请求
	time_t tDelOvertimeTask_begin, tDelOvertimeTask_end;	//统计 删除过期车辆任务 所用的时间
	tDelOvertimeTask_begin = clock();

	if (!UnAllocatedCar.empty())
	{
		//for (int i = 0; i < UnAllocatedCar.size(); i++)
		for (vector<CarInfo>::iterator UACit = UnAllocatedCar.begin(); UACit != UnAllocatedCar.end();)
		{
			if (cts > (UACit->dt - UACit->et + 1))
			{
				////测试 : 能否正确根据“判断条件”踢出过期车辆任务(成功)
				//cout << "车辆 UnAllocatedCar[" << i << "].id = " << UnAllocatedCar[i].id
				//	<< " type = " << UnAllocatedCar[i].type
				//	<< " at = " << UnAllocatedCar[i].at
				//	<< " dt = " << UnAllocatedCar[i].dt
				//	<< " et = " << UnAllocatedCar[i].et
				//	<< " TR = [" << UnAllocatedCar[i].TR->cpu << ", " << UnAllocatedCar[i].TR->gpu << ", " << UnAllocatedCar[i].TR->memory << ", " << UnAllocatedCar[i].TR->disk << "]"
				//	<< " bid = " << UnAllocatedCar[i].bid << endl;
				//cout << "因为当前时间槽 t > dt - et + 1 <=> " << cts << " > " << UnAllocatedCar[i].dt << " - " << UnAllocatedCar[i].et << " + 1 ";
				//cout << "即车辆 UnAllocatedCar[" << i << "] 已过任务有效期，故将其踢出集合 UnAllocatedCar[]" << endl;
				UACit = UnAllocatedCar.erase(UACit);	//踢出任务时间过期的车辆
			}
			else
			{
				UACit++;
			}
		}
	}

	tDelOvertimeTask_end = clock();
	DelOvertimeTask_RunTime += static_cast<double>(tDelOvertimeTask_end - tDelOvertimeTask_begin) / CLOCKS_PER_SEC * 1000;

	//3.将新到达的车辆的类型（信息）全部并入容器 UnAllocatedCar
	time_t tAddArrivedCar_begin, tAddArrivedCar_end;	//统计 删除过期车辆任务 所用的时间
	tAddArrivedCar_begin = clock();

	if (!Car.empty())
	{
		//for (int i = 0; i < Car.size(); i++)
		for (vector<CarInfo>::iterator Cit = Car.begin(); Cit != Car.end();)
		{
			//仅并入到达时间 at 与当前时间槽 cts 相等的车辆信息（类型）
			if (Cit->at == cts)
			{
				UnAllocatedCar.push_back(*Cit);	//将 at == cts 且未得到分配的车辆 放入容器 UnAllocatedCar
				Cit = Car.erase(Cit);			//将已经放入 UnAllocatedCar 的车辆 踢出 Car
			}
			else
			{
				Cit++;
			}
		}
	}

	tAddArrivedCar_end = clock();
	AddArrivedCar_RunTime += static_cast<double>(tAddArrivedCar_end - tAddArrivedCar_begin) / CLOCKS_PER_SEC * 1000;

	IsEcsRCEmpty();		//判断 所有基站容量是否为空

	if (UnAllocatedCar.empty() || EcsRCEmpty)	//不执行OTRAP算法
	{
		//if(UnAllocatedCar.empty())
			//cout << "当前时间槽 t = " << cts << ", 不存在未被分配的车辆(UnAllocatedCar.empty() = true)，故不执行OTRAP算法！" << endl;
		//else
			//cout << "当前时间槽 t = " << cts << ", 没有可用的资源向量(EcsRCEmpty = true)，故不执行OTRAP算法！" << endl;

		tPreWork_end = clock();		//准备工作结束计时
		PreWork_RunTime += static_cast<double>(tPreWork_end - tPreWork_begin) / CLOCKS_PER_SEC * 1000;

		return;
	}
	else		//执行OTRAP算法
	{
		vector<EcsInfo> vEcsInfo_cp(ECS);	//ECS副本
		vector<CarInfo> BeAllocatedCar_cp(BeAllocatedCar);	//BeAllocatedCar副本
		vector<CarInfo> UnAllocatedCar_cp(UnAllocatedCar);	//UnAllocatedCar副本

		////测试：打印副本 vEcsInfo_cp, UnAllocatedCar_cp, BeAllocatedCar_cp(已通过)
		//cout << "副本-基站 信息如下：" << endl;
		//for (int j = 0; j < vEcsInfo_cp.size(); j++)
		//{
		//	cout << "基站：id = " << vEcsInfo_cp[j].id;
		//	cout << " type = " << vEcsInfo_cp[j].type;
		//	cout << " CR = " << vEcsInfo_cp[j].CR;
		//	cout << " loc = " << vEcsInfo_cp[j].loc;
		//	cout << " CA = [" << vEcsInfo_cp[j].CA[0] << "," << vEcsInfo_cp[j].CA[1] << "] ";
		//	cout << " RC = <" << vEcsInfo_cp[j].RC->cpu << " " << vEcsInfo_cp[j].RC->gpu << " " << ECS[j].RC->memory << " " << vEcsInfo_cp[j].RC->disk << "> ";
		//	cout << endl;
		//}
		//cout << endl;
		//cout << "副本-已分配车辆容器 BeAllocatedCar_cp 的车辆信息如下：" << endl;
		//for (int i = 0; i < BeAllocatedCar_cp.size(); i++)
		//{
		//	cout << "车辆 " << i << " : id = " << BeAllocatedCar_cp[i].id
		//		<< " type = " << BeAllocatedCar_cp[i].type
		//		<< " at = " << BeAllocatedCar_cp[i].at
		//		<< " dt = " << BeAllocatedCar_cp[i].dt
		//		<< " et = " << BeAllocatedCar_cp[i].et
		//		<< " TR[4] = [" << BeAllocatedCar_cp[i].TR->cpu << ", " << BeAllocatedCar_cp[i].TR->gpu << ", " << BeAllocatedCar_cp[i].TR->memory << ", " << BeAllocatedCar_cp[i].TR->disk << "] "
		//		<< " bid = " << BeAllocatedCar_cp[i].bid
		//		<< " bat = " << BeAllocatedCar[i].bat
		//		<< " ConnectTo = " << BeAllocatedCar[i].ConnectTo << endl;
		//		/*<< " CM = " << endl;
		//	for (int j = 0; j < M; j++)
		//	{
		//		for (int t = 0; t < T; t++)
		//		{
		//			cout << UnAllocatedCar_cp[i].CM[j][t] << " ";
		//		}
		//		cout << endl;
		//	}*/
		//	cout << endl;
		//}
		//cout << endl;
		//cout << "副本-未分配车辆容器 UnAllocatedCar_cp 的车辆信息如下：" << endl;
		//for (int i = 0; i < UnAllocatedCar_cp.size(); i++)
		//{
		//	cout << "车辆 " << i << " : id = " << UnAllocatedCar_cp[i].id << " type = " << UnAllocatedCar_cp[i].type
		//		<< " InitLoc(m) = " << UnAllocatedCar_cp[i].InitLoc << " v(m/s) = " << UnAllocatedCar_cp[i].v
		//		<< " at = " << UnAllocatedCar_cp[i].at << " dt = " << UnAllocatedCar_cp[i].dt << " et = " << UnAllocatedCar_cp[i].et
		//		<< " TR[4] = [" << UnAllocatedCar_cp[i].TR->cpu << ", " << UnAllocatedCar_cp[i].TR->gpu << ", " << UnAllocatedCar_cp[i].TR->memory << ", " << UnAllocatedCar_cp[i].TR->disk << "] "
		//		<< " bid = " << UnAllocatedCar_cp[i].bid << endl;
		//		/*<< " CM = "<< endl;
		//	for (int j = 0; j < M; j++)
		//	{
		//		for (int t = 0; t < T; t++)
		//		{
		//			cout << UnAllocatedCar_cp[i].CM[j][t] << " ";
		//		}
		//		cout << endl;
		//	}
		//	cout << endl;*/
		//}
		//cout << endl;

		tPreWork_end = clock();		//准备工作结束计时
		PreWork_RunTime += static_cast<double>(tPreWork_end - tPreWork_begin) / CLOCKS_PER_SEC * 1000;

		time_t tAlloc_begin, tAlloc_end;
		tAlloc_begin = clock();		//分配函数开始计时

		OVMAP_mod_ALLOC(cts, ECS, BeAllocatedCar, UnAllocatedCar);

		tAlloc_end = clock();		//分配函数结束计时
		ALLOC_RunTime += static_cast<double>(tAlloc_end - tAlloc_begin) / CLOCKS_PER_SEC * 1000;

		////测试
		//cout << "当前时间槽为 t = " << cts << endl;
		//cout << "执行OTRAP_ALLOC后，容器 BeAllocatedCar 中的车辆信息如下：" << endl;
		//for (int i = 0; i < BeAllocatedCar.size(); i++)
		//{
		//	cout << "车辆 " << i << " : id = " << BeAllocatedCar[i].id << " type = " << BeAllocatedCar[i].type
		//		<< " InitLoc = " << BeAllocatedCar[i].InitLoc
		//		<< " v = " << BeAllocatedCar[i].v
		//		<< " at = " << BeAllocatedCar[i].at << " dt = " << BeAllocatedCar[i].dt << " et = " << BeAllocatedCar[i].et
		//		<< " TR[4] = [" << BeAllocatedCar[i].TR->cpu << ", " << BeAllocatedCar[i].TR->gpu << ", " << BeAllocatedCar[i].TR->memory << ", " << BeAllocatedCar[i].TR->disk << "] "
		//		<< " bid = " << BeAllocatedCar[i].bid
		//		<< " ConnectTo = " << BeAllocatedCar[i].ConnectTo
		//		<< " bat = " << BeAllocatedCar[i].bat << endl;
		//}
		//cout << endl;
		//cout << "执行OTRAP_ALLOC后，容器 UnAllocatedCar 中的车辆信息如下：" << endl;
		//for (int i = 0; i < UnAllocatedCar.size(); i++)
		//{
		//	cout << "车辆 " << i << " : id = " << UnAllocatedCar[i].id
		//		<< " type = " << UnAllocatedCar[i].type
		//		<< " InitLoc = " << UnAllocatedCar[i].InitLoc
		//		<< " v = " << UnAllocatedCar[i].v
		//		<< " at = " << UnAllocatedCar[i].at << " dt = " << UnAllocatedCar[i].dt << " et = " << UnAllocatedCar[i].et
		//		<< " TR[4] = [" << UnAllocatedCar[i].TR->cpu << ", " << UnAllocatedCar[i].TR->gpu << ", " << UnAllocatedCar[i].TR->memory << ", " << UnAllocatedCar[i].TR->disk << "] "
		//		<< " bid = " << UnAllocatedCar[i].bid << endl;
		//}
		//cout << endl;
		//cout << "执行OTRAP_ALLOC后，容器 tmp_X 中的车辆信息如下：" << endl;
		//for (int i = 0; i < tmp_X.size(); i++)
		//{
		//	cout << "车辆 " << i << " : id = " << tmp_X[i].id << " type = " << tmp_X[i].type
		//		<< " at = " << tmp_X[i].at << " dt = " << tmp_X[i].dt << " et = " << tmp_X[i].et
		//		<< " TR[4] = [" << tmp_X[i].TR->cpu << ", " << tmp_X[i].TR->gpu << ", " << tmp_X[i].TR->memory << ", " << tmp_X[i].TR->disk << "] "
		//		<< " bid = " << tmp_X[i].bid << " bat = " << tmp_X[i].bat << " ConnectTo = " << tmp_X[i].ConnectTo
		//		<< " pay = " << tmp_X[i].pay << endl;
		//}
		//cout << endl;

		//保存
		//1.截止至[1,t]获得的社会福利
		TotalSocialWelfare += cts_SocialWelfare;
		//2.当前时间槽 t 的分配结果（未计算付款）
		if (!tmp_X.empty())
		{
			//for (int i = 0; i < tmp_X.size(); i++)
			for (vector<CarInfo>::iterator Xit = tmp_X.begin(); Xit != tmp_X.end(); Xit++)
			{
				cts_AllocResult.push_back(*Xit);
			}
		}

		//只有在 当前时间槽 t 有车辆获得分配(容器 cts_AllocResult 不为空)时，执行OTRAP_PAY 才是有意义的
		if (!cts_AllocResult.empty())
		{
			////测试
			//cout << "执行 OTRAP_PAY 前，容器 cts_AllocResult 中的车辆信息如下：" << endl;
			//for (int i = 0; i < cts_AllocResult.size(); i++)
			//{
			//	cout << "车辆 " << i << " : id = " << cts_AllocResult[i].id << " type = " << cts_AllocResult[i].type
			//		<< " at = " << cts_AllocResult[i].at << " dt = " << cts_AllocResult[i].dt << " et = " << cts_AllocResult[i].et
			//		<< " TR[4] = [" << cts_AllocResult[i].TR->cpu << ", " << cts_AllocResult[i].TR->gpu << ", " << cts_AllocResult[i].TR->memory << ", " << cts_AllocResult[i].TR->disk << "] "
			//		<< " bid = " << cts_AllocResult[i].bid << " bat = " << cts_AllocResult[i].bat << " ConnectTo = " << cts_AllocResult[i].ConnectTo
			//		<< " pay = " << cts_AllocResult[i].pay << endl;
			//}
			//cout << endl;

			time_t tPay_begin, tPay_end;
			tPay_begin = clock();	//支付函数计时开始

			OVMAP_mod_PAY(cts, vEcsInfo_cp, BeAllocatedCar_cp, UnAllocatedCar_cp, cts_AllocResult);

			tPay_end = clock();		//支付函数计时结束
			PAY_RunTime += static_cast<double>(tPay_end - tPay_begin) / CLOCKS_PER_SEC * 1000;

			/*cout << "执行 OTRAP_PAY 后，容器 cts_AllocResult 中的车辆信息（主要看付款）如下：" << endl;
			for (int i = 0; i < cts_AllocResult.size(); i++)
			{
				cout << "车辆 " << i << " : id = " << cts_AllocResult[i].id << " type = " << cts_AllocResult[i].type
					<< " at = " << cts_AllocResult[i].at << " dt = " << cts_AllocResult[i].dt << " et = " << cts_AllocResult[i].et
					<< " TR[4] = [" << cts_AllocResult[i].TR->cpu << ", " << cts_AllocResult[i].TR->gpu << ", " << cts_AllocResult[i].TR->memory << ", " << cts_AllocResult[i].TR->disk << "] "
					<< " bid = " << cts_AllocResult[i].bid << " bat = " << cts_AllocResult[i].bat << " ConnectTo = " << cts_AllocResult[i].ConnectTo
					<< " pay = " << cts_AllocResult[i].pay << endl;
			}
			cout << endl;*/

			//3.截止至[1,t]的分配结果（已计算付款）
			//for (int i = 0; i < cts_AllocResult.size(); i++)
			for (vector<CarInfo>::iterator cts_ARit = cts_AllocResult.begin(); cts_ARit != cts_AllocResult.end(); cts_ARit++)
			{
				AllocResult.push_back(*cts_ARit);
			}
		}
		/*else
		{
			cout << "没有车辆在当前时间槽 t = " << cts << " 获得分配（cts_AllocResult.empty() == true），故不执行 OTRAP_PAY 算法！" << endl << endl;
		}*/
	}
}

void OVMAP_mod_ALLOC(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& BACar, vector<CarInfo>& UACar)
{
	//0.每次执行 OTRAP_ALLOC 前的准备工作
	tmp_X.clear();
	cts_SocialWelfare = 0;
	//for (int j = 0; j < ECS.size(); j++)
	for (auto ECSit = vEcsInfo.begin(); ECSit != vEcsInfo.end(); ECSit++)
	{
		ECSit->InDegree = 0;				//基站入度置 0，
		ECSit->AbleConnectToECS.clear();	//存放 可与基站j建立连接的车辆的容器 清空
	}

	//1.计算每个基站的入度
	for (int j = 0; j < ECS.size(); j++)
	{
		for (int i = 0; i < UACar.size(); i++)	//遍历每辆车的可连接矩阵 CM[j][t]
		{

			//[] 里面存放的类型是 long long int ，而 t 是 int 
			//t-1 有可能发生溢出的风险，若将 t 的类型设置为 long long int（符合[]里的数字类型），则可避免警告
			//设置 CM[j][t-1] 而不是 CM[j][t] 的原因:算法运行的时间范围是[1,T]，但矩阵存储的下标从0开始
			if (UACar[i].CM[j][cts - 1] == 1)
			{
				UACar[i].alloc_flag = true;			//默认车辆 UACar[i] 能得到分配，但不确定要连接哪个基站
				//UACar[i].ConnectTo = ECS[j].id;		//默认车辆能连接ECS[j]，当车辆能连接多个基站时，该值会被覆盖多次
				ECS[j].InDegree++;
			}
		}
	}

	//2.按基站入度升序，对vEcsInfo中的所有基站进行排序
	sort(ECS.begin(), ECS.end(), EcsInDegreeAscend);

	////测试：打印排序后的基站顺序(成功)
	//cout << "按入度递增的顺序，基站信息如下：" << endl;
	//for (int j = 0; j < ECS.size(); j++)
	//{
	//	cout << "基站 " << j << " 的 InDegree = " << ECS[j].InDegree;
	//	cout << " id = " << ECS[j].id;
	//	cout << " type = " << ECS[j].type;
	//	cout << " CR = " << ECS[j].CR;
	//	cout << " loc = " << ECS[j].loc;
	//	cout << " CA = [" << ECS[j].CA[0] << "," << ECS[j].CA[1] << "] ";
	//	cout << " RC = <" << ECS[j].RC->cpu << " " << ECS[j].RC->gpu << " " << ECS[j].RC->memory << " " << ECS[j].RC->disk << "> ";
	//	cout << endl;
	//}

	//3.逐个考察基站 j 的情况：检查哪些 i 能和 j 相连，并将 i 放入密度集合（降序）中
	//入读递增排序后，基站容器 ECS[j] 中 [j] 的次序已经发生变化，但CM[j][t]的[j] 仍然指 id 为 (j+1) 的基站
	for (int j = 0; j < ECS.size(); j++)
	{
		if (ECS[j].InDegree != 0)	//仅考察入度不为 0 的基站的情况
		{
			for (int i = 0; i < UACar.size(); i++)
			{
				//仅考察那些能够连接基站的车辆，第二个条件防止车辆属性 ConnectTo 被重复赋值
				if (UACar[i].alloc_flag == true && UACar[i].ConnectTo == -1)
				{
					int ecsid = ECS[j].id;	//记录：入度排序后，ECS[j].id(唯一且不变)
					//入读递增排序后，基站容器 ECS[j] 中 [j] 的次序已经发生变化，但CM[j][t]的[j] 仍然指 id 为 (j+1) 的基站
					if (UACar[i].CM[ecsid - 1][cts - 1] == 1)
					{
						UACar[i].ConnectTo = ECS[j].id;		//确定车辆连接ECS[j]
						CalcCarBidDensity(UACar[i]);	//计算 f
						ECS[j].AbleConnectToECS.push_back(UACar[i]);	//放入 ECS[j].AbleConnectToECS 中
						UACar.erase(UACar.begin() + i);		//从 UACar[] 中删除车辆 i
					}
				}
			}

			if (!ECS[j].AbleConnectToECS.empty())	// ECS[j].AbleConnectToECS.size() == ECS[j].InDegree
			{
				////测试：密度降序排序前
				//cout << "当前时间槽 t = " << cts << ", 在ECS[" << ECS[j].id << "].AbleConnectToECS 中，按照 f 排序前：" << endl;
				//for (int i = 0; i < ECS[j].AbleConnectToECS.size(); i++)
				//{
				//	cout << "车辆 " << i << " : id = " << ECS[j].AbleConnectToECS[i].id << " type = " << ECS[j].AbleConnectToECS[i].type
				//		<< " at = " << ECS[j].AbleConnectToECS[i].at << " dt = " << ECS[j].AbleConnectToECS[i].dt << " et = " << ECS[j].AbleConnectToECS[i].et
				//		<< " TR[4] = [" << ECS[j].AbleConnectToECS[i].TR->cpu << ", " << ECS[j].AbleConnectToECS[i].TR->gpu << ", " << ECS[j].AbleConnectToECS[i].TR->memory << ", " << ECS[j].AbleConnectToECS[i].TR->disk << "] "
				//		<< " bid = " << ECS[j].AbleConnectToECS[i].bid << " dr = " << ECS[j].AbleConnectToECS[i].dr
				//		<< " f = " << ECS[j].AbleConnectToECS[i].f << endl;
				//}

				//按资源密度 f[i] 递减排序（已通过测试）
				sort(ECS[j].AbleConnectToECS.begin(), ECS[j].AbleConnectToECS.end(), CarBidDensityDescend);

				////测试：密度降序排序后
				//cout << "时间槽 t = " << cts << ", 在ECS[" << ECS[j].id << "].AbleToConnectECS 中，按照 f 排序后：" << endl;
				//for (int i = 0; i < ECS[j].AbleConnectToECS.size(); i++)
				//{
				//	cout << "车辆 " << i << " : id = " << ECS[j].AbleConnectToECS[i].id << " type = " << ECS[j].AbleConnectToECS[i].type
				//		<< " at = " << ECS[j].AbleConnectToECS[i].at << " dt = " << ECS[j].AbleConnectToECS[i].dt << " et = " << ECS[j].AbleConnectToECS[i].et
				//		<< " TR[4] = [" << ECS[j].AbleConnectToECS[i].TR->cpu << ", " << ECS[j].AbleConnectToECS[i].TR->gpu << ", " << ECS[j].AbleConnectToECS[i].TR->memory << ", " << ECS[j].AbleConnectToECS[i].TR->disk << "] "
				//		<< " bid = " << ECS[j].AbleConnectToECS[i].bid << " dr = " << ECS[j].AbleConnectToECS[i].dr
				//		<< " f = " << ECS[j].AbleConnectToECS[i].f << endl;
				//}

				for (int i = 0; i < ECS[j].AbleConnectToECS.size(); i++)
				{
					int cpuEnough = ECS[j].RC->cpu - ECS[j].AbleConnectToECS[i].TRD->cpu;
					int gpuEnough = ECS[j].RC->gpu - ECS[j].AbleConnectToECS[i].TRD->gpu;
					int memoryEnough = ECS[j].RC->memory - ECS[j].AbleConnectToECS[i].TRD->memory;
					int diskEnough = ECS[j].RC->disk - ECS[j].AbleConnectToECS[i].TRD->disk;

					//只要任意一种资源不足，就不为该车辆分配
					if ((cpuEnough < 0) || (gpuEnough < 0) || (memoryEnough < 0) || (diskEnough < 0))
					{
						//如果资源不够分配，恢复 ECS[j].AbleConnectToECS[i]的 alloc_flag 和 ConnectTo 属性, 并将其放回 UACar[i]
						ECS[j].AbleConnectToECS[i].alloc_flag = false;
						ECS[j].AbleConnectToECS[i].ConnectTo = -1;
						UACar.push_back(ECS[j].AbleConnectToECS[i]);	//放回 UACar[i]
						// “因基站资源不足而未被分配的车辆” 被移除 ECS[j].AbleConnectToECS
						ECS[j].AbleConnectToECS.erase(ECS[j].AbleConnectToECS.begin() + i);
					}
					else	//资源够分，为ECS[j].AbleConnectToECS[i] 分配资源
					{
						//更改获得分配的车辆的属性
						ECS[j].AbleConnectToECS[i].bat = cts;		// 记录得到分配的时间 t[i][ba] = t	
						BACar.push_back(ECS[j].AbleConnectToECS[i]);	//将得到分配的车辆 并入 容器 BeAllocatedCar
						tmp_X.push_back(ECS[j].AbleConnectToECS[i]);		// X[t]= X[t] + x[i][j][t]
						cts_SocialWelfare += ECS[j].AbleConnectToECS[i].bid;	// V[t] = V[t] + b[i]

						//为 i 分配资源，更新容量
						ECS[j].RC->cpu -= ECS[j].AbleConnectToECS[i].TRD->cpu;
						ECS[j].RC->gpu -= ECS[j].AbleConnectToECS[i].TRD->gpu;
						ECS[j].RC->memory -= ECS[j].AbleConnectToECS[i].TRD->memory;
						ECS[j].RC->disk -= ECS[j].AbleConnectToECS[i].TRD->disk;

						ECS[j].AbleConnectToECS.erase(ECS[j].AbleConnectToECS.begin() + i);
					}
				}
			}
			/*else
			{
				cout << "当前时间槽 t = " << cts << ", 没有任何车辆能够连接基站 " << ECS[j].id << " (ECS[" << ECS[j].id << "].AbleConnectToECS.empty() == true)" << endl;
			}*/
		}
		/*else
		{
			cout << "当前时间槽 t = " << cts << ",基站 " << ECS[j].id << " 的入度为 0 (InDegree = 0)，不为任何车辆分配资源。" << endl;
		}*/
	}
}

void OVMAP_mod_PAY(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& BACar, vector<CarInfo>& UACar, vector<CarInfo>& cts_AR)
{
	//pay过小的原因在于：
	//假设在当前时间槽 cts 中，对于某个特定的基站（资源充足）来说，只有一个车辆连接该基站
	//那么，无论该车辆怎样降低付款，都能获得分配，故车辆的付款会变得极小
	//解决方法是：增大实验的样本数量（读入的车辆数），保证资源分配具有竞争性，即：
	//对于各个基站而言，每个时间槽 t 都应当能连接多个车辆，此时，若车辆过分降低投标，就会输掉拍卖。

	for (int i = 0; i < cts_AR.size(); i++)	// cts_AR = current time slot_Allocate Result
	{
		//int modbidNum = 1;
		double AR_i_bid = 0.00, UB_i = 0.00, LB_i = 0.00;
		//使用临时变量 AR_i_bid 保存 cts_AR[i].bid，在不改变 cts_AR[i].bid 的情况下，满足算法的使用需要
		AR_i_bid = cts_AR[i].bid;
		UB_i = AR_i_bid;
		AR_i_bid = (double)((UB_i + LB_i) / (double)2);	//根据二分法，先降低 AR_i_bid

		while (double(fabs(UB_i - LB_i)) >= epsilon)	//还未求得最小的获胜投标(付款)
		{
			vector<EcsInfo>Ecs_cp(ECS);
			vector<CarInfo>BACar_cp(BACar);
			vector<CarInfo>UACar_cp(UACar);	//已经被修改 n+1 次bid，不改变UACar[]的任何值，保证上一个胜者的投标恢复

			//改变对应的 UACar_cp[k].id 的投标，再运行 OTRAP_ALLOC
			for (int k = 0; k < UACar_cp.size(); k++)
			{
				if (UACar_cp[k].id == cts_AR[i].id)
				{
					UACar_cp[k].bid = AR_i_bid;
					//cout << "第 " << modbidNum << " 次修改后：获胜车辆" << UACar_cp[k].id <<" 的投标为：" << UACar_cp[k].bid << endl;
					//modbidNum++;
				}
			}

			//cout << "OTRAP_PAY 中 运行 OTRAP_ALLOC : " << endl;
			OVMAP_mod_ALLOC(cts, Ecs_cp, BACar_cp, UACar_cp);
			//此时，tmp_X[]存放：当前时间槽 t ，获胜者 i 降低投标后，再运行OTRAP_ALLOC选出的胜者车辆集合
			//修改 UACar[i].bid, 直到能够确定最佳投标(付款)
			for (int k = 0; k <= tmp_X.size(); k++)
			{
				if (k < tmp_X.size())	//在tmp_X.size()中遍历, 只要能在 tmp_X 中遍历到，表示依然获胜
				{
					if (tmp_X[k].id == cts_AR[i].id)	//降低投标后，UACar[i]依然获胜
					{
						UB_i = tmp_X[k].bid;		//仍然获胜的投标作为UB_i，tmp_X[k].bid = AR_i_bid = UACar[k].bid
						AR_i_bid = (double)((UB_i + LB_i) / (double)2);	//再降低 UACar[i].bid
						break;
					}
				}
				else	// 此时 k == tmp_X.size();即获胜车辆 i 降低投标后不再获胜
				{
					//降低投标后，新投标的值为 AR_i_bid ，导致 UACar[i] 不能获胜
					LB_i = AR_i_bid;	//将引起失败的投标值作为LB_i
					AR_i_bid = (double)((UB_i + LB_i) / (double)2);	//适当提高 UACar[i].bid
				}
			}
		}
		cts_AR[i].pay = (double)((UB_i + LB_i) / (double)2);
	}
}

void IsEcsRCEmpty()
{
	int flag = 0;
	for (int j = 0; j < vEcsInfo.size(); j++)
	{
		if ((vEcsInfo[j].RC->cpu == 0) && (vEcsInfo[j].RC->gpu == 0) && (vEcsInfo[j].RC->memory == 0) && (vEcsInfo[j].RC->disk == 0))
		{
			flag += 0;
		}
		else
		{
			flag += 1;
		}
	}
	if (flag == 0)
		EcsRCEmpty = true;
}

bool EcsInDegreeAscend(const EcsInfo& ecs1, const EcsInfo& ecs2)
{
	if (ecs1.InDegree == ecs2.InDegree)	//若基站的入度相等，按照基站位置升序排列（位置靠前的基站能服务到达时间较早的车辆，提升资源利用率）
		return ecs1.loc < ecs2.loc;
	else
		return ecs1.InDegree < ecs2.InDegree;
}

void CalcCarBidDensity(CarInfo& car)
{
	double Bid = 0;
	double ExecutionTime = 0;
	double request_CPU = 0, request_GPU = 0, request_Memory = 0, request_Disk = 0;
	double BidDensity = 0;

	//1.记录分子（车辆的投标）
	Bid = car.bid;

	//2.计算分母
	ExecutionTime = (double)car.et;		//记录执行时间et

	request_CPU = (double)car.TRD->cpu;
	request_GPU = (double)car.TRD->gpu;
	request_Memory = (double)car.TRD->memory;
	request_Disk = (double)car.TRD->disk;

	double tmp = request_CPU * request_GPU * request_Memory * request_Disk;	// 记录 请求资源累乘项

	BidDensity = Bid / (ExecutionTime * tmp);

	//3.算出投标密度并赋值
	car.f = BidDensity;
}

bool CarBidDensityDescend(const CarInfo& car1, const CarInfo& car2)
{
	if (car1.f == car2.f)	//若车辆的投标密度相等，按照到达时间升序排列（越早到达，任务越紧急）
		return car1.at < car2.at;
	else
		return car1.f > car2.f;
}

//第三步：将结果保存到本地
void SaveResult()
{
	CalcUsageRatio();
	CalcServedCarRatio();
	CalcNormalPayRatio();

	ofstream ofs;

	// 根据实验要求，每次实验之前都要修改 保存路径 和 抽取的数量，如
	// 保存算法 OTRAP 的求解结果
	string OVMAP_mod_SolutionFile = "../data/ExperimentalResult/exp3/4OVMAP_mod_Solution/EcsInfo_5_0_5/OVMAP_mod_Solution_CarInfo_" + to_string(S_CarNum) + "_" + to_string(M_CarNum) + "_" + to_string(L_CarNum) + "-" + to_string(ExeNum) + ".txt";
	ofs.open(OVMAP_mod_SolutionFile, ios::out | ios::trunc);
	//数据保存格式：
	//车辆序号	车辆ID(车辆类型)	初始位置	速度	到达时间	截止时间	执行时间	任务资源需求			投标(系数)			得到分配的时间	连接的基站(基站类型)	连接情况		付款
	//SeqNum	CarId(type)			InitLoc		V		AT			DT			ET			TaskResourceDemand		Bid(Coefficient)	BAT				ConnectToECS(type)		Connectivity	Payment
	ofs << "SeqNum\t" << "Car_Id(Type)\t" << "InitLoc(m)\t" << "V(m/t)\t" << "AT\t" << "DT\t" << "ET\t" << "TaskResourceDemand\t" << "Bid(coefficient)\t" << "ConnectToECS(type)\t" << "BeAllocatedTime\t" << "Connectivity\t" << "Payment" << endl;
	for (int i = 0; i < AllocResult.size(); i++)
	{
		ofs << i + 1 << "\t";
		ofs << AllocResult[i].id << "(" << AllocResult[i].type << ")" << "\t\t";
		ofs << AllocResult[i].InitLoc << "\t";
		ofs << AllocResult[i].v << "\t";
		ofs << AllocResult[i].at << "\t";
		ofs << AllocResult[i].dt << "\t";
		ofs << AllocResult[i].et << "\t";
		ofs << "<" << AllocResult[i].TRD->cpu << "," << AllocResult[i].TRD->gpu << "," << AllocResult[i].TRD->memory << "," << AllocResult[i].TRD->disk << ">\t\t";
		ofs << AllocResult[i].bid << "(" << AllocResult[i].mu << ")\t";
		ofs << AllocResult[i].ConnectTo << "(";
		for (int j = 0; j < M; j++)
		{
			if (vEcsInfo[j].id == AllocResult[i].ConnectTo)
			{
				ofs << vEcsInfo[j].type;
			}
		}
		ofs << ")\t\t";
		ofs << AllocResult[i].bat << "\t\t";
		ofs << AllocResult[i].alloc_flag << "\t\t";
		ofs << AllocResult[i].pay << endl;
	}
	ofs << endl;

	//输出求得的总社会福利
	ofs << "1.社会福利: SocialWelfare_max = " << TotalSocialWelfare << endl;
	ofs << endl;

	//输出算法运行时间
	ofs << "2.算法运行时间: RunTime = " << RunTime << " ms" << endl;
	//测试：找出运行时间长的原因
	ofs << "(1)OVMAP_mod 准备工作运行时间：PreWork_RunTime = " << PreWork_RunTime << " ms" << endl;
	ofs << "其中，回收资源所花时间：ReturnResource_RunTime = " << ReturnResource_RunTime << " ms" << endl;
	ofs << "其中，删除过期任务所花时间：DelOvertimeTask_RunTime = " << DelOvertimeTask_RunTime << " ms" << endl;
	ofs << "其中，添加新到达车辆所花时间：AddArrivedCar_RunTime = " << AddArrivedCar_RunTime << " ms" << endl;
	ofs << "(2)OVMAP_mod 分配函数运行时间：ALLOC_RunTime = " << ALLOC_RunTime << " ms" << endl;
	ofs << "(3)OVMAP_mod 支付函数运行时间：PAY_RunTime = " << PAY_RunTime << " ms" << endl;
	ofs << endl;

	//输出资源利用率
	ofs << "3.资源利用率: UsageRatio " << endl;
	ofs << "(1)总CPU利用率: UR_t_cpu = " << UR_t_cpu << endl;
	ofs << "(2)总GPU利用率: UR_t_gpu = " << UR_t_gpu << endl;
	ofs << "(3)总Memory利用率: UR_t_memory = " << UR_t_memory << endl;
	ofs << "(4)总Disk利用率: UR_t_disk = " << UR_t_disk << endl;
	ofs << endl;

	//输出服务车辆比例
	ofs << "4.服务车辆比例: SR_t_Car = " << SR_t_Car << endl;
	ofs << "其中，小型车辆任务服务占比: SR_s_Car = " << SR_s_Car << endl;
	ofs << "其中，中型车辆任务服务占比: SR_m_Car = " << SR_m_Car << endl;
	ofs << "其中，大型车辆任务服务占比: SR_l_Car = " << SR_l_Car << endl;
	ofs << endl;

	//输出正确付款的车辆比例
	ofs << "5.正常付款的获胜车辆比例: NPR_t_Car = " << NPR_t_Car << endl;
	ofs << "其中，小型获胜车辆正常付款占比:  NPR_s_Car = " << NPR_s_Car << endl;
	ofs << "其中，中型获胜车辆正常付款占比:  NPR_m_Car = " << NPR_m_Car << endl;
	ofs << "其中，大型获胜车辆正常付款占比:  NPR_l_Car = " << NPR_l_Car << endl;

	ofs.close();
}

void CalcUsageRatio()
{
	//统计使用了的资源
	//容器 AllocResult 中的所有车辆均已得到分配
	for (int i = 0; i < AllocResult.size(); i++)
	{
		UsedResource.cpu += AllocResult[i].TRD->cpu * AllocResult[i].et;
		UsedResource.gpu += AllocResult[i].TRD->gpu * AllocResult[i].et;
		UsedResource.memory += AllocResult[i].TRD->memory * AllocResult[i].et;
		UsedResource.disk += AllocResult[i].TRD->disk * AllocResult[i].et;
	}
	//统计所有基站的资源容量
	for (int j = 0; j < vEcsInfo.size(); j++)
	{
		TotalResource.cpu += vEcsInfo[j].RC->cpu;
		TotalResource.gpu += vEcsInfo[j].RC->gpu;
		TotalResource.memory += vEcsInfo[j].RC->memory;
		TotalResource.disk += vEcsInfo[j].RC->disk;
	}

	//计算资源利用率
	if (M != 0)	//只要读入的基站信息不为空
	{
		UR_t_cpu = (double)UsedResource.cpu / ((double)TotalResource.cpu * (double)T);
		UR_t_gpu = (double)UsedResource.gpu / ((double)TotalResource.gpu * (double)T);
		UR_t_memory = (double)UsedResource.memory / ((double)TotalResource.memory * (double)T);
		UR_t_disk = (double)UsedResource.disk / ((double)TotalResource.disk * (double)T);
	}
}

void CalcServedCarRatio()
{
	int Served_t_Car = AllocResult.size();		//服务车辆总数
	int Served_s_Car = 0;		//服务的小型车辆数
	int Served_m_Car = 0;		//服务的中型车辆数
	int Served_l_Car = 0;		//服务的大型车辆数

	//统计：得到分配的车辆的任务类型数量
	for (int i = 0; i < AllocResult.size(); i++)
	{
		if (AllocResult[i].type == "S")
		{
			Served_s_Car++;
		}
		else if (AllocResult[i].type == "M")
		{
			Served_m_Car++;
		}
		else if (AllocResult[i].type == "L")
		{
			Served_l_Car++;
		}
	}

	//只要读入的车辆任务信息不为空
	if (N != 0)
	{
		SR_t_Car = (double)Served_t_Car / (double)N;
	}
	else
	{
		SR_t_Car = 0.00;
	}
	if (S_CarNum != 0)
	{
		SR_s_Car = (double)Served_s_Car / (double)Served_t_Car;
	}
	else
	{
		SR_s_Car = 0.00;
	}
	if (M_CarNum != 0)
	{
		SR_m_Car = (double)Served_m_Car / (double)Served_t_Car;
	}
	else
	{
		SR_m_Car = 0.00;
	}
	if (L_CarNum != 0)
	{
		SR_l_Car = (double)Served_l_Car / (double)Served_t_Car;
	}
	else
	{
		SR_l_Car = 0.00;
	}
}

void CalcNormalPayRatio()
{
	int NP_t_Car = 0, NP_s_Car = 0, NP_m_Car = 0, NP_l_Car = 0;
	int AllocatedCar = AllocResult.size();

	//统计 获胜车辆任务的 数量 和 类型
	for (int i = 0; i < AllocResult.size(); i++)
	{
		if (AllocResult[i].pay > epsilon)	//如果获胜车辆的pay > epsilon，认为其付款正常
		{
			NP_t_Car++;
			if (AllocResult[i].type == "S")
			{
				NP_s_Car++;
			}
			else if (AllocResult[i].type == "M")
			{
				NP_m_Car++;
			}
			else if (AllocResult[i].type == "L")
			{
				NP_l_Car++;
			}
		}
	}
	if (AllocatedCar != 0)
	{
		NPR_t_Car = (double)NP_t_Car / (double)AllocatedCar;
	}
	else
	{
		NPR_t_Car = 0.00;
	}
	if (NP_t_Car != 0 && NP_s_Car != 0)
	{
		NPR_s_Car = (double)NP_s_Car / (double)NP_t_Car;
	}
	else
	{
		NPR_s_Car = 0.00;
	}
	if (NP_t_Car != 0 && NP_m_Car != 0)
	{
		NPR_m_Car = (double)NP_m_Car / (double)NP_t_Car;
	}
	else
	{
		NPR_m_Car = 0.00;
	}
	if (NP_t_Car != 0 && NP_l_Car != 0)
	{
		NPR_l_Car = (double)NP_l_Car / (double)NP_t_Car;
	}
	else
	{
		NPR_l_Car = 0.00;
	}
}

int main()
{
	srand((unsigned)time(NULL));

	T_vCarInfo.reserve(20000);
	BeAllocatedCar.reserve(20000), UnAllocatedCar.reserve(20000), AllocResult.reserve(20000);
	cts_AllocResult.reserve(20000), tmp_X.reserve(20000);

	for (; ExeNum <= count_OVMAP_mod; ExeNum++)
	//if(ExeNum <= count_OTRAP)		//检查 bug 使用
	{
		cout << "这是第 " << ExeNum << " 次运行 OVMAP_mod 算法 ! " << endl;

		//准备工作，重置使用过的数据和容器
		TotalSocialWelfare = 0, cts_SocialWelfare = 0;

		RunTime = 0;
		PreWork_RunTime = 0, ReturnResource_RunTime = 0, DelOvertimeTask_RunTime = 0, AddArrivedCar_RunTime = 0;
		ALLOC_RunTime = 0;
		PAY_RunTime = 0;

		UsedResource.cpu = 0, UsedResource.gpu = 0, UsedResource.memory = 0, UsedResource.disk = 0;
		TotalResource.cpu = 0, TotalResource.gpu = 0, TotalResource.memory = 0, TotalResource.disk = 0;
		UR_t_cpu = 0, UR_t_gpu = 0, UR_t_memory = 0, UR_t_disk = 0;

		SR_t_Car = 0, SR_s_Car = 0, SR_m_Car = 0, SR_l_Car = 0;

		NPR_t_Car = 0, NPR_s_Car = 0, NPR_m_Car = 0, NPR_l_Car = 0;

		vEcsInfo.clear(), T_vCarInfo.clear(), BeAllocatedCar.clear(), UnAllocatedCar.clear();
		AllocResult.clear(), cts_AllocResult.clear(), tmp_X.clear();

		//第一步：读入数据
		LoadEcsInfo(EcsInfoFile);

		LoadCarInfo(RS_CarInfoFile_S, RS_CarInfoFile_S_CM, T_vCarInfo, S_CarNum);	//读入小型车辆信息
		//LoadCarInfo(RS_CarInfoFile_M, RS_CarInfoFile_M_CM, T_vCarInfo, M_CarNum);	//读入中型车辆信息
		//LoadCarInfo(RS_CarInfoFile_L, RS_CarInfoFile_L_CM, T_vCarInfo, L_CarNum);	//读入大型车辆信息

		int count_S_Car = 0, count_M_Car = 0, count_L_Car = 0;
		for (vector<CarInfo>::iterator carit = T_vCarInfo.begin(); carit != T_vCarInfo.end(); carit++)
		{
			if (carit->type == "S")
				count_S_Car++;
			else if (carit->type == "M")
				count_M_Car++;
			else if (carit->type == "L")
				count_L_Car++;
			else
				cout << "读入的车辆类型错误，请重新运行程序，再读入正确的车辆任务信息！" << endl;
		}
		if (count_S_Car != 0)
		{
			cout << "成功读入小型车辆任务信息：" << count_S_Car << " 条！" << endl;
		}
		if (count_M_Car != 0)
		{
			cout << "成功读入中型车辆任务信息：" << count_M_Car << " 条！" << endl;
		}
		if (count_L_Car != 0)
		{
			cout << "成功读入大型车辆任务信息：" << count_L_Car << " 条！" << endl;
		}

		////测试：是否正确读入基站和车辆信息（成功）
		//cout << "读入的基站信息如下：" << endl;
		//for (int j = 0; j < vEcsInfo.size(); j++)
		//{
		//	cout << "基站：id = " << vEcsInfo[j].id;
		//	cout << " type = " << vEcsInfo[j].type;
		//	cout << " CR = " << vEcsInfo[j].CR;
		//	cout << " loc = " << vEcsInfo[j].loc;
		//	cout << " CA = [" << vEcsInfo[j].CA[0] << "," << vEcsInfo[j].CA[1] << "] ";
		//	cout << " RC = <" << vEcsInfo[j].RC->cpu << " " << vEcsInfo[j].RC->gpu << " " << vEcsInfo[j].RC->memory << " " << vEcsInfo[j].RC->disk << "> ";
		//	cout << endl;
		//}
		//cout << "读入的车辆信息如下：" << endl;
		//for (int i = 0; i < T_vCarInfo.size(); i++)
		//{
		//	cout << "车辆 " << i << " : id = " << T_vCarInfo[i].id 
		//		<< " type = " << T_vCarInfo[i].type
		//		<< " InitLoc(m) = " << T_vCarInfo[i].InitLoc 
		//		<< " v(m/s) = " << T_vCarInfo[i].v
		//		<< " at = " << T_vCarInfo[i].at 
		//		<< " dt = " << T_vCarInfo[i].dt 
		//		<< " et = " << T_vCarInfo[i].et
		//		<< " TR[4] = [" << T_vCarInfo[i].TR->cpu << ", " << T_vCarInfo[i].TR->gpu << ", " << T_vCarInfo[i].TR->memory << ", " << T_vCarInfo[i].TR->disk << "] "
		//		<< " bid = " << T_vCarInfo[i].bid << " CM = " << endl;
		//	for (int j = 0; j < M; j++)
		//	{
		//		for (int t = 0; t < T; t++)
		//		{
		//			cout << T_vCarInfo[i].CM[j][t] << " ";
		//		}
		//		cout << endl;
		//	}
		//}

		cout << "在时间槽[1, " << T << "]，开始运行 OVMAP_mod 算法！" << endl;

		time_t tBegin, tEnd;
		tBegin = clock();	//开始计时

		//第二步：每个时间槽执行一次OVMAP*算法
		for (int t = 1; t <= T; t++)
		{
			//cout << "当前时间槽 t = " << t << ", 执行 OTRAP 算法：" << endl;
			OVMAP_mod(t, vEcsInfo, T_vCarInfo);
		}

		tEnd = clock();	//计时结束

		cout << "第 " << ExeNum << " 次运行 OVMAP_mod 算法结束！" << endl;
		cout << endl;

		RunTime = static_cast<double>(tEnd - tBegin) / CLOCKS_PER_SEC * 1000;	

		////展示结果
		////运行时间
		//cout << "OVMAP_mod 算法的运行时间为：RunTime = " << RunTime << "ms" << endl;
		////社会福利
		//cout << "整个运行时间[1," << T << "]中，OVMAP_mod 算法求解的社会福利为：SocialWelfare = " << TotalSocialWelfare << endl;
		////分配结果
		//cout << "整个运行时间[1," << T << "]中，OVMAP_mod 算法求解的分配结果为：AllocResult = " << endl;
		//for (int i = 0; i < AllocResult.size(); i++)
		//{
		//	cout << "车辆 " << i + 1 << " : id = " << AllocResult[i].id << " type = " << AllocResult[i].type
		//		<< " at = " << AllocResult[i].at << " dt = " << AllocResult[i].dt << " et = " << AllocResult[i].et
		//		<< " TR[4] = [" << AllocResult[i].TR->cpu << ", " << AllocResult[i].TR->gpu << ", " << AllocResult[i].TR->memory << ", " << AllocResult[i].TR->disk << "] "
		//		<< " bid = " << AllocResult[i].bid << " bat = " << AllocResult[i].bat << " ConnectTo = " << AllocResult[i].ConnectTo
		//		<< " pay = " << AllocResult[i].pay << endl;
		//}

		/*cout << "运行 OVMAP_mod 算法后，在时间槽[1,T]完成任务的车辆集合 AccomplishTaskCar = " << endl;
		for (int i = 0; i < AccomplishTaskCar.size(); i++)
		{
			cout << "车辆 " << i << " : id = " << AccomplishTaskCar[i].id << " type = " << AccomplishTaskCar[i].type
				<< " at = " << AccomplishTaskCar[i].at << " dt = " << AccomplishTaskCar[i].dt << " et = " << AccomplishTaskCar[i].et
				<< " TR[4] = [" << AccomplishTaskCar[i].TR->cpu << ", " << AccomplishTaskCar[i].TR->gpu << ", " << AccomplishTaskCar[i].TR->memory << ", " << AccomplishTaskCar [i].TR->disk << "] "
				<< " bid = " << AccomplishTaskCar[i].bid << " bat = " << AccomplishTaskCar[i].bat << " ConnectTo = " << AccomplishTaskCar[i].ConnectTo << endl;
		}*/

		//第三步：将结果保存到本地
		SaveResult();
	}

	system("pause");
	return 0;
}


