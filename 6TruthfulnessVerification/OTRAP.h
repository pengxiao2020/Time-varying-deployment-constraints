#pragma once
#include "GlobalDefinition.h"
#include "EcsInfo.h"
#include "CarInfo.h"

//��һ������������
vector<EcsInfo> vEcsInfo;	//������л�վ��Ϣ������

vector<CarInfo> T_vCarInfo;	//������г�����Ϣ������

//vector<CarInfo> S_vCarInfo;	//���С�ͳ�����Ϣ������
//vector<CarInfo> M_vCarInfo;	//������ͳ�����Ϣ������
//vector<CarInfo> L_vCarInfo;	//��Ŵ��ͳ�����Ϣ������

//�����վ��Ϣ��һ���Զ��ꡣ
void LoadEcsInfo(string EcsInfofile);
//���복����Ϣ�������Ͷ���
void LoadCarInfo(string CarInfofile, string CarCMfile, vector<CarInfo>& vCar, int CarNum);

//�ڶ�����ÿ��ʱ���ִ��һ��OTRAP�㷨
vector<CarInfo> BeAllocatedCar;	//��÷���������ִ������ĳ�������
vector<CarInfo> UnAllocatedCar;	//δ��÷����Ҵ���������Ч�ڵĳ�������

vector<CarInfo> AllocResult;		//��ֹ��[1,t]����÷�������г�������
vector<CarInfo> cts_AllocResult;	//��ǰʱ��۵ķ����� cts = current tims slot

vector<CarInfo> tmp_X;			//���ÿ������ OTRAP_ALLOC ��õ�����ĳ������ϣ��´����� OTRAP_ALLOC ǰ���

//1.OTRAP �㷨���
void OTRAP(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& Car);		//OTRAP�㷨���
void IsEcsRCEmpty();		//�ж� ���л�վ���� �Ƿ�Ϊ��
bool EcsRCEmpty = false;	//��� ���л�վ��Դ�Ƿ�գ���ʼֵΪ false

//2.OTRAP ���亯��
void OTRAP_ALLOC(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& BACar, vector<CarInfo>& UACar);	//OTRAP ���亯��
bool EcsInDegreeAscend(const EcsInfo& ecs1, const EcsInfo& ecs2);	//����վ�������Ի�վ����
void Calc_CarValueDensity(CarInfo& car, EcsInfo& ecs);	//���㳵������Դ�ܶ� Car[i].f
bool CarValueDensityDescend(const CarInfo& car1, const CarInfo& car2);	//�� ������Դ�ܶ�Car[i].f ����Գ�������

//3.OTRAP ֧�����������ַ���
void OTRAP_PAY(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& BACar, vector<CarInfo>& UACar, vector<CarInfo>& cts_AR);


//��������������,���浽����
void SaveResult();
void CalcUsageRatio();	//������Դ������
void CalcServedCarRatio();	//�������������
void CalcNormalPayRatio();	//������������ĳ�������
