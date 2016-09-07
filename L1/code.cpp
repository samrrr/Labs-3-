#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>

using namespace std;

struct DATA1 //массив
{
	char a[27];

	void gen()
	{
		int r = 0;
		for (int i = 0; i < 26; i++)
		if (rand() % 2 == 0)
		{
			a[r] = 'a' + i;
			r++;
		}
		a[r] = 0;
	}

};

struct SP_EL
{
	char ch;
	SP_EL *n;
};

struct DATA2 //список
{
	SP_EL *spis;
	void gen()
	{
		SP_EL *p = spis;
		while (p)
		{
			SP_EL *p1 = p;
			p = p->n;
			delete p1;
		}

		spis = NULL;

		for (int i = 0; i < 26; i++)
			if (rand() % 2 == 0)
			{
				SP_EL *p = new SP_EL;
				p->ch = 'a' + i;
				p->n = spis;
				spis = p;
			}
	}
};

struct DATA3 //юниверсум
{
	bool a[26];

	void gen()
	{

		for (int i = 0; i < 26; i++)
			a[i] = rand() % 2;
	}
};

struct DATA4 //сжатый юниверсум
{
	long a;

	void gen()
	{

		a = 0;

		for (int i = 0; i < 26; i++)
			a |= (rand() % 2)<<i;
	}
};

void init(char *_s, DATA1 *_a)
{
	int ais[26];
	SP_EL *p;
	
	for (int i = 0; i < 26; i++)
		ais[i] = 0;

	while (*_s)
	{
		if (*_s >= 'a' && *_s <= 'z')
			if (ais[*_s - 'a'] == 0)
			{
				ais[*_s - 'a'] = 1;
			}
		_s++;
	}

	int r = 0;

	for (int i = 0; i < 26; i++)
		if (ais[i] == 1)
		{
			_a->a[r] = i + 'a';
			r++;
		}
	_a->a[r] = 0;

}

void init(char *_s, DATA2 *_a)
{
	int ais[26];
	SP_EL *p;

	_a->spis = NULL;

	for (int i = 0; i < 26; i++)
		ais[i] = 0;

	while (*_s)
	{
		if (*_s >= 'a' && *_s <= 'z')
			if (ais[*_s - 'a'] == 0)
			{
				ais[*_s - 'a'] = 1;
			}
		_s++;
	}

	for (int i = 25; i >= 0; i--)
		if (ais[i] == 1)
		{
			p = new SP_EL;
			p->n = _a->spis;
			p->ch = i + 'a';
			_a->spis = p;
		}
}

void init(char *_s, DATA3 *_a)
{
	for (int i = 0; i < 26; i++)
		_a->a[i] = 0;
	
	while (*_s)
	{
		if (*_s >= 'a' && *_s <= 'z')
			_a->a[*_s - 'a'] = 1;
		_s++;
	}
}

void init(char *_s, DATA4 *_a)
{
	_a->a = 0;


	while (*_s)
	{
		if (*_s >= 'a' && *_s <= 'z')
		{
			_a->a |= 1 << (*_s - 'a');
		}
		_s++;
	}

}

void put(DATA1 _a)
{
	cout << "{" << _a.a << "}\n";
}

void put(DATA2 _a)
{
	cout << "{";

	for (SP_EL *p = _a.spis; p; p = p->n)
		cout << p->ch;

	cout << "}\n";
}

void put(DATA3 _a)
{
	cout << "{";

	for (int i = 0; i < 26; i++)
		if (_a.a[i])
		{
			cout << (char)(i + 'a');
		}

	cout << "}\n";
}

void put(DATA4 _a)
{
	cout << "{";

	for (int i = 0; i < 26; i++)
		if (_a.a & (1 << i))
		{
			cout << (char)(i + 'a');
		}

	cout << "}\n";
}

void processing(DATA1 &_a, DATA1 &_b, DATA1 &_c, DATA1 &_d, DATA1 &_e);

int main()
{
	time_t t;
	time(&t);
	srand(t);
	setlocale(0, "RU");
	//cout <<  "Главное меню";

	int exit = 0;


	char s_a[30], s_b[30], s_c[30], s_d[30];

	int i;

	/** /

	//1-N^2
	//2-N^2
	//3-1
	//4-1
	cout << "Вводите A:";
	gets_s(s_a, 30);
	cout << "Вводите B:";
	gets_s(s_b, 30);
	cout << "Вводите C:";
	gets_s(s_c, 30);
	cout << "Вводите D:";
	gets_s(s_d, 30);

	cout << "Массив:";
	processing(DATA1(s_a), DATA1(s_b), DATA1(s_c), DATA1(s_d)).put();

	cout << "Список:";
	processing(DATA2(s_a), DATA2(s_b), DATA2(s_c), DATA2(s_d)).put();

	cout << "Юниверсум:";
	processing(DATA3(s_a), DATA3(s_b), DATA3(s_c), DATA3(s_d)).put();

	cout << "Машинное слово:";
	processing(DATA4(s_a), DATA4(s_b), DATA4(s_c), DATA4(s_d)).put();
	/**/
	system("cls");

	DATA1 a;
	DATA1 b;
	DATA1 c;
	DATA1 d;
	DATA1 e;

	a.gen();
	b.gen();
	c.gen();
	d.gen();

	//init("abcd", &a);
	//init("cdef", &b);
	//init("cfr", &c);
	//init("xz", &d);

	cout << "A:";
	put(a);
	cout << "B:";
	put(b);
	cout << "C:";
	put(c);
	cout << "D:";
	put(d);
	cout << "E:";
	processing(a, b, c, d,e);
	put(e);
	/*
	auto c2 = clock();
	auto c1 = clock();

	for (i = 0; i < 100000; i++)
	e = processing(a, b, c, d);

	c2 = clock();

	cout << "\n" << "E:";
	e.put();
	cout << "Тактов:" << c2 - c1 << "\n";
	cout << "Тактов на 1 запуск:" << (c2 - c1) / (float)100000 << "\n";

	system("pause");
	*/
	system("pause");
	
}

void processing(DATA1 &_a, DATA1 &_b, DATA1 &_c, DATA1 &_d, DATA1 &_e)
{
	//a & b / c | d

	int r = 0;

	DATA1 f;

	//1
	for (char *s1 = _a.a, *s2 = _b.a; *s1 & *s2; *s1 > *s2 ? s2++ : s1++)
		if (*s1 == *s2)
		{
			f.a[r] = *s1;
			r++;
		}
	f.a[r] = 0;

	//2
	for (char *s1 = f.a, *s2 = _c.a; *s1 & *s2; *s1 > *s2 ? s2++ : s1++)
		if (*s1 == *s2)
		{
			*s1 = '-';
			r++;
		}

	r = 0;
	for (char *s1 = f.a; *s1; s1++)
		if (*s1 != '-')
		{
			f.a[r] = *s1;
			r++;
		}
	f.a[r] = 0;

	//3
	r = 0;
	char *s1=f.a, *s2=_d.a;
	/** /
	if (*s1 < *s2)
	{
		if (*s1 != 0)
		{
			_e.a[r] = *s1;
			r++;
		}
	}
	else
	{
		if (*s2 != 0)
		{
			_e.a[r] = *s2;
			r++;
		}
	}
	/**/
	while (*s1 || *s2)
	{
		if (*s1 > *s2 && *s2 != 0 || *s1 == 0)
		{
			if (*s2 != _e.a[r - 1] && *s2 != 0)
			{
				_e.a[r] = *s2;
				r++;
			}
			s2++;
		}
		else
		{
			if (*s1 != _e.a[r - 1] && *s1 != 0)
			{
				_e.a[r] = *s1;
				r++;
			}
			s1++;
		}
	}
	_e.a[r] = 0;
	
}


