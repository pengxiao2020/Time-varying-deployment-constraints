#pragma once
#include "GlobalDefinition.h"
#include "EcsInfo.h"
#include "CarInfo.h"

//��һ������������
//�����վ��Ϣ��һ���Զ��ꡣ
void LoadEcsInfo(string EcsInfofile);	
//��ȡ������Ϣ�������Ͷ���
void LoadCarInfo(string CarInfofile, string CarCMfile,int CarNum, CarInfo * carp);


//�ڶ��������亯�����������ŷ�����
int * TRAP_IP(CarInfo * carp);
int LessthanOrEqual(int a, int b);		//����С�ڵ��ڵ�������ֵ
int GreaterthanOrEqual(int a, int b);	//���ش��ڵ��ڵ�������ֵ

//��������֧���������������������
void TRAP_PAY(int* X);
//��װһ���������� Car[i] �߳���������Car[]��
//������env, model, cplex, ��������[], Ҫ�߳��ĳ���
void RemoveCar_i(CarInfo* carp, int id);
//��װһ���������ָ� Car[i] ����Ϣ
void RecoverCar_i(CarInfo* carp, int id);

//���Ĳ���������,���浽����
void SaveResult();

void CalcUsageRatio();	//������Դ������

void CalcServedCarRatio();	//�������������

