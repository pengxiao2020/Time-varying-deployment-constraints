#include "RandomSampling.h"
#include <iostream>
using namespace std;

//1.读入 1GenerateData 生成的大数据库
//(1)读入基站信息
void LoadEcsInfo(string EcsInfofile)
{
	ifstream ifs_ECS(EcsInfofile);	//一次性读入所有类型的基站信息
	//for (int j = 0; j < M && ECS != vEcsInfo.end(); j++, ECS++)	//读入基站信息：资源容量
	for (int j = 0; j < M; j++)
	{
		EcsInfo ecs;	//临时 EcsInfo 对象
		//先读入具体值到对象的属性中，再将该对象放入vector中
		ifs_ECS >> ecs.id;
		ifs_ECS >> ecs.type;
		ifs_ECS >> ecs.CR;
		ifs_ECS >> ecs.loc;
		ifs_ECS >> ecs.CA[0];
		ifs_ECS >> ecs.CA[1];
		ifs_ECS >> ecs.RC->cpu;
		ifs_ECS >> ecs.RC->gpu;
		ifs_ECS >> ecs.RC->memory;
		ifs_ECS >> ecs.RC->disk;
		vEcsInfo.push_back(ecs);
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
//(2)读入车辆信息
void LoadCarInfo(string CarInfofile, string CarCMfile, vector<CarInfo>& Car, int CarNum)
{
	ifstream ifs_Car(CarInfofile);		//读入车辆任务信息
	ifstream ifs_Car_CM(CarCMfile);		//读入车辆可连接矩阵
	for (int i = 0; i < CarNum; i++)	//读入车辆信息
	{
		//提示栈空间不足的原因是，每辆车的CM占用的栈空间(10*1440)过大
		// 1.使用 vector<vector<bool>> 存储 CM，可避免该问题
		// 2.动态指针也可解决该问题(采用)
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

	int count_S_Car = 0, count_M_Car = 0, count_L_Car = 0;
	for (int i = 0; i < CarNum; i++)
	{
		if (Car[i].type == "S")
			count_S_Car++;
		else if (Car[i].type == "M")
			count_M_Car++;
		else if (Car[i].type == "L")
			count_L_Car++;
		else
			cout << "车辆类型错误！请重新运行程序，再读入文件！" << endl;
	}
	if (count_S_Car != 0)
	{
		cout << "成功读入小型车辆信息：" << count_S_Car << " 条！" << endl;
	}
	if (count_M_Car != 0)
	{
		cout << "成功读入中型车辆信息：" << count_M_Car << " 条！" << endl;
	}
	if (count_L_Car != 0)
	{
		cout << "成功读入大型车辆信息：" << count_L_Car << " 条！" << endl;
	}
}

//2.随机抽取五组车辆数据，每组车辆数据个数为 100, 500, 5000, 10000, 20000。且每组数据要抽取10次。
// 供算法 VCG-TRAP 、OVMAP* 和 OTRAP 调入使用。
void RandomSampling(vector<CarInfo>& Car, vector<CarInfo>& rsCar, string type, int SamplingNum)
{

	//抽取 参与实验 的车辆任务信息
	//for (int i = 0; i < SamplingNum; i++)	//效率过低，不采用
	//{
	//	rsCar.push_back(Car[i]);
	//}

	if (SamplingNum <= Car.size())
	{
		//打乱车辆在容器中的排列顺序
		random_shuffle(Car.begin(), Car.end());

		for (vector<CarInfo>::iterator carit = Car.begin(); carit != Car.begin() + SamplingNum; carit++)
		{
			rsCar.push_back(*carit);
		}
	}
	else
	{
		cout << "随机抽取的车辆数大于生成的车辆数( " << SamplingNum << " > " << Car.size() << " )，无法正确抽取！ " << endl;
	}

	cout << "已经随机抽取 " << SamplingNum << " 条 " << type << " 型车辆任务信息！" << endl;
}

//3.将信息保存到本地
//(1)将基站信息保存到本地(原封不动)
void SaveEcsInfo()
{
	ofstream ofs;
	//展示给用户看的基站信息汇总
	//string EcsInfoFile_show = "../data/2RandomSampling/exp1/EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";	//抽取实验一数据
	//string EcsInfoFile_show = "../data/2RandomSampling/exp2/data_CarInfo_50%_5000_0_5000/EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";	//抽取实验二数据
	string EcsInfoFile_show = "../data/2RandomSampling/exp3/EcsInfo_9_0_1/EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";	//抽取实验三数据
	ofs.open(EcsInfoFile_show, ios::out | ios::trunc);
	ofs << "ECS_Id" << '\t' << "Type" << '\t' << "CoverageRadius(m)" << '\t' << "Loc(m)" << '\t' << "CoverageArea(m)" << '\t' << "ResourceCapacity" << endl;
	for (vector<EcsInfo>::iterator ecs = vEcsInfo.begin(); ecs != vEcsInfo.end(); ecs++)
	{
		ofs << ecs->id << "\t";							//基站编号
		ofs << ecs->type << "\t";						//基站类型 S/M/L
		ofs << ecs->CR << "\t\t";						//基站工作半径 CoverageRadius	
		ofs << ecs->loc << "\t";						//基站位置 Location
		ofs << "[" << ecs->CA[0] << "," << ecs->CA[1] << "]\t";	//基站覆盖范围 CoverageArea
		ofs << "<" << ecs->RC->cpu << "," << ecs->RC->gpu << "," << ecs->RC->memory << "," << ecs->RC->disk << ">\t";	//基站资源容量 ResourceCapacity
		ofs << endl;
	}
	ofs.close();
	
	//将所有基站的信息都输出到同一个.txt文件中保存，供算法输入使用
	//string EcsInfoFile_input = "../data/2RandomSampling/exp1/data_EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";	//抽取实验一数据
	//string EcsInfoFile_input = "../data/2RandomSampling/exp2/data_CarInfo_50%_5000_0_5000/data_EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";	//抽取实验二数据
	string EcsInfoFile_input = "../data/2RandomSampling/exp3/EcsInfo_9_0_1/data_EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) + ".txt";	//抽取实验三数据
	ofs.open(EcsInfoFile_input, ios::out | ios::trunc);
	for (vector<EcsInfo>::iterator ecs = vEcsInfo.begin(); ecs != vEcsInfo.end(); ecs++)
	{
		ofs << ecs->id << " ";					//基站编号
		ofs << ecs->type << " ";				//基站类型 S/M/L
		ofs << ecs->CR << " ";					//基站工作半径 CoverageRadius
		ofs << ecs->loc << " ";					//基站位置 Location	
		ofs << ecs->CA[0] << " " << ecs->CA[1] << " ";	//基站覆盖范围 CoverageArea
		ofs << ecs->RC->cpu << " " << ecs->RC->gpu << " " << ecs->RC->memory << " " << ecs->RC->disk << " ";	//基站资源容量 ResourceCapacity
		ofs << endl;
	}
	ofs.close();

	cout << "已经成功将 " <<tEcsNum << "条基站信息写入EcsInfo_" + to_string(S_EcsNum) + "_" + to_string(M_EcsNum) + "_" + to_string(L_EcsNum) +  ".txt 中!" << endl;
	cout << "其中，小型基站数量为：" << count_S_ECS << ", "
		<< "中型基站数量为：" << count_M_ECS << ", "
		<< "大型基站数量为：" << count_L_ECS << ". " << endl;
	cout << endl;

}

//(2)将随机抽取的车辆数据保存到本地
void SaveCarInfo()
{
	//1. 保存“供用户查看”的随机抽取的车辆信息
	ofstream ofs;
	//(1)保存随机抽取的车辆任务信息(除可连接矩阵CM)
	//string CarInfoFile_show = "../data/2RandomSampling/exp1/RS_CarInfo_" + to_string(RS_S_CarNum) + "_" + to_string(RS_M_CarNum) + "_" + to_string(RS_L_CarNum) + "-" + to_string(ExeNum) + ".txt";	//抽取实验一数据
	//string CarInfoFile_show = "../data/2RandomSampling/exp2/data_CarInfo_50%_5000_0_5000/RS_CarInfo_" + to_string(RS_S_CarNum) + "_" + to_string(RS_M_CarNum) + "_" + to_string(RS_L_CarNum) + "-" + to_string(ExeNum) + ".txt";	//抽取实验二数据
	string CarInfoFile_show = "../data/2RandomSampling/exp3/EcsInfo_9_0_1/RS_CarInfo_" + to_string(RS_S_CarNum) + "_" + to_string(RS_M_CarNum) + "_" + to_string(RS_L_CarNum) + "-" + to_string(ExeNum) + ".txt";	//抽取实验三数据
	ofs.open(CarInfoFile_show, ios::out | ios::trunc);	//如果文件存在，先删除，再创建
	ofs << "Car_Id" << '\t' << "Type" << '\t' << "InitLoc(m)" << '\t' << "v(m/t)" << '\t' << "AT" << '\t' << "DT" << '\t' << "ET" << '\t' << "TaskResourceDemand" << '\t' << "Bid" << '\t' << "BidCoefficient" << endl;
	//小型车辆任务信息(除可连接矩阵CM)
	for (vector<CarInfo>::iterator car = RS_S_vCarInfo.begin(); car != RS_S_vCarInfo.end(); car++)
	{
		//数据格式：编号   类型   出发点   速度 到达时间 截止时间 执行时间 任务资源需求			投标	投标系数		
		//数据格式：CarId  Type   InitLoc  v    at       dt       et       TaskResourceDemand   b		BidCoefficient   
		ofs << car->id << "\t";			//车辆编号：表示这是第几辆车子 
		ofs << car->type << "\t";		//车辆/任务类型：S/M/L 
		ofs << car->InitLoc << "\t";	//车辆初始位置：Initial Location
		ofs << car->v << "\t";			//车辆行驶速度：Velocity
		ofs << car->at << "\t";			//车辆到达时间/产生任务时间：Arrive Time
		ofs << car->dt << "\t";			//任务截止时间：Deadline Time
		ofs << car->et << "\t";			//执行任务时间：Execution Time
		ofs << "<" << car->TRD->cpu << "," << car->TRD->gpu << "," << car->TRD->memory << "," << car->TRD->disk << ">\t\t";	//任务资源需求：Task Request
		ofs << car->bid << "\t";		//投标
		ofs << car->mu << endl;			//报价系数：BidCoefficient
	}

	////中型车辆任务信息(除可连接矩阵CM)
	//for (vector<CarInfo>::iterator car = RS_M_vCarInfo.begin(); car != RS_M_vCarInfo.end(); car++)
	//{
	//	//数据格式：编号   类型   出发点   速度 到达时间 截止时间 执行时间 任务资源需求			投标	投标系数		
	//	//数据格式：CarId  Type   InitLoc  v    at       dt       et       TaskResourceDemand   b		BidCoefficient 
	//	ofs << car->id << "\t";			//车辆编号：表示这是第几辆车子 
	//	ofs << car->type << "\t";		//车辆/任务类型：S/M/L 
	//	ofs << car->InitLoc << "\t";		//车辆初始位置：Initial Location
	//	ofs << car->v << "\t";			//车辆行驶速度：Velocity
	//	ofs << car->at << "\t";			//车辆到达时间/产生任务时间：Arrive Time
	//	ofs << car->dt << "\t";			//任务截止时间：Deadline Time
	//	ofs << car->et << "\t";			//执行任务时间：Execution Time
	//	ofs << "<" << car->TRD->cpu << "," << car->TRD->gpu << "," << car->TRD->memory << "," << car->TRD->disk << ">\t\t";	//任务资源需求：Task Request
	//	ofs << car->bid << "\t";		//投标
	//	ofs << car->mu << endl;			//投标系数: BidCoefficient
	//}
	
	////大型车辆任务信息(除可连接矩阵CM)
	//for (vector<CarInfo>::iterator car = RS_L_vCarInfo.begin(); car != RS_L_vCarInfo.end(); car++)
	//{
	//	//数据格式：编号   类型   出发点   速度 到达时间 截止时间 执行时间 任务资源需求			投标	投标系数		
	//	//数据格式：CarId  Type   InitLoc  v    at       dt       et       TaskResourceDemand   b		BidCoefficient 
	//	ofs << car->id << "\t";			//车辆编号：表示这是第几辆车子 
	//	ofs << car->type << "\t";		//车辆/任务类型：S/M/L 
	//	ofs << car->InitLoc << "\t";	//车辆初始位置：Initial Location
	//	ofs << car->v << "\t";			//车辆行驶速度：Velocity
	//	ofs << car->at << "\t";			//车辆到达时间/产生任务时间：Arrival Time
	//	ofs << car->dt << "\t";			//任务截止时间：Deadline Time
	//	ofs << car->et << "\t";			//执行任务时间：Execution Time
	//	ofs << "<" << car->TRD->cpu << "," << car->TRD->gpu << "," << car->TRD->memory << "," << car->TRD->disk << ">\t\t";	//任务资源需求：TaskResourceDemand
	//	ofs << car->bid << "\t";		//投标
	//	ofs << car->mu << endl;			//投标系数: BidCoefficient
	//}

	ofs << endl;
	ofs.close();

	//(2)保存随机抽取的车辆的 可连接矩阵CM 信息（太占空间，已省略）
	
	//string Car_CM_show = "../data/2RandomSampling/data_RS_CarInfo_20000_20000_20000/RS_Car_CM_" + to_string(RS_S_CarNum) + "_" + to_string(RS_M_CarNum) + "_" + to_string(RS_L_CarNum) + "-" + to_string(ExeNum) + ".txt";
	////string Car_CM_show = "../data/2RandomSampling/test/RS_Car_CM_" + to_string(RS_S_CarNum) + "_" + to_string(RS_M_CarNum) + "_" + to_string(RS_L_CarNum) + "-" + to_string(ExeNum) + ".txt";
	//ofs.open(Car_CM_show, ios::out | ios::trunc);	//如果文件存在，先删除，再创建
	////小型车辆任务的可连接矩阵
	//for (vector<CarInfo>::iterator car = RS_S_vCarInfo.begin(); car != RS_S_vCarInfo.end(); car++)
	//{
	//	//数据格式：编号   类型   出发点   速度 到达时间 截止时间 可连接矩阵
	//	//数据格式：CarId  Type   InitLoc   V      AT       DT       CM
	//	//			可连接矩阵
	//	ofs << "CarId:" << car->id << " ";	//车辆编号：表示这是第几辆车子 
	//	ofs << "Type:" << car->type << " ";		//车辆/任务类型：S/M/L 
	//	ofs << "InitLoc(m):" << car->InitLoc << " ";	//车辆初始位置：Initial Location
	//	ofs << "V(m/t):" << car->v << " ";			//车辆行驶速度：Velocity
	//	ofs << "AT:" << car->at << " ";		//车辆到达时间/产生任务时间：Arrive Time
	//	ofs << "DT:" << car->dt << " ";		//完成任务截止时间：Deadline Time
	//	ofs << "ET:" << car->et << " ";		//执行任务时间：Execution Time
	//	ofs << "CM:" << endl;
	//	//遍历外边的 vector<vector<bool>>，行：基站
	//	for (vector<vector<bool>>::iterator rit = car->CM.begin(); rit != car->CM.end(); rit++)
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
	////中型车辆任务的可连接矩阵
	//for (vector<CarInfo>::iterator car = RS_M_vCarInfo.begin(); car != RS_M_vCarInfo.end(); car++)
	//{
	//	//数据格式：编号   类型   出发点   速度 到达时间 截止时间 可连接矩阵
	//	//数据格式：CarId  Type   InitLoc   V      AT       DT       CM
	//	//			可连接矩阵
	//	ofs << "CarId:" << car->id << " ";	//车辆编号：表示这是第几辆车子 
	//	ofs << "Type:" << car->type << " ";		//车辆/任务类型：S/M/L 
	//	ofs << "InitLoc(m):" << car->InitLoc << " ";	//车辆初始位置：Initial Location
	//	ofs << "V(m/t):" << car->v << " ";			//车辆行驶速度：Velocity
	//	ofs << "AT:" << car->at << " ";		//车辆到达时间/产生任务时间：Arrive Time
	//	ofs << "DT:" << car->dt << " ";		//完成任务截止时间：Deadline Time
	//	ofs << "ET:" << car->et << " ";		//执行任务时间：Execution Time
	//	ofs << "CM:" << endl;
	//	//遍历外边的 vector<vector<bool>>，行：基站
	//	for (vector<vector<bool>>::iterator rit = car->CM.begin(); rit != car->CM.end(); rit++)
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
	////大型车辆任务的可连接矩阵
	//for (vector<CarInfo>::iterator car = RS_L_vCarInfo.begin(); car != RS_L_vCarInfo.end(); car++)
	//{
	//	//数据格式：编号   类型   出发点   速度 到达时间 截止时间 可连接矩阵
	//	//数据格式：CarId  Type   InitLoc   V      AT       DT       CM
	//	//			可连接矩阵
	//	ofs << "CarId:" << car->id << " ";	//车辆编号：表示这是第几辆车子 
	//	ofs << "Type:" << car->type << " ";		//车辆/任务类型：S/M/L 
	//	ofs << "InitLoc(m):" << car->InitLoc << " ";	//车辆初始位置：Initial Location
	//	ofs << "V(m/t):" << car->v << " ";			//车辆行驶速度：Velocity
	//	ofs << "AT:" << car->at << " ";		//车辆到达时间/产生任务时间：Arrive Time
	//	ofs << "DT:" << car->dt << " ";		//完成任务截止时间：Deadline Time
	//	ofs << "ET:" << car->et << " ";		//执行任务时间：Execution Time
	//	ofs << "CM:" << endl;
	//	//遍历外边的 vector<vector<bool>>，行：基站
	//	for (vector<vector<bool>>::iterator rit = car->CM.begin(); rit != car->CM.end(); rit++)
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

	//2. 保存“供算法调入使用”的随机抽取的车辆信息
	SaveCarInfoAsInput(RS_S_vCarInfo, "S", RS_S_vCarInfo.size());
	//SaveCarInfoAsInput(RS_M_vCarInfo, "M", RS_M_vCarInfo.size());
	//SaveCarInfoAsInput(RS_L_vCarInfo, "L", RS_L_vCarInfo.size());
	
	cout << "已经随机抽取 " << RS_T_CarNum << " 条车辆任务信息并保存到 RS_CarInfo_" + to_string(RS_S_CarNum) + "_" + to_string(RS_M_CarNum) + "_" + to_string(RS_L_CarNum) + "-" + to_string(ExeNum) + ".txt 中！" << endl;
	cout << "其中，小型车辆任务数量为：" << RS_S_vCarInfo.size() << ","
		<< "中型车辆任务数量为：" << RS_M_vCarInfo.size() << ","
		<< "大型车辆任务数量为：" << RS_L_vCarInfo.size() << "." << endl;
}
//封装一个函数，用来 保存“供算法输入使用”的车辆任务信息
void SaveCarInfoAsInput(vector<CarInfo>& rsCar, string type, int rscarnum)
{
	ofstream ofs;
	//(1)保存随机抽取的车辆信息（不包括车辆可连接矩阵CM）
	//string CarInfoFile_Input = "../data/2RandomSampling/exp1/data_RS_CarInfo_" + type + "_" + to_string(rscarnum) + "-" + to_string(ExeNum) + ".txt";	//抽取实验一数据使用
	//string CarInfoFile_Input = "../data/2RandomSampling/exp2/data_CarInfo_50%_5000_0_5000/data_RS_CarInfo_" + type + "_" + to_string(rscarnum) + "-" + to_string(ExeNum) + ".txt";	//抽取实验二数据使用
	string CarInfoFile_Input = "../data/2RandomSampling/exp3/EcsInfo_9_0_1/data_RS_CarInfo_" + type + "_" + to_string(rscarnum) + "-" + to_string(ExeNum) + ".txt";	//抽取实验三数据使用
	ofs.open(CarInfoFile_Input, ios::out | ios::trunc);
	for (vector<CarInfo>::iterator rscar = rsCar.begin(); rscar != rsCar.end(); rscar++)
	{
		//数据格式：编号   类型   出发点   速度 到达时间 截止时间 执行时间 任务资源需求			投标	投标系数		
		//数据格式：CarId  Type   InitLoc  v    at       dt       et       TaskResourceDemand   b		BidCoefficient   
		ofs << rscar->id << " ";		//车辆编号：表示这是第几辆车子 
		ofs << rscar->type << " ";		//车辆/任务类型：S/M/L 
		ofs << rscar->InitLoc << " ";	//车辆初始位置：Initial Location
		ofs << rscar->v << " ";			//车辆行驶速度：Velocity
		ofs << rscar->at << " ";		//车辆到达时间/产生任务时间：Arrive Time
		ofs << rscar->dt << " ";		//任务截止时间：Deadline Time
		ofs << rscar->et << " ";		//执行任务时间：Execution Time			
		ofs << rscar->TRD->cpu << " " << rscar->TRD->gpu << " " << rscar->TRD->memory << " " << rscar->TRD->disk << " ";	//任务资源需求：TaskResourceDemand
		ofs << rscar->bid << " ";		//投标: Bid
		ofs << rscar->mu << endl;		//投标系数: BidCoefficient
	}
	ofs.close();

	//(2)保存随机抽取的车辆可连接矩阵CM
	//string CarCMFile_Input = "../data/2RandomSampling/exp1/data_RS_Car_CM_" + type + "_" + to_string(rscarnum) + "-" + to_string(ExeNum) + ".txt";	//抽取实验一数据使用
	//string CarCMFile_Input = "../data/2RandomSampling/exp2/data_CarInfo_50%_5000_0_5000/data_RS_Car_CM_" + type + "_" + to_string(rscarnum) + "-" + to_string(ExeNum) + ".txt";	//抽取实验二数据使用
	string CarCMFile_Input = "../data/2RandomSampling/exp3/EcsInfo_9_0_1/data_RS_Car_CM_" + type + "_" + to_string(rscarnum) + "-" + to_string(ExeNum) + ".txt";	//抽取实验三数据使用
	ofs.open(CarCMFile_Input, ios::out | ios::trunc);
	for (vector<CarInfo>::iterator rscar = rsCar.begin(); rscar != rsCar.end(); rscar++)
	{
		for (vector<vector<bool>>::iterator rit = rscar->CM.begin(); rit != rscar->CM.end(); rit++)	//遍历矩阵 CM 的行：M
		{
			for (vector<bool>::iterator cit = (*rit).begin(); cit != (*rit).end(); cit++)	//遍历矩阵 CM 每行中的每列：T
			{
				ofs << (*cit) << " ";
			}
			ofs << endl;
		}
		ofs << endl;
	}
	ofs.close();

}

int main()
{
	srand((unsigned)time(NULL));

	//1.读入 1GenerateData 生成的大数据库
	time_t tLoadData_begin, tLoadData_end;
	tLoadData_begin = clock();
	//(1)读入基站信息
	LoadEcsInfo(EcsInfoFile);
	//(2)读入车辆信息
	//预留空间 : 
	S_vCarInfo.reserve(41000);
	M_vCarInfo.reserve(41000);
	L_vCarInfo.reserve(41000);

	RS_S_vCarInfo.reserve(22000);
	RS_M_vCarInfo.reserve(22000);
	RS_L_vCarInfo.reserve(22000);

	LoadCarInfo(CarInfoFile_S, CarInfoFile_S_CM, S_vCarInfo, S_tCarNum);	//小型车辆任务信息
	//LoadCarInfo(CarInfoFile_M, CarInfoFile_M_CM, M_vCarInfo, M_tCarNum);	//中型车辆任务信息
	//LoadCarInfo(CarInfoFile_L, CarInfoFile_L_CM, L_vCarInfo, L_tCarNum);	//大型车辆任务信息

	tLoadData_end = clock();
	LoadData_RunTime = static_cast<double>(tLoadData_end - tLoadData_begin) / CLOCKS_PER_SEC;

	cout << "读入数据花费时间：LoadData_Runtime = " << LoadData_RunTime << " s" << endl;
	cout << endl;

	//测试：是否成功读入基站和车辆任务信息(成功)

	/*cout << "读入的基站信息如下：" << endl;
	for (int j = 0; j < vEcsInfo.size(); j++)
	{
		cout << "基站：id = " << vEcsInfo[j].id;
		cout << " type = " << vEcsInfo[j].type;
		cout << " CR = " << vEcsInfo[j].CR;
		cout << " loc = " << vEcsInfo[j].loc;
		cout << " CA = [" << vEcsInfo[j].CA[0] << "," << vEcsInfo[j].CA[1] << "] ";
		cout << " RC = <" << vEcsInfo[j].RC->cpu << " " << vEcsInfo[j].RC->gpu << " " << vEcsInfo[j].RC->memory << " " << vEcsInfo[j].RC->disk << "> ";
		cout << endl;
	}
	cout << endl;
	cout << "抽取的小型车辆信息如下：" << endl;
	for (int i = 0; i < S_vCarInfo.size(); i++)
	{
		cout << "车辆 " << i << " : id = " << S_vCarInfo[i].id
			<< " type = " << S_vCarInfo[i].type
			<< " InitLoc(m) = " << S_vCarInfo[i].InitLoc
			<< " v(m/s) = " << S_vCarInfo[i].v
			<< " at = " << S_vCarInfo[i].at
			<< " dt = " << S_vCarInfo[i].dt
			<< " et = " << S_vCarInfo[i].et
			<< " TR[4] = [" << S_vCarInfo[i].TR->cpu << ", " << S_vCarInfo[i].TR->gpu << ", " << S_vCarInfo[i].TR->memory << ", " << S_vCarInfo[i].TR->disk << "] "
			<< " mu = " << S_vCarInfo[i].mu << " bid = " << S_vCarInfo[i].bid << " CM = " << endl;
		for (int j = 0; j < M; j++)
		{
			for (int t = 0; t < T; t++)
			{
				cout << S_vCarInfo[i].CM[j][t] << " ";
			}
			cout << endl;
		}
	}
	cout << "抽取的中型车辆信息如下：" << endl;
	for (int i = 0; i < M_vCarInfo.size(); i++)
	{
		cout << "车辆 " << i << " : id = " << M_vCarInfo[i].id
			<< " type = " << M_vCarInfo[i].type
			<< " InitLoc(m) = " << M_vCarInfo[i].InitLoc
			<< " v(m/s) = " << M_vCarInfo[i].v
			<< " at = " << M_vCarInfo[i].at
			<< " dt = " << M_vCarInfo[i].dt
			<< " et = " << M_vCarInfo[i].et
			<< " TR[4] = [" << M_vCarInfo[i].TR->cpu << ", " << M_vCarInfo[i].TR->gpu << ", " << M_vCarInfo[i].TR->memory << ", " << M_vCarInfo[i].TR->disk << "] "
			<< " mu = " << M_vCarInfo[i].mu << " bid = " << M_vCarInfo[i].bid << " CM = " << endl;
		for (int j = 0; j < M; j++)
		{
			for (int t = 0; t < T; t++)
			{
				cout << M_vCarInfo[i].CM[j][t] << " ";
			}
			cout << endl;
		}
	}
	cout << "抽取的大型车辆信息如下：" << endl;
	for (int i = 0; i < L_vCarInfo.size(); i++)
	{
		cout << "车辆 " << i << " : id = " << L_vCarInfo[i].id
			<< " type = " << L_vCarInfo[i].type
			<< " InitLoc(m) = " << L_vCarInfo[i].InitLoc
			<< " v(m/s) = " << L_vCarInfo[i].v
			<< " at = " << L_vCarInfo[i].at
			<< " dt = " << L_vCarInfo[i].dt
			<< " et = " << L_vCarInfo[i].et
			<< " TR[4] = [" << L_vCarInfo[i].TR->cpu << ", " << L_vCarInfo[i].TR->gpu << ", " << L_vCarInfo[i].TR->memory << ", " << L_vCarInfo[i].TR->disk << "] "
			<< " mu = " << L_vCarInfo[i].mu << " bid = " << L_vCarInfo[i].bid << " CM = " << endl;
		for (int j = 0; j < M; j++)
		{
			for (int t = 0; t < T; t++)
			{
				cout << L_vCarInfo[i].CM[j][t] << " ";
			}
			cout << endl;
		}
	}*/
	
	//2.随机抽取五组车辆数据，每组车辆数据个数为 100, 500, 5000, 10000, 20000。且每组数据要抽取10次。
	// 供算法 OPT-TRAP 、OVMAP* 和 OTRAP 调入使用。
	for(; ExeNum <= SamplingNum; ExeNum++)
	//if(ExeNum <= SamplingNum)
	{
		cout << "这是第 " << ExeNum << " 次随机抽取（RandomSampling） " << RS_S_CarNum << "_" << RS_M_CarNum << "_" << RS_L_CarNum << " 条车辆任务信息！" << endl;

		time_t tSampling_begin, tSampling_end;
		tSampling_begin = clock();

		RandomSampling(S_vCarInfo, RS_S_vCarInfo, "S", RS_S_CarNum);		//随机抽取小型车辆任务信息
		//RandomSampling(M_vCarInfo, RS_M_vCarInfo, "M", RS_M_CarNum);		//随机抽取中型车辆任务信息
		//RandomSampling(L_vCarInfo, RS_L_vCarInfo, "L", RS_L_CarNum);		//随机抽取大型车辆任务信息
		
		tSampling_end = clock();
		Sampling_RunTime += static_cast<double>(tSampling_end - tSampling_begin) / CLOCKS_PER_SEC;

		time_t tSaveData_begin, tSaveData_end;
		tSaveData_begin = clock();
		
		//3.将信息保存到本地
		//(1)将基站信息保存到本地
		//SaveEcsInfo();
		//(2)将随机抽取的车辆数据保存到本地
		SaveCarInfo();

		tSaveData_end = clock();
		SaveData_RunTime += static_cast<double>(tSaveData_end - tSaveData_begin) / CLOCKS_PER_SEC;

		cout << "第 " << ExeNum << " 次随机采样花费时间：Sampling_RunTime = " << Sampling_RunTime << " s" << endl;
		cout << "第 " << ExeNum << " 次保存数据花费时间：SaveData_Runtime = " << SaveData_RunTime << " s" << endl;
		cout << endl;

		//保存好车辆信息后要及时清空容器，方便下次存取车辆任务信息
		RS_S_vCarInfo.clear();
		RS_M_vCarInfo.clear();
		RS_L_vCarInfo.clear();

		Sampling_RunTime = 0, SaveData_RunTime = 0;

	}

	//3.将信息保存到本地
	//(1)将基站信息保存到本地（只需要保存一次）
	SaveEcsInfo();

	system("pause");

	return 0;
}
