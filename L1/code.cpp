#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

class DATA1 //массив
{
private:
	int t;
	int a[26];
public:

	DATA1()
	{
		t = 0;
	}
	void init(char *_s)
	{
		t = 1;
		for (int i = 0; i < 26; i++)
			a[i] = 0;

		while (*_s)
		{
			if (*_s >= 'a' && *_s <= 'z')
				a[*_s - 'a'] = 1;
			_s++;
		}
	}
	DATA1(char *_s)
	{
		init(_s);
	}
	void put()
	{
		if (t == 0)
		{
			cout << "Нет данных\n";
		}
		bool b = 0;
		for (int i = 0; i < 26; i++)
			if (a[i])
			{
				b = 1;
				cout << (char)(i + 'a');
			}

		if (b == 0)
		{
			cout << "Пустое множество\n";
		}
		else
			cout << "\n";
	}

	DATA1 friend operator & (DATA1 _a, DATA1 _b)
	{

	}
	DATA1 friend operator | (DATA1 _a, DATA1 _b);
	DATA1 friend operator ~ (DATA1 _a);

};

int processing_1(int _in);

int main()
{
	setlocale(0,"RU");
	cout <<  "Главное меню";

	DATA1 d;

	d.init("agrert");
	d.put();
	
	Sleep(20342);
}



