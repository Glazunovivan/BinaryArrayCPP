//������� ��������
#define _CRT_SECURE_NO_WARNINGS //��������� ��� ������������� � ������������� �-�����
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <bitset>
#include <time.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int count = 0;

	FILE *fileOpen, *fileOutput;

	//�������� �������� ������ 
	//��������� ���� �� ��������� �������������������
	if ((fileOpen = fopen("D:\\generateRandomSort.txt", "r")) == 0)	//� �������� �������
	{
		cout << "������ �������� �������� �����"; return 1;
	}
	cout << "������ ��������� ��������� ���������� ������� ��������.\n�������������..." << endl;
	//������������ ���������� �������
	char str[9];
	while (fgets(str, 9, fileOpen) != NULL) 
	{
		count++;
	}
	cout <<"���������� ������� � ����� \" generateRandomShuffle.txt\": " << count << endl;

	//������� � ���� ���������� 8������� ��������� * (���������� �������/8), ������ ��� 8 - ��� ���������� ��� � �����. 
	unsigned char *arr = (unsigned char*)malloc(sizeof(unsigned char)*(count/8));
	//�������� ������� ����
	for (int i = 0; i < (count/8); i++) 
	{
		arr[i] = 0x00;	//��� ���� � ����
	}
	cout << "���������������� ������� ������.\n";
	fclose(fileOpen);
	
	if ((fileOpen = fopen("D:\\generateRandomShuffle.txt", "r")) == 0)
	{
		cout << "������ �������� �������� �����";
		return 1;
	}

	//���� ���������� ��������������� ����
	if ((fileOutput = fopen("D:\\sortedSequence.txt", "w+b")) == 0)	//��������� � �������� ������� � ��������� ������
	{
		cout << "������ �������� ��������� �����";
		return 1;
	}

	int number = 0;		//����� ������� ����� ���������� � ����
	cout << "��������� ������� ������.... �����" << endl;
	//��������� ������
	while (fgets(str, 9, fileOpen) != NULL) 
	{
		number = atoi(str);
		//cout << number << endl;
		//� ������� ������� [�����/8 - 125 000]  
		arr[(number/8)-125000] |= (0x80 >> (number % 8));
	}
	fclose(fileOpen);
	
	//��������� ������������� ����
	cout << "��������� �������� ����... ��������� ��� ��������" << endl;
	for (int i = 0; i < count/8; i++)		//���� 
	{
		unsigned char mask = 0x80;	//����� 1000 0000
		for (int j = 0; j < 8; j++)	//���
		{
			if ((arr[i] & mask) != 0)
			{
				number = ((i * 8) + j)+1000000;
				fprintf(fileOutput, "%u\n", number);	//��� ��-������� - ��������� ������
			}
			mask = mask >> 1;
		}
	}
	float sizeMemoryInMegaByte = (sizeof(*arr) * (count / 8))/(1024*1024);
	cout << "����� ���������� ����������� ������ ������� �������� (��������): "<<sizeMemoryInMegaByte <<endl;
	cout << "����� ������ ��������� (� ��������): " << clock() / 1000.0 << endl;
	fclose(fileOutput);
	free(arr);
	cout << "�������� ������ � ������� ������ :). ��������� ���� \"sortedSequence.txt\"" << endl;
	
	system("PAUSE");
	return 0;
}


#pragma region ��� ������ �� ���������. �������!!!!! ����� � ������! ����������� ���� ���� ��� ���������
/*
* unsigned int num[6] = { 1,20,5,9,12,8 };

for (int i = 0; i < 6; i++)
{
	cout << num[i] << " ";
}
cout << endl;
unsigned char bitArray[3];
//�������� ����
for (int i = 0; i < 3; i++)
{
	bitArray[i] = 0x00;
}

for (int i = 0; i < 3; i++)
{
	cout<<bitset<8>(bitArray[i])<<" ";
}
cout << endl;

//�������� �� ���� ������
for (int i = 0; i < 6; i++)
{
	//����� = ����� ���� � �������
	//cout << num[i] << endl;
	//� ����� ���� ���������
	bitArray[(num[i] / 8)] |= (0x80 >> (num[i] % 8));
}

for (int i = 0; i < 3; i++)
{
	cout<< bitset<8>(bitArray[i])<<" ";
}

cout << endl;

//����� �����
for (int i = 0; i < 3; i++)
{
	unsigned char mask = 0x80;	//����� 1000 0000
	//����� ����
	for (int j = 0; j < 8; j++)
	{
		if ((bitArray[i] & mask) != 0)
		{
			int chislo = (i * 8) + j;
			cout << chislo << " ";
		}
		mask = mask >> 1;
	}
}

cout << endl;
*/
#pragma endregion
