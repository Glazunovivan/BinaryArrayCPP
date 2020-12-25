//битовые операции
#define _CRT_SECURE_NO_WARNINGS //директива для совместимости с классическими ф-циями
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

	//открытие входного потока 
	//открываем файл со смешанной последовательностью
	if ((fileOpen = fopen("D:\\generateRandomSort.txt", "r")) == 0)	//в бинарном формате
	{
		cout << "Ошибка открытия входного файла"; return 1;
	}
	cout << "Данная программа реализует сортировку битовым массивом.\nПриготовьтесь..." << endl;
	//подсчитываем количество записей
	char str[9];
	while (fgets(str, 9, fileOpen) != NULL) 
	{
		count++;
	}
	cout <<"Количество записей в файле \" generateRandomShuffle.txt\": " << count << endl;

	//создаем в куче количество 8битовых элементов * (количество записей/8), потому что 8 - это количество бит в байте. 
	unsigned char *arr = (unsigned char*)malloc(sizeof(unsigned char)*(count/8));
	//обнуляем порядок туть
	for (int i = 0; i < (count/8); i++) 
	{
		arr[i] = 0x00;	//все БИТЫ В НОЛЬ
	}
	cout << "Инициализировали битовый массив.\n";
	fclose(fileOpen);
	
	if ((fileOpen = fopen("D:\\generateRandomShuffle.txt", "r")) == 0)
	{
		cout << "Ошибка открытия входного файла";
		return 1;
	}

	//сюда записываем отсортированный файл
	if ((fileOutput = fopen("D:\\sortedSequence.txt", "w+b")) == 0)	//открываем в бинарном формате с удалением данных
	{
		cout << "Ошибка открытия выходного файла";
		return 1;
	}

	int number = 0;		//число которое будем записывать в файл
	cout << "Заполняем битовый массив.... Ждите" << endl;
	//заполняем массив
	while (fgets(str, 9, fileOpen) != NULL) 
	{
		number = atoi(str);
		//cout << number << endl;
		//в элемент массива [число/8 - 125 000]  
		arr[(number/8)-125000] |= (0x80 >> (number % 8));
	}
	fclose(fileOpen);
	
	//заполняем упорядоченный файл
	cout << "Формируем выходной файл... Подождите еще немножко" << endl;
	for (int i = 0; i < count/8; i++)		//байт 
	{
		unsigned char mask = 0x80;	//маска 1000 0000
		for (int j = 0; j < 8; j++)	//бит
		{
			if ((arr[i] & mask) != 0)
			{
				number = ((i * 8) + j)+1000000;
				fprintf(fileOutput, "%u\n", number);	//как по-другому - непонятно вообще
			}
			mask = mask >> 1;
		}
	}
	float sizeMemoryInMegaByte = (sizeof(*arr) * (count / 8))/(1024*1024);
	cout << "Объем занимаемой оперативной памяти битовым массивом (мегабайт): "<<sizeMemoryInMegaByte <<endl;
	cout << "Время работы программы (в секундах): " << clock() / 1000.0 << endl;
	fclose(fileOutput);
	free(arr);
	cout << "Очистили память и закрыли потоки :). Проверьте файл \"sortedSequence.txt\"" << endl;
	
	system("PAUSE");
	return 0;
}


#pragma region ЭТО ПРИМЕР ИЗ МЕТОДИЧКИ. РАБОЧИЙ!!!!! ПОТОМ И КРОВЬЮ! ЗАГЛЯДЫВАЕМ СЮДА ЕСЛИ ЧЕТ НЕПОНЯТНО
/*
* unsigned int num[6] = { 1,20,5,9,12,8 };

for (int i = 0; i < 6; i++)
{
	cout << num[i] << " ";
}
cout << endl;
unsigned char bitArray[3];
//обнуляем биты
for (int i = 0; i < 3; i++)
{
	bitArray[i] = 0x00;
}

for (int i = 0; i < 3; i++)
{
	cout<<bitset<8>(bitArray[i])<<" ";
}
cout << endl;

//проходим по всем числам
for (int i = 0; i < 6; i++)
{
	//число = номер бита в массиве
	//cout << num[i] << endl;
	//в какой байт сохраняем
	bitArray[(num[i] / 8)] |= (0x80 >> (num[i] % 8));
}

for (int i = 0; i < 3; i++)
{
	cout<< bitset<8>(bitArray[i])<<" ";
}

cout << endl;

//номер байта
for (int i = 0; i < 3; i++)
{
	unsigned char mask = 0x80;	//маска 1000 0000
	//номер бита
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
