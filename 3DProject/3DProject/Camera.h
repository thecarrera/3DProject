#pragma once
#include "Includes.h"




class Camera
{
private:
	DirectX::XMMATRIX viewM;
	DirectX::XMMATRIX projM;

public:
	Camera();
	~Camera();
	
	void createCamera();
	void createCamera(	DirectX::XMVECTOR cameraPos,
						DirectX::XMVECTOR lookAt,
						DirectX::XMVECTOR upVec,
						float FOV,
						float ARO,
						float nPlane,
						float fPlane);

	void moveCamera();
};