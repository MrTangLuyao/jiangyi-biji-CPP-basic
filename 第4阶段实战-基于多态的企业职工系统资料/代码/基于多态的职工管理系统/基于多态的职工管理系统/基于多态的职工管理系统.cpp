#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "workerManager.h"

int main(){

	WorkerManager wm;
	int choice = 0;
	while (1)
	{
		wm.Show_Menu();
		cout << endl << "����������ѡ��:" << endl;
		cin >> choice;
		cin.get();
		switch (choice)
		{
		case 0:return 0; break;
		case 1:wm.Add_Emp();  cout << "���س�������" << endl;  cin.get(); break;
		case 2:wm.Del_Emp();  cout << "���س�������" << endl;  cin.get(); break;
		case 3:wm.Show_Emp(); cout << "���س�������" << endl;  cin.get(); break;
		case 4:wm.Mod_Emp();  cout << "���س�������" << endl;  cin.get(); break;
		case 5:wm.Find_Emp(); cout << "���س�������" << endl;  cin.get(); break;
		case 6:wm.Sort_Emp(); cout << "���س�������" << endl;  cin.get(); break;
		case 7:wm.Clean_File();   cout << "���س�������" << endl;  cin.get(); break;
		}
		system("cls");
	}

	system("pause");
	return EXIT_SUCCESS;
}