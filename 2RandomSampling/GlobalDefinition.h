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

// �ý����������Ҫ���ܣ�
// (1)���� 1GenerateData ���ɵĴ����ݿ�
// (2)�����ȡ���鳵�����ݣ�ÿ�鳵�����ݸ���Ϊ 100, 500, 5000, 10000, 20000����ÿ������Ҫ��ȡ10�Ρ�
// (3)�������ȡ�����ݱ��浽����

/* �������������ڽ���ʵ��һ������Ҫ���� С�ͳ�����Ϊ100ʱ���㷨��õ���ḣ����ִ��ʱ�䡢������������Դ�����ʡ�
 * 1.����Ҫ��������ݿ�CarInfo_40000_40000_40000�е����ݣ����ֱ����40000��С�ͳ������ݡ�40000�����ͳ������ݺ�40000�����ͳ������ݡ�
 * 2.��40000��С�ͳ������������ȡ 100 ��С�ͳ������ݣ�����Ҫ�����ȡ10�Ρ����ͳ������ݺʹ��ͳ���������Ȼ��
 * 3.��ô��С�ͳ�����Ϊ100ʱ��ϵͳ��õ���ḣ�� = ��10�� 100��С�ͳ������ݻ�õ���ḣ�� ֮�ͣ� / 10��
 */

const int SamplingNum = 10;	//�����ȡ�ܴ���,�̶�Ϊ10��
int ExeNum = 1;				//��ǰ��ȡ����,��ʼֵΪ1

//�����ļ�����
#define EcsInfoFile "../data/1GenerateData/exp3/EcsInfo_9_0_1/data_EcsInfo_9_0_1.txt"
//���� �����Ӿ��� �� ���೵������ �ֿ�����
#define CarInfoFile_S "../data/1GenerateData/exp3/EcsInfo_9_0_1/data_CarInfo_S_40000.txt"		//С�ͳ���������Ϣ
#define CarInfoFile_S_CM "../data/1GenerateData/exp3/EcsInfo_9_0_1/data_Car_CM_S_40000.txt"		//С�ͳ��������Ӿ���

#define CarInfoFile_M "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_CarInfo_M_40000.txt"		//���ͳ���������Ϣ
#define CarInfoFile_M_CM "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_Car_CM_M_40000.txt"		//���ͳ��������Ӿ���

#define CarInfoFile_L "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_CarInfo_L_40000.txt"		//���ͳ���������Ϣ
#define CarInfoFile_L_CM "../data/1GenerateData/exp1_exp2/CarInfo_40000_40000_40000/data_Car_CM_L_40000.txt"		//���ͳ��������Ӿ���


#define RoadLength 10000	//��·����
#define TTS 2160		//��ʱ��� TTS = Total Time Slot

#define RESOURCE 4		//����4����Դ��CPU,GPU,Memory,Disk

#define S_EcsNum 9		//�����С�ͻ�վ��
#define M_EcsNum 0		//��������ͻ�վ��
#define L_EcsNum 1		//����Ĵ��ͻ�վ��
#define tEcsNum (S_EcsNum+M_EcsNum+L_EcsNum)  //��վ����

#define RS_S_CarNum 10000		//�����ȡ��С�ͳ��������� 
#define RS_M_CarNum 0		//�����ȡ�����ͳ���������
#define RS_L_CarNum 0		//�����ȡ�Ĵ��ͳ���������
#define RS_T_CarNum (RS_S_CarNum+RS_M_CarNum+RS_L_CarNum)  //�����ȡ�ĳ�����������

#define S_tCarNum 40000	//С�ͳ�����������
#define M_tCarNum 40000	//���ͳ����������� 
#define L_tCarNum 40000	//���ͳ����������� 

const int T = TTS;			//ʱ���
const int M = tEcsNum;		//��վ����
const int N = RS_T_CarNum;	//�����ȡ�ĳ�����������
const int R = RESOURCE;		//RKNum = Resource Kind Number ��Դ������

const double gamma[R] = { 10, 40, 1, 0.03 };	//gamma�� 4 �൥λ��Դ��CPU,GPU,Memory,Disk���ĵ�λʱ��ʹ�óɱ�

//�����Զ���ṹ�壺��Դ
//������ ��վ��Դ����������������Դ����
struct Resource
{
	int cpu = 0;	//��Դ:cpu
	int gpu = 0;	//��Դ:gpu
	int memory = 0;	//��Դ:memory
	int disk = 0;	//��Դ:disk
};