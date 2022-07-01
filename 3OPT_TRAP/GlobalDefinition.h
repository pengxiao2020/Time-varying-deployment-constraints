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

#include <ilcplex/ilocplex.h>

//����Ŀ ��ע�� �Ǳ�Ҫ��ʾ�Ĳ��Դ��룬��Ҫ�����빦�ܣ�������ȡ��ע��

// /../��ʾ����ǰĿ¼��һ��

const int count_OPT_TRAP = 10;		// OPT_TRAP ���д�������Ϊ 10
int ExeNum = 1;						// �ڼ������г��򣬳�ʼֵΪ 1
int count_TRAP_IP = 1;				// ��¼���ŷ����㷨 TRAP-IP() �����õĴ�������ʼֵΪ 1

// ����ʵ��Ҫ��ÿ�����д���֮ǰ��Ҫ���ݡ�ʹ�õĻ�վ��Ϣ�����޸� �ļ�·�� �� �ļ�������
// ../data/2RandomSampling/exp1/data_RS_CarInfo_S_100-
// ../data/2RandomSampling/exp1/data_RS_CarInfo_S_500-
#define EcsInfoFile "../data/2RandomSampling/exp1/data_EcsInfo_10_0_0.txt"	//��վ��Ϣ	

// ���ݲ��õ�ʵ��Ҫ��ÿ�����д���֮ǰ��Ҫ�޸Ĵ�š�����������Ϣ����·�����ļ������磺
//���� �����Ӿ��� �� ���೵������ �ֿ�����
#define RS_CarInfoFile_S "../data/2RandomSampling/exp1/data_RS_CarInfo_S_500-" + to_string(ExeNum) +".txt"		//С�ͳ���������Ϣ
#define RS_CarInfoFile_S_CM "../data/2RandomSampling/exp1/data_RS_Car_CM_S_500-" + to_string(ExeNum) +".txt"		//С�ͳ��������Ӿ���

#define RS_CarInfoFile_M "../data/2RandomSampling/exp1/data_RS_CarInfo_M_500-" + to_string(ExeNum) +".txt"		//���ͳ���������Ϣ
#define RS_CarInfoFile_M_CM "../data/2RandomSampling/exp1/data_RS_Car_CM_M_500-" + to_string(ExeNum) +".txt"		//���ͳ��������Ӿ���

#define RS_CarInfoFile_L "../data/2RandomSampling/exp1/data_RS_CarInfo_L_500-" + to_string(ExeNum) +".txt"		//���ͳ���������Ϣ
#define RS_CarInfoFile_L_CM "../data/2RandomSampling/exp1/data_RS_Car_CM_L_500-" + to_string(ExeNum) +".txt"		//���ͳ��������Ӿ���

#define RoadLength 10000	//��·����
#define TTS 2160		//��ʱ��� TTS = Total Time Slot

#define RESOURCE 4		//����4����Դ��CPU,GPU,Memory,Disk

#define S_EcsNum 10		//�����С�ͻ�վ��
#define M_EcsNum 0		//��������ͻ�վ��
#define L_EcsNum 0		//����Ĵ��ͻ�վ��
#define tEcsNum (S_EcsNum+M_EcsNum+L_EcsNum)  //��վ����

//���ݶ�����ļ�����ͬ��ÿ��������Ҫ���ò�ͬ�����֣�������������
#define S_CarNum 500     //�����С�ͳ��������� 
#define M_CarNum 0     //��������ͳ���������
#define L_CarNum 0     //����Ĵ��ͳ���������
#define tCarNum (S_CarNum+M_CarNum+L_CarNum)  //������������

const int T = TTS;		//ʱ���
const int M = tEcsNum;	//����Ļ�վ����
const int N = tCarNum;	//����ĳ�����������
const int R = RESOURCE;	//RKNum = Resource Kind Number ��Դ������

//�����Զ���ṹ�壺��Դ
//������ ��վ��Դ����������������Դ����
struct Resource
{
	//��Դ�����а���������Դ
	int cpu = 0;	//��Դ : cpu
	int gpu = 0;	//��Դ : gpu
	int memory = 0; //��Դ : memory
	int disk = 0;	//��Դ : disk
};

string Status;					//��õĽ�����ʣ�Optimal��ʾ���Ž�
double SocialWelfare = 0.00;	//���������ḣ��
double RunTime = 0.00;			//TRAP-IP�㷨������ʱ��

int AllocResult[N];			//��ŷ�����������
double Payment[N];			//��ų������������

//����һ����ά����cnt[i][j][t]���������ϵͳ�����ӽ�� cnt = connectivity
//cnt[i][j][t] = cplex.getValue(x[i][j][t]);
int cnt[N][M][T];
//����һ����ά����tmp_cnt[i][j][t]���ݴ�����ϵͳ�����ӽ�����������ݻָ�
int tmp_cnt[N][M][T];

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