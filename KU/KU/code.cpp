#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>


#include <conio.h>
#include <time.h>
#include <iostream>
#include <queue>
#include <deque>
#include <list>
#include <thread>
#include <mutex>


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

const int SIZE_X_DECREATE = 10;
const int SIZE_Y_DECREATE = 80;
using namespace std;

#pragma intrinsic(__rdtsc)


class TREE_STORE_NODE
{
private:
	int val;
	vector <TREE_STORE_NODE*> q;
	TREE_STORE_NODE(TREE_STORE_NODE* _n)
	{
		val = _n->val;
		q.resize(_n->q.size());
		for (int i = 0; i < q.size(); i++)
		{
			if (_n->q[i] == nullptr)
				q[i] = nullptr;
			else
				q[i] = new TREE_STORE_NODE(_n->q[i]);
		}
	}
	TREE_STORE_NODE(int _n, int _val) :val(_val)
	{
		q.resize(_n);
		for (int i = 0; i < _n; i++)
			q[i] = nullptr;
	}
	~TREE_STORE_NODE()
	{
		for (int i = 0; i < q.size(); i++)
			if (q[i])
				delete q[i];
	}
	friend class TREE_STORE;
	friend class TREE_STORE_ITERATOR;
};


class TREE_STORE_ITERATOR
{
	struct ITER_N_L
	{
		int i;
		TREE_STORE_NODE *l;
	};
private:

	vector <ITER_N_L> arr;

	TREE_STORE *t;
public:
	TREE_STORE_ITERATOR()
	{
		t = nullptr;
	}
	TREE_STORE_ITERATOR(const TREE_STORE_ITERATOR &_a)
	{
		t = _a.t;
		arr = _a.arr;
	}
	void get_next();
	friend const TREE_STORE_ITERATOR operator++(TREE_STORE_ITERATOR &_a)
	{
		_a.get_next();
		return _a;
	}
	friend const TREE_STORE_ITERATOR operator++(TREE_STORE_ITERATOR &_a, int)
	{
		auto b(_a);
		_a.get_next();
		return b;
	}
	vector<int> operator *()
	{
		vector<int> q;
		q.resize(arr.size());
		for (int i = 0; i < arr.size(); i++)
			q[i] = arr[i].i;
		return q;
	}
	friend bool operator ==(const TREE_STORE_ITERATOR &_a, const TREE_STORE_ITERATOR &_b)
	{
		if (_a.arr.size() != _b.arr.size())
			return 0;
		if (_a.t != _b.t)
			return 0;
		for (int i = 0; i < _a.arr.size(); i++)
			if (_a.arr[i].i != _b.arr[i].i)
				return 0;
		return 1;
	}
	friend bool operator !=(const TREE_STORE_ITERATOR &_a, const TREE_STORE_ITERATOR &_b)
	{
		return !(_a == _b);
	}
	friend class TREE_STORE;
};

class TREE_STORE
{
private:
	TREE_STORE_NODE *node;
	int n;
public:
	TREE_STORE(int _n)
	{
		node = new TREE_STORE_NODE(_n,0);
		n = _n;
	}
	void add_ray(vector<int> _v)
	{
		TREE_STORE_NODE *p=node;
		int i = 0;
		while (i<_v.size())
		{
			if (!p->q[_v[i]])
			{
				p->q[_v[i]] = new TREE_STORE_NODE(n, 0);
			}
			p = p->q[_v[i]];
			i++;
		} 
		p->val = 1;
	}
	~TREE_STORE()
	{
		delete node;
	}
	TREE_STORE_ITERATOR begin()
	{
		TREE_STORE_ITERATOR i;
		int o = -1;
		for (int r = 0; r < n; r++)
			if (node->q[r] != nullptr)
			{
				o = r;
				r = n;
			}
		if (o != -1)
		{
			i.arr.resize(1);
			i.arr[0].i = o;
			i.arr[0].l = node;
			i.t = this;
			if (node->q[i.arr[0].i]->val == 0)
				i.get_next();
		}
		else
		{
			i = this->end();
		}
		return i;
	}
	TREE_STORE_ITERATOR end()
	{
		TREE_STORE_ITERATOR i;
		i.arr.resize(0);
		i.t = this;
		return i;
	}
	TREE_STORE (const TREE_STORE &_a)
	{
		node = new TREE_STORE_NODE(_a.node);
		n = _a.n;
	}
	TREE_STORE &operator =(const TREE_STORE &_a)
	{
		delete node;
		node = new TREE_STORE_NODE(_a.node);
		n = _a.n;

		return *this;
	}
	friend class TREE_STORE_ITERATOR;
};


void TREE_STORE_ITERATOR::get_next()
{
	bool b = 0;
	bool end = 0;

	do
	{
		int k = arr.size();

		if (k == 0)
		{
			throw 12345;
		}
		k--;
		auto l = arr[k].l->q[arr[k].i];
		b = 0;
		int j = 0;
		for (int i = 0; i < t->n; i++)
			if (l->q[i])
			{
				j = i;
				i = t->n;
				b = 1;
			}

		if (b == 1)
		{
			arr.resize(k + 2);
			k++;
			arr[k].i = j;
			arr[k].l = l;
			if (l->q[j]->val == 1)
			{
				end = 1;
				b = 0;
			}
		}
	} while (b == 1);
	if (!end)
	{
		int k = arr.size();

		if (k > 0)
		{
			do
			{
				arr.resize(k);
				k--;
				do
				{
					arr[k].i++;
				} while (arr[k].i < t->n && arr[k].l->q[arr[k].i] == nullptr);
			} while (k > 0 && arr[k].i >= t->n);
		}
		else
		{
			throw "out of TREE_STORE_ITERATOR";
		}

		if (k == 0 && arr[k].i == t->n)
		{
			arr.resize(0);
		}
		else
			while (arr[k].l->q[arr[k].i]->val == 0)
			{

				k = arr.size();

				if (k == 0)
				{
					throw "OUT OF TREE RAY";
				}
				k--;
				auto l = arr[k].l->q[arr[k].i];
				b = 0;
				int j = 0;
				for (int i = 0; i < t->n; i++)
					if (l->q[i])
					{
						j = i;
						i = t->n;
						b = 1;
					}

				if (b == 1)
				{
					arr.resize(k + 2);
					k++;
					arr[k].i = j;
					arr[k].l = l;
					if (l->q[j]->val == 1)
					{
						end = 1;
						b = 0;
					}
				}

			}

	}


	
}


class GRAPH
{
	vector<vector<int>> a;
public:
	GRAPH(int _n);
	GRAPH(const GRAPH &_a);
	GRAPH operator =(const GRAPH &_a);
	void put();
	int getN(){ return a.size(); }
	vector<int> operator[](const int _i);
	TREE_STORE get_cycles_el();
	void remove_point(int);
};

int compare(const void *_a, const void *_b)
{
	return (*(int*)_a - *(int*)_b);
}

void GRAPH::remove_point(int _i)
{
	if (_i < 0 || _i >= a.size())
		return;

	a[_i] = a[a.size() - 1];

	a.resize(a.size()-1);
	
	for (int i = 0; i < a.size(); i++)
	{
		int offs = 0;

		for (int r = 0; r < a[i].size(); r++)
		{
			if (a[i][r] == _i)
			{
				offs++;
			}
			else
			{
				if (a[i][r] == a.size())
				{
					a[i][r - offs] = _i;
				}
				else
				{
					a[i][r - offs] = a[i][r];
				}
			}
		}

		if (offs > 0)
		{
			a[i].resize(a[i].size() - offs);
		}

		if (a[i].size()>0)
			qsort(&a[i][0], a[i].size(), sizeof(int), compare);
		 
	}

}

vector<int> GRAPH::operator[](const int _i)
{
	if (_i < 0 || _i >= a.size())
		return a[0];
	return a[_i];
}

GRAPH::GRAPH(int _n = 0)
{
	if (_n <= 0 || _n > 2048)
	{
		return;
	}
	a.resize(_n);

	vector<int> arr;

	arr.resize(_n);

	for (int i = 0; i < a.size(); i++)
	{
		int o = 0;
		for (int r = 0; r < a.size(); r++)
			if (rand() % 15 < 1)
			{
				arr[o] = r;
				o++;
			}

		a[i].resize(o);

		for (int r = 0; r < o; r++)
		{
			a[i][r] = arr[r];
		}
	}
}

GRAPH::GRAPH(const GRAPH &_a)
{
	a=_a.a;
}

void GRAPH::put()
{
	//printf("   ");
	//for (int r = 0; r < n; r++)
	//	printf("%3i", r);
	//cout << endl;
	//for (int r = -1; r < n; r++)
	//	printf("---");

	cout << endl;

	for (int i = 0; i < a.size(); i++)
	{
		printf("%3i| ", i);
		for (int r = 0; r < a[i].size(); r++)
			printf("%i  ", (int)a[i][r]);
		cout << endl;
	}
}

TREE_STORE GRAPH::get_cycles_el()
{
	TREE_STORE res(a.size());

	vector <int> used;
	vector <int> vertex_ray;
	vector <int> id_ray;

	GRAPH gr=*this;
	
	vector <int> otobr;
	otobr.resize(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		otobr[i] = i;
	}
	int is_del;
	do
	{
		is_del = 0;
		for (int i = gr.a.size() - 1; i >= 0; i--)
		{
			int b = 0;
			if (gr.a[i].size() != 0)
				b = 1;
			for (int r = 0; r < gr.a.size() && b == 1; r++)
				for (int o = 0; o < gr.a[r].size(); o++)
					if (gr.a[r][o] == i)
						b = 2;

			if (b < 2)
			{
				otobr[i] = otobr[gr.a.size() - 1];
				gr.remove_point(i);
				is_del = 1;
			}
		}
	} while (is_del);
	

	cout << "new gr:"<<endl;
	gr.put();
	
	if (gr.a.size() == 0)
		return res;

	used.resize(gr.a.size() + 3);
	used.resize(gr.a.size() + 3);
	vertex_ray.resize(gr.a.size() + 3);
	id_ray.resize(gr.a.size() + 3);

	bool b = 1;

	int k;

	k = 1;
	id_ray[0] = -1;
	vertex_ray[0] = 0;
	

	while (b)
	{
		//while (cyc_ray[k] != -1)
		//	k++;

		k++;
		do
		{
			k--;
			if (k > 0)
			{
				used[vertex_ray[k]] = 0;
				vector<int> &v_l = gr.a[vertex_ray[k - 1]];
				do
				{
					id_ray[k]++;

				} while (id_ray[k] < v_l.size() && v_l[id_ray[k]] <= vertex_ray[0] && used[v_l[id_ray[k]]] == 1);
			}
			else
			{
				id_ray[k]++;
			}

		} while (k > 0 && !(id_ray[k] < gr.a[vertex_ray[k - 1]].size() && gr.a[vertex_ray[k - 1]][id_ray[k]] <= vertex_ray[0] && id_ray[k] < gr.a[vertex_ray[k - 1]].size()));

		if (k > 0)
		{
			vertex_ray[k] = gr.a[vertex_ray[k - 1]][id_ray[k]];
			used[vertex_ray[k]] = 1;
		}
		else
			vertex_ray[0] = id_ray[0];
		

		if (vertex_ray[0] != gr.a.size())
		{
			if (vertex_ray[0] != vertex_ray[k] || k == 0)
			{
				int b1 = 0;
				do
				{
					int d = -1;
					for (int i = 0; i < gr.a[vertex_ray[k]].size(); i++)
						if (used[gr.a[vertex_ray[k]][i]] == 0 && gr.a[vertex_ray[k]][i] <= vertex_ray[0])
						{
							d = i;
							i = gr.a.size();
						}


					k++;
					id_ray[k] = d;
					if (d != -1)
					{
						vertex_ray[k] = gr.a[vertex_ray[k - 1]][d];
						used[vertex_ray[k]] = 1;
						if (k>0 && vertex_ray[k] == vertex_ray[0])
						{
							b1 = 1;
						}
					}
					else
					{
						vertex_ray[k] = -1;
						b1 = 1;
						k--;
					}


				} while (b1==0);
			}

			if (k > 0 && vertex_ray[k] == vertex_ray[0])
			{
				vector <int> vec;
				vec.resize(k+1);
				for (int gr3 = 0; gr3<=k; gr3++)
					vec[gr3] = otobr[vertex_ray[gr3]];

				res.add_ray(vec);


			}
			

		}
		else
		{
			b = 0;
		}

	}

	return res;
}


struct W_MOUSE
{
	int x, y;
	int mchl, mchr, mdol, mdor;
};

typedef struct													// Create A Structure
{
	GLubyte	*imageData;											// Image Data (Up To 32 Bits)
	GLuint	bpp;												// Image Color Depth In Bits Per Pixel.
	GLuint	x;													// Image Width
	GLuint	y;													// Image Height
	GLuint	texID;												// Texture ID Used To Select A Texture
} TextureImage;													// Structure Name

bool LoadTGA(TextureImage *texture, char *filename, int fff=GL_LINEAR/*GL_NEAREST*/)				// Loads A TGA File Into Memory
{
	GLubyte		TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };		// Uncompressed TGA Header
	GLubyte		TGAcompare[12];									// Used To Compare TGA Header
	GLubyte		header[6];										// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;									// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;										// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;											// Temporary Variable
	GLuint		type = GL_RGBA;									// Set The Default GL Mode To RBGA (32 BPP)

	glEnable(GL_TEXTURE_2D);

	FILE *file = fopen(filename, "rb");							// Open The TGA File

	if (file == NULL ||											// Does File Even Exist?
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// Does The Header Match What We Want?
		fread(header, 1, sizeof(header), file) != sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)										// Did The File Even Exist? *Added Jim Strong*
			return FALSE;										// Return False
		else													// Otherwise
		{
			fclose(file);										// If Anything Failed, Close The File
			return FALSE;										// Return False
		}
	}

	texture->x = header[1] * 256 + header[0];				// Determine The TGA x	(highbyte*256+lowbyte)
	texture->y = header[3] * 256 + header[2];				// Determine The TGA y	(highbyte*256+lowbyte)

	if (texture->x <= 0 ||									// Is The x Less Than Or Equal To Zero
		texture->y <= 0 ||									// Is The y Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32))						// Is The TGA 24 or 32 Bit?
	{
		fclose(file);											// If Anything Failed, Close The File
		return FALSE;											// Return False
	}

	texture->bpp = header[4];								// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel = texture->bpp / 8;							// Divide By 8 To Get The Bytes Per Pixel
	imageSize = (texture->x)*(texture->y)*bytesPerPixel;	// Calculate The Memory Required For The TGA Data
	//imageSize	=128*128*128;	
	texture->imageData = (GLubyte *)malloc(imageSize);			// Reserve Memory To Hold The TGA Data

	if (texture->imageData == NULL ||								// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file) != imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if (texture->imageData != NULL)							// Was Image Data Loaded
			free(texture->imageData);							// If So, Release The Image Data

		fclose(file);											// Close The File
		return FALSE;											// Return False
	}

	for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)			// Loop Through The Image Data
	{															// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp = texture->imageData[i];								// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];		// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;						// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose(file);												// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);						// Generate OpenGL texture IDs
	fff = GL_LINEAR;
	glBindTexture(GL_TEXTURE_2D, texture[0].texID);				// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, fff);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, fff);	// Linear Filtered

	if (texture[0].bpp == 24)										// Was The TGA 24 Bits
	{
		type = GL_RGB;											// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].x, texture[0].y, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;												// Texture Building Went Ok, Return True
}

class GL_PTINT_TEXT
{
	GLuint base;
	TextureImage tex;
public:
	~GL_PTINT_TEXT()										// Delete The Font List
	{
		free(tex.imageData);
	}

	void init()									// Build Our Bitmap Font
	{
		LoadTGA(&tex, "font.tga");
	}


	void operator ()(const char *fmt, ...)					// Custom GL "Print" Routine
	{
		char		text[512];								// Holds Our String
		va_list		ap;										// Pointer To List Of Arguments

		if (fmt == NULL)									// If There's No Text
			return;											// Do Nothing

		va_start(ap, fmt);									// Parses The String For Variables
		vsprintf(text, fmt, ap);							// And Converts Symbols To Actual Numbers
		va_end(ap);											// Results Are Stored In Text

		int i;
		char *s;
		for (s = text,i=0; *s; s++,i++)
		{
			int x, y;
			x = *s % 16;
			y = *s / 16;

			glBindTexture(GL_TEXTURE_2D, tex.texID);
			glBegin(GL_POLYGON);
			glTexCoord2f((0 + x) / 16.0, (0 + y) / 16.0); glVertex3f(0 + i*0.8, 0, 0);
			glTexCoord2f((0 + x) / 16.0, (1 + y) / 16.0); glVertex3f(0 + i*0.8, -1, 0);
			glTexCoord2f((1 + x) / 16.0, (1 + y) / 16.0); glVertex3f(1 + i*0.8, -1, 0);
			glTexCoord2f((1 + x) / 16.0, (0 + y) / 16.0); glVertex3f(1 + i*0.8, 0, 0);
			glEnd();

		}


	}
};

GL_PTINT_TEXT glPrint;



class OPENGL_WINDOW
{
private:
	
	HDC			hDC = NULL;		// Private GDI Device Context
	HGLRC		hRC = NULL;		// Permanent Rendering Context
	HWND		hWnd = NULL;		// Holds Our Window Handle
	HINSTANCE	hInstance;		// Holds The Instance Of The Application

	bool	keys[256];			// Array Used For The Keyboard Routine
	bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
	bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

	bool enabled;

	bool initialise;

	int razokx;
	int razoky;
	float pers_angle;
	W_MOUSE mouse;

	//static LRESULT CALLBACK WinMessage(HWND _window, unsigned int _message, WPARAM _wParam, LPARAM _lParam);	
	//LRESULT CALLBACK WinMessage(HWND _window, unsigned int _message, WPARAM _wParam, LPARAM _lParam);

	static LRESULT CALLBACK WndProcS(HWND _window, unsigned int _message, WPARAM _wParam, LPARAM _lParam)
	{
		OPENGL_WINDOW* application = 0;

		if (_message == WM_NCCREATE)
			application = (OPENGL_WINDOW*)_lParam;
		else
			application = (OPENGL_WINDOW*)GetWindowLong(_window, GWL_USERDATA);

		return application->WndProc(_window, _message, _wParam, _lParam);
	}
	LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
		UINT	uMsg,			// Message For This Window
		WPARAM	wParam,			// Additional Message Information
		LPARAM	lParam)			// Additional Message Information
	{
		//cout << uMsg << endl;
		switch (uMsg)									// Check For Windows Messages
		{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active = TRUE;						// Program Is Active
			}
			else
			{
				disable();
				enable();
				active = FALSE;						// Program Is No Longer Active
			}

			return 0;
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
			case SC_SCREENSAVE:					// Screensaver Trying To Start?
			case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				//rly this your problem....
				return 0;
			}
			break;
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			disable();
			return 0;
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			//cout << wParam<<endl;
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			if (wParam == 910)
			{
				disable();
				enable();
			}
			return 0;
			
		}
		case WM_ACTIVATEAPP:
		{
			//cout << "app\n";
			break;
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			razokx = LOWORD(lParam); razoky = HIWORD(lParam);
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
			break;
		}
		
		case WM_MOUSEMOVE:
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);
			break;
		case WM_LBUTTONDOWN:
			mouse.mdol = 1;
			mouse.mchl = 1;
			break;
		case WM_LBUTTONUP:
			mouse.mchl = 0;
			break;
		case WM_RBUTTONDOWN:
			mouse.mdor = 1;
			mouse.mchr = 1;
			break;
		case WM_RBUTTONUP:
			mouse.mchr = 0;
			break;

		}

		// Pass All Unhandled Messages To DefWindowProc
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
	{
		if (height == 0)										// Prevent A Divide By Zero By
		{
			height = 1;										// Making Height Equal One
		}

		glViewport(0, 0, width, height);						// Reset The Current Viewport

		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window
		gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1, 10000.0f);

		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
	}

	int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
	{
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glAlphaFunc(GL_GREATER, 0.99f);
		glDisable(GL_ALPHA_TEST);

		return TRUE;										// Initialization Went OK
	}

	int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
	{

		return TRUE;										// Everything Went OK
	}

	GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
	{
		if (fullscreen)										// Are We In Fullscreen Mode?
		{
			ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
			ShowCursor(TRUE);								// Show Mouse Pointer
		}

		if (hRC)											// Do We Have A Rendering Context?
		{
			if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
			{
				MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			}

			if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
			{
				MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			}
			hRC = NULL;										// Set RC To NULL
		}

		if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
		{
			MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			hDC = NULL;										// Set DC To NULL
		}

		if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
		{
			MessageBox(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			hWnd = NULL;										// Set hWnd To NULL
		}

		if (!UnregisterClass(L"OpenGL", hInstance))			// Are We Able To Unregister Class
		{
			MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			hInstance = NULL;									// Set hInstance To NULL
		}
	}

	/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
	*	title			- Title To Appear At The Top Of The Window				*
	*	width			- Width Of The GL Window Or Fullscreen Mode				*
	*	height			- Height Of The GL Window Or Fullscreen Mode			*
	*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
	*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

	BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
	{
		GLuint		PixelFormat;			// Holds The Results After Searching For A Match
		WNDCLASS	wc;						// Windows Class Structure
		DWORD		dwExStyle;				// Window Extended Style
		DWORD		dwStyle;				// Window Style
		RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
		WindowRect.left = (long)0;			// Set Left Value To 0
		WindowRect.right = (long)width;		// Set Right Value To Requested Width
		WindowRect.top = (long)0;				// Set Top Value To 0
		WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

		fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

		hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
		wc.lpfnWndProc = (WNDPROC)WndProcS;					// WndProc Handles Messages
		wc.cbClsExtra = 0;									// No Extra Window Data
		wc.cbWndExtra = 0;									// No Extra Window Data
		wc.hInstance = hInstance;							// Set The Instance
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
		wc.hbrBackground = NULL;									// No Background Required For GL
		wc.lpszMenuName = NULL;									// We Don't Want A Menu
		wc.lpszClassName = L"OpenGL";								// Set The Class Name

		if (!RegisterClass(&wc))									// Attempt To Register The Window Class
		{
			MessageBox(NULL, L"Failed To Register The Window Class.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;											// Return FALSE
		}

		if (fullscreen)												// Attempt Fullscreen Mode?
		{
			DEVMODE dmScreenSettings;								// Device Mode
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
			dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
			dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
			dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
				if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", L"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
				{
					fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
				}
				else
				{
					// Pop Up A Message Box Letting User Know The Program Is Closing.
					MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
					return FALSE;									// Return FALSE
				}
			}
		}

		if (fullscreen)												// Are We Still In Fullscreen Mode?
		{
			dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
			dwStyle = WS_POPUP;										// Windows Style
			ShowCursor(FALSE);										// Hide Mouse Pointer
		}
		else
		{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
			dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
		}

		AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

		// Create The Window
		if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
			L"OpenGL",							// Class Name
			L"title not work",								// Window Title
			dwStyle |							// Defined Window Style
			WS_CLIPSIBLINGS |					// Required Window Style
			WS_CLIPCHILDREN,					// Required Window Style
			0, 0,								// Window Position
			WindowRect.right - WindowRect.left,	// Calculate Window Width
			WindowRect.bottom - WindowRect.top,	// Calculate Window Height
			NULL,								// No Parent Window
			NULL,								// No Menu
			hInstance,							// Instance
			this)))							
		{
			KillGLWindow();								// Reset The Display
			MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		SetWindowLong(hWnd, GWL_USERDATA, (long int)this);

		static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
			1,											// Version Number
			PFD_DRAW_TO_WINDOW |						// Format Must Support Window
			PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,							// Must Support Double Buffering
			PFD_TYPE_RGBA,								// Request An RGBA Format
			bits,										// Select Our Color Depth
			0, 0, 0, 0, 0, 0,							// Color Bits Ignored
			0,											// No Alpha Buffer
			0,											// Shift Bit Ignored
			0,											// No Accumulation Buffer
			0, 0, 0, 0,									// Accumulation Bits Ignored
			16,											// 16Bit Z-Buffer (Depth Buffer)  
			0,											// No Stencil Buffer
			0,											// No Auxiliary Buffer
			PFD_MAIN_PLANE,								// Main Drawing Layer
			0,											// Reserved
			0, 0, 0										// Layer Masks Ignored
		};

		if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
		{
			KillGLWindow();								// Reset The Display
			MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
		{
			KillGLWindow();								// Reset The Display
			MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
		{
			KillGLWindow();								// Reset The Display
			MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
		{
			KillGLWindow();								// Reset The Display
			MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
		{
			KillGLWindow();								// Reset The Display
			MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		ShowWindow(hWnd, SW_SHOW);						// Show The Window
		SetForegroundWindow(hWnd);						// Slightly Higher Priority
		SetFocus(hWnd);									// Sets Keyboard Focus To The Window
		ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

		if (!InitGL())									// Initialize Our Newly Created GL Window
		{
			KillGLWindow();								// Reset The Display
			MessageBox(NULL, L"Initialization Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;								// Return FALSE
		}

		return TRUE;									// Success
	}




public:
	OPENGL_WINDOW()
	{
		enabled = 0;
	}
	~OPENGL_WINDOW()
	{
		disable();
	}

	void draw()
	{
		DrawGLScene();
		SwapBuffers(hDC);
	}
	void upd()
	{
		mouse.mdol = 0;
		mouse.mdor = 0;
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	bool enable()
	{
		if (enabled)
			return 0;

		enabled = 1;

		hDC = NULL;
		hRC = NULL;
		hWnd = NULL;

		active = TRUE;

		fullscreen = false;
		CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen);
		razokx = 640; razoky = 480;

		//fullscreen = true;
		//CreateGLWindow("NeHe's OpenGL Framework", GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 16, fullscreen);


		return 1;
	}
	bool is_enabled()
	{
		return enabled;
	}
	bool disable()
	{
		if (!enabled)
			return 0;
		enabled = 0;
		KillGLWindow();
		return 1;
	}
	int get_wx()
	{
		return razokx;
	}
	int get_wy()
	{
		return razoky;
	}
	float get_angle()
	{
		return 60;
	}
	const bool* get_keys()
	{
		return keys;
	}
	W_MOUSE get_mouse()
	{
		return mouse;
	}

};

struct COLOR
{
	float r, g, b, a;
};


void put_icon()
{
	glDisable(GL_DEPTH_TEST);
	static float angle = 0;


	angle += 1;

	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	glColor3f((rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0);
	glBegin(GL_POLYGON);
	glVertex3f(0,1, 0);
	glVertex3f(-1,-1, 0);
	glVertex3f(1,-1, 0);
	glEnd();

	glColor3f((rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0);
	for (int i = -90; i < 90; i += 10)
	{
		glBegin(GL_POLYGON);
		glVertex3f(i / 180.0, cos(i/180.0*3.1415926)/4, 0);
		glVertex3f(i / 180.0, -cos(i / 180.0 * 3.1415926) / 4, 0);
		glVertex3f((i + 10) / 180.0, -cos((i + 10) / 180.0 * 3.1415926) / 4, 0);
		glVertex3f((i + 10) / 180.0, cos((i + 10) / 180.0 * 3.1415926) / 4, 0);
		glEnd();
	}

	glColor3f((rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0);
	for (int i = 0; i < 360; i += 10)
	{
		glBegin(GL_POLYGON);
		glVertex3f(sin(i / 180.0*3.1415926) / 4, cos(i / 180.0*3.1415926) / 4, 0);
		glVertex3f(sin((i + 10) / 180.0*3.1415926) / 4, cos((i + 10) / 180.0 * 3.1415926) / 4, 0);
		glVertex3f(0,0, 0);
		glEnd();
	}

	glPopMatrix();
}

class vec5f
{
public:
	float x, y, z, tx, ty;
	vec5f()
	{
		x = 0; y = 0; z = 0; tx = 0; ty = 0;
	}
	vec5f(float _x, float _y, float _z, float _tx=0, float _ty=0)
	{
		x = _x; y = _y; z = _z; tx = _tx; ty = _ty;
	}
};

class GUI_BUTTON
{
private:
public:
	vector <vec5f> p;
	GLuint tex_id;
	string text;
	GUI_BUTTON(const vector <vec5f> &_p, GLuint _tex_id,const string &_text)
	{
		text = _text;
		tex_id = _tex_id;
		p = _p;
	}
	void put()
	{
		glColor4f(1, 1, 1, 1);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
		for (int i = 0; i < p.size(); i++)
		{
			glTexCoord2f(p[i].tx, p[i].ty);
			glVertex3f(p[i].x, p[i].y, p[i].z);
		}
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glColor4f(0, 0, 0, 1);
		glPushMatrix();
		glTranslatef(p[0].x, p[0].y, 0);
		glScalef((p[2].y - p[0].y), -(p[2].y - p[0].y), 0);
		glPrint(text.data());
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
};

class GUI
{
private:
public:
	vector <GUI_BUTTON> b;
	void put()
	{
		for (int i = 0; i < b.size(); i++)
			b[i].put();
	}

};

void process_graph(GRAPH g,TREE_STORE &res,mutex &m)
{
	m.lock();
	//cout << "proc begin" << endl;
	res = g.get_cycles_el();
	//cout << "proc end" << endl;
	m.unlock();
}

int main()
{
	OPENGL_WINDOW w;
	GUI gui[5];
	int menu = 0;


	vector<vec5f> points;
	points.resize(4);
	

	points[0] = vec5f(10, 10, 0);
	points[2] = vec5f(410, 60, 0);
	points[1].x = points[2].x; points[1].y = points[0].y; points[1].z = points[2].z;
	points[3].x = points[0].x; points[3].y = points[2].y; points[3].z = points[0].z;
	gui[0].b.push_back(GUI_BUTTON(points, 0, "Run test"));

	points[0] = vec5f(10, 70, 0);
	points[2] = vec5f(410, 120, 0);
	points[1].x = points[2].x; points[1].y = points[0].y; points[1].z = points[2].z;
	points[3].x = points[0].x; points[3].y = points[2].y; points[3].z = points[0].z;
	gui[0].b.push_back(GUI_BUTTON(points, 0, "About"));

	points[0] = vec5f(10, 130, 0);
	points[2] = vec5f(410, 180, 0);
	points[1].x = points[2].x; points[1].y = points[0].y; points[1].z = points[2].z;
	points[3].x = points[0].x; points[3].y = points[2].y; points[3].z = points[0].z;
	gui[0].b.push_back(GUI_BUTTON(points, 0, "Crash"));



	points[0] = vec5f(10, 10, 0);
	points[2] = vec5f(410, 60, 0);
	points[1].x = points[2].x; points[1].y = points[0].y; points[1].z = points[2].z;
	points[3].x = points[0].x; points[3].y = points[2].y; points[3].z = points[0].z;
	gui[1].b.push_back(GUI_BUTTON(points, 0, "Gen new"));

	points[0] = vec5f(10, 70, 0);
	points[2] = vec5f(410, 120, 0);
	points[1].x = points[2].x; points[1].y = points[0].y; points[1].z = points[2].z;
	points[3].x = points[0].x; points[3].y = points[2].y; points[3].z = points[0].z;
	gui[1].b.push_back(GUI_BUTTON(points, 0, "Back"));



	points[0] = vec5f(10, 10, 0);
	points[2] = vec5f(410, 60, 0);
	points[1].x = points[2].x; points[1].y = points[0].y; points[1].z = points[2].z;
	points[3].x = points[0].x; points[3].y = points[2].y; points[3].z = points[0].z;
	gui[2].b.push_back(GUI_BUTTON(points, 0, "Back"));


	mutex m;

	w.enable();
	glPrint.init();

	thread th;
	TREE_STORE res(20);

	while (1)
	{

		if (!w.is_enabled())
			return -1;
		w.upd();


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glLoadIdentity();									
		glClearColor(0,0,0, 0.5f);


		glPushMatrix();
		//glTranslatef(-1, 0, -1);
		float mult = cos(w.get_angle() / 180 * 3.1415926) / sin(w.get_angle() / 180 * 3.1415926);
		glTranslatef(-1*(float)w.get_wx() / (float)w.get_wy()*mult, mult, -1);
		glScalef(2 / (float)w.get_wy()*mult, -2 / (float)w.get_wy()*cos(w.get_angle() / 180 * 3.1415926) / sin(w.get_angle() / 180 * 3.1415926), 1);
		gui[menu].put();
		glPopMatrix();

		auto mouse = w.get_mouse();

		int butt = -1;

		for (int i = 0; i < gui[menu].b.size(); i++)
			if (gui[menu].b[i].p[0].x < mouse.x)
				if (gui[menu].b[i].p[0].y<mouse.y)
					if (gui[menu].b[i].p[2].x>mouse.x)
						if (gui[menu].b[i].p[2].y > mouse.y)
							butt = i;

		if (butt != -1 && mouse.mdol == 1)
		{
			switch (menu)
			{
			case 0:
				switch (butt)
				{
				case 0:
					menu = 1;
					break;
				case 1:
					menu = 2;
					break;
				case 2:
					int i43e = *((char*)0x00);
					break;
				}
				break;
			case 1:
				switch (butt)
				{
				case 0:
					break;
				case 1:
					menu = 0;
					break;
				}
				break;
			case 2:
				switch (butt)
				{
				case 0:
					menu = 0;
					break;
				}
				break;
			}
		}

		if (menu == 1)
		{

		}


		glPushMatrix();
		glTranslatef(0,0,-4);
		//put_icon();

		glEnable(GL_TEXTURE_2D);

		glColor4f(0.5, 0.5, 0.5, 1);
		//glRasterPos2f(-0.45, 0.35);

		/*
		glDisable(GL_TEXTURE_2D);
		glColor4f(1, 1, 1, 1);
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
		glTexCoord2f(0, 1); glVertex3f(0, 1, 0);
		glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
		glTexCoord2f(1, 0); glVertex3f(1, 0, 0);
		glEnd();
		*/
		glPopMatrix();




		w.draw();
		//int rr = rand() % 1000;
		//cout << rr << endl;
		//srand(rr);
		GRAPH a(20);
		a.put();
		process_graph(a, ref(res), ref(m));


		auto iter = res.begin();
		while (iter != res.end())
		{
			auto ray = *iter;

			for (int i = 0; i < ray.size(); i++)
			{
				cout << ray[i] << " ";
			}
			cout << endl;
			iter.get_next();
		}

		/** /

		if (!th.joinable())
		{
			th = thread(process_graph, a, ref(res), ref(m));
		}
		else
		{
			if (m.try_lock())
			{

				a.put();

				while (!res.empty())
				{
					auto &arr = res.front();

					for (int i = 0; i < arr.size(); i++)
						cout << arr[i];
					cout << endl;
					res.pop();
				}

				th.detach();
				th = thread(process_graph, a, ref(res), ref(m));
				m.unlock();
			}
		}
		/**/
		/*
		auto res=a.get_cycles_el();

		while (!res.empty())
		{
			auto &arr = res.front();
			
			for (int i = 0; i < arr.size();i++)
				cout << arr[i];
			cout << endl;
			res.pop();
		}
		a.put();
		*/

		//Sleep(1000);
	}
}

