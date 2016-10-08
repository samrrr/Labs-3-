#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <queue>
#include <deque>
#include <list>


using namespace std;

#pragma intrinsic(__rdtsc)

class GRAPH
{
	int or;//0-неориентированный 1-ориентированный
	int n;
	char **a;
public:
	GRAPH(int _n);
	GRAPH(const GRAPH &_a);
	GRAPH operator =(const GRAPH &_a);
	void put();
	string get_kom_sv();
	friend void gen_by_kom(string& s);
	int getN(){ return n; }
	bool isOr(){ return or; }
	char* operator[](const int _i);
	//GRAPH operator &();
	//friend GRAPH operator &(const GRAPH &_a, const GRAPH &_b);
};

string GRAPH::get_kom_sv()
{
	deque <int> col;
	col.resize(n);

	for (int i = 0; i < n;i++)
		col[i] = -1;

	for (int i = 0; i < n; i++)
	{
		if (col[i] == -1)
			col[i] = i;
		for (int o = 0; o < n; o++)
			for (int r = 0; r < n; r++)
				if (col[r] == i)
				{
					for (int j = 0; j < n; j++)
					{
						if (a[r][j] == 1 || a[j][r] == 1)
						{
							col[j] = i;
						}
					}
				}
	}

	deque <int> a;
	a.resize(n);

	for (int i = 0; i < n; i++)
		a[i] = 0;

	for (int i = 0; i < n; i++)
		a[col[i]]++;

	string s;

	for (int i = n; i > 0; i--)
		for (int r = 0; r < n; r++)
			if (a[r] == i)
				s = s + (char)(i+'0');

	return s;
}

GRAPH GRAPH::operator = (const GRAPH &_a)
{
	if (this == &_a)
		return *this;

	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[] a;

	n = _a.n;
	or = _a.or;

	a = new char*[n];
	for (int i = 0; i < n; i++)
		a[i] = new char[n];

	for (int i = 0; i < n; i++)
		for (int r = 0; r < n; r++)
			a[i][r] = _a.a[i][r];

	return *this;
}

GRAPH::GRAPH(int _n = 0)
{
	if (_n <= 0 || _n > 2048)
	{
		n = 0;
		return;
	}
	or = 0;
	n = _n;
	a = new char*[n];
	for (int i = 0; i < n; i++)
		a[i] = new char[n];
	for (int i = 0; i < n; i++)
		for (int r = 0; r < n; r++)
			a[i][r] = rand() % 7 <1;
}

GRAPH::GRAPH(const GRAPH &_a)
{
	n = _a.n;
	a = new char*[n];
	for (int i = 0; i < n; i++)
		a[i] = new char[n];
	for (int i = 0; i < n; i++)
		for (int r = 0; r < n; r++)
			a[i][r] = _a.a[i][r];
}

void GRAPH::put()
{
	printf("   ");
	for (int r = 0; r < n; r++)
		printf("%3i", r);
	cout << endl;
	for (int r = -1; r < n; r++)
		printf("---");

	cout << endl;

	for (int r = 0; r < n; r++)
	{
		printf("%3i| ", r);
		for (int i = 0; i < n; i++)
			printf("%i  ", (int)a[i][r]);
		cout << endl;
	}
}

class TREE_EL
{
	int val;
	int summ;
	TREE_EL *l;
	TREE_EL *r;
public:
	TREE_EL(int _val,int _summ)
	{
		val = _val;
		summ = _summ;
		l = nullptr;
		r = nullptr;
	}
	
	~TREE_EL()
	{
		delete l;
		delete r;
	}



	friend class TREE;
	friend class GEN_KOM_SV;
};

class TREE
{
	TREE_EL *root;
public:
	TREE()
	{
		root = nullptr;
	}
	void gen_m_comb(int _n);
	friend class GEN_KOM_SV;
};

void TREE::gen_m_comb(int _n)
{
	queue <TREE_EL*> q;

	root = new TREE_EL(_n,0);

	q.push(root);

	while (!q.empty())
	{
		TREE_EL *e=q.front();

		if (e->summ + e->val <= _n)
		{
			e->l = new TREE_EL(e->val, e->summ + e->val);
			q.push(e->l);
		}
		if (e->val > 1)
		{
			e->r = new TREE_EL(e->val - 1, e->summ);
			q.push(e->r);
		}

		q.pop();

		
	}
}

class GEN_KOM_SV
{
public:
	deque <string> s;
	int n;
	
	GEN_KOM_SV()
	{
		n = 0;
	}
	GEN_KOM_SV(int _n)
	{
		n = _n;
		TREE t;
		
		t.gen_m_comb(10);

		queue < TREE_EL* > q;
		queue < string > q_s;

		q_s.push("");
		q.push(t.root);


		while (!q.empty())
		{

			TREE_EL *e = q.front();
			if (e->l != nullptr)
			{
				q.push(e->l);
				q_s.push(q_s.front()+(char)(e->val+'0'));
			}
			if (e->r != nullptr)
			if (e->summ < 10)
			{
				q.push(e->r);
				q_s.push(q_s.front());
			}
			if (e->summ == 10)
			{
				cout << q_s.front().data() << endl;
				s.push_back(q_s.front());
			}
			q.pop();
			q_s.pop();
		}
	}
	int getN()
	{
		return s.size();
	}
	string getS(int _n)
	{
		if (_n < 0)
			return "";
		if (_n >= s.size())
			return "";
		return s[_n];
	}

};



int main()
{


	/** /
	int a(0), b(0);
	long double u = 1 ;

	int arr[100];
	int buf[7];//(номер тарелки для пирожнного)

	for (int i = 0; i < 100; i++)
		arr[i] = 0;

	for (int i = 0; i < 7; i++)
		buf[i] = 0;

	while (buf[6]==0)
	{
		buf[0]++;
		for (int i = 0; i < 6; i++)
			if (buf[i] == 3)
			{
				buf[i] = 0;
				buf[i+1]++;
			}

		int buf1[3];//(тарелки 1-есть пир. 0-нет)
		for (int o = 0; o < 3; o++)
			buf1[o] = 0;

		for (int o = 0; o < 6; o++)
			buf1[buf[o]] = 1;

		if (buf1[0] == 1 && buf1[1] == 1 && buf1[2] == 1)
			arr[1]++;
		arr[0]++;
	}
	cout << arr[0] << " " << arr[1];
	system("pause");
	/**/
	
	/**/
	int arr[100];

	for (int i = 0; i < 100; i++)
		arr[i] = 0;

	list <string>all;

	for (int i=0;i<1000000;i++)
	{

		string result = "";
		for (int cake = 0; cake < 6; cake++)
		{
			int plate = rand() % 3;
			result += plate;
		}



	}

	/**/

	/** /
	GRAPH a(10);

	cout << a.get_kom_sv().data();

	GEN_KOM_SV kom(10);

	a.put();

	system("pause");
	/**/
}

