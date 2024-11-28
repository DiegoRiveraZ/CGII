#pragma once

#ifndef _DXRender_
#define _DXRender_

#include "Constants.h"

#include "Camara.h"
#include "Light.h"
#include "MeshPrimitives.h"

#include "GameMath.h"

#include <colision_math.h>

#include<iostream>
#include <string>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

float x= 1;
float z =1;
float v = 1;

float xm, zm;

float xv, zv;

float camx, camz;
float antcamx, antcamz;

class DXRender
{

private:
	//Global Declarations//|
	IDXGISwapChain* SwapChain;
	
	ID3D11RenderTargetView* renderTargetView;
	ID3D11DepthStencilView* depthStencilView;

	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;
	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;

	D3DXMATRIX View;
	D3DXMATRIX Projection;


	MPrimitives *cubo;
	MPrimitives *esfera;
	MPrimitives *toroide;
	MPrimitives *cono;
	MPrimitives *cilindro;
	MPrimitives* edificio;
	MPrimitives* barrier;
	MPrimitives* Bike;
	MPrimitives* Edificio1;
	MPrimitives* leaves;
	MPrimitives* trunk;
	MPrimitives* racefence;
	MPrimitives* rubble;
	MPrimitives* sandbag;
	MPrimitives* startline;
	MPrimitives *billboard;
	MPrimitives* senal;
	MPrimitives* barril;
	MPrimitives* cono1;
	MPrimitives* flags;
	MPrimitives* llantas;
	MPrimitives* tree;
	MPrimitives *skydomo;
	MPrimitives *terreno;
	MPrimitives *Bitmap;
	MPrimitives* track;
	MPrimitives *BoundingSphere1;
	MPrimitives *BoundingSphere2;

	//JUEGO MODELOS
	MPrimitives* gokart;
	MPrimitives* gokart2;

	Camara *camara;
	Camara *skyCamara;

	float rotPerFrame;
	float sphereSpeed;
	D3DXVECTOR2 BoundingSphereTranslation;
	D3DXVECTOR2 DummyBoundyEvents;
	D3DXVECTOR2 LastBoundingPosition;

	//Variables personales.
	RaceCoords racecoords;
	rectangle_colision colision1;
	rectangle_colision colision2;
	race_check_point check_points;
	race_check_point check_points2;
	
	float PC_multiply = 1.0;

	float angleb;
	float velocity = 14 * PC_multiply;
	float camYaw = 0;

	float aceleration = 0.000005f*PC_multiply;
	float deceleration = 0.00001f * PC_multiply;
	float top_speed = 0.09f * PC_multiply;
	float velocity_car = 0.0f * PC_multiply;

	float speed = 0.02f * (PC_multiply);
	float wheeling = .002f * (PC_multiply );

	int posicionX, posicionY;

	bool first_person = false;
	float distance_to_floor = 12;


public:
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;

	DXRender()
	{
		rotPerFrame = 0.0f;
	}

	bool InitDevice(HWND hwnd, int Width, int Height)
	{
		//Describe our Buffer
		DXGI_MODE_DESC bufferDesc;

		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

		bufferDesc.Width = Width;
		bufferDesc.Height = Height;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		//Describe our SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc;

		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		//Create our SwapChain
		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
			D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);

		//Create our BackBuffer
		ID3D11Texture2D* BackBuffer;
		SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

		//Create our Render Target
		d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
		BackBuffer->Release();

		//Crea la descripcion del raster, el cual determina como se dibujaran los poligonos
		D3D11_RASTERIZER_DESC rasterDesc;
		ID3D11RasterizerState* rasterState;
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_NONE;//se puede manipular para transparencias, cambiar a D3D11_CULL_NONE;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0;

		d3d11Device->CreateRasterizerState(&rasterDesc, &rasterState);
		d3d11DevCon->RSSetState(rasterState);

		
		//Describe our Depth/Stencil Buffer
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ID3D11Texture2D* depthStencilBuffer;

		depthStencilDesc.Width     = Width;
		depthStencilDesc.Height    = Height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count   = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0; 
		depthStencilDesc.MiscFlags      = 0;

		//Create the Depth/Stencil View
		d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
		d3d11Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

		//Set our Render Target
		d3d11DevCon->OMSetRenderTargets( 1, &renderTargetView, depthStencilView );



		cubo = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/cube.txt", L"Texturas/Edificio2/edificio2.jpg", L"Texturas/Edificio2/edificio2.jpg", ShaderDiffuse);
		esfera = new MPrimitives(d3d11Device, d3d11DevCon, 32, 32, 1.0f, L"Texturas/escudo.jpg", L"Texturas/escudoNormal.jpg", ShaderDiffuse);
		toroide = new MPrimitives(d3d11Device, d3d11DevCon, 32, 32, 1.0f, 0.5f, L"Texturas/escudo.jpg", L"Texturas/escudoNormal.jpg", ShaderDiffuse);
		cilindro = new MPrimitives(d3d11Device, d3d11DevCon, 16, 1.0f, 1.0f, 2.0f, L"Texturas/escudo.jpg", L"Texturas/escudoNormal.jpg", ShaderDiffuse);
		cono = new MPrimitives(d3d11Device, d3d11DevCon, 16, 0.0f, 1.0f, 2.0f, L"Texturas/escudo.jpg", L"Texturas/escudoNormal.jpg", ShaderDiffuse);
		//edificio = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/Edificio2/Edificio2.txt", L"Texturas/Edificio2/edificio2.jpg", L"Texturas/Edificio2/edificio2.jpg", ShaderDiffuse);

		edificio = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/Edificio2/Edificio2.txt", L"Texturas/Edificio2/edificio2.jpg", L"Texturas/Edificio2/edificio2.jpg", ShaderSpecular);
		barrier = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/Barrier/Barrier.txt", L"Texturas/Barrier/barrier2.png", L"Texturas/Barrier/barrier.png", ShaderDiffuse);
		Bike = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/Bike/Bike.txt", L"Texturas/Bike/Bike.bmp", L"Texturas/Bike/Bike.bmp", ShaderDiffuse);
		Edificio1 = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/Edificio1/Edificio1.txt", L"Texturas/Edificio1/edificio1.jpg", L"Texturas/Edificio1/edificio1.jpg", ShaderNormalmap);
		leaves = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/maple-tree/leaves.txt", L"Texturas/maple-tree/sugar_maple_leaf.png", L"Texturas/maple-tree/sugar_maple_leaf.png", ShaderDiffuse);

		trunk = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/maple-tree/trunk.txt", L"Texturas/Sandbag/sandbag.bmp", L"Texturas/Sandbag/sandbag.bmp", ShaderDiffuse);
		racefence = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/race-fence/race-fence.txt", L"Texturas/race-fence/Track_Fence_albedo.jpg", L"Texturas/Edificio1/edificio1.jpg", ShaderDiffuse);
		rubble = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/Rubble/Rubble.txt", L"Texturas/Rubble/rubble.bmp", L"Texturas/Rubble/rubble.bmp", ShaderDiffuse);
		sandbag = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/Sandbag/Sandbag.txt", L"Texturas/Sandbag/sandbag.bmp", L"Texturas/Sandbag/sandbag.bmp", ShaderDiffuse);
		startline = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/starting-line/startline.txt", L"Texturas/Bike/Bike.bmp", L"Texturas/Bike/Bike.bmp", ShaderDiffuse);
		
		gokart = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/AE2.txt", L"Texturas/AE86 Texture.png", L"Texturas/Edificio1/edificio1.jpg", ShaderDiffuse);
		gokart2 = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/2AE2.txt", L"Texturas/AE86 Texture.png", L"Texturas/Edificio1/edificio1.jpg", ShaderDiffuse);

		track = new MPrimitives(d3d11Device, d3d11DevCon, "Texturas/track/track.txt", L"Texturas/track/track.jpg", L"Texturas/track/track.jpg", ShaderDiffuse);

		billboard = new MPrimitives(d3d11Device, d3d11DevCon, 2.0f, 2.0f, L"Texturas/ave.png");
		senal = new MPrimitives(d3d11Device, d3d11DevCon, 5.0f, 5.0f, L"Texturas/senal5.png");
		barril = new MPrimitives(d3d11Device, d3d11DevCon, 5.0f, 5.0f, L"Texturas/barril.png");
		cono1 = new MPrimitives(d3d11Device, d3d11DevCon, 5.0f, 5.0f, L"Texturas/cono.png");
		flags = new MPrimitives(d3d11Device, d3d11DevCon, 5.0f, 5.0f, L"Texturas/flags.png");
		llantas = new MPrimitives(d3d11Device, d3d11DevCon, 5.0f, 5.0f, L"Texturas/llantas.png");
		tree = new MPrimitives(d3d11Device, d3d11DevCon, 10.0f, 10.0f, L"Texturas/tree.png");

		skydomo = new MPrimitives(d3d11Device, d3d11DevCon, 32, 32, 1000.0f, L"Texturas/sky2.jpg", L"Texturas/escudoNormal.jpg", ShaderDiffuse);
		terreno = new MPrimitives(d3d11Device, d3d11DevCon, 500.0f, L"Texturas/teterr.jpg", L"Texturas/texterr2.jpg", "Texturas/heightmap2v3.bmp", ShaderMultitextura);

		BoundingSphere1 = new MPrimitives(d3d11Device, d3d11DevCon, 32, 32, 1.0f, L"Texturas/escudo.jpg", L"Texturas/escudoNormal.jpg", ShaderDiffuse);
		BoundingSphere2 = new MPrimitives(d3d11Device, d3d11DevCon, 32, 32, 1.0f, L"Texturas/escudo.jpg", L"Texturas/escudoNormal.jpg", ShaderDiffuse);
		BoundingSphereTranslation = D3DXVECTOR2(0, 0);
		
		//Inicializar variables creadas por usuario
		InitObj_Matrix();
		
		check_points.init_race();
		check_points2.init_race();
		

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(d3d11Device, d3d11DevCon);

		return true;
	}

	bool InitDirectInput(HINSTANCE hInstance, HWND hwnd)
	{
		DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&DirectInput,
			NULL); 

		DirectInput->CreateDevice(GUID_SysKeyboard,
			&DIKeyboard,
			NULL);

		DirectInput->CreateDevice(GUID_SysMouse,
			&DIMouse,
			NULL);

		DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
		DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		DIMouse->SetDataFormat(&c_dfDIMouse);
		DIMouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

		return true;
	}

	void DetectInput(HWND hwnd )
	{
		DIMOUSESTATE mouseCurrState;

		BYTE keyboardState[256];

		DIKeyboard->Acquire();
		DIMouse->Acquire();

		DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);

		DIKeyboard->GetDeviceState(sizeof(keyboardState),(LPVOID)&keyboardState);

		

		

		float moveLeftRight = 0;
		float moveBackForward = 0;

		camYaw = 0;
		float camPitch = 0;

		bool car_mode = true;
		

		if(keyboardState[DIK_A])
		{
			if (car_mode) {
				camYaw -= wheeling;
			}
			else {
				moveLeftRight -= speed;
			}

			
			
		}
		if(keyboardState[DIK_D])
		{	
			if (car_mode) {
				camYaw += wheeling;
			}
			else {
				moveLeftRight += speed;
			}

		}
		if(keyboardState[DIK_W])

		{
			if (car_mode) {
				
				velocity_car += aceleration;
				clamp(velocity_car, 0.04, top_speed);

				moveBackForward += velocity_car;
			}
			else {

				moveBackForward += speed;
			}
		}

		else {
			if (car_mode){
				velocity_car -= deceleration;
				clamp(velocity_car, 0, top_speed);
				if (velocity_car > 0) {
					moveBackForward += velocity_car;
				}
			}
		}

		if(keyboardState[DIK_S])
		{
			if (car_mode) {

			}
			else {

				moveBackForward -= speed;
			}
		}
		if (keyboardState[DIK_LEFT])
		{
			DummyBoundyEvents.x = -.01f;
		}
		if (keyboardState[DIK_RIGHT])
		{
			DummyBoundyEvents.x = .01f;
		}
		if (keyboardState[DIK_UP])
		{
			DummyBoundyEvents.y = .01f;
		}
		if (keyboardState[DIK_DOWN])
		{
			DummyBoundyEvents.y = -.01f;
		}
		if (keyboardState[DIK_SPACE])
		{
			agregar_coordenadas(camara->Position.x - 50, camara->Position.z - 50);
		}

		if (keyboardState[DIK_C]) {

			if (first_person) {
				first_person = false;
				camara->Pitch = 1.4;
			}
			else {
				first_person = true;
			}
			

			
		}
		/*if (keyboardState[DIK_TAB]) {
			
			

			string positionXStr ="X:"+ to_string(posicionX) + " Y:"+ to_string(posicionY) ;
			LPCSTR posicionXchar = positionXStr.c_str();
			
			MessageBoxA(hwnd, posicionXchar, "COLISION 1", NULL);

			
		}*/

		if((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
		{
			float smoothness = 0.001f;
			camYaw = mouseCurrState.lX * smoothness;

			camPitch = mouseCurrState.lY * smoothness;

			if (camara->Pitch > 1.5) {
				camara->Pitch = 1.5;
			}

			if (camara->Pitch < -1.5) {
				camara->Pitch = (-1.5);
			}
			
			

			mouseLastState = mouseCurrState;
		}

		camara->UpdateCamera(moveBackForward, moveLeftRight, camYaw, camPitch); 
		skyCamara->setSkyCamara(camara);
	}

	void ReleaseObjects()
	{
		//Release the COM Objects we created
		SwapChain->Release();
		d3d11Device->Release();
		d3d11DevCon->Release();
		renderTargetView->Release();
		depthStencilView->Release();

		
	}


	//Inicializael lugar donde estaran los objetos
	//aqui le dices donde va a estar el objeto.
	void InitObj_Matrix() {

		edificio->set_obj_v(333, 1, 389);
		barrier->set_obj_v(168, 1, 132);

		Bike->set_obj_v(230, 5, 290);
		Edificio1->set_obj_v(500, 1, 305);
		leaves->set_obj_v(281, 3, 195);
		trunk->set_obj_v(281, 2, 195);
		racefence->set_obj_v(193, 1, 187);
		rubble->set_obj_v(217, -1, 137);
		sandbag->set_obj_v(269, 0, 355);
		startline->set_obj_v(236, -1, 292);
		cubo->set_obj_v(0, 0, 0);
	
		gokart->set_obj_v(0, 2, 0);
		gokart2->set_obj_v(0, 2, 0);

		track->set_obj_v(280, 1, 260);

		//senal->set_obj_v(217, 5, 137);
		/*barril->set_obj_v(0, 9, 0);
		cono1->set_obj_v(0, 9, 0);
		flags->set_obj_v(0, 9, 0);
		llantas->set_obj_v(0, 9, 0);
		tree->set_obj_v(0, 9, 0);*/

	}


	void init_colision() {

		colision1.init_rectangle(5, 5, 5);
		colision2.init_rectangle(5, 5, 5);


		colision1.set_position(Bike->get_obj_v());

		colision2.set_position(gokart->get_obj_v());
	}
	

	bool InitScene(int Width, int Height)
	{
		//Create the Viewport
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = Width;
		viewport.Height = Height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		//set light values
		light.direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		light.ambient = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
		light.diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		//Set the Viewport
		d3d11DevCon->RSSetViewports(1, &viewport);

		//Create the camera
		D3DXVECTOR3 Position = D3DXVECTOR3(50, 2.0f, 40.0f);
		D3DXVECTOR3 Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		camara = new Camara(Position,Target,Up, Width, Height);
		skyCamara = new Camara(Position,Target,Up, Width, Height);
		//esta es la gui
		Bitmap = new MPrimitives(d3d11Device, d3d11DevCon, 1, 1, L"Texturas/Health.png", camara);

		

		racecoords.rellenar();

		D3DXVECTOR2 a;
		a= racecoords.get_punto(2);
		a = a;

		init_colision();

		camara->Position.x = 289;
		camara->Position.z = 365;

		return true;
	}

	void UpdateScene(HWND hwnd)
	{
		

		posicionX = camara->Position.x;
		posicionY = camara->Position.y;

		
		LastBoundingPosition = BoundingSphereTranslation;
		BoundingSphereTranslation += DummyBoundyEvents;

	
		rotPerFrame += 0.1f;

		D3DXMATRIX rotMatY, northMat, westMat, eastMat, southMat, scale, rotMatX,MatAcomodo, scaletrack, rottrack, terrscale, ediscale1, edirot1, ediscale2;
		
		

		D3DXMATRIX Bounding1, Bounding2, BoundinMatTranslation, fencescale, rotfence, scale3;
		D3DXMATRIX edificiopos, barrierpos, bikepos, edificio1pos, leavespos, trunkpos, fencepos, rubblepos, sandbagpos, startlinepos, trackpos;
		D3DXMATRIX senalpos, barrilpos, conopos, flagspos, llantaspos, treepos;

		//Variables del juego
		D3DXVECTOR3 gokartV;
		D3DXVECTOR3 camCoord;
		D3DXVECTOR2 CarMoveVec;

		D3DXMATRIX rotMatBike;
		D3DXMATRIX gokartM;

		
		colision1.return_translated_position();

		if (colision1.check_colision(colision2)) {
			
			velocity = 0;

			velocity = velocity;
		}
		else {
			velocity = 14;
		}


		

		//las coordenadas del jugador o la camara si se van a usar
		camCoord = D3DXVECTOR3(camara->Position.x - 50,15, camara->Position.z - 50);
		
		//las coordenadas del lugar hacia donde se va a mover el carro.
		//calcula la distancia de dos puntos y genera un vector hacia ese punto.
		CarMoveVec = D3DXVECTOR2(racecoords.get_selector_punto().x - Bike->get_obj_v().x, racecoords.get_selector_punto().y - Bike->get_obj_v().z);
		CarMoveVec = nomralizeVec2(CarMoveVec);

		//Ccambia de lugar o hacia donde debe de ir en los puntos de la pista
		racecoords.get_checkpoint(D3DXVECTOR2(Bike->get_obj_v().x, Bike->get_obj_v().z));


		CarMoveVec.x = CarMoveVec.x / 1000;
		CarMoveVec.y = CarMoveVec.y / 1000;

		//calcula el angulo hacia donde se mueve el carro.
		angleb = AngleofVectorT(CarMoveVec);
		//mueve el objeto hacia cierta direccion
		Bike->sum_obj_v(CarMoveVec.x * velocity, 0, CarMoveVec.y * velocity);

		if (!first_person) {
			gokart->set_obj_v(camCoord.x, -10, camCoord.z);
			gokart2->set_obj_v(camCoord.x, 2, camCoord.z);

			colision2.set_position(gokart2->get_obj_v());

			camara->Position.y = 6.0;
		}
		else {
			gokart->set_obj_v(camCoord.x, 2, camCoord.z);
			gokart2->set_obj_v(camCoord.x, -10, camCoord.z);

			colision2.set_position(gokart->get_obj_v());

			camara->Position.y = 30;
		}


		
		
		
		//rotar objetos
		D3DXMatrixRotationY(&rotMatBike, D3DXToRadian(angleb));
		D3DXMatrixRotationY(&rotMatY, D3DXToRadian(rotPerFrame));

		D3DXMatrixRotationY(&gokartM, camara->Yaw);
		



		D3DXMatrixTranslation(&MatAcomodo, 50, 3, 50);

		D3DXMatrixTranslation(&northMat, 0, 3, 0);
		D3DXMatrixTranslation(&southMat, 0, -3, 0);
		D3DXMatrixTranslation(&eastMat, 3, 0, 0);
		D3DXMatrixTranslation(&westMat, -3, 0, 0);
		D3DXMatrixTranslation(&Bounding1, 3, 6, 0);
		D3DXMatrixTranslation(&Bounding2, -3, 6, 0);

		D3DXMatrixTranslation(&BoundinMatTranslation, BoundingSphereTranslation.x, BoundingSphereTranslation.y, 0);
		D3DXMatrixScaling(&scale, 0.03f, 0.03f, 0.03f);

		D3DXMatrixScaling(&scaletrack, 24.00f, 28.00f, 24.00f);
		D3DXMatrixRotationY(&rottrack, 90.0f);
		D3DXMatrixScaling(&ediscale1, 2.00f, 3.00f, 7.50f);
		D3DXMatrixRotationY(&edirot1, 0.36f);
		D3DXMatrixScaling(&ediscale2, 2.00f, 2.00f, 2.00f);
		D3DXMatrixScaling(&fencescale, 7.00f, 1.00f, 2.00f);
		D3DXMatrixRotationY(&rotfence, -1.21f);
		D3DXMatrixScaling(&scale3, 3.00f, 3.00f, 3.00f);

		D3DXMatrixScaling(&terrscale, 3.00f, 1.00f, 3.00f);

		D3DXMatrixTranslation(&senalpos, 267, 8, 217);
		D3DXMatrixTranslation(&barrilpos, 257, 5, 297);
		D3DXMatrixTranslation(&conopos, 267, 5, 297);
		D3DXMatrixTranslation(&flagspos, 267, 15, 197);
		D3DXMatrixTranslation(&llantaspos, 307, 5, 247);
		D3DXMatrixTranslation(&treepos, 267, 8, 267);

		

		cubo->UpdateScene(rotMatY * MatAcomodo);
		esfera->UpdateScene(rotMatY * northMat * MatAcomodo);
		toroide->UpdateScene(rotMatY * eastMat* MatAcomodo);
		cilindro->UpdateScene(rotMatY * eastMat * northMat* MatAcomodo);
		cono->UpdateScene(rotMatY * westMat* MatAcomodo);

		edificio->UpdateScene_Obj(ediscale1 * edirot1 * MatAcomodo);
		barrier->UpdateScene_Obj(ediscale2 * MatAcomodo);

		//carro
		Bike->UpdateScene_Obj(rotMatBike*MatAcomodo);

		Edificio1->UpdateScene_Obj(ediscale2 * edirot1 * MatAcomodo);
		leaves->UpdateScene_Obj(scale3 * MatAcomodo);
		trunk->UpdateScene_Obj(scale3 * MatAcomodo);
		racefence->UpdateScene_Obj(fencescale * rotfence * MatAcomodo);
		rubble->UpdateScene_Obj(scale3 * MatAcomodo);
		sandbag->UpdateScene_Obj(scale3 * MatAcomodo);
		startline->UpdateScene_Obj(ediscale2 * MatAcomodo);
		gokart->UpdateScene_Obj(gokartM * MatAcomodo);
		gokart2->UpdateScene_Obj(gokartM * MatAcomodo);

		track->UpdateScene_Obj(rottrack * scaletrack * MatAcomodo);

		

		
		billboard->UpdateScene(westMat * northMat* MatAcomodo);
		senal->UpdateScene(senalpos);
		barril->UpdateScene(barrilpos);
		cono1->UpdateScene(conopos);
		flags->UpdateScene(flagspos);
		llantas->UpdateScene(llantaspos);
		tree->UpdateScene(treepos);
		

		D3DXMATRIX skyRotMat, terrMat;
		D3DXMatrixRotationX(&skyRotMat, D3DXToRadian(-90));
		skydomo->UpdateScene(skyRotMat);


		//D3DXMatrixTranslation(&terrMat, -50, 0, -50);
		D3DXMatrixIdentity(&terrMat);
		terreno->UpdateScene(terrscale* terrMat);

		//camara->Position.y = terreno->getTerrainCollision(camara->getXZ()) +3;
		

		//colisioes
		colision1.set_position(Bike->get_obj_v());
		//colision2.set_position(gokart->get_obj_v());


		BoundingSphere1->UpdateScene(Bounding1 * MatAcomodo * BoundinMatTranslation);
		BoundingSphere2->UpdateScene(Bounding2* MatAcomodo);

		check_points.check(colision2);
		check_points2.check(colision1);

	/*	if (check_points.checkpoints[1]) {
			MessageBoxW(hwnd, L"COLISION 1", L"COLISION 1", NULL);
		}*/

		
		//if (CheckBoundingSphereCollision(BoundingSphere1->PrimitiveBoundings->Radius,
		//	BoundingSphere1->PrimitiveBoundings->PositionM, BoundingSphere1->getWorldMatrix(),
		//	BoundingSphere2->PrimitiveBoundings->Radius,
		//	BoundingSphere2->PrimitiveBoundings->PositionM, BoundingSphere2->getWorldMatrix())){

		//	BoundingSphereTranslation = LastBoundingPosition;
		//}

		if (310<camCoord.x && 330>camCoord.x) {
			if (400 < camCoord.z && 410 > camCoord.z) {

				/*camCoord.x = antcamx;
				camCoord.z = antcamz;*/

				MessageBoxW(hwnd, L"COLISION 1", L"COLISION 1", NULL);
			};
		};


		DummyBoundyEvents.x = 0;
		DummyBoundyEvents.y = 0;
		antcamx = camCoord.x;
		antcamz = camCoord.z;
	}

	void DrawScene()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(200, 300));
		
		ImGuiWindowFlags window_flags = 0;
		//window_flags |= ImGuiWindowFlags_NoBackground;
		//window_flags |= ImGuiWindowFlags_NoTitleBar;





		//if (ImGui::Begin("Test",NULL, window_flags)) {

		//	ImGui::SetWindowFontScale(2.0f);
		//	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
		//	ImGui::Text("campitch: %f", camara->Pitch);
		//	ImGui::Text("view = %f, %f", camara->Position.x, camara->Position.z);
		//	ImGui::Text("vueltas = %i",check_points.return_vueltas());
		//	ImGui::PopStyleColor();
		//	for (int i = 0; i < 10; i++) {
		//		if (check_points.checkpoints[i]) {
		//			

		//			string str ="C" +to_string(i)+".- TRUE";

		//			int n = str.length();

		//			// declaring character array (+1 for null
		//			  // character)
		//			char arr[10];

		//			// copying the contents of the string to
		//			  // char array
		//			strcpy_s(arr, str.c_str());

		//			cout << "{ ";
		//			for (int i = 0; i < n; i++)
		//				cout << arr[i] << ", ";
		//			cout << "}";

		//			ImGui::Text(arr);
		//		}

		//		else {
		//			string str = "C" + to_string(i) + ".- FALSE";

		//			int n = str.length();

		//			// declaring character array (+1 for null
		//			  // character)
		//			char arr[11];

		//			// copying the contents of the string to
		//			  // char array
		//			strcpy_s(arr, str.c_str());

		//			cout << "{ ";
		//			for (int i = 0; i < n; i++)
		//				cout << arr[i] << ", ";
		//			cout << "}";

		//			ImGui::Text(arr);
		//		}
		//	}

		//}ImGui::End(); 

		window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_NoTitleBar;

		


		bool prub = false;

		if(check_points2.ganar && !check_points.ganar){
			ImGui::SetNextWindowPos(ImVec2(600, 450));
			ImGui::SetNextWindowSize(ImVec2(400, 300));

			if (ImGui::Begin("Contador", NULL, window_flags)) {

				ImGui::SetWindowFontScale(2.0f);

				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));

				ImGui::Text("PERDISTE");
				ImGui::PopStyleColor();

				ImGui::Text("view = %f, %f", camara->Position.x, camara->Position.z);



			}ImGui::End();
		}
		else {
			


			if (check_points.ganar)
			{
				ImGui::SetNextWindowPos(ImVec2(600, 450));
				ImGui::SetNextWindowSize(ImVec2(400, 300));

				if (ImGui::Begin("Contador", NULL, window_flags)) {

					ImGui::SetWindowFontScale(2.0f);

					ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));

					ImGui::Text("GANASTE");
					ImGui::PopStyleColor();


					ImGui::Text("view = %f, %f", camara->Position.x, camara->Position.z);


				}ImGui::End();

			}
			else {





				ImGui::SetNextWindowPos(ImVec2(0, 720));
				ImGui::SetNextWindowSize(ImVec2(400, 300));

				if (ImGui::Begin("Contador", NULL, window_flags)) {

					ImGui::SetWindowFontScale(2.0f);
					ImGui::Text("vueltas %i/5", check_points.return_vueltas() + 1);
					ImGui::Text("Velocidad %.1f Km/Hr", velocity_car * 1250);

					ImGui::Text("view = %f, %f", camara->Position.x, camara->Position.z);


				}ImGui::End();
			}
		}
		ImGui::Render();



		

		//Clear our backbuffer to the updated color
		D3DXCOLOR bgColor(0.0f, 0.0f, 0.25f, 1.0f);
		d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);
		//Refresh the Depth/Stencil view
		d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
		
		//cubo->DrawScene(camara);
		esfera->DrawScene(camara);
		toroide->DrawScene(camara);
		cilindro->DrawScene(camara);

		cono->DrawScene(camara);
		edificio->DrawScene(camara);
		barrier->DrawScene(camara);
		Bike->DrawScene(camara);
		Edificio1->DrawScene(camara);
		leaves->DrawScene(camara);
		trunk->DrawScene(camara);
		racefence->DrawScene(camara);
		rubble->DrawScene(camara);
		sandbag->DrawScene(camara);
		startline->DrawScene(camara);

		gokart->DrawScene(camara);
		gokart2->DrawScene(camara);

		track->DrawScene(camara);
		billboard->DrawScene(camara);
		senal->DrawScene(camara);
		barril->DrawScene(camara);
		cono1->DrawScene(camara);
		flags->DrawScene(camara);
		llantas->DrawScene(camara);
		tree->DrawScene(camara);

		
		
		terreno->DrawScene(camara);
		skydomo->DrawScene(skyCamara);

		BoundingSphere1->DrawScene(camara);
		BoundingSphere2->DrawScene(camara);

		//Bitmap->DrawBitmap(camara);




		 // Show demo window! :)

		
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		//Present the backbuffer to the screen
		SwapChain->Present(0, 0);
	}

	
	bool CheckBoundingSphereCollision(float firstSphereRadius,
		D3DXVECTOR3 firstSpherePos,
		D3DXMATRIX firstObjWorldSpace,
		float secondSphereRadius,
		D3DXVECTOR3 secondSpherePos,
		D3DXMATRIX secondObjWorldSpace)
	{
		//Declare local variables
		D3DXVECTOR3 world_1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 world_2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float objectsDistance = 0.0f;

		//Transform the objects world space to objects REAL center in world space
		D3DXVec3TransformCoord(&world_1, &firstSpherePos, &firstObjWorldSpace);
		D3DXVec3TransformCoord(&world_2, &secondSpherePos, &secondObjWorldSpace);

		// Create Vector to verify distance
		world_1 -= world_2;

		//Get the distance between the two objects
		objectsDistance = D3DXVec3Length(&world_1);
		//objectsDistance = XMVectorGetX(XMVector3Length(world_1 - world_2));

		//If the distance between the two objects is less than the sum of their bounding spheres...
		if (objectsDistance <= (firstSphereRadius + secondSphereRadius))
			return true;

		//If the bounding spheres are not colliding, return false
		return false;

		
	}
	
	


};

#endif