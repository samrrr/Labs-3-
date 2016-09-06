#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>

using namespace std;

class DATA1 //массив
{
private:
	int t;
	char a[27];
public:

	DATA1()
	{
		t = 1;
		a[0] = 0;
	}
	void gen()
	{
		t = 1;
		int r = 0;
		for (int i = 0; i < 26; i++)
		if (rand() % 2 == 0)
		{
			a[r] = 'a' + i;
			r++;
		}
		a[r] = 0;
	}
	void init(char *_s)
	{
		t = 1;

		int r = 0;
		int ais[26];
		for (int i = 0; i < 26; i++)
			ais[i] = 0;

		a[0] = 0;

		while (*_s)
		{
			if (*_s >= 'a' && *_s <= 'z')
				if (ais[*_s - 'a'] == 0)
				{
					ais[*_s - 'a'] = 1;
					a[r] = *_s;
					a[r + 1] = 0;
					r++;
				}
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
		cout << a;

		if (a[0] == 0)
		{
			cout << "Пустое множество\n";
		}
		else
			cout << "\n";
	}

	const DATA1& operator= (const DATA1 &_a)
	{
		t = _a.t;
		for (int i = 0; i < 27; i++)
			a[i] = _a.a[i];

		return *this;
	}
	DATA1(const DATA1 &_a)
	{
		t = _a.t;
		for (int i = 0; i < 27; i++)
			a[i] = _a.a[i];
	}
	friend DATA1 operator & (const DATA1 &_a, const DATA1 &_b)
	{
		DATA1 c;

		if (_a.t == 0 || _b.t == 0)
			return c;

		int r = 0;

		for (char* s1 = (char*)_a.a; *s1; s1++)
			for (char* s2 = (char*)_b.a; *s2; s2++)
				if (*s2 == *s1)
				{
					c.a[r] = *s1;
					c.a[r + 1] = 0;
					r++;
				}

		return c;
	}
	friend DATA1 operator | (const DATA1 &_a, const DATA1 &_b)
	{
		DATA1 c = _a;

		if (_a.t == 0 || _b.t == 0)
			return c;

		int r = strlen(c.a);

		for (char* s1 = (char*)_b.a; *s1; s1++)
		{
			bool b = 0;
			for (char* s2 = c.a; *s2; s2++)
				if (*s2 == *s1)
				{
					b = 1;
				}
			if (b == 0)
			{
				c.a[r] = *s1;
				c.a[r + 1] = 0;
				r++;
			}
		}

		return c;
	}
	friend DATA1 operator ~ (const DATA1 &_a)
	{
		DATA1 c;
		int r = 0;

		for (char ch = 'a'; ch <= 'z'; ch++)
		{
			bool b = 0;
			for (char* s = (char*)_a.a; *s; s++)
				if (*s == ch)
					b = 1;
			if (b == 0)
			{
				c.a[r] = ch;
				c.a[r + 1] = 0;
				r++;
			}
		}

		return c;
	}

};

struct SP_EL
{
	char ch;
	SP_EL *n;
};

class DATA2 //список
{
private:
	int t;
	SP_EL *spis;
public:


	~DATA2()
	{
		SP_EL *p = spis;
		while (p)
		{
			SP_EL *p1 = p;
			p = p->n;
			delete p1;
		}
	}

	DATA2()
	{
		t = 1;
		spis = 0;
	}
	void gen()
	{
		t = 1;

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
	void init(char *_s)
	{
		t = 1;

		int ais[26];
		SP_EL *p;

		spis = NULL;

		for (int i = 0; i < 26; i++)
			ais[i] = 0;

		while (*_s)
		{
			if (*_s >= 'a' && *_s <= 'z')
				if (ais[*_s - 'a'] == 0)
				{
					ais[*_s - 'a'] = 1;
					p = new SP_EL;
					p->n = spis;
					spis = p;
					spis->ch = *_s;
				}
			_s++;
		}
	}
	DATA2(char *_s)
	{
		init(_s);
	}
	void put()
	{
		
		for (SP_EL *p = spis;p;p=p->n)
			cout << p->ch;

		if (spis == 0)
		{
			cout << "Пустое множество\n";
		}
		else
			cout << "\n";
	}

	const DATA2& operator= (const DATA2 &_a)
	{
		t = _a.t;
		SP_EL *p;

		p = spis;
		while (p)
		{
			SP_EL *p1 = p;
			p = p->n;
			delete p1;
		}

		spis = NULL;

		for (SP_EL *el = _a.spis; el; el = el->n)
		{
			p = new SP_EL;
			p->ch = el->ch;
			p->n = spis;
			spis = p;
		}

		return *this;
	}
	DATA2(const DATA2 &_a)
	{
		t = _a.t;
		spis = 0;
		SP_EL *p;


		for (SP_EL *el = _a.spis; el; el = el->n)
		{
			p = new SP_EL;
			p->ch = el->ch;
			p->n = spis;
			spis = p;
		}


	}
	friend DATA2 operator & (const DATA2 &_a, const DATA2 &_b)
	{
		DATA2 c;
		c.t = 1;

		for (SP_EL *p1 = _a.spis; p1; p1 = p1->n)
			for (SP_EL *p2 = _b.spis; p2; p2 = p2->n)
				if (p1->ch == p2->ch)
				{
					SP_EL *p = new SP_EL;
					p->n = c.spis;
					c.spis = p;
					p->ch = p1->ch;
				}


		return c;
	}
	friend DATA2 operator | (const DATA2 &_a, const DATA2 &_b)
	{
		DATA2 c = _a;

		for (SP_EL *p2 = _b.spis; p2; p2 = p2->n)
		{
			bool b = 0;
			for (SP_EL *p1 = _a.spis; p1; p1 = p1->n)
				if (p1->ch == p2->ch)
				{
					b = 1;
				}

			if (b == 0)
			{
				SP_EL *p = new SP_EL;
				p->n = c.spis;
				c.spis = p;
				p->ch = p2->ch;
			}

		}


		return c;
	}
	friend DATA2 operator ~ (const DATA2 &_a)
	{
		DATA2 c;

		for (char ch = 'a'; ch <= 'z'; ch++)
		{
			bool b = 0;
			for (SP_EL *p1 = _a.spis; p1; p1 = p1->n)
				if (p1->ch == ch)
					b = 1;
			if (b == 0)
			{
				SP_EL *p = new SP_EL;
				p->n = c.spis;
				c.spis = p;
				p->ch = ch;
			}
		}

		return c;
	}

};

class DATA3 //юниверсум
{
private:
	int t;
	bool a[26];
public:

	DATA3()
	{
		t = 1;
		for (int i = 0; i < 26; i++)
			a[i] = 0;
	}
	void gen()
	{
		t = 1;

		for (int i = 0; i < 26; i++)
			a[i] = rand() % 2;
	}
	void init(char *_s)
	{
		t = 1;

		for (int i = 0; i < 26; i++)
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
	DATA3(char *_s)
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

	const DATA3& operator= (const DATA3 &_a)
	{
		t = _a.t;
		for (int i = 0; i < 26; i++)
			a[i] = _a.a[i];

		return *this;
	}
	DATA3(const DATA3 &_a)
	{
		t = _a.t;
		for (int i = 0; i < 26; i++)
			a[i] = _a.a[i];
	}
	friend DATA3 operator & (const DATA3 &_a, const DATA3 &_b)
	{
		DATA3 c;

		for (int i = 0; i < 26; i++)
		{
			c.a[i] = _a.a[i] & _b.a[i];
		}

		return c;
	}
	friend DATA3 operator | (const DATA3 &_a, const DATA3 &_b)
	{
		DATA3 c;

		for (int i = 0; i < 26; i++)
		{
			c.a[i] = _a.a[i] | _b.a[i];
		}

		return c;
	}
	friend DATA3 operator ~ (const DATA3 &_a)
	{
		DATA3 c;

		for (int i = 0; i < 26; i++)
		{
			c.a[i] = !_a.a[i];
		}

		return c;
	}

};

class DATA4 //сжатый юниверсум
{
private:
	int t;
	long a;
public:

	DATA4()
	{
		t = 1;
		a = 0;
	}
	void gen()
	{
		t = 1;

		a = 0;

		for (int i = 0; i < 26; i++)
			a |= (rand() % 2)<<i;
	}
	void init(char *_s)
	{
		t = 1;
		a = 0;
		

		while (*_s)
		{
			if (*_s >= 'a' && *_s <= 'z')
			{
				a |= 1<<(*_s - 'a');
			}
			_s++;
		}
	}
	DATA4(char *_s)
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
			if (a & (1<<i))
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

	const DATA4& operator= (const DATA4 &_a)
	{
		t = _a.t;
		a = _a.a;

		return *this;
	}
	DATA4(const DATA4 &_a)
	{
		t = _a.t;
		a = _a.a;
	}
	friend DATA4 operator & (const DATA4 &_a, const DATA4 &_b)
	{
		DATA4 c;

		c.a = _a.a & _b.a;

		return c;
	}
	friend DATA4 operator | (const DATA4 &_a, const DATA4 &_b)
	{
		DATA4 c;

		c.a = _a.a | _b.a;

		return c;
	}
	friend DATA4 operator ~ (const DATA4 &_a)
	{
		DATA4 c;

		c.a = ~_a.a;

		return c;
	}

};


DATA1 processing(DATA1 _a, DATA1 _b, DATA1 _c, DATA1 _d);
DATA2 processing(DATA2 _a, DATA2 _b, DATA2 _c, DATA2 _d);
DATA3 processing(DATA3 _a, DATA3 _b, DATA3 _c, DATA3 _d);
DATA4 processing(DATA4 _a, DATA4 _b, DATA4 _c, DATA4 _d);

int main()
{
	setlocale(0, "RU");
	//cout <<  "Главное меню";

	int exit = 0;

	while(!exit){
		DATA4 a, b, c, d, e;

		char s_a[30], s_b[30], s_c[30], s_d[30];

		int i;

		/** /
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

		cout << "Введите 1 или 2 или 3 или 4   5-выход:\n";


		scanf("%i", &i);
		if (i == 5)
			exit = 1;
		switch (i)
		{
		case 1:
		{
			DATA1 a;
			DATA1 b;
			DATA1 c;
			DATA1 d;
			DATA1 e;

			a.gen();
			b.gen();
			c.gen();
			d.gen();

			cout << "A:";
			a.put();
			cout << "B:";
			b.put();
			cout << "C:";
			c.put();
			cout << "D:";
			d.put();
			cout << "E:";
			e = processing(a, b, c, d);
			e.put();

			auto c2 = clock();
			auto c1 = clock();

			for (i = 0; i < 100000; i++)
				e = processing(a, b, c, d);

			c2 = clock();

			cout << "E:";
			e.put();
			cout << "Тактов:" << c2 - c1 << "\n";
			cout << "Тактов на 1 запуск::" << (c2 - c1) / (float)100000 << "\n";

			system("pause");
		}
		break;
		case 2:
		{
			DATA2 a;
			DATA2 b;
			DATA2 c;
			DATA2 d;
			DATA2 e;

			a.gen();
			b.gen();
			c.gen();
			d.gen();

			cout << "A:";
			a.put();
			cout << "B:";
			b.put();
			cout << "C:";
			c.put();
			cout << "D:";
			d.put();
			cout << "E:";
			e = processing(a, b, c, d);
			e.put();

			auto c2 = clock();
			auto c1 = clock();

			for (i = 0; i < 10000; i++)
			{
				e = processing(a, b, c, d);
			}

			c2 = clock();

			cout << "E:";
			e.put();
			cout << "Тактов:" << c2 - c1 << "\n";
			cout << "Тактов на 1 запуск::" << (c2 - c1) / (float)10000 << "\n";

			system("pause");
		}
		break;
		case 3:
		{
			DATA3 a;
			DATA3 b;
			DATA3 c;
			DATA3 d;
			DATA3 e;

			a.gen();
			b.gen();
			c.gen();
			d.gen();

			cout << "A:";
			a.put();
			cout << "B:";
			b.put();
			cout << "C:";
			c.put();
			cout << "D:";
			d.put();
			cout << "E:";
			e = processing(a, b, c, d);
			e.put();

			auto c2 = clock();
			auto c1 = clock();

			for (i = 0; i < 100000; i++)
				e = processing(a, b, c, d);

			c2 = clock();

			cout << "E:";
			e.put();
			cout << "Тактов:" << c2 - c1 << "\n";
			cout << "Тактов на 1 запуск::" << (c2 - c1) / (float)100000 << "\n";

			system("pause");
		}
		break;
		case 4:
		{
			DATA4 a;
			DATA4 b;
			DATA4 c;
			DATA4 d;
			DATA4 e;

			a.gen();
			b.gen();
			c.gen();
			d.gen();

			cout << "A:";
			a.put();
			cout << "B:";
			b.put();
			cout << "C:";
			c.put();
			cout << "D:";
			d.put();
			cout << "E:";
			e = processing(a, b, c, d);
			e.put();

			auto c2 = clock();
			auto c1 = clock();

			for (i = 0; i < 100000; i++)
				e = processing(a, b, c, d);

			c2 = clock();

			cout << "E:";
			e.put();
			cout << "Тактов:" << c2 - c1 << "\n";
			cout << "Тактов на 1 запуск:" << (c2 - c1) / (float)100000 << "\n";

			system("pause");
		}
		break;
		}


	}
	
}

DATA1 processing(DATA1 _a, DATA1 _b, DATA1 _c, DATA1 _d)
{
	return (_a & _b) & (~_c) | _d;
}
DATA2 processing(DATA2 _a, DATA2 _b, DATA2 _c, DATA2 _d)
{
	return (_a & _b) & (~_c) | _d;
}
DATA3 processing(DATA3 _a, DATA3 _b, DATA3 _c, DATA3 _d)
{
	return (_a & _b) & (~_c) | _d;
}
DATA4 processing(DATA4 _a, DATA4 _b, DATA4 _c, DATA4 _d)
{
	return (_a & _b) & (~_c) | _d;
}


