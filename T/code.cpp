#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/


class HEX
{
public:
	int ID;
	int conn[7];
	int vis;
	int pt;
	int army;//-1 - 1 enemy
	int parmy;
	int own;//-1 - 1 enemy
	int cont;

	HEX()
	{
		for (int i = 0; i<6; i++)
		{
			conn[i] = -1;
		}
	}
};


HEX map[1000];
int N;

struct H_ACT
{
	int ID;
	int x;
};

class STAT_HEX
{
public:
	int n;
	int *m;


	STAT_HEX()
	{
		n = 0;
		m = nullptr;
	}
	void init(int _n)
	{
		delete[] m;

		n = _n;
		m = new int[n];
		for (int i = 0; i<n; i++)
			m[i] = -1;
	}
	void proc(HEX* map)
	{

		int i, r, o, j;
		deque <H_ACT> act;
		for (i = 0; i<n; i++)
			if (m[i] != -1)
			{
				H_ACT a;
				a.ID = i;
				a.x = m[i];
				m[i] = -1;
				act.push_front(a);
			}

		sort(act.begin(), act.end(), [](const H_ACT &_a, const H_ACT &_b){return bool(_a.x > _b.x); });

		deque <H_ACT> q;

		if (act.size() <= 0)
			return;

		deque <int> is;
		is.resize(n);
		for (i = 0; i < n; i++)
			is[n] = 0;

		q.push_front(act[0]);
		is[act[0].ID] = 1;
		act.pop_back();

		while (q.size()>0)
		{
			//cerr <<q.size() <<endl;
			int i = 0;

			HEX h = map[q.front().ID];

			if (m[q.front().ID] == -1 || m[q.front().ID] >= q.front().x)
			{
				m[q.front().ID] = q.front().x;
				for (int r = 0; h.conn[r] != -1; r++)
				{
					if (is[h.conn[r]] == 0)
					{
						H_ACT a;
						a.ID = h.conn[r];
						a.x = q.front().x + 1;
						q.push_back(a);
						is[h.conn[r]] = 1;
						m[h.conn[r]] = a.x;
					}
				}
			}

			is[q.front().ID] = 1;

			q.pop_front();
			while (q.size() <= 0 && act.size()>0)
			{
				q.push_front(act[0]);
				is[act[0].ID] = 1;
				act.pop_front();
			}

			while (act.size()>0 && q.front().x >= act.front().x)
			{
				q.push_front(act[0]);
				is[act[0].ID] = 1;
				act.pop_front();
			}
		}


	}


	void fill(HEX* map)
	{

		int i, r, o, j;
		deque <H_ACT> act;
		for (i = 0; i<n; i++)
			if (m[i] != -1)
			{
				H_ACT a;
				a.ID = i;
				a.x = m[i];
				m[i] = -1;
				act.push_front(a);
			}

		sort(act.begin(), act.end(), [](const H_ACT &_a, const H_ACT &_b){return bool(_a.x > _b.x); });

		deque <H_ACT> q;

		if (act.size() <= 0)
			return;

		deque <int> is;
		is.resize(n);
		for (i = 0; i < n; i++)
			is[n] = 0;

		q.push_front(act[0]);
		is[act[0].ID] = 1;
		act.pop_back();

		while (q.size()>0)
		{
			//cerr <<q.size() <<endl;
			int i = 0;

			HEX h = map[q.front().ID];

			if (m[q.front().ID] == -1 || m[q.front().ID] >= q.front().x)
			{
				m[q.front().ID] = q.front().x;
				for (int r = 0; h.conn[r] != -1; r++)
				{
					if (is[h.conn[r]] == 0)
					{
						H_ACT a;
						a.ID = h.conn[r];
						a.x = q.front().x;
						q.push_back(a);
						is[h.conn[r]] = 1;
						m[h.conn[r]] = a.x;
					}
				}
			}

			is[q.front().ID] = 1;

			q.pop_front();
			while (q.size() <= 0 && act.size()>0)
			{
				q.push_front(act[0]);
				is[act[0].ID] = 1;
				act.pop_front();
			}

			while (act.size()>0 && q.front().x >= act.front().x)
			{
				q.push_front(act[0]);
				is[act[0].ID] = 1;
				act.pop_front();
			}


		}


	}

	void expand_zero(HEX* map)
	{

	}




};


void S_frist_step(int _pl);


int main()
{
	int playerCount; // the amount of players (2 to 4)
	int myId; // my player ID (0, 1, 2 or 3)
	int zoneCount; // the amount of zones on the map
	int linkCount; // the amount of links between all zones
	cin >> playerCount >> myId >> zoneCount >> linkCount; cin.ignore();

	N = zoneCount;


	for (int i = 0; i < zoneCount; i++) {
		int zoneId; // this zone's ID (between 0 and zoneCount-1)
		int platinumSource;
		cin >> zoneId >> platinumSource; cin.ignore();
		map[zoneId].ID = zoneId;
		map[zoneId].pt = platinumSource;
		map[zoneId].conn[0] = -1;
	}
	for (int i = 0; i < linkCount; i++) {
		int zone1;
		int zone2;
		cin >> zone1 >> zone2; cin.ignore();
		int r = 0;
		while (map[zone1].conn[r] != -1)
		{
			r++;
		}
		map[zone1].conn[r] = zone2;
		map[zone1].conn[r + 1] = -1;

		r = 0;
		while (map[zone2].conn[r] != -1)
		{
			r++;
		}
		map[zone2].conn[r] = zone1;
		map[zone2].conn[r + 1] = -1;
	}

	if (1 == 2)
	{
		int platinum; // my available Platinum
		cin >> platinum; cin.ignore();
		for (int i = 0; i < zoneCount; i++)
		{
			int zId; // this zone's ID
			int ownerId; // the player who owns this zone (-1 otherwise)
			int podsP[4];
			cin >> zId >> ownerId >> podsP[0] >> podsP[1] >> podsP[2] >> podsP[3]; cin.ignore();
			HEX h = map[zId];
			h.army = -podsP[0] - podsP[1] - podsP[2] - podsP[3] + 2 * podsP[myId];
			h.own = 0;
			if (ownerId != -1)
				h.own = -1;
			if (ownerId == myId)
				h.own = 1;
			map[zId] = h;
		}
		cout << endl << endl;
	}



	int frame = 0;

	// game loop
	while (1) {
		int platinum; // my available Platinum
		cin >> platinum; cin.ignore();
		for (int i = 0; i < zoneCount; i++)
		{
			int zId; // this zone's ID
			int ownerId; // the player who owns this zone (-1 otherwise)
			int podsP[4];
			cin >> zId >> ownerId >> podsP[0] >> podsP[1] >> podsP[2] >> podsP[3]; cin.ignore();
			HEX h = map[zId];
			h.army = -podsP[0] - podsP[1] - podsP[2] - podsP[3] + 2 * podsP[myId];
			h.own = 0;
			h.parmy = 0;
			if (ownerId != -1)
				h.own = -1;
			if (ownerId == myId)
				h.own = 1;
			map[zId] = h;
		}

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		STAT_HEX front;
		front.init(zoneCount);

		for (int i = 0; i < zoneCount; i++)
		{
			HEX h = map[i];
			if (h.own != 1)
				front.m[i] = 1;
		}

		front.proc(map);


		STAT_HEX cap_point;
		cap_point.init(zoneCount);

		for (int i = 0; i < zoneCount; i++)
		{
			HEX h = map[i];
			if (h.own != 1 && h.pt>0)
				cap_point.m[i] = 1;
		}

		cap_point.proc(map);





		bool is_active = 0;



		//1-capture
		for (int i = 0; i < zoneCount; i++)
		{
			HEX h = map[i];
			int j = 0;
			int min = 100;

			if (h.pt > 0 && h.own != 1)
			{
				int my = 0;
				int enemy = -h.army;

				for (int r = 0; h.conn[r] != -1; r++)
				{
					HEX h1 = map[h.conn[r]];
					if (h1.army>0)
						my += h1.army;
				}

				if (my > enemy)
				{
					for (int r = 0; h.conn[r] != -1 && enemy >= 0; r++)
					{
						HEX h1 = map[h.conn[r]];
						if (h1.army > 0)
						{
							my -= h1.army;
							enemy -= h1.army;
							cout << h1.army << " " << h.conn[r] << " " << i << " ";

							map[i].parmy += h1.army;
							map[h.conn[r]].army = 0;
						}
					}

				}
			}

		}


		//2-defense
		for (int i = 0; i < zoneCount; i++)
		{
			HEX h = map[i];
			int j = 0;
			int min = 100;

			if (h.pt > 0 && h.own == 1)
			{
				int my = h.army;
				int enemy = 0;

				for (int r = 0; h.conn[r] != -1; r++)
				{
					HEX h1 = map[h.conn[r]];
					if (h1.army>0)
						my += h1.army;
					if (h1.army<0)
						enemy -= h1.army;
				}

				if (my > enemy)
				{

				}
			}

		}



		for (int i = 0; i < zoneCount; i++)
		{
			HEX h = map[i];
			for (int j = 0; j<h.army; j++)
			{
				int min = 1000;
				int o = 0;
				int co = 1;
				for (int r = 0; h.conn[r] != -1; r++)
				{
					if (min == cap_point.m[h.conn[r]])
					{
						co++;
						if (rand() % co == 0)
							o = r;
					}


					if (min>cap_point.m[h.conn[r]])
					{
						min = cap_point.m[h.conn[r]];
						co = 1;
						o = r;
					}
				}


				cout << 1 << " " << i << " " << h.conn[o] << " ";
			}
		}

		cout << endl;


		//1-def
		for (int i = 0; i < zoneCount; i++)
		{
			HEX h = map[i];
			if (h.pt > 0 && h.own == 1)
			{
				int enemy = 0;

				for (int r = 0; h.conn[r] != -1; r++)
				{
					HEX h1 = map[h.conn[r]];
					if (h1.army<0)
						enemy -= h1.army;
				}
				if (enemy>0)
					cout << enemy << " " << i << " ";

			}
		}




		if (frame == 0)
		{
			S_frist_step(playerCount);
		}

		deque <HEX> free_hex;

		for (int i = 0; i < zoneCount; i++)
		{
			if (map[i].own == 0 && map[i].pt>0)
				free_hex.push_front(map[i]);
		}

		sort(free_hex.begin(), free_hex.end(), [](const HEX &_a, const HEX &_b){return bool(_a.pt > _b.pt); });
		cerr << free_hex.size();
		for (int i = 0; i < free_hex.size() && platinum / 20>0; i++)
		{
			cerr << "1 " << i << " ";
			cout << "1 " << free_hex[i].ID << " ";
			platinum -= 20;
		}

		for (int i = 0; i < 100 && platinum / 20>0; i++)
		{
			int o = 0;
			int count = 0;
			for (int r = 0; r < zoneCount; r++)
			{
				if (map[r].own == 0)
				{
					count++;
					if (rand() % count == 0)
						o = r;
				}
				else
				{
					bool b = 0;

					for (int o = 0; map[r].conn[o] != -1; o++)
						if (map[map[r].conn[o]].own != 1)
							b = 1;

					if (map[r].own == 1 && b == 1)
					{
						count++;
						if (rand() % count == 0)
							o = r;
					}
				}
			}
			cout << "1 " << o << " ";
			platinum -= 20;

		}
		cout << endl;
		frame++;

	}
}



void S_one_cont(int units)
{
	struct CONT_ST
	{
		int pt;
	};
	int positions = (10+units-1) / units;


	vector <int> cont_plat;


	for (int i = 0; i < N; i++)
	{
		if (map[i].cont + 1 > cont_plat.size())
		{
			cont_plat.resize(map[i].cont + 1);
		}
	}
	
	for (int i = 0; i < cont_plat.size(); i++)
		cont_plat[i] = 0;

	for (int i = 0; i < N; i++)
	{
		cont_plat[map[i].cont] += map[i].pt;
	}

	int best = 0;

	for (int i = 0; i < cont_plat.size(); i++)
		if (cont_plat[i]>cont_plat[best])
			best = i;

	for (int r = 0; r < positions; r++)
	{
		cerr << "place ";
		int j = -1;
		int o = 0;
		for (int i = 0; i < N; i++)
		{
			if (map[i].cont == best && map[i].pt>0 && map[j].parmy == 0)
			{
				o++;
				if (rand() % o == 0)
					j = i;
			}
		}
		map[j].parmy = units;
		if (j!=-1)
		cout << units << " " << j << " ";
	}


}

void mark_cont()
{
	STAT_HEX cont;
	cont.init(N);

	int k = 0;

	for (int i = 0; i < N; i++)
	{
		if (cont.m[i] == -1)
		{
			cont.m[i] = k;
			k++;
		}
		for (int r = 0; r < N; r++)
			cont.fill(map);

	}

	for (int i = 0; i < N; i++)
	{
		map[i].cont = cont.m[i];

	}

	//while (1){ static int r345 = 2; r345++; }//pfffff

}

void S_frist_step(int _pl)
{
	int world_type;

	int ptl[8];

	mark_cont();

	for (int r = 0; r < 8; r++)
		ptl[r]=0;

	for (int r = 0; r < N; r++)
	{
		ptl[map[r].pt]++;
	}

	for (int r = 0; r < 7; r++)
		ptl[7] += ptl[r];




	if (_pl == 2)
	{
		S_one_cont(1);
	}
	if (_pl == 3 ||_pl==4)
	{
		if (ptl[7]>30)
		{
			S_one_cont(1);
		}
		S_one_cont(2);
	}
}