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

//EcsInfo �����������վ��Ϣ

//��վ��Ϣ �á��� class������ʾ
//��վ j ����Դ�������� c[i] ʹ�á����� vector���洢

class EcsInfo
{
public:
	//����
	//��վ��� 1~tEcsNum
	int m_ecsId = 0;

	//��վ���� S M L 
	string type;	//type = S/M/L;

	//��վλ�ã�һά��·�У��õ�m_loc��ʶ����ά��·��Ҫ��make_pair��ʾ
	int m_loc = 0;

	//��վ���ǰ뾶 coverage radius��100m, 200m, 300m
	int m_cr = 0;

	//��վ���Ƿ�Χ
	//���� m_loc ȷ������վ�ľ��帲�Ƿ�Χ m_aCA : member_arrayCoverageArea
	//m_aCA[2] = [�����䣬������] = [m_loc - m_cr, m_loc + m_cr]
	int m_aCA[2];

	//��Դ�������� m_c������������Դ��(CPU, GPU, Memory, Disk)
	//ע�� m_c.size() == m_s.size()�����߶�ӦԪ�ص�����������Ӽ�����Դ��������գ�
	vector<int> m_rc;

};
