#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>

using namespace std;

struct DATA1 //массив
{
	char a[27];
};

struct SP_EL
{
	char ch;
	SP_EL *n;
};

struct DATA2 //список
{
	SP_EL *spis;
};

struct DATA3 //юниверсум
{
	bool a[26];
};

struct DATA4 //сжатый юниверсум
{
	long a;
};

char* gen()
{
	static char s[27];
	int r = 0;
	for (int i = 0; i < 26; i++)
		if (rand() % 2 == 0)
		{
			s[r] = 'a' + i;
			r++;
		}
	s[r] = 0;
	return s;
}

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
void processing(DATA2 &_a, DATA2 &_b, DATA2 &_c, DATA2 &_d, DATA2 &_e);

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

	DATA1 a1;
	DATA1 b1;
	DATA1 c1;
	DATA1 d1;
	DATA1 e1;

	DATA2 a2;
	DATA2 b2;
	DATA2 c2;
	DATA2 d2;
	DATA2 e2;


	strcpy(s_a, gen());
	strcpy(s_b, gen());
	strcpy(s_c, gen());
	strcpy(s_d, gen());

	init(s_a, &a2);
	init(s_b, &b2);
	init(s_c, &c2);
	init(s_d, &d2);

	init(s_a, &a1);
	init(s_b, &b1);
	init(s_c, &c1);
	init(s_d, &d1);

	cout << "A:";
	put(a1);
	cout << "B:";
	put(b1);
	cout << "C:";
	put(c1);
	cout << "D:";
	put(d1);

	processing(a1, b1, c1, d1, e1);
	processing(a2, b2, c2, d2, e2);

	cout << "E1:";
	put(e1);
	cout << "E2:";
	put(e2);
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
	//  1   2   3
	//a & b / c | d

	int r = 0;

	DATA1 f;

	//1
	for (char *s1 = _a.a, *s2 = _b.a; *s1 && *s2; *s1 > *s2 ? s2++ : s1++)
		if (*s1 == *s2)
		{
			f.a[r] = *s1;
			r++;
		}
	f.a[r] = 0;

	//2
	for (char *s1 = f.a, *s2 = _c.a; *s1 && *s2; *s1 > *s2 ? s2++ : s1++)
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

	while (*s1 || *s2)
	{
		if (*s1 > *s2 && *s2 != 0 || *s1 == 0)
		{
			if ((r == 0 || *s2 != _e.a[r - 1]) && *s2 != 0)
			{
				_e.a[r] = *s2;
				r++;
			}
			s2++;
		}
		else
		{
			if ((r == 0 || *s1 != _e.a[r - 1]) && *s1 != 0)
			{
				_e.a[r] = *s1;
				r++;
			}
			s1++;
		}
	}
	_e.a[r] = 0;
	
}

void processing(DATA2 &_a, DATA2 &_b, DATA2 &_c, DATA2 &_d, DATA2 &_e)
{
	//  1   2   3
	//a & b / c | d


	DATA2 f;
	f.spis = NULL;
	//1
	SP_EL *p;

	for (SP_EL *p1 = _a.spis, *p2 = _b.spis; p1 != NULL && p2 != NULL; p1->ch > p2->ch ? p2 = p2->n : p1 = p1->n)
		if (p1->ch == p2->ch)
		{
			if (f.spis == NULL)
			{
				p = new SP_EL;
				f.spis = p;
				p->n = NULL;
			}
			else
			{
				p->n = new SP_EL;
				p = p->n;
				p->n = NULL;
			}
			p->ch = p1->ch;
		}

	//2
	SP_EL **g = &f.spis;
	for (SP_EL *p1 = f.spis, *p2 = _c.spis; p1 != NULL && p2 != NULL;)
	{
		if (p1->ch == p2->ch)
		{
			p = p1->n;
			delete (*g);
			*g = p;
			p1 = (*g);

		}


		if (p1->ch > p2->ch)
		{
			p2 = p2->n;
		}
		else
		{
			p1 = p1->n;
			g = &((*g)->n);
		}
	}
	

	//3
	SP_EL *p1 = f.spis, *p2 = _d.spis;
	p = 0;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->ch > p2->ch && p2 != 0 || p1 == 0)
		{
			if (p == NULL || p2->ch != p->ch)
			{
				if (p == NULL)
				{
					p = new SP_EL;
					_e.spis = p;
				}
				else
				{
					p->n = new SP_EL;
					p = p->n;
				}
				p->n = NULL;
				p->ch = p2->ch;
			}
			p2 = p2->n;
		}
		else
		{
			if (p == NULL || p1->ch != p->ch)
			{
				if (p == NULL)
				{
					p = new SP_EL;
					_e.spis = p;
				}
				else
				{
					p->n = new SP_EL;
					p = p->n;
				}
				p->n = NULL;
				p->ch = p1->ch;
			}
			p1 = p1->n;
		}
	}
	
}


