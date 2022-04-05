#include "workerManager.h"
#include <fstream>
#include "worker.h"
#include <string>
#include "employee.h"
#include "manager.h"
#include "boss.h"

//构造函数
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//文件存在，并且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空!" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}


	//文件中有记录

	//获取职工个数
	int num = get_EmpNum();
	//cout << "职工个数为：" << num << endl;

	this->m_EmpNum = num;

	this->m_EmpArray = new Worker * [this->m_EmpNum];

	//初始化职工
	init_Emp(this->m_EmpArray);
}

//统计人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);


	int id;
	string name;
	string dname;

	int num = 0;
	//ifs.seekg(ios::beg); // 光标移动到文件首
	while (ifs >> id && ifs >> name &&  ifs >> dname)
	{
		//cout << "姓名： " << s.m_Name << " 学号： " << s.m_SId << endl;
		num++;
	}
	ifs.close();

	return num;
}

//初始化员工
void WorkerManager::init_Emp(Worker ** sArray)
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	//	ifs.seekg(ios::beg); // 光标移动到文件首
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{

		//cout << "职工号： " << id << " 姓名： " << name << " 部门号："<<dId << endl;
		Worker * worker = NULL;
		if (dId == 1)  // 1普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) //2经理
		{
			worker = new Manager(id, name, dId);
		}
		else //总裁
		{
			worker = new Boss(id, name, dId);
		}
		sArray[index] = worker;


		index++;
	}
}

//展示菜单
void WorkerManager::Show_Menu()
{
	cout << "欢迎来到职工管理系统！" << endl;
	cout << "0.退出程序" << endl;
	cout << "1.增加职工" << endl;
	cout << "2.删除职工" << endl;
	cout << "3.显示所有职工信息" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按职工编号排序" << endl;
	cout << "7.清空文档" << endl;
}

//增加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入增加职工数量： " << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker ** newSpace = new Worker*[newSize];

		//将原空间下内容存放到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第 " << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cin.get();

			cout << "请输入第 " << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cin.get();

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			cin.get();

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1: //普通员工
				worker = new Employee(id,name,1);
				break;
			case 2: //经理
				worker = new Manager(id, name, 2);
				break;
			case 3:  //老板
				worker = new Boss(id, name,3);
				break;
			default:
				break;
			}


			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的个数
		this->m_EmpNum = newSize;

		//更新到文件中
		this->save();

		//提示信息
		cout << "成功添加" << addNum << "名新职工！" << endl;

		//文件当前不为空
		this->m_FileIsEmpty = false;
	}
	else
	{
		cout << "输入有误" << endl;
	}
}


//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		return;
	}

	//按学号删除
	cout << "请输入想要删除的职工号：" << endl;
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

	if (index != -1)  //说明index上位置数据需要删除
	{
		for (int i = index; i < this->m_EmpNum - 1; i++)
		{
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;

		this->save();
		cout << "删除成功！" << endl;
	}
	else
	{
		cout << "删除失败，未找到该职工" << endl;
	}
}


//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		return;
	}

	cout << "请输入修改职工的编号：" << endl;
	int id;
	cin >> id;
	cin.get();

	for (int i = 0; i < m_EmpNum; i++)
	{
		if (id == m_EmpArray[i]->m_Id)
		{
			//查到此人
			cout << "查到: " << id << "号职工，请输入新职工号： " << endl;

			int newId = 0;
			cin >> newId;
			cin.get();

			cout << "请输入新姓名：" << endl;
			string newName = "";
			cin >> newName;
			cin.get();

			cout << "请输入岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			int dSelect;
			cin >> dSelect;
			cin.get();

			m_EmpArray[i]->m_Id = newId;
			m_EmpArray[i]->m_Name = newName;

			cout << "修改成功" << endl;
			this->save();

			return;
		}
	}

	cout << "修改失败，查无此人" << endl;
}


//显示职工
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		return;
	}

	for (int i = 0; i < m_EmpNum; i++)
	{
		cout << "职工编号： " << this->m_EmpArray[i]->m_Id << " \t职工姓名： " << this->m_EmpArray[i]->m_Name << " \t岗位：" << this->m_EmpArray[i]->getDeptName() << " \t岗位职责：" << this->m_EmpArray[i]->getDuty() << endl;
	}
}


//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		return;
	}

	cout << "请输入查找的方式：" << endl;
	cout << "1、按职工编号查找" << endl;
	cout << "2、按姓名查找" << endl;

	int select = 0;
	cin >> select;
	cin.get();

	if (select == 1) //按职工号查找
	{
		int id;
		cout << "请输入查找的职工编号：" << endl;
		cin >> id;
		cin.get();
		for (int i = 0; i < m_EmpNum; i++)
		{
			if (m_EmpArray[i]->m_Id == id)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				cout << "职工编号： " << this->m_EmpArray[i]->m_Id << " \t职工姓名： " << this->m_EmpArray[i]->m_Name << " \t岗位：" << this->m_EmpArray[i]->getDeptName() << " \t岗位职责：" << this->m_EmpArray[i]->getDuty() << endl;
				return;
			}
		}

	}
	else  //按姓名查找
	{
		string name;
		cout << "请输入查找的姓名：" << endl;
		cin >> name;
		cin.get();
		for (int i = 0; i < m_EmpNum; i++)
		{
			if (m_EmpArray[i]->m_Name == name)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				cout << "职工编号： " << this->m_EmpArray[i]->m_Id << " \t职工姓名： " << this->m_EmpArray[i]->m_Name << " \t岗位：" << this->m_EmpArray[i]->getDeptName() << " \t岗位职责：" << this->m_EmpArray[i]->getDuty() << endl;
				return;
			}
		}
	}

	cout << "查找失败，查无此人" << endl;

}


//排序职工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		return;
	}

	cout << "请选择排序方式： " << endl;
	cout << "1、按职工号进行升序" << endl;
	cout << "2、按职工号进行降序" << endl;

	int select = 0;
	cin >> select;
	cin.get();

	for (int i = 0; i < m_EmpNum; i++)
	{
		int minOrMax = i;
		for (int j = i + 1; j < m_EmpNum; j++)
		{
			if (select == 1) //升序
			{
				if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
				{
					minOrMax = j;
				}
			}
			else  //降序
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

	cout << "排序成功" << endl;
	this->save();
	this->Show_Emp();
}


//清空文件
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

	cout << "清空成功！" << endl;
}


//更新文件
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


//析构函数
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
	}
}

