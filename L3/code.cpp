#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <queue>

using namespace std;



class NODE {
	char d;	 //тег узла
	NODE * pl;	// левый сын
	NODE * pr;	// правый сын
public:
	NODE() : pl(nullptr), pr(nullptr), d(rand() % 20) {} // конструктор узла
	~NODE()
	{
		if (pl) delete pl; // деструктор (уничтожает поддерево)
		if (pr) delete pr;
	}
	friend class TREE;
	friend int put_node(NODE * n, char **s, int x, int y);
	friend char mark_pr(NODE * n, char ch);
	friend char obh_sh(NODE * n);
};

class TREE
{
	int N;	// узлов без сыновей
	int depth;	// узлов без сыновей
	NODE * root;	// указатель на вершину дерева
public:
	void InTREE(char*);	// создание дерева
	void GenTREE(int max_depth);	// создание дерева
	void mark();
	int proc();
	void OutTREE();	// выдача на экран
};

char num_to_ch(char num)
{
	if (num + 'a' <= 'z')
		return num + 'a';
	else
		return num + 'a' - 'z' - 1 + 'A';
}

char obh_sh(NODE * n)
{
	if (n == nullptr)
		return 0;
	queue < NODE* > q;

	int N=1;

	q.push(n);

	while (!q.empty())
	{
		n = q.front();

		if (n->pl)
		{
			N++;
			q.push(n->pl);
		}
		if (n->pr)
		{
			N++;
			q.push(n->pr);
		}

		cout << num_to_ch(n->d) << ' ';
		q.pop();
	}
	return N;
}

char mark_pr(NODE * n, char ch=0)
{
	if (n == nullptr)
		return ch;

	n->d = ch;

	return mark_pr(n->pr, mark_pr(n->pl,ch+1));
}

void TREE::mark()
{
	mark_pr(root);
}

int TREE::proc()
{
	return obh_sh(root);
}

int put_node(NODE * n,char **s, int x=0, int y=0)
{
	if (n == nullptr)
		return 1;

	int ras, ras1,ras2;

	ras1 = put_node(n->pl, s, x, y + 2);
	ras = ras1;
	if (n->pl == nullptr || n->pr == nullptr)
		ras -= 2;
	ras2 = put_node(n->pr, s, x + ras + 1, y + 2);
	ras = ras + 1 + ras2;

	s[y][x + ras / 2] = num_to_ch(n->d);

	if (n->pl != nullptr || n->pr != nullptr)
		s[y+1][x + ras / 2] = '.';

	if (n->pl != nullptr && n->pr != nullptr)
	{
		for (int i = x+ras1/2+1; i <= x+ras1+1+ras2/2-1 ;i++)
			s[y+2][i] = '.';
	}
	

	return ras;

}

void TREE::OutTREE()
{
	char *s;
	char **ss;


	s = new char[N * 2 * (depth * 2 + 1) + 1];
	ss = new char*[depth * 2 + 3];

	for (int i = 0; i < N * 2 * (depth * 2 + 1); i++)
		s[i] = ' ';

	for (int i = 0; i < depth * 2 + 1; i++)
	{
		s[(i+1)*N*2-1]='\n';
		ss[i] = s + i*N * 2;
	}

	s[N * 2 * (depth * 2 + 1)] = 0;




	put_node(root, ss);





	cout << N << endl << s;
	

	delete[]ss;
	delete[]s;

}

void TREE::InTREE(char *s)
{
	N = 0;
	depth = 0;

	NODE ** arr_n = new NODE*[100 + 1];
	int * arr_s = new int[100 + 1];//0-left 1-right

	int l = 0;
	bool b = 0;

	root = new NODE();
	arr_n[0] = root;
	arr_s[0] = 0;

	for (; b == 0;)
	{
		if (*s == 0)
			return;

		if (*(s++)=='1')
		{
			l++;
			if (l>depth)depth = l;
			if (arr_s[l - 1] == 0)
			{
				arr_n[l] = new NODE();
				arr_n[l - 1]->pl = arr_n[l];
				arr_s[l] = 0;
			}
			else
			{
				arr_n[l] = new NODE();
				arr_n[l - 1]->pr = arr_n[l];
				arr_s[l] = 0;
			}
		}
		else
		{
			if (arr_s[l] == 0)
			{
				arr_s[l] = 1;
			}
			else
			{
				if (arr_n[l]->pl == nullptr)
				{
					N++;
				}
				while (l >= 0 && arr_s[l] == 1)
					l--;
				if (l < 0)
				{
					b = 1;
				}
				else
				{
					arr_s[l] = 1;
				}
			}
		}
	}



	delete[]arr_n;
	delete[]arr_s;
}


void TREE::GenTREE(int n)
{
	N = 0;
	depth = 0;
	if (n < 0)return;
	if (n == 0)
		root = new NODE();

	NODE ** arr_n = new NODE*[n + 1];
	int * arr_s = new int[n + 1];//0-left 1-right

	int l = 0;
	bool b = 0;

	root = new NODE();
	arr_n[0] = root;
	arr_s[0] = 0;

	for (; b == 0;)
	{
		if (rand() % n < n - l)
		{
			l++;
			if (l>depth)depth = l;
			if (arr_s[l - 1] == 0)
			{
				arr_n[l] = new NODE();
				arr_n[l - 1]->pl = arr_n[l];
				arr_s[l] = 0;
			}
			else
			{
				arr_n[l] = new NODE();
				arr_n[l - 1]->pr = arr_n[l];
				arr_s[l] = 0;
			}
		}
		else
		{
			if (arr_s[l] == 0)
			{
				arr_s[l] = 1;
			}
			else
			{
				if (arr_n[l]->pl == nullptr)
				{
					N++;
				}
				while (l >= 0 && arr_s[l] == 1)
					l--;
				if (l < 0)
				{
					b = 1;
				}
				else
				{
					arr_s[l] = 1;
				}
			}
		}
	}



	delete[]arr_n;
	delete[]arr_s;
}

int main()
{

	setlocale(0,"RU");
	srand(time(nullptr));


	TREE l;

	char ch;
	char buf[70];

	do{
		system("cls");
		l.GenTREE(6);

		//gets_s(buf, 70);
		//l.InTREE(buf);

		l.mark();

		l.OutTREE();

		int n = l.proc();

		cout << "\nN=" << n << "\n";
		cout << "Сделать ещё тест?(y/n)";

		do
		{
			ch = getch();
		} while (ch != 'y' && ch != 'Y' &&ch != 'n' &&ch != 'N');

	} while (ch == 'y' || ch == 'Y');

}

