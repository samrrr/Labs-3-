#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>

#include <conio.h>
#include <time.h>
#include <iostream>
#include <queue>
#include <deque>
#include <list>


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")

const int SIZE_X_DECREATE = 10;
const int SIZE_Y_DECREATE = 80;
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
	int getN(){ return n; }
	bool isOr(){ return or; }
	char* operator[](const int _i);
	string get_cycles_el();
};

char* GRAPH::operator[](const int _i)
{
	if (_i < 0 || _i >= n)
		return NULL;
	return a[_i];
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
			a[i][r] = rand() % 6 <1;
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

	for (int i = 0; i < n; i++)
	{
		printf("%3i| ", i);
		for (int r = 0; r < n; r++)
			printf("%i  ", (int)a[i][r]);
		cout << endl;
	}
}

string GRAPH::get_cycles_el()
{
	string res = "";

	vector<int> used;
	vector <int> cyc_ray;

	used.resize(n + 3);
	cyc_ray.resize(n + 3);

	bool b = 1;

	cyc_ray[0] = -1;

	if (cyc_ray[0] == -1)
	{
		cyc_ray[0] = 0;

		bool b1 = 1;
		int k = 0;
		while (b1)
		{
			int d = -1;
			for (int i = 0; i<n; i++)
				if (a[cyc_ray[k]][i] && used[i] == 0)
				{
					d = i;
					i = n;
				}


			k++;
			cyc_ray[k] = d;
			if (d != -1)
			{
				used[d] = 1;
			}
			else
			{
				b1 = 0;
			}
			if (k>0 && cyc_ray[k] == cyc_ray[0])
			{
				b1 = 0;
				cyc_ray[k + 1] = -1;
			}
		}

		if (cyc_ray[k] == cyc_ray[0] && k > 0)
		{
			for (int gr = 0; cyc_ray[gr] != -1; gr++)
				res = res + (char)(cyc_ray[gr] + '0');
			res = res + '\n';
		}
		//for (int gr = 0; cyc_ray[gr] != -1; gr++)
		//	cout << cyc_ray[gr];
		//cout << endl;

	}


	while (b)
	{
		int k;

		k = 0;
		while (cyc_ray[k] != -1)
			k++;

		do
		{
			k--;
			used[cyc_ray[k]] = 0;
			do
			{
				cyc_ray[k]++;
			} while (cyc_ray[k] < n && k>0 && (a[cyc_ray[k - 1]][cyc_ray[k]] == 0 || used[cyc_ray[k]] == 1));

		} while (k > 0 && cyc_ray[k] == n);

		if (k > 0)
			used[cyc_ray[k]] = 1;

		cyc_ray[k + 1] = -1;


		if (cyc_ray[0] != n)
		{
			if (cyc_ray[0] != cyc_ray[k] || k == 0)
			{
				bool b1 = 1;
				while (b1)
				{
					int d = -1;
					for (int i = 0; i < n; i++)
						if (a[cyc_ray[k]][i] && used[i] == 0)
						{
							d = i;
							i = n;
						}


					k++;
					cyc_ray[k] = d;
					if (d != -1)
					{
						used[d] = 1;
					}
					else
					{
						b1 = 0;
					}

					if (k>0 && cyc_ray[k] == cyc_ray[0])
					{
						b1 = 0;
						cyc_ray[k + 1] = -1;
					}

				}
			}

			if (cyc_ray[k] == cyc_ray[0] && k > 0)
			{
				for (int gr = 0; cyc_ray[gr] != -1; gr++)
					res = res + (char)(cyc_ray[gr] + '0');
				res = res + '\n';
			}

			//for (int gr = 0; cyc_ray[gr] != -1; gr++)
			//	cout << cyc_ray[gr];
			//cout << endl;

		}
		else
		{
			b = 0;
		}

	}

	return res;
}



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
		cout << uMsg << endl;
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
			cout << wParam<<endl;
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
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
			break;
		}

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
		gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

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

		//fullscreen = false;
		//CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen);

		fullscreen = true;
		CreateGLWindow("NeHe's OpenGL Framework", GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 16, fullscreen);


		return 1;
	}
	bool disable()
	{
		if (!enabled)
			return 0;
		enabled = 0;
		KillGLWindow();
		return 1;
	}
	
};

struct COLOR
{
	float r, g, b, a;
};


void put_icon()
{
	glDisable(GL_DEPTH_TEST);
	static int angle = 0;
	static int old_clock = clock();

	static COLOR c1, c2, c3;
	static COLOR c1n, c2n, c3n;
	static COLOR c1o, c2o, c3o;
	static float c1t,c2t,c3t;


	int diff = old_clock - clock();
	old_clock = clock();

	angle = (angle + (diff) / 10) % 360;

	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	//glColor3f((rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0);
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
	glVertex3f(0,1, 0);
	glVertex3f(-1,-1, 0);
	glVertex3f(1,-1, 0);
	glEnd();

	//glColor3f((rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0);
	glColor3f(0.8, 0.5, 0.5);
	for (int i = -90; i < 90; i += 10)
	{
		glBegin(GL_POLYGON);
		glVertex3f(i / 180.0, cos(i/180.0*3.1415926)/4, 0);
		glVertex3f(i / 180.0, -cos(i / 180.0 * 3.1415926) / 4, 0);
		glVertex3f((i + 10) / 180.0, -cos((i + 10) / 180.0 * 3.1415926) / 4, 0);
		glVertex3f((i + 10) / 180.0, cos((i + 10) / 180.0 * 3.1415926) / 4, 0);
		glEnd();
	}

	//glColor3f((rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0);
	glColor3f(0.5, 0.0, 0.5);
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

int main()
{
	MSG msg;
	BOOL done = FALSE;
	OPENGL_WINDOW w;

	w.enable();

	while (1)
	{
		w.upd();


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		glLoadIdentity();									
		glClearColor(0,0,0, 0.5f);

		glPushMatrix();
		glTranslatef(0,0,-4);
		put_icon();
		glPopMatrix();


		w.draw();

		//GRAPH a(9);

		//a.put();

		//cout<<a.get_cycles_el().data();

		//Sleep(1000);
	}
}

