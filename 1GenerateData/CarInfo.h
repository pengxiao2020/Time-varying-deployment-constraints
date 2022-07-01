#pragma once
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>		//�ڽ���������
#include <numeric>
using namespace std;

class CarInfo
{
public:
    //����

    //�������:1~tCarNum��
    int m_carId = 0;

    //��������: s / m / l
    string type;

    //������ʼλ�ã���ǰλ�ã����Ӿ��ȷֲ� U[0,L],  il = Initial Location
    int m_il = 0;

    //�����ٶ�: ��m/sΪ��λ����Χ: v = [10,20]m/s = [100,200]m/t
    int m_v = 0;

    //����ʱ��, ������̬�ֲ� N[T/2,(T/8)^2] 
    int m_at = 0;         //at = ArriveTime

    //������ɽ�ֹʱ�� d[i]
    int m_dt = 0;         // dt = DeadlineTime

    //ִ��ʱ��e[i]
    int m_et = 0;         // et = ExecutionTime

    //������Դ����s[i]������������Դ��(CPU, GPU, Memory, Disk)
    //ע�� m_c.size() == m_s.size()�����߶�ӦԪ�ص�����������Ӽ�����Դ��������գ�
    vector<int> m_s;

    //Ͷ��ϵ�� mu[i] = [0.25, 4]
    //���Ӿ��ȷֲ� U[0.25, 4]
    double m_mu = 0.00;     //ϣ����ĸ mu = BidCoefficient

    //Ͷ��b[i]
    double m_b = 0.00;      // b = Bid

    //�����Ŀ����Ӿ���(ConnectableMatrix) = ʱ�䲿��Լ������
    vector<vector<bool>> m_cm;

    //����p[i]
    double m_p = 0.00;       // p = Payment

};
