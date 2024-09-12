//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h> 
//	include the Direct3D 9 library
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#pragma comment (lib , "d3dx9.lib")
#include <iostream>
#include <fstream>
#include <string>
#include "FrameTimer.h"
#include "AudioManager.h"
using namespace std;
//--------------------------------------------------------------------

//	Window handle
HWND g_hWnd = NULL;
//	Window's structure
WNDCLASS wndClass;
MSG msg;
int windowHeight = 512;
int windowWidth = 1024;
int grassSquare = 32;

LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
BYTE  diKeys[256];


//	Define how the screen presents.
D3DPRESENT_PARAMETERS d3dPP;


LPDIRECT3DTEXTURE9 standGrassTexture = NULL;
LPDIRECT3DTEXTURE9 groundGrassTexture = NULL;

//pointer Texture
LPDIRECT3DTEXTURE9 backgroundTexture = NULL;
int bgWidth = windowWidth;
int bgHeight = windowHeight;

D3DXVECTOR3 gravityAcc = D3DXVECTOR3(0.0f, 2.0f, 0.0f);

LPDIRECT3DTEXTURE9 player1Texture = NULL;
int player1textureheight = 256;
int player1texturewidth = 128;
int player1row = 4;
int player1col = 4;
int player1MaxFrame = 4;

D3DXVECTOR3 player1Speed = D3DXVECTOR3(10.0f, 0, 0);
D3DXVECTOR3 player1Velocity = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3 jumpForce = D3DXVECTOR3(0, -25.0f, 0);
int player1CurrentFrame = 1;
RECT player1Rect;
int player1SpriteHeight = player1textureheight / player1row;
int player1SpriteWidth = player1texturewidth / player1col;
enum player1Direction { MOVEDOWN, MOVELEFT, MOVERIGHT, MOVEUP };
int player1CurrentDirection = MOVEDOWN;
D3DXVECTOR3 player1Position(0, 0, 0);
D3DXVECTOR3 test(200, 20, 0);
int player1FrameCounter = 0;

D3DXVECTOR3 grassPosition(0, 0, 0);

//Sprite Interface / Sprite Brush
LPD3DXSPRITE spriteBrush = NULL;

int oldYPosition = 0;
int newYPosition = 0;
int oldXPosition = 0;
int newXPosition = 0;
bool isPlayerGrounded = false;
bool isPlayerJumped = false;
bool isPlayerAtGlass = false;
bool isPlayerMoving = false;

AudioManager* theAudioManager = new AudioManager();

void createWindow();
bool windowIsRunning();
void cleanupWindow();
void sprite();
bool playerIsGround();
int playerWhichSide();
bool playerIsJumping();
int playerWhichArea();
void levelArrange();
bool playerIsFalling();
bool playerAtGrass();
void gravityCheck();
bool playerIsMoving();


FrameTimer* gameTimer = new FrameTimer();

//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		/*case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;

			case VK_UP:
				nbFrameCounter++;
				break;

			case VK_DOWN:
				nbFrameCounter--;
				break;
			}*/

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//--------------------------------------------------------------------

//	use int main if you want to have a console to print out message
//int main()

void createWindow() {
	//	Practical 1 //------------------------------------------------------------------------------------------------------------------------------
	/*
	Step 1
	Define and Register a Window.
	*/

	//	Set all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "apek legend", WS_OVERLAPPEDWINDOW, 0, 100, windowWidth, windowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);

	gameTimer->Init(40); // fps setting 

	//	Some interesting function to try out.
	//	ShowCursor(false);

	ZeroMemory(&msg, sizeof(msg));

	theAudioManager->InitializeAudio();
	theAudioManager->LoadSounds();
	theAudioManager->PlayBgm();
	theAudioManager->PlayMusic();
}

bool windowIsRunning() {

	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/
	//while (msg.message != WM_QUIT)
	//{

		/*
			The if- version process one message per one iteration loop
			The while- version will clear the message queue before dealing with your own code.

			Another function is GetMessage.
			This function is not suitable for game, because it will block your program until it recieves a message.
			your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
			Suitable for event based program, such as bussiness app.
		*/
		//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT)
			return false;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}

	/*
		Write your code here...
	*///}

	return true;
}

void cleanupWindow() {
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}
void createDevice() {

}
void cleanDevice() {

}

void render() {

}
void sprite()
{

}
void Update(int frame) {
	for (int i = 0; i < frame; i++) {
		gravityCheck();
		if (player1Position.y >= windowHeight - player1SpriteHeight) {
			isPlayerGrounded = true;
		}

		//if (playerIsGround()) {
		//	if (diKeys[DIK_SPACE] & 0x80) {
		//		player1CurrentDirection = MOVEUP;
		//		//player1Position.y = newYPosition;
		//		//isPlayerJumped = true;
		//		player1Velocity.y = 0;
		//		player1Velocity += jumpForce;
		//		isPlayerAtGlass = false;
		//		isPlayerGrounded = false; // Set to false when jumping

		//		switch (playerWhichArea()) {
		//		case 1:theAudioManager->Play1Jump(); break;
		//		case 2:theAudioManager->Play2Jump(); break;
		//		case 3:theAudioManager->Play3Jump(); break;
		//		case 4:theAudioManager->Play4Jump(); break;
		//		}
		//	}
		//}
		//else {
		//	if (player1Position.y >= windowHeight - player1SpriteHeight) {
		//		player1Position.y = newYPosition;
		//		isPlayerGrounded = true;
		//		player1Velocity.y = 0; // Set grounded state
		//		switch (playerWhichArea()) {
		//		case 1:theAudioManager->Play1Footstep(); break;
		//		case 2:theAudioManager->Play2Footstep(); break;
		//		case 3:theAudioManager->Play3Footstep(); break;
		//		case 4:theAudioManager->Play4Footstep(); break;
		//		}
		//	}
		//	else {
		//		isPlayerGrounded = false; // Player is in the air
		//	}
		//}

		if (playerWhichSide() != 1) {
			player1Speed.x *= -1;
		}

		if (playerWhichSide() != 1 && !playerIsJumping()) {
			if (playerWhichSide() == 2) {
				player1Position.x = windowWidth - player1SpriteWidth;
			}
			else if (playerWhichSide() == 0) {
				player1Position.x = 0;
			}
		}

		if (player1Speed.x < 0 && playerIsGround()) {
			player1Speed.x *= -1;
		}

		//nbFrameCounter++; 
		/*if (diKeys[DIK_UP] & 0x80)
		{
			player1CurrentDirection = MOVEUP;
			player1CurrentFrame++;
			player1Position.y -= player1Speed;
		}
		if (diKeys[DIK_DOWN] & 0x80)
		{
			player1CurrentDirection = MOVEDOWN;
			player1CurrentFrame++;
			player1Position.y += player1Speed;
		}*/
		if (diKeys[DIK_RIGHT] & 0x80)
		{
			player1CurrentDirection = MOVERIGHT;
			player1CurrentFrame++;
			player1Position += player1Speed;
			isPlayerMoving = true;
		}
		else if (diKeys[DIK_LEFT] & 0x80)
		{
			player1CurrentDirection = MOVELEFT;
			player1CurrentFrame++;
			player1Position -= player1Speed;
			isPlayerMoving = true;
		}
		else {
			isPlayerMoving = false;
		}

	}
	if (diKeys[DIK_ESCAPE] & 0x80)
	{
		std::cout << "Escape" << std::endl;
		PostQuitMessage(0);
	}

}

bool playerIsGround() {
	return isPlayerGrounded;
}

int playerWhichSide() {
	if (player1Position.x < 0) { return 0; }
	else if (player1Position.x > (windowWidth - player1SpriteWidth)) { return 2; }
	else { return 1; }
}

bool playerIsJumping() {
	return isPlayerJumped;
}

bool playerIsFalling() {
	return (!isPlayerGrounded) && ((oldYPosition - newYPosition) < 0);
}

int playerWhichArea() {
	if (player1Position.x < (windowWidth / 4)) { return 1; }
	else if (player1Position.x >= (windowWidth / 4) && player1Position.x < (windowWidth / 2)) { return 2; }
	else if (player1Position.x >= (windowWidth / 2) && player1Position.x < (windowWidth * 3 / 4)) { return 3; }
	else { return 4; }
}

bool playerAtGrass() {
	return isPlayerAtGlass;
}

bool playerIsMoving() {
	return isPlayerMoving;
}

void cleanSprite()
{

}
void GetInput() {
	dInputKeyboardDevice->Acquire();
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
}

void levelArrange() {
	int unitWidth = 0;
	int unitHeight = 0;

	ifstream levelFile("level/1.txt");

	char ch;

	while (levelFile.get(ch)) {
		if (ch == '0' || ch == '2') {
			grassPosition.x = unitWidth * grassSquare;
			grassPosition.y = unitHeight * grassSquare;
			RECT grassRect;
			grassRect.left = 0;
			grassRect.top = 0;
			grassRect.right = grassSquare;
			grassRect.bottom = grassSquare;

			// Draw the grass
			if (ch == '0') {
				spriteBrush->Draw(standGrassTexture, &grassRect, NULL, &grassPosition, D3DCOLOR_XRGB(255, 255, 255));
			}
			else if (ch == '2') {
				spriteBrush->Draw(groundGrassTexture, &grassRect, NULL, &grassPosition, D3DCOLOR_XRGB(255, 255, 255));
			}

			// Collision detection
			if (playerIsFalling()||playerIsMoving()) {
				if (((player1Position.y + player1SpriteHeight) >= grassPosition.y) &&
					((player1Position.y + player1SpriteHeight) <= (grassPosition.y + grassSquare)) &&
					((player1Position.x + player1SpriteWidth) > grassPosition.x) &&
					(player1Position.x < (grassPosition.x + grassSquare))) {

					// Player is on the grass
					isPlayerGrounded = true;
					isPlayerAtGlass = true;// Adjust player position

				}
				if (playerAtGrass()) {
					if (((player1Position.y + player1SpriteHeight) < grassPosition.y) ||
						((player1Position.y + player1SpriteHeight) > (grassPosition.y + grassSquare)) ||
						((player1Position.x + player1SpriteWidth) < grassPosition.x) ||
						(player1Position.x > (grassPosition.x + grassSquare))) {
						isPlayerGrounded = false;
						isPlayerAtGlass = false;

					}
					//else {
					//	isPlayerGrounded = true;
					//	isPlayerAtGlass = true;
					//}
					//else {
					//	if (playerAtGrass()) {
					//		isPlayerGrounded = false;
					//		isPlayerAtGlass = false;// Adjust player position
					//	} // Player is not on the grass
				}

			}
			/*if (playerAtGrass()) {
				if (((player1Position.y + player1SpriteHeight) < grassPosition.y) ||
					((player1Position.y + player1SpriteHeight) > (grassPosition.y + grassSquare)) ||
					((player1Position.x + player1SpriteWidth) < grassPosition.x) ||
					(player1Position.x > (grassPosition.x + grassSquare))) {
					isPlayerGrounded = false;
					isPlayerAtGlass = false;
				}
				else {
					isPlayerGrounded = true;
					isPlayerAtGlass = true;
				}
			}*/
		}
		else if (ch == '\n') {
			unitWidth = -1;
			unitHeight++;
		}
		unitWidth++;
	}

	levelFile.close();
}

void gravityCheck() {
	if (playerIsGround()) {
		player1Velocity.y = 0;
		player1Position.y = newYPosition;
		isPlayerGrounded = true; // Set grounded state
		isPlayerJumped = false;
		if (diKeys[DIK_SPACE] & 0x80) {
			player1CurrentDirection = MOVEUP;
			//player1Position.y = newYPosition;
			//isPlayerJumped = true;
			player1Velocity.y = 0;
			player1Velocity += jumpForce;
			player1Position += player1Velocity;

			isPlayerAtGlass = false;
			isPlayerGrounded = false; // Set to false when jumping

			switch (playerWhichArea()) {
			case 1:theAudioManager->Play1Jump(); break;
			case 2:theAudioManager->Play2Jump(); break;
			case 3:theAudioManager->Play3Jump(); break;
			case 4:theAudioManager->Play4Jump(); break;
			}
		}
	}
	else {
		oldYPosition = player1Position.y;

		player1Velocity += gravityAcc;
		player1Position += player1Velocity;

		newYPosition = player1Position.y;
	}
}
//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	createWindow();
	IDirect3DDevice9* d3dDevice;
	//	Define Direct3D 9.
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&d3dPP, sizeof(d3dPP));
	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = windowWidth;
	d3dPP.BackBufferHeight = windowHeight;
	d3dPP.hDeviceWindow = g_hWnd;


	//	Create a Direct3D 9 device.
	HRESULT hrbg = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hrbg))
		return 0;
	//	Create sprite. Study the documentation. 
	HRESULT hr = D3DXCreateSprite(d3dDevice, &spriteBrush); // pass in your graphic card
	//	Create texture. Study the documentation.
	//Reading the file from HDD and storing it in the GPU(DEVICE)
	hr = D3DXCreateTextureFromFile(d3dDevice, "image/background.png", &backgroundTexture);

	if (FAILED(hr))
	{
		// Handle error
		return 0;
	}

	hr = D3DXCreateTextureFromFile(d3dDevice, "image/standgrass.png", &standGrassTexture);

	if (FAILED(hr))
	{
		// Handle error
		return 0;
	}

	hr = D3DXCreateTextureFromFile(d3dDevice, "image/groundgrass.png", &groundGrassTexture);

	/*hr = D3DXCreateTextureFromFileEx(d3dDevice, "image/background.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &backgroundTexture);*/

	if (FAILED(hr))
	{
		// Handle error
		return 0;
	}

	hr = D3DXCreateTextureFromFileEx(d3dDevice, "image/militia.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &player1Texture);

	if (FAILED(hr))
	{
		// Handle error
		return 0;
	}

	/*HRESULT HelloWorld = D3DXCreateSprite(d3dDevice, &spriteBrush);
	LPD3DXFONT font = NULL;

	HelloWorld = hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	HRESULT hline = D3DXCreateSprite(d3dDevice, &spriteBrush);
	LPD3DXLINE line = NULL;
	hline = D3DXCreateLine(d3dDevice, &line);*/

	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//check if succeed or fail


	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	while (windowIsRunning())
	{
		cout << playerIsGround() << endl;
		//cout << gameTimer->FramesToUpdate() << endl;
		GetInput();
		//Physics
		//Logic
		//Render
		render();
		d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		//	Begin the scene
		d3dDevice->BeginScene();

		//	To Do:
		//	Drawing.

			//	Specify alpha blend will ensure that the sprite will render the background with alpha.
			//sprite brush, begin drawing
		spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

		//	Specify the "	" rectangle.
		/*RECT spriteRect;
		spriteRect.left = nbFrameCounter % nbRow * nbSpriteWidth;
		spriteRect.top = nbFrameCounter / nbCol * nbSpriteWidth;
		spriteRect.right = spriteRect.left + nbSpriteWidth;
		spriteRect.bottom = spriteRect.top + nbSpriteHeight;*/

		//	Sprite rendering. Study the documentation.
	/*	spriteBrush->Draw(texture, &spriteRect, NULL, &numberPosition, D3DCOLOR_XRGB(255, 255, 255));*/

		//spriteBrush->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		//spriteBrush->Draw(texture, &spriteRect, NULL, &D3DXVECTOR3(32, 32, 0), D3DCOLOR_XRGB(255, 255, 255));

		//	End sprite drawing
		//sprite brush stop drawing

		RECT bgRect;
		bgRect.left = 0;
		bgRect.top = 0;
		bgRect.right = bgWidth;
		bgRect.bottom = bgHeight;

		spriteBrush->Draw(backgroundTexture, &bgRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

		//RECT grassRect;
		//grassRect.left = 0;
		//grassRect.top = 0;
		//grassRect.right = grassSquare;
		//grassRect.bottom = grassSquare;

		//spriteBrush->Draw(standGrassTexture, &grassRect, NULL, &test, D3DCOLOR_XRGB(255, 255, 255));

		//D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(200, 200), D3DXVECTOR2(200, 400) };
		//	Begin to draw the lines.
		/*line->Begin();
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->End();*/

		RECT player1Rect;
		player1Rect.top = player1CurrentDirection * player1SpriteHeight;
		player1Rect.bottom = player1Rect.top + player1SpriteHeight;
		player1Rect.left = player1CurrentFrame % player1MaxFrame * player1SpriteWidth;
		player1Rect.right = player1Rect.left + player1SpriteWidth;

		spriteBrush->Draw(player1Texture, &player1Rect, NULL, &player1Position, D3DCOLOR_XRGB(255, 255, 255));

		//gravityCheck();
		Update(gameTimer->FramesToUpdate());
		levelArrange();



		spriteBrush->End();
		//	End the scene  
		d3dDevice->EndScene();

		//	Present the back buffer to screen
		d3dDevice->Present(NULL, NULL, NULL, NULL);
		//Sound
		//	To Do:

	}


	player1Texture->Release();
	player1Texture = NULL;

	spriteBrush->Release();
	spriteBrush = NULL;

	dInput->Release();
	dInput = NULL;
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	//	Release DirectInput.

	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
	cleanupWindow();

	return 0;

}
//--------------------------------------------------------------------