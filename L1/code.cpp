#include <windows.h>
#include <conio.h>
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

	DATA2()
	{
		t = 1;
		spis = 0;
	}
	void init(char *_s)
	{
		t = 1;

		int ais[26];
		SP_EL *p;

		for (int i = 0; i < 26; i++)
			ais[i] = 0;

		while (*_s)
		{
			if (*_s >= 'a' && *_s <= 'z')
				if (ais[*_s - 'a'] == 0)
				{
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

		for (int i = 0; i < 26;i++)
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


DATA1 processing(DATA1 _a, DATA1 _b, DATA1 _c, DATA1 _d);
DATA2 processing(DATA2 _a, DATA2 _b, DATA2 _c, DATA2 _d);
DATA3 processing(DATA3 _a, DATA3 _b, DATA3 _c, DATA3 _d);
//DATA4 processing(DATA4 _a, DATA4 _b, DATA4 _c, DATA4 _d);

int main()
{
	setlocale(0,"RU");
	//cout <<  "Главное меню";

	DATA3 a,b,c,d,e;

	a.init("abcde");
	b.init(" cdefg");
	c.init("bczw");
	d.init("zfq");

	a.put();
	b.put();
	c.put();
	d.put();

	(~c).put();
	(a&b).put();
	((a & b) & (~c)).put();
	e = (a & b) & (~c) | d;

	e.put();

	
	Sleep(20342);
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
/*
DATA4 processing(DATA4 _a, DATA4 _b, DATA4 _c, DATA4 _d)
{
	return (_a & _b) & (~_c) | _d;
}
*/

