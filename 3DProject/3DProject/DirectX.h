#pragma once
#include "Linker.h"



/*
#################################################################################################################################
#																																#
#							All Direct X components, mostly the core engine of the pipeline.									#
#							Allowing us to add key techniques as modules.														#
#																																#
#################################################################################################################################
*/

class DX
{
//Core
public:
	ID3D11Device*			gDevice = nullptr;

private:
	ID3D11DeviceContext*	gDeviceContext = nullptr;
	IDXGISwapChain*			gSwapChain = nullptr;
	ID3D11RenderTargetView* gBackBufferRTV = nullptr;
	ID3D11DepthStencilView* gDSV = nullptr;
	ID3D11Texture2D*		gDepthStencil = nullptr;
	ID3D11Debug*			dbg = nullptr;

	ID3D11Buffer*			VPBuffer;
	ID3D11Buffer*			worldBuffer;
	ID3D11Buffer*			lightBuffer;
	
	ID3D11InputLayout*		gVertexLayout = nullptr;
	
	ID3D11VertexShader*		gVertexShader = nullptr;

	ID3D11GeometryShader*	gGeometryShader = nullptr;

	ID3D11PixelShader*		gFragmentShader = nullptr;

public:
	DX();
	~DX();
	void Clean();
	void setDbg();
	void setDbgName(ID3D11DeviceChild* child, const std::string& name);
	void setDbgName(ID3D11Device* child, const std::string& name);
	void setDbgName(IDXGISwapChain* child, const std::string& name);

	void OfflineCreation(ID3D11Device* &gDevice,HMODULE hModule, HWND* wndHandle);
	void CreateDirect3DContext(HWND* wndHandle);
	void CreateDepthBuffer();
	void SetViewPort();
	
	void CreateShaders();
	void CreateCBuffers();

	void Render();
	void clearRender();
	void Update();

	void drawAll();
	void drawFile();
	void drawMesh();

	void printMatrices(DirectX::XMMATRIX& mat);

private:
	Linker link;

	camMatrices		camMat;
	objMatrices		worldMat;
	lightMatrices	lightMat;

};