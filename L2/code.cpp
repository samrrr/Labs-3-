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

struct DATA3 //универсум
{
	bool a[N_CH];
};

struct DATA4 //машинное слово
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

	for (int i = N_CH - 1; i >= 0; i--)
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



class SET1
{
private:
	char a[N_CH + 1];
public:

	SET1()
	{
		a[0] = 0;
	}
	void init(char *_s)
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
				a[r] = i + ST_CH;
				r++;
			}
		a[r] = 0;
	}
	SET1(char *_s)
	{
		init(_s);
	}

	void put()
	{
		cout << "{";
		cout << a;
		cout << "}\n";
	}

	const SET1& operator= (const SET1 &_a)
	{
		for (int i = 0; i < N_CH + 1; i++)
			a[i] = _a.a[i];

		return *this;
	}
	SET1(const SET1 &_a)
	{
		for (int i = 0; i < N_CH + 1; i++)
			a[i] = _a.a[i];
	}
	friend SET1 operator & (const SET1 &_a, const SET1 &_b)
	{
		SET1 c;

		int r = 0;
		for (const char *s1 = _a.a, *s2 = _b.a; *s1 && *s2; *s1 > *s2 ? s2++ : s1++)
			if (*s1 == *s2)
			{
				c.a[r] = *s1;
				r++;
			}
		c.a[r] = 0;

		return c;
	}
	friend SET1 operator | (const SET1 &_a, const SET1 &_b)
	{
		SET1 c;

		int r;
		r = 0;
		const char *s1 = _a.a, *s2 = _b.a;

		while (*s1 || *s2)
		{
			if (*s1 > *s2 && *s2 != 0 || *s1 == 0)
			{
				if ((r == 0 || *s2 != c.a[r - 1]) && *s2 != 0)
				{
					c.a[r] = *s2;
					r++;
				}
				s2++;
			}
			else
			{
				if ((r == 0 || *s1 != c.a[r - 1]) && *s1 != 0)
				{
					c.a[r] = *s1;
					r++;
				}
				s1++;
			}
		}
		c.a[r] = 0;


		return c;
	}
	friend SET1 operator / (const SET1 &_a, const SET1 &_b)
	{
		SET1 c = _a;
		int r;

		for (char *s1 = c.a, *s2 = (char*)_b.a; *s1 && *s2; *s1 > *s2 ? s2++ : s1++)
			if (*s1 == *s2)
			{
				*s1 = '-';
			}

		r = 0;
		for (char *s1 = c.a; *s1; s1++)
			if (*s1 != '-')
			{
				c.a[r] = *s1;
				r++;
			}
		c.a[r] = 0;

		return c;
	}

};

class SET2
{
private:
	int id;
	SP_EL *spis;
public:


	~SET2()
	{
		printf("Деструктор(%i)\n",id);
		SP_EL *p = spis;
		while (p)
		{
			SP_EL *p1 = p;
			p = p->n;
			delete p1;
		}
	}

	SET2()
	{
		id = rand() % 10000;
		printf("Конструктор(%i)\n", id);
		spis = 0;
	}
	void init(char *_s)
	{
		id = rand() % 10000;
		printf("Инициализация от строки(%i)\n", id);

		int ais[N_CH];
		SP_EL *p;

		spis = nullptr;

		for (int i = 0; i < N_CH; i++)
			ais[i] = 0;

		while (*_s)
		{
			if (*_s >= 'a' && *_s <= 'z')
				ais[*_s - 'a'] = 1;
			_s++;
		}

		for (int i = N_CH-1; i >=0; i--)
			if (ais[i])
			{
				p = new SP_EL;
				p->n = spis;
				spis = p;
				spis->ch = i + ST_CH;
			}

	}
	SET2(char *_s)
	{
		printf("Конструктор от строки\n");
		init(_s);
	}
	void put()
	{

		cout << "{";
		for (SP_EL *p = spis; p; p = p->n)
			cout << p->ch;

		cout << "}\n";
	}

	const SET2& operator= (const SET2 &_a)
	{
		printf("=(%i)\n",_a.id);
		SP_EL *p;

		p = spis;
		while (p)
		{
			SP_EL *p1 = p;
			p = p->n;
			delete p1;
		}

		SP_EL *l;
		SP_EL *el = _a.spis;

		spis = new SP_EL;
		spis->ch = el->ch;
		l = spis;
		el = el->n;

		for (; el; el = el->n)
		{
			p = new SP_EL;
			p->ch = el->ch;
			l->n = p;
			l = p;
		}
		l->n = nullptr;

		return *this;
	}
	SET2(SET2 &&_a)
	{
		spis = _a.spis;
		id = _a.id;
		_a.spis = nullptr;
		printf("Перемещение(%i) id копии(%i)\n", _a.id, id);

	}
	SET2(const SET2 &_a)
	{
		id = rand() % 10000;
		printf("Создание копии(%i) id копии(%i)\n", _a.id, id);
		if (_a.spis == nullptr)
		{
			spis = nullptr;
			return;
		}
		SP_EL *p;
		SP_EL *l;
		SP_EL *el = _a.spis;

		spis = new SP_EL;
		spis->ch = el->ch;
		l = spis;
		el = el->n;

		for (; el; el = el->n)
		{
			p = new SP_EL;
			p->ch = el->ch;
			l->n = p;
			l = p;
		}
		l->n = nullptr;

	}
	friend SET2 operator & (const SET2 &_a, const SET2 &_b)
	{
		printf("& (%i)&(%i)\n", _a.id, _b.id);
		SET2 c;

		SP_EL *p;

		for (SP_EL *p1 = _a.spis, *p2 = _b.spis; p1 != nullptr && p2 != nullptr;
			p1->ch > p2->ch ? p2 = p2->n : p1 = p1->n)
			if (p1->ch == p2->ch)
			{
				if (c.spis == nullptr)
				{
					p = new SP_EL;
					c.spis = p;
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



		return c;
	}
	friend SET2 operator | (const SET2 &_a, const SET2 &_b)
	{
		printf("| (%i)|(%i)\n", _a.id, _b.id);
		SET2 c;

		SP_EL *p1 = _a.spis, *p2 = _b.spis;
		SP_EL *p = nullptr;

		c.spis = 0;

		while (p1 || p2)
		{
			if (p1 == 0 || p2 != 0 && p1->ch > p2->ch)
			{
				if (p == nullptr || p2->ch != p->ch)
				{
					if (p == nullptr)
					{
						p = new SP_EL;
						c.spis = p;
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
						c.spis = p;
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

		return c;
	}


	friend SET2 operator / (const SET2 &_a,const SET2 &_b)
	{
		printf("/ (%i)/(%i)\n", _a.id, _b.id);
		SET2 c(_a);

		SP_EL *p;

		for (SP_EL **p1 = &c.spis, *p2 = _b.spis; (*p1) && p2;)
		{
			if ((*p1)->ch == p2->ch)
			{
				p = (*p1)->n;
				delete (*p1);
				*p1 = p;

			}

			if (*p1)
				if ((*p1)->ch > p2->ch)
				{
					p2 = p2->n;
				}
				else
				{
					p1 = &((*p1)->n);
				}

		}

		return c;
	}

};

class SET3 
{
private:
	bool a[N_CH];
public:

	SET3()
	{
		for (int i = 0; i < N_CH; i++)
			a[i] = 0;
	}
	void init(char *_s)
	{

		for (int i = 0; i < N_CH; i++)
			a[i] = 0;


		while (*_s)
		{
			if (*_s >= 'a' && *_s <= 'z')
				if (a[*_s - 'a'] == 0)
				{
					a[*_s - 'a'] = 1;
				}
			_s++;
		}
	}
	SET3(char *_s)
	{
		init(_s);
	}
	void put()
	{

		bool b = 0;

		cout << "{";
		for (int i = 0; i < N_CH; i++)
			if (a[i])
			{
				b = 1;
				cout << (char)(i + 'a');
			}

		cout << "}\n";
	}

	const SET3& operator= (const SET3 &_a)
	{
		for (int i = 0; i < N_CH; i++)
			a[i] = _a.a[i];

		return *this;
	}
	SET3(const SET3 &_a)
	{
		for (int i = 0; i < N_CH; i++)
			a[i] = _a.a[i];
	}
	friend SET3 operator & (const SET3 &_a, const SET3 &_b)
	{
		SET3 c;

		for (int i = 0; i < N_CH; i++)
		{
			c.a[i] = _a.a[i] & _b.a[i];
		}

		return c;
	}
	friend SET3 operator | (const SET3 &_a, const SET3 &_b)
	{
		SET3 c;

		for (int i = 0; i < N_CH; i++)
		{
			c.a[i] = _a.a[i] | _b.a[i];
		}

		return c;
	}
	friend SET3 operator / (const SET3 &_a, const SET3 &_b)
	{
		SET3 c;

		for (int i = 0; i < N_CH; i++)
		{
			c.a[i] = _a.a[i] & !_b.a[i];
		}

		return c;
	}

};

class SET4 //ñæàòûé þíèâåðñóì
{
private:
	long a;
public:

	SET4()
	{
		a = 0;
	}
	void init(char *_s)
	{
		a = 0;


		while (*_s)
		{
			if (*_s >= 'a' && *_s <= 'z')
			{
				a |= 1 << (*_s - 'a');
			}
			_s++;
		}
	}
	SET4(char *_s)
	{
		init(_s);
	}
	void put()
	{

		bool b = 0;

		cout << "{";
		for (int i = 0; i < N_CH; i++)
			if (a & (1 << i))
			{
				b = 1;
				cout << (char)(i + 'a');
			}

		cout << "}\n";
	}

	const SET4& operator= (const SET4 &_a)
	{
		a = _a.a;

		return *this;
	}
	SET4(const SET4 &_a)
	{
		a = _a.a;
	}
	friend SET4 operator & (const SET4 &_a, const SET4 &_b)
	{
		SET4 c;

		c.a = _a.a & _b.a;

		return c;
	}
	friend SET4 operator | (const SET4 &_a, const SET4 &_b)
	{
		SET4 c;

		c.a = _a.a | _b.a;

		return c;
	}
	friend SET4 operator / (const SET4 &_a, const SET4 &_b)
	{
		SET4 c;

		c.a = _a.a & ~_b.a;

		return c;
	}

};






unsigned long long time_req()
{
	return __rdtsc();
}




void processing(SET1 &_a, SET1 &_b, SET1 &_c, SET1 &_d, SET1 &_e);
void processing(SET2 &_a, SET2 &_b, SET2 &_c, SET2 &_d, SET2 &_e);
void processing(SET3 &_a, SET3 &_b, SET3 &_c, SET3 &_d, SET3 &_e);
void processing(SET4 &_a, SET4 &_b, SET4 &_c, SET4 &_d, SET4 &_e);



//////////////////////////////////////////////////////////////////////////////////////////////////////


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

		SET1 a5;
		SET1 b5;
		SET1 c5;
		SET1 d5;
		SET1 e5;

		SET2 a6;
		SET2 b6;
		SET2 c6;
		SET2 d6;
		SET2 e6;

		SET3 a7;
		SET3 b7;
		SET3 c7;
		SET3 d7;
		SET3 e7;

		SET4 a8;
		SET4 b8;
		SET4 c8;
		SET4 d8;
		SET4 e8;


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

		a5 = s_a;
		b5 = s_b;
		c5 = s_c;
		d5 = s_d;

		a6 = s_a;
		b6 = s_b;
		c6 = s_c;
		d6 = s_d;

		a7 = s_a;
		b7 = s_b;
		c7 = s_c;
		d7 = s_d;

		a8 = s_a;
		b8 = s_b;
		c8 = s_c;
		d8 = s_d;

		cout << "\n\n";

		processing(a6, b6, c6, d6, e6);
		system("pause");
		unsigned __int64 t1, t2, t3, t4;

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

		t3 = time_req();
		for (i = 0; i < REP1; i++)
		{
			processing(a5, b5, c5, d5, e5);
		}
		t4 = time_req();


		cout << "\nМассив(Повторений:" << REP1 << "):\n";
		cout << "Тактов на 1 запуск:" << (t2 - t1) / (float)REP1 << "(без классов), " << (t4 - t3) / (float)REP1 << "(с классами)\n";

		t1 = time_req();
		for (i = 0; i < REP2; i++)
		{
			processing(a2, b2, c2, d2, e2);
			freesp(e2);
		}
		t2 = time_req();

		t3 = time_req();
		for (i = 0; i < REP2; i++)
		{
			processing(a6, b6, c6, d6, e6);
		}
		t4 = time_req();

		processing(a2, b2, c2, d2, e2);

		freesp(a2);
		freesp(b2);
		freesp(c2);
		freesp(d2);
		freesp(e2);
		cout << "\nСписок(Повторений:" << REP2 << "):\n";
		cout << "Тактов на 1 запуск:" << (t2 - t1) / (float)REP2 << "(без классов), " << (t4 - t3) / (float)REP2 << "(с классами)\n";

		t1 = time_req();
		for (i = 0; i < REP3; i++)
		{
			if (i % (REP4 / 10) == 0)
				cout << " \b";
			e3.a[0] = 0;
			processing(a3, b3, c3, d3, e3);
		}
		t2 = time_req();
		i=e3.a[0]%10;
		cout << i << "\b ";
		t3 = time_req();
		for (i = 0; i < REP3; i++)
		{
			processing(a7, b7, c7, d7, e7);
		}
		t4 = time_req();

		cout << "\nУниверсум(Повторений:" << REP3 << "):\n";
		cout << "Тактов на 1 запуск:" << (t2 - t1) / (float)REP3 << "(без классов), " << (t4 - t3) / (float)REP3 << "(с классами)\n";

		t1 = time_req();
		for (i = 0; i < REP4; i++)
		{
			if (i % (REP4 / 10) == 0)
				cout << " \b";
			e4.a = 0;
			processing(a4, b4, c4, d4, e4);
		}
		t2 = time_req();

		t3 = time_req();
		for (i = 0; i < REP3; i++)
		{
			if (i % (REP4 / 10) == 0)
				cout << " \b";
			processing(a8, b8, c8, d8, e8);
		}
		t4 = time_req();

		cout << "\nМашинное слово(Повторений:" << REP4 << "):\n";
		cout << "Тактов на 1 запуск:" << (t2 - t1) / (float)REP4 << "(без классов), " << (t4 - t3) / (float)REP4 << "(с классами)\n";


		
		cout << "Сделать ещё тест?(y/n)";

		do
		{
			ch = getch();
		} while (ch != 'y' && ch != 'Y' &&ch != 'n' &&ch != 'N');

	} while (ch == 'y' || ch == 'Y');

}


//////////////////////////////////////////////////////////////////////////////////////////////////////


void processing(SET1 &_a, SET1 &_b, SET1 &_c, SET1 &_d, SET1 &_e)
{
	_e = (_a & _b) / (_c) | _d;
}
void processing(SET2 &_a, SET2 &_b, SET2 &_c, SET2 &_d, SET2 &_e)
{
	_e = (_a & _b) / _c | _d;
}
void processing(SET3 &_a, SET3 &_b, SET3 &_c, SET3 &_d, SET3 &_e)
{
	_e = (_a & _b) / (_c) | _d;
}
void processing(SET4 &_a, SET4 &_b, SET4 &_c, SET4 &_d, SET4 &_e)
{
	_e = (_a & _b) / (_c) | _d;
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