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

vector<CarInfo> tmp_X;			//���ÿ������ OVMAP_mod_ALLOC ��õ�����ĳ������ϣ��´����� OVMAP_mod_ALLOC ǰ���

//1.OVMAP_mod �㷨���
void OVMAP_mod(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& Car);		//OVMAP_mod�㷨���
void IsEcsRCEmpty();		//�ж� ���л�վ���� �Ƿ�Ϊ��
bool EcsRCEmpty = false;	//��� ���л�վ��Դ�Ƿ�գ���ʼֵΪ false

//2.OVMAP_mod ���亯��
void OVMAP_mod_ALLOC(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& BACar, vector<CarInfo>& UACar);	//OVMAP_mod ���亯��
bool EcsInDegreeAscend(const EcsInfo& ecs1, const EcsInfo& ecs2);	//����վ�������Ի�վ����
void CalcCarBidDensity(CarInfo& car);	//���㳵����Ͷ���ܶ� f
bool CarBidDensityDescend(const CarInfo& car1, const CarInfo& car2);	//�� ����Ͷ���ܶ�Car[i].f ����Գ�������

//3.OVMAP_mod ֧�����������ַ���
void OVMAP_mod_PAY(int cts, vector<EcsInfo>& ECS, vector<CarInfo>& BACar, vector<CarInfo>& UACar, vector<CarInfo>& cts_AR);


//��������������,���浽����
void SaveResult();
void CalcUsageRatio();	//������Դ������
void CalcServedCarRatio();	//�������������
void CalcNormalPayRatio();	//������������ĳ�������
