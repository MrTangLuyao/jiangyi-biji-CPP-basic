//��ͨԱ���ļ�
#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Employee :public Worker
{
public:

	//���캯��
	Employee(int id , string name , int dId);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡ��λ����
	virtual string getDeptName();

};