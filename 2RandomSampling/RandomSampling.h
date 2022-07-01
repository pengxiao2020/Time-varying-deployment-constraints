#pragma once

#include "EcsInfo.h"
#include "CarInfo.h"

// �ý����������Ҫ���ܣ�
// 1.���� 1GenerateData ���ɵĴ����ݿ�
// 2.�����ȡ���鳵�����ݣ�ÿ�鳵�����ݸ���Ϊ 100, 500, 5000, 10000, 20000����ÿ������Ҫ��ȡ10�Ρ�
// 3.�������ȡ�����ݱ��浽����

/* �������������ڽ���ʵ��һ������Ҫ���� С�ͳ�����Ϊ100ʱ���㷨��õ���ḣ����ִ��ʱ�䡢������������Դ�����ʡ�
 * (1)����Ҫ��������ݿ�CarInfo_40000_40000_40000�е����ݣ����ֱ����40000��С�ͳ������ݡ�40000�����ͳ������ݺ�40000�����ͳ������ݡ�
 * (2)��40000��С�ͳ������������ȡ 100 ��С�ͳ������ݣ�����Ҫ�����ȡ10�Ρ����ͳ������ݺʹ��ͳ���������Ȼ��
 * (3)��ô��С�ͳ�����Ϊ100ʱ��ϵͳ��õ���ḣ�� = ��10�� 100��С�ͳ������ݻ�õ���ḣ�� ֮�ͣ� / 10��
 */

//1.���ļ��� 1GenerateData �ж������ɵ�����
int count_S_ECS = 0, count_M_ECS = 0, count_L_ECS = 0;
double LoadData_RunTime = 0.00;
double Sampling_RunTime = 0.00;
double SaveData_RunTime = 0.00;

vector<EcsInfo> vEcsInfo;	//������л�վ��Ϣ������

vector<CarInfo> T_vCarInfo;	//������г�����Ϣ������
vector<CarInfo> S_vCarInfo;	//���С�ͳ�����Ϣ������
vector<CarInfo> M_vCarInfo;	//������ͳ�����Ϣ������
vector<CarInfo> L_vCarInfo;	//��Ŵ��ͳ�����Ϣ������

//(1)�����վ��Ϣ
void LoadEcsInfo(string EcsInfofile);
//(2)���복��������Ϣ
void LoadCarInfo(string CarInfofile, string CarCMfile, vector<CarInfo>& Car, int CarNum);

//2.�����ȡ���鳵�����ݣ�ÿ�鳵�����ݸ���Ϊ 100, 500, 5000, 10000, 20000����ÿ������Ҫ��ȡ10�Ρ�
// ���㷨 OPT-TRAP ��OVMAP* �� OTRAP ����ʹ�á�
vector<CarInfo> RS_S_vCarInfo;	//��������ȡ��С�ͳ�������
vector<CarInfo> RS_M_vCarInfo;	//��������ȡ�����ͳ�������
vector<CarInfo> RS_L_vCarInfo;	//��������ȡ�Ĵ��ͳ�������

//(1)�����ȡ�̶������ĳ�����Ϣ
//��������������tCar = total Car
//�����ȡ�ĳ�����������rsCar = random sampling Car
void RandomSampling(vector<CarInfo>& Car, vector<CarInfo>& rsCar, string type, int SamplingNum);

//3.����Ϣ���浽����
//(1)����վ��Ϣ���浽����
void SaveEcsInfo();
//(2)�������ȡ�ĳ������ݱ��浽����
//exenum �ڼ���ִ�д���
void SaveCarInfo();
//��װһ���������������桰���㷨����ʹ�á��ĳ���������Ϣ
void SaveCarInfoAsInput(vector<CarInfo>& rsCar, string type, int rscarnum);


