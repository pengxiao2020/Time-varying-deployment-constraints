#pragma once
#include "CarInfo.h"
#include "EcsInfo.h"

#include <random>
#include <tchar.h>
#include <windows.h>
using namespace std;


//�ý����������Ҫ���ܣ�����ʵ�����õĴ����ݿⲢ�����ݱ��浽����


//ʵ��˼·��
// (1)���Դ���׶�
// ��վ������10
// ��������30
// (2)ʵ��׶�
// �˳�����ҹ��������45000~80000��ÿСʱ��������1666~3333��ʱ��Σ�04:00am ~ 10:00am
// ��߷�ĳ�������ʱ����ѭ��̬�ֲ� at~N[T/2,(T/6)^2]����95%�ĳ����ĵ���ʱ�䶼Ӧ������[05:00am, 09:00am]
// Ϊ����������ԣ���������һ��������ݼ����������ȡ�̶��������ݣ�����ʵ�顣
// �������� 120,000 ���������ݲ���ʵ�飬��������С�д� ����������Ϣ�� 40,000 �������㷨���á�
// ��·���� �� L = 10000
// ʱ��ۣ�T = 2160�� 1t = 10s
// �����ٶ� v = [100,200]t/s = [10,20]m/s = [36,72]km/h; 
// ��վ�����뾶(4G��׼) S: 1000m, M: 2000m, L: 3000
// ��վ����10
// ��������С�ͳ������� 40000�� ���ͳ������� 40000�� ���ͳ������� 40000	

#define RoadLength 10000	//һά��·����
#define TTS 2160	//TTS = Total Time Slot
#define RKNum 4	    //��Դ�������the Number of Resources' Kind���ֱ�ָ�� CPU, GPU, Memory, Disk

#define S_EcsNum 9		//С�ͻ�վ��
#define M_EcsNum 0		//���ͻ�վ��
#define L_EcsNum 1		//���ͻ�վ��
#define tEcsNum (S_EcsNum+M_EcsNum+L_EcsNum)  //��վ����

#define S_CarNum 40000			//С�ͳ���������
#define M_CarNum 0			//���ͳ���������
#define L_CarNum 0			//���ͳ���������
#define tCarNum (S_CarNum+M_CarNum+L_CarNum)  //������������

//gamma�� 4 �൥λ��Դ��CPU,GPU,Memory,Disk���ĵ�λʱ��ʹ�óɱ�
const double gamma[4] = { 10, 40, 1, 0.03 };

#define S_ECS_CR 1000 //С�ͻ�վ���ǰ뾶
#define M_ECS_CR 2000 //С�ͻ�վ���ǰ뾶
#define L_ECS_CR 3000 //С�ͻ�վ���ǰ뾶

#define S_ECS_RC_CPU 20			//С�ͻ�վCPU����		40		50		100
#define S_ECS_RC_GPU 10			//С�ͻ�վGPU����		20		50		100
#define S_ECS_RC_MEMORY	40		//С�ͻ�վMEMORY����	80		200		400
#define S_ECS_RC_DISK 250		//С�ͻ�վDISK����		500		1600	3200

#define M_ECS_RC_CPU 40 		//���ͻ�վCPU����			
#define M_ECS_RC_GPU 20			//���ͻ�վGPU����
#define M_ECS_RC_MEMORY	80		//���ͻ�վMEMORY����
#define M_ECS_RC_DISK 500		//���ͻ�վDISK����

#define L_ECS_RC_CPU 80			//���ͻ�վCPU����
#define L_ECS_RC_GPU 40			//���ͻ�վGPU����
#define L_ECS_RC_MEMORY	160		//���ͻ�վMEMORY����
#define L_ECS_RC_DISK 1000		//���ͻ�վDISK����

const int L = RoadLength;
const int T = TTS;

//��һ���֣���վ���
//1.���ɻ�վ��Ϣ
void GenerateEcsInfo();
//����vector����������������ɵĻ�վ��Ϣ
vector<EcsInfo> vEcsInfo;
//����vector�������ֱ�������Ų�ͬ���ͻ�վ����Ϣ
vector<EcsInfo> s_vEcsInfo;	//���С�ͻ�վ������ s_vEcsInfo = small vEcsInfo
vector<EcsInfo> m_vEcsInfo;	//������ͻ�վ������ m_vEcsInfo = medium vEcsInfo
vector<EcsInfo> l_vEcsInfo;	//��Ŵ��ͻ�վ������ l_vEcsInfo = large vEcsInfo
//��װһ�������������ɻ�վλ��
int CalcEcsLoc(EcsInfo& ei);
//ʹ������arrCA[2]����Ż�վ���Ƿ�Χ
int* CalcEcsCA(EcsInfo& ei);

//�ڶ����֣��������
//1.���ɳ�����Ϣ
void GenerateCarInfo();
//��ų�����Ϣ��������vector<CarInfo>
vector<CarInfo> vCarInfo;
//����vector�������ֱ�������Ų�ͬ���͵ĳ�����Ϣ
vector<CarInfo> s_vCarInfo;	//���С�ͳ��������� s_vCarInfo = small vCarInfo
vector<CarInfo> m_vCarInfo;	//������ͳ��������� m_vCarInfo = medium vCarInfo
vector<CarInfo> l_vCarInfo;	//��Ŵ��ͳ��������� l_vCarInfo = large vCarInfo

vector<int> vCarIL;		//��ų�����ʼλ�� InitLoc ������
vector<int> vCarAT;		//��ų�������ʱ�� ArrivalTime ������
vector<double>vCarBC;	//��ų���Ͷ��ϵ�� BidCoefficient ������ 
						//һ�복����Ͷ��ϵ��Ϊ[0.25,1],��һ�복����Ͷ��ϵ��Ϊ[1,4]
						
//(1)���ɳ�����ʼλ��(��ǰλ��)�ĺ��� InitialLocation(CurrentLocation)
void UniformDistributionCarIL();
//(2)���ɳ�������ʱ��ĺ���
//�������� Normal Distribution ����������������ɳ�������ʱ��
void NormalDistributionCarAT();
//(3)���ɳ�����ֹʱ��ĺ���
int GenerateCarDT(CarInfo& ci);
//(4)���ɳ���Ͷ��ϵ���ĺ���
//�������� Uniform Distribution ����������������ɳ���Ͷ��ϵ����
void UniformDistributionCarBC();
//(5)����Ͷ��ĺ���
double CalcCarBid(CarInfo& ci);
//(6)���㳵����ʱ�䲿��Լ������Ҳ�п����Ӿ��� Calculate Car's Connectable Matrix
vector<vector<bool>> CalcCarCM(CarInfo& ci);

//�������֣������ɵ����ݱ��浽����
//1.����վ��Ϣ���浽���ع��û��鿴
void SaveEcsInfo();
////(1)��װһ���������ѻ�վ�������Ա��浽��ͬ�ļ��У����㷨����ʹ��
//void SaveEcsInfoAsInput(vector<EcsInfo>& v, string type, int ecsnum);
//(2)��װһ���������������Դ��������
void WriteEcsRC(ofstream& ofs, int val);
//2.��������Ϣ(�������Ӿ�����)���浽����
void SaveCarInfo();
//��װһ���������ѳ����ĸ������Ա��浽��ͬ�ļ��У����㷨����ʹ��
void SaveCarInfoAsInput(vector<CarInfo>& v, string type, int carnum);
//(1)��װһ�������������������������Դ��������
void WriteCarTR(ofstream& ofs, int val);