#include "workerManager.h"
#include <fstream>
#include "worker.h"
#include <string>
#include "employee.h"
#include "manager.h"
#include "boss.h"

//���캯��
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ����������
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//�ļ����ڣ�����û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��!" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}


	//�ļ����м�¼

	//��ȡְ������
	int num = get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;

	this->m_EmpNum = num;

	this->m_EmpArray = new Worker * [this->m_EmpNum];

	//��ʼ��ְ��
	init_Emp(this->m_EmpArray);
}

//ͳ������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);


	int id;
	string name;
	string dname;

	int num = 0;
	//ifs.seekg(ios::beg); // ����ƶ����ļ���
	while (ifs >> id && ifs >> name &&  ifs >> dname)
	{
		//cout << "������ " << s.m_Name << " ѧ�ţ� " << s.m_SId << endl;
		num++;
	}
	ifs.close();

	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp(Worker ** sArray)
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	//	ifs.seekg(ios::beg); // ����ƶ����ļ���
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{

		//cout << "ְ���ţ� " << id << " ������ " << name << " ���źţ�"<<dId << endl;
		Worker * worker = NULL;
		if (dId == 1)  // 1��ͨԱ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) //2����
		{
			worker = new Manager(id, name, dId);
		}
		else //�ܲ�
		{
			worker = new Boss(id, name, dId);
		}
		sArray[index] = worker;


		index++;
	}
}

//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "��ӭ����ְ������ϵͳ��" << endl;
	cout << "0.�˳�����" << endl;
	cout << "1.����ְ��" << endl;
	cout << "2.ɾ��ְ��" << endl;
	cout << "3.��ʾ����ְ����Ϣ" << endl;
	cout << "4.�޸�ְ����Ϣ" << endl;
	cout << "5.����ְ����Ϣ" << endl;
	cout << "6.��ְ���������" << endl;
	cout << "7.����ĵ�" << endl;
}

//����ְ��
void WorkerManager::Add_Emp()
{
	cout << "����������ְ�������� " << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Worker ** newSpace = new Worker*[newSize];

		//��ԭ�ռ������ݴ�ŵ��¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//����������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "������� " << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			cin.get();

			cout << "������� " << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cin.get();

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;
			cin.get();

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1: //��ͨԱ��
				worker = new Employee(id,name,1);
				break;
			case 2: //����
				worker = new Manager(id, name, 2);
				break;
			case 3:  //�ϰ�
				worker = new Boss(id, name,3);
				break;
			default:
				break;
			}


			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µĸ���
		this->m_EmpNum = newSize;

		//���µ��ļ���
		this->save();

		//��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "����ְ����" << endl;

		//�ļ���ǰ��Ϊ��
		this->m_FileIsEmpty = false;
	}
	else
	{
		cout << "��������" << endl;
	}
}


//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		return;
	}

	//��ѧ��ɾ��
	cout << "��������Ҫɾ����ְ���ţ�" << endl;
	int id = 0;
	cin >> id;
	cin.get();
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;

			break;
		}
	}

	if (index != -1)  //˵��index��λ��������Ҫɾ��
	{
		for (int i = index; i < this->m_EmpNum - 1; i++)
		{
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;

		this->save();
		cout << "ɾ���ɹ���" << endl;
	}
	else
	{
		cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
	}
}


//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		return;
	}

	cout << "�������޸�ְ���ı�ţ�" << endl;
	int id;
	cin >> id;
	cin.get();

	for (int i = 0; i < m_EmpNum; i++)
	{
		if (id == m_EmpArray[i]->m_Id)
		{
			//�鵽����
			cout << "�鵽: " << id << "��ְ������������ְ���ţ� " << endl;

			int newId = 0;
			cin >> newId;
			cin.get();

			cout << "��������������" << endl;
			string newName = "";
			cin >> newName;
			cin.get();

			cout << "�������λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			int dSelect;
			cin >> dSelect;
			cin.get();

			m_EmpArray[i]->m_Id = newId;
			m_EmpArray[i]->m_Name = newName;

			cout << "�޸ĳɹ�" << endl;
			this->save();

			return;
		}
	}

	cout << "�޸�ʧ�ܣ����޴���" << endl;
}


//��ʾְ��
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		return;
	}

	for (int i = 0; i < m_EmpNum; i++)
	{
		cout << "ְ����ţ� " << this->m_EmpArray[i]->m_Id << " \tְ�������� " << this->m_EmpArray[i]->m_Name << " \t��λ��" << this->m_EmpArray[i]->getDeptName() << " \t��λְ��" << this->m_EmpArray[i]->getDuty() << endl;
	}
}


//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		return;
	}

	cout << "��������ҵķ�ʽ��" << endl;
	cout << "1����ְ����Ų���" << endl;
	cout << "2������������" << endl;

	int select = 0;
	cin >> select;
	cin.get();

	if (select == 1) //��ְ���Ų���
	{
		int id;
		cout << "��������ҵ�ְ����ţ�" << endl;
		cin >> id;
		cin.get();
		for (int i = 0; i < m_EmpNum; i++)
		{
			if (m_EmpArray[i]->m_Id == id)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				cout << "ְ����ţ� " << this->m_EmpArray[i]->m_Id << " \tְ�������� " << this->m_EmpArray[i]->m_Name << " \t��λ��" << this->m_EmpArray[i]->getDeptName() << " \t��λְ��" << this->m_EmpArray[i]->getDuty() << endl;
				return;
			}
		}

	}
	else  //����������
	{
		string name;
		cout << "��������ҵ�������" << endl;
		cin >> name;
		cin.get();
		for (int i = 0; i < m_EmpNum; i++)
		{
			if (m_EmpArray[i]->m_Name == name)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				cout << "ְ����ţ� " << this->m_EmpArray[i]->m_Id << " \tְ�������� " << this->m_EmpArray[i]->m_Name << " \t��λ��" << this->m_EmpArray[i]->getDeptName() << " \t��λְ��" << this->m_EmpArray[i]->getDuty() << endl;
				return;
			}
		}
	}

	cout << "����ʧ�ܣ����޴���" << endl;

}


//����ְ��
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		return;
	}

	cout << "��ѡ������ʽ�� " << endl;
	cout << "1����ְ���Ž�������" << endl;
	cout << "2����ְ���Ž��н���" << endl;

	int select = 0;
	cin >> select;
	cin.get();

	for (int i = 0; i < m_EmpNum; i++)
	{
		int minOrMax = i;
		for (int j = i + 1; j < m_EmpNum; j++)
		{
			if (select == 1) //����
			{
				if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
				{
					minOrMax = j;
				}
			}
			else  //����
			{
				if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
				{
					minOrMax = j;
				}
			}
		}

		if (i != minOrMax)
		{
			int temp = m_EmpArray[i]->m_Id;
			m_EmpArray[i]->m_Id = m_EmpArray[minOrMax]->m_Id;
			m_EmpArray[minOrMax]->m_Id = temp;
		}

	}

	cout << "����ɹ�" << endl;
	this->save();
	this->Show_Emp();
}


//����ļ�
void WorkerManager::Clean_File()
{
	ofstream ofs(FILENAME, ios::trunc);
	ofs.close();

	if (this->m_EmpArray != NULL)
	{
		this->m_EmpNum = 0;
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

	this->m_FileIsEmpty = true;

	cout << "��ճɹ���" << endl;
}


//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " " << this->m_EmpArray[i]->m_Name << " " << this->m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}


//��������
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
	}
}

