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
#include <functional>		//�ڽ���������
#include <numeric>
using namespace std;

//����Ŀ ��ע�� �Ǳ�Ҫ��ʾ�Ĳ��Դ��룬��Ҫ�����빦�ܣ�������ȡ��ע��

const int count_OVMAP_mod = 10;			// OVMAP_mod ���д�������Ϊ 10
int ExeNum = 1;							// �ڼ������г��򣬳�ʼֵΪ 1


// ����ʵ��Ҫ��ÿ��ʵ��֮ǰ��Ҫ���ݡ�ʹ�õĻ�վ��Ϣ�����޸� �ļ�·�� �� �ļ���
#define EcsInfoFile "../data/2RandomSampling/exp3/EcsInfo_5_0_5/data_EcsInfo_5_0_5.txt"	//��վ��Ϣ

//���ݲ��õ�ʵ��Ҫ����Ҫ�޸Ĵ�š�����������Ϣ����·�����ļ������磺
//���� �����Ӿ��� �� ���೵������ �ֿ����棨����ĳ�����ϢС�� 20000 ����
//ʵ��һ�����޸�С�ͳ�����ȡ�ļ�·����/exp1/data_RS_CarInfo_S_xxxxx-
//ʵ�����Ҫ�޸ġ�С�ͳ�����ȡ�ļ�·�� �� ���ͳ�����ȡ�ļ�·������С�ͳ�����ȡ�ļ�·�� �� ���ͳ�����ȡ�ļ�·����:/exp2/data_CarInfo_5%_9500_0_500/data_RS_CarInfo_S_9500-

#define RS_CarInfoFile_S "../data/2RandomSampling/exp3/EcsInfo_5_0_5/data_RS_CarInfo_S_10000-" + to_string(ExeNum) + ".txt"	//С�ͳ���������Ϣ
#define RS_CarInfoFile_S_CM "../data/2RandomSampling/exp3/EcsInfo_5_0_5/data_RS_Car_CM_S_10000-" + to_string(ExeNum) + ".txt"	//С�ͳ��������Ӿ���(ʱ�䲿��Լ������)

#define RS_CarInfoFile_M "../data/2RandomSampling/exp1/data_RS_CarInfo_M_10000-" + to_string(ExeNum) + ".txt"	//���ͳ���������Ϣ
#define RS_CarInfoFile_M_CM "../data/2RandomSampling/exp1/data_RS_Car_CM_M_10000-" + to_string(ExeNum) + ".txt"	//���ͳ��������Ӿ���(ʱ�䲿��Լ������)

#define RS_CarInfoFile_L "../data/2RandomSampling/exp2/data_CarInfo_5%_9500_0_500/data_RS_CarInfo_L_500-" + to_string(ExeNum) + ".txt"	//���ͳ���������Ϣ
#define RS_CarInfoFile_L_CM "../data/2RandomSampling/exp2/data_CarInfo_5%_9500_0_500/data_RS_Car_CM_L_500-" + to_string(ExeNum) + ".txt"	//���ͳ��������Ӿ���(ʱ�䲿��Լ������)


#define RoadLength 10000	//��·����
#define TTS 2160		//��ʱ��� TTS = Total Time Slot

#define RESOURCE 4		//����4����Դ��CPU,GPU,Memory,Disk

#define S_EcsNum 5		//�����С�ͻ�վ��
#define M_EcsNum 0		//��������ͻ�վ��
#define L_EcsNum 5		//����Ĵ��ͻ�վ��
#define tEcsNum (S_EcsNum+M_EcsNum+L_EcsNum)  //��վ����

//���ݶ�����ļ�����ͬ��ÿ��������Ҫ���ò�ͬ�����֣�������������
//ʵ�����������͡����ͳ���������Ϣ����Ϊ��0%, 5%, 10%, 20%, 50% 
#define S_CarNum 10000		//�����С�ͳ��������� 
#define M_CarNum 0			//��������ͳ���������
#define L_CarNum 0		//����Ĵ��ͳ���������
#define tCarNum (S_CarNum+M_CarNum+L_CarNum)  //������������

const int T = TTS;		//ʱ���
const int M = tEcsNum;	//��վ����
const int N = tCarNum;	//������������
const int R = RESOURCE;	//RKNum = Resource Kind Number ��Դ������

const double gamma[R] = { 10, 40, 1, 0.03 };	//gamma�� 4 �൥λ��Դ��CPU,GPU,Memory,Disk���ĵ�λʱ��ʹ�óɱ�

const double epsilon = 0.000001;	//����һ����С�����֣�OVMAP_mod_PAY ȷ������ʹ��

double TotalSocialWelfare = 0.00;	//��ֹ��[1,t], ������ḣ��
double cts_SocialWelfare = 0.00;	//��ǰʱ�����õ���ḣ�� cts = current tims slot

double RunTime = 0.00;					//OVMAP_mod �㷨������ʱ��
double PreWork_RunTime = 0.00;			//1. OVMAP_mod �㷨׼������������ʱ��
double ReturnResource_RunTime = 0.00;	//1.1 �������� Cars �黹 ECS ��Դ������ʱ��
double DelOvertimeTask_RunTime = 0.00;	//1.2 ɾ�� UnAllocatedCar �еĹ��ڳ�������������ʱ��
double AddArrivedCar_RunTime = 0.00;	//1.3 ���µ���ĳ���������ӽ����� UnAllocatedCar ������ʱ�� 

double ALLOC_RunTime = 0.00;			//2.OVMAP_mod_ALLOC ���亯������ʱ��

double PAY_RunTime = 0.00;				//3.OVMAP_mod_PAY ֧����������ʱ��

//�����Զ���ṹ�壺��Դ
//������ ��վ��Դ����������������Դ����
struct Resource
{
	//��Դ�����а���������Դ
	int cpu = 0;	//��Դ:cpu
	int gpu = 0;	//��Դ:gpu
	int memory = 0;	//��Դ:memory
	int disk = 0;	//��Դ:disk
};

struct Resource UsedResource;	//����ϵͳʹ�õ���Դ
struct Resource TotalResource;	//����ϵͳ����Դ����

double UR_t_cpu = 0.00;			//��CPU������
double UR_t_gpu = 0.00;			//��GPU������
double UR_t_memory = 0.00;		//��Memory������
double UR_t_disk = 0.00;		//��Disk������

double SR_t_Car = 0.00;		//����������
double SR_s_Car = 0.00;		//С�ͳ�������������
double SR_m_Car = 0.00;		//С�ͳ�������������
double SR_l_Car = 0.00;		//С�ͳ�������������

double NPR_t_Car = 0.00;	//��ȷ����ĳ������� NPR = Normal Pay Ratio
double NPR_s_Car = 0.00;	//��ȷ�����С�ͳ�������
double NPR_m_Car = 0.00;	//��ȷ��������ͳ�������
double NPR_l_Car = 0.00;	//��ȷ����Ĵ��ͳ�������