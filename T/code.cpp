#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/

class POS
{
public:
	int x, y,n;
	POS(int _x, int _y,int _n) :x(_x), y(_y),n(_n){}
};

class MARK
{
public:
	int w[100][200];
	int a[100][200];


	void proc(string wall, string emepty, string target, string start, char map[100][200])
	{
		deque<POS> q;
		for (int i = 0; i<100; i++)
			for (int r = 0; r<200; r++)
			{
				for (int o = 0; o < wall.length(); o++)
					if (map[i][r] == wall[o])
						w[i][r] = '#';

				for (int o = 0; o < emepty.length(); o++)
					if (map[i][r] == emepty[o])
						w[i][r] = ' ';

				for (int o = 0; o < target.length(); o++)
					if (map[i][r] == target[o])
						w[i][r] = 'C';

				for (int o = 0; o < start.length(); o++)
					if (map[i][r] == start[o])
						w[i][r] = 'T';

				a[i][r] = -1;
				if (map[i][r] == 'C')
				{
					q.push_back(POS(i,r,0));
				}
			}

		while (q.size() != 0)
		{
			POS p=(q.front());
			q.pop_front();
			if (a[p.x][p.y] == -1)
			{
				a[p.x][p.y] = p.n;

				int xx, yy;

				xx = -1; yy = 0;
				if (w[p.x + xx][p.y + yy] == ' ' || w[p.x + xx][p.y + yy] == 'T')
				{
					q.push_back(POS(p.x, p.y, p.n + 1));
				}

				xx = 1; yy = 0;
				if (w[p.x + xx][p.y + yy] == ' ' || w[p.x + xx][p.y + yy] == 'T')
				{
					q.push_back(POS(p.x, p.y, p.n + 1));
				}

				xx = 0; yy = 1;
				if (w[p.x + xx][p.y + yy] == ' ' || w[p.x + xx][p.y + yy] == 'T')
				{
					q.push_back(POS(p.x, p.y, p.n + 1));
				}

				xx = 0; yy = -1;
				if (w[p.x + xx][p.y + yy] == ' ' || w[p.x + xx][p.y + yy] == 'T')
				{
					q.push_back(POS(p.x, p.y, p.n + 1));
				}


			}
		}

	}
};

int main()
{
	int R; // number of rows.
	int C; // number of columns.
	int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
	cin >> R >> C >> A; cin.ignore();

	// game loop
	while (1) {
		int ky; // row where Kirk is located.
		int kx; // column where Kirk is located.
		cin >> ky >> kx; cin.ignore();
		char lab[100][200];

		for (int i = 0; i < R; i++)
		{
			string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
			cin >> ROW; cin.ignore();
			for (int r = 0; r<ROW.length(); r++)
				lab[r][i] = ROW[r];
		}

		POS c_pos(0,0,-1);

		for (int i = 0; i < C; i++)
			for (int r = 0; r < R; r++)
				if (lab[i][r] == 'C')
					c_pos = POS(i,r,0);
		lab[kx][ky] = 'K';
		MARK m_exp;
		m_exp.proc("#C", ".?T", "?","K", lab);
		MARK m_freeway;
		m_exp.proc("#?", ".K", "T","C", lab);

		if (c_pos.n == -1 || m_freeway.a[c_pos.x][c_pos.y]>A)
		{

		}


		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		cout << "RIGHT" << endl; // Kirk's next move (UP DOWN LEFT or RIGHT).
	}
}