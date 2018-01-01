#include <Windows.h>
#include <stdio.h>
#include "winfuncs.h"
#include <gl/GL.h>
#include <xinput.h>

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define global_file static

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Debug stuff
bool wDown = false;
bool sDown = false;

// end debug stuff

int isKeyDown(char* key) 
{
  printf("asked for key: %s\n", key);
  if (wDown == false) return 0; 
  else return 1;
}

void clearScreen()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void InitGL(HWND hWnd) 
{
  PIXELFORMATDESCRIPTOR pfd =
  {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
    PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
    32,                        //Colordepth of the framebuffer.
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0, 0, 0, 0,
    24,                        //Number of bits for the depthbuffer
    8,                        //Number of bits for the stencilbuffer
    0,                        //Number of Aux buffers in the framebuffer.
    PFD_MAIN_PLANE,
    0,
    0, 0, 0
  };

  HDC ourWindowHandleToDeviceContext = GetDC(hWnd);

  int  letWindowsChooseThisPixelFormat;
  letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd); 
  SetPixelFormat(ourWindowHandleToDeviceContext,letWindowsChooseThisPixelFormat, &pfd);

  HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
  wglMakeCurrent (ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);


  printf("OPENGL VERSION: %s\n", (char*)glGetString(GL_VERSION) );

}


int hswinmain(int width, int height) 
{
	
  printf("in hswinmain\n");
  
  HINSTANCE hinst = GetModuleHandle(NULL);
	
  WNDCLASS wcx;
  wcx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wcx.lpfnWndProc = WinProc;
  wcx.cbClsExtra = 0;
  wcx.cbWndExtra = 0;
  wcx.hInstance = hinst; 
  wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcx.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
  wcx.lpszMenuName = NULL;
  wcx.lpszClassName = "MainWClass";


  RegisterClass(&wcx);

  HWND hWnd = CreateWindow(
			   "MainWClass",
			   "BitcoinApp",
			   WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			   CW_USEDEFAULT,
			   CW_USEDEFAULT,
			   width,
			   height,
			   (HWND) NULL,
			   (HMENU) NULL,
			   hinst,
			   (LPVOID) NULL);

  if (hWnd == NULL)
  {
      printf("error creating window!\n");
      return 1;
  }
	
  InitGL(hWnd);
  glClearColor(1, 0, 0, 1);
	
  ShowWindow(hWnd, SW_SHOW);
  UpdateWindow(hWnd);
			  
  printf("starting up\n");
  
  MSG msg;
  HDC hdc = GetDC(hWnd);
  
  while(true){
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    
      if (msg.message == WM_QUIT) {
      printf("got quit message\n");
      exit(0);
    }
    
    // Poll for controller input
    XINPUT_STATE inputState;
    ZeroMemory(&inputState, sizeof(inputState));
    
    for (DWORD controllerIndex = 0; controllerIndex < XUSER_MAX_COUNT; ++controllerIndex)
    {
       if (XInputGetState(controllerIndex, &inputState) == ERROR_SUCCESS)
       {
         //printf("controller %d sent: %d\n", controllerIndex, inputState.dwPacketNumber);
         bool up = inputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
         if (up) printf("up pressed!\n");
         
       }
       else 
       {
         // TODO handle the case of non controller availibility0
         //printf("no controller here %d\n", controllerIndex);
       }
    }
    // Debug print keyboard state
    //printf("w pressed/s pressed: %d/%d\n", wDown, sDown);
    

  
    
    // call Haskell update function
    gameUpdate();
    SwapBuffers(hdc);
  }
 
  return 0;
}


LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

  switch (msg) 
  {
    case WM_KEYDOWN:
    {
      if (wParam == VK_DOWN) 
      {
          sDown = true;
          
      }
      if (wParam == VK_UP) wDown = true;
      break;
    }
    
    case WM_KEYUP:
    {
      if (wParam == VK_DOWN)
      {
        sDown = false;
        
      }
      if (wParam == VK_UP) wDown = false;
      break;
    }
    
    
    
    case WM_CLOSE: PostQuitMessage(0); break;
    default: return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  
  return 0;
	
}