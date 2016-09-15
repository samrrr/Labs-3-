
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>

using namespace std;

#pragma intrinsic(__rdtsc)

const long REP1 = 1000000;
const long REP2 = 10000;
const long REP3 = 1000000;
const long REP4 = 1000000;

const char ST_CH = 'a';
const char EN_CH = 'z';
const int N_CH = 26;


struct DATA1 //массив
{
	char a[N_CH + 1];
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

void freesp(DATA2 _sp)
{
	while (_sp.spis != nullptr)
	{
		SP_EL* p;
		p = _sp.spis;
		_sp.spis = _sp.spis->n;
		delete p;
	}
	_sp.spis = nullptr;
}

struct DATA3 //юниверсум
{
	bool a[N_CH];
};

struct DATA4 //сжатый юниверсум
{
	long a;
};

char* gen(int _n = rand() % (N_CH - 5) + 5)
{
	static char s[N_CH + 1];
	bool n[N_CH];
	int r = 0;

	if (_n > N_CH)
		_n = N_CH;

	for (int i = 0; i < N_CH; i++)
		n[i] = 0;
	while (_n > 0)
	{
		int i;

		i = rand() % N_CH;
		while (n[i])
			i = (i + 1) % N_CH;

		n[i] = 1;

		_n--;
	}

	for (int i = 0; i < N_CH; i++)
	if (n[i])
	{
		s[r] = ST_CH + i;
		r++;
	}
	s[r] = 0;
	return s;
}

void init(char *_s, DATA1 *_a)
{
	int ais[N_CH];

	for (int i = 0; i < N_CH; i++)
		ais[i] = 0;

	while (*_s)
	{
		if (*_s >= ST_CH && *_s <= EN_CH)
		if (ais[*_s - ST_CH] == 0)
		{
			ais[*_s - ST_CH] = 1;
		}
		_s++;
	}

	int r = 0;

	for (int i = 0; i < N_CH; i++)
	if (ais[i] == 1)
	{
		_a->a[r] = i + ST_CH;
		r++;
	}
	_a->a[r] = 0;

}

void init(char *_s, DATA2 *_a)
{
	int ais[N_CH];
	SP_EL *p;

	_a->spis = NULL;

	for (int i = 0; i < N_CH; i++)
		ais[i] = 0;

	while (*_s)
	{
		if (*_s >= ST_CH && *_s <= EN_CH)
		if (ais[*_s - ST_CH] == 0)
		{
			ais[*_s - ST_CH] = 1;
		}
		_s++;
	}

	for (int i = N_CH-1; i >= 0; i--)
	if (ais[i] == 1)
	{
		p = new SP_EL;
		p->n = _a->spis;
		p->ch = i + ST_CH;
		_a->spis = p;
	}
}

void init(char *_s, DATA3 *_a)
{
	for (int i = 0; i < N_CH; i++)
		_a->a[i] = 0;

	while (*_s)
	{
		if (*_s >= ST_CH && *_s <= EN_CH)
			_a->a[*_s - ST_CH] = 1;
		_s++;
	}
}

void init(char *_s, DATA4 *_a)
{
	_a->a = 0;


	while (*_s)
	{
		if (*_s >= ST_CH && *_s <= EN_CH)
		{
			_a->a |= 1 << (*_s - ST_CH);
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

	for (int i = 0; i < N_CH; i++)
	if (_a.a[i])
	{
		cout << (char)(i + ST_CH);
	}

	cout << "}\n";
}

void put(DATA4 _a)
{
	cout << "{";

	for (int i = 0; i < N_CH; i++)
	if (_a.a & (1 << i))
	{
		cout << (char)(i + ST_CH);
	}

	cout << "}\n";
}

void processing(DATA1 &_a, DATA1 &_b, DATA1 &_c, DATA1 &_d, DATA1 &_e);
void processing(DATA2 &_a, DATA2 &_b, DATA2 &_c, DATA2 &_d, DATA2 &_e);
void processing(DATA3 &_a, DATA3 &_b, DATA3 &_c, DATA3 &_d, DATA3 &_e);
void processing(DATA4 &_a, DATA4 &_b, DATA4 &_c, DATA4 &_d, DATA4 &_e);

unsigned long long time_req()
{
	return __rdtsc();
}

int main()
{
	srand(time(nullptr));
	setlocale(0, "RU");
	
	char s_a[30], s_b[30], s_c[30], s_d[30];

	int i;

	char ch;

	do{
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

		DATA3 a3;
		DATA3 b3;
		DATA3 c3;
		DATA3 d3;
		DATA3 e3;

		DATA4 a4;
		DATA4 b4;
		DATA4 c4;
		DATA4 d4;
		DATA4 e4;

		strcpy(s_a, gen());
		strcpy(s_b, gen());
		strcpy(s_c, gen());
		strcpy(s_d, gen());

		cout << "N среднее=" << (strlen(s_a) + strlen(s_b) + strlen(s_c) + strlen(s_d)) / 4.0
			<< " \n";

		init(s_a, &a1);
		init(s_b, &b1);
		init(s_c, &c1);
		init(s_d, &d1);

		init(s_a, &a2);
		init(s_b, &b2);
		init(s_c, &c2);
		init(s_d, &d2);

		init(s_a, &a3);
		init(s_b, &b3);
		init(s_c, &c3);
		init(s_d, &d3);

		init(s_a, &a4);
		init(s_b, &b4);
		init(s_c, &c4);
		init(s_d, &d4);

		unsigned __int64 t1, t2;

		cout << "A:";
		put(a1);
		cout << "B:";
		put(b1);
		cout << "C:";
		put(c1);
		cout << "D:";
		put(d1);
		cout << "\n";

		t1 = time_req();
		for (i = 0; i < REP1; i++)
		{
			e1.a[0] = 0;
			processing(a1, b1, c1, d1, e1);
		}
		t2 = time_req();

		cout << "Массив:\n";
		cout << "E1:";
		put(e1);
		cout << "Тактов за " << REP1 << " повторений:" << t2 - t1 << "\n";
		cout << "Тактов на 1 повторение:" << (t2 - t1) / (float)REP1 << "\n\n";

		t1 = time_req();
		for (i = 0; i < REP2; i++)
		{
			processing(a2, b2, c2, d2, e2);
			freesp(e2);
		}
		t2 = time_req();

		processing(a2, b2, c2, d2, e2);

		cout << "Список:\n";
		cout << "E2:";
		put(e2);
		freesp(a2);
		freesp(b2);
		freesp(c2);
		freesp(d2);
		freesp(e2);
		cout << "Тактов за " << REP2 << " повторений:" << t2 - t1 << "\n";
		cout << "Тактов на 1 повторение:" << (t2 - t1) / (float)REP2 << "\n\n";

		t1 = time_req();
		for (i = 0; i < REP3; i++)
		{
			e3.a[0] = 0;
			processing(a3, b3, c3, d3, e3);
		}
		t2 = time_req();

		cout << "Универсум:\n";
		cout << "E3:";
		put(e3);
		cout << "Тактов за " << REP3 << " повторений:" << t2 - t1 << "\n";
		cout << "Тактов на 1 повторение:" << (t2 - t1) / (float)REP3 << "\n\n";

		t1 = time_req();
		for (i = 0; i < REP4; i++)
		{
			if (i % (REP4 / 10) == 0)
				cout << " \b";
			e4.a = 0;
			processing(a4, b4, c4, d4, e4);
		}
		t2 = time_req();

		cout << "Машинное слово:\n";
		cout << "E4:";
		put(e4);
		cout << "Тактов за " << REP4 << " повторений:" << t2 - t1 << "\n";
		cout << "Тактов на 1 повторение:" << (t2 - t1) / (float)REP4 << "\n\n";


		cout << "Сделать ещё тест?(y/n)";

		do
		{
			ch = getch();
		} while (ch != 'y' && ch != 'Y' &&ch != 'n' &&ch != 'N');

	} while (ch == 'y' || ch == 'Y');

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
	char *s1 = f.a, *s2 = _d.a;

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
	f.spis = nullptr;
	//1
	SP_EL *p;

	for (SP_EL *p1 = _a.spis, *p2 = _b.spis; p1 != nullptr && p2 != nullptr;
		p1->ch > p2->ch ? p2 = p2->n : p1 = p1->n)
	if (p1->ch == p2->ch)
	{
		if (f.spis == nullptr)
		{
			p = new SP_EL;
			f.spis = p;
			p->n = nullptr;
		}
		else
		{
			p->n = new SP_EL;
			p = p->n;
			p->n = nullptr;
		}
		p->ch = p1->ch;
	}

	//2
	SP_EL **g = &f.spis;
	for (SP_EL *p1 = f.spis, *p2 = _c.spis; p1 && p2;)
	{
		if (p1->ch == p2->ch)
		{
			p = p1->n;
			delete (*g);
			*g = p;
			p1 = (*g);

		}

		if (p1)
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

	_e.spis = 0;

	while (p1 || p2)
	{
		if (p1 == 0 || p2 != 0 && p1->ch > p2->ch)
		{
			if (p == nullptr || p2->ch != p->ch)
			{
				if (p == nullptr)
				{
					p = new SP_EL;
					_e.spis = p;
				}
				else
				{
					p->n = new SP_EL;
					p = p->n;
				}
				p->n = nullptr;
				p->ch = p2->ch;
			}
			p2 = p2->n;
		}
		else
		{
			if (p == nullptr || p1->ch != p->ch)
			{
				if (p == nullptr)
				{
					p = new SP_EL;
					_e.spis = p;
				}
				else
				{
					p->n = new SP_EL;
					p = p->n;
				}
				p->n = nullptr;
				p->ch = p1->ch;
			}
			p1 = p1->n;
		}
	}

	freesp(f);

}

void processing(DATA3 &_a, DATA3 &_b, DATA3 &_c, DATA3 &_d, DATA3 &_e)
{
	//a & b / c | d

	for (int i = 0; i < N_CH; i++)
		_e.a[i] = ((_a.a[i] & _b.a[i]) & (~_c.a[i])) | _d.a[i];
}

void processing(DATA4 &_a, DATA4 &_b, DATA4 &_c, DATA4 &_d, DATA4 &_e)
{
	//a & b / c | d

	_e.a = ((_a.a & _b.a) & (~_c.a)) | _d.a;
}
