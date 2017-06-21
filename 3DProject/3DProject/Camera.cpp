#include "Camera.h"

Camera::Camera()
{
	this->viewM = DirectX::XMMatrixIdentity();
	this->projM = DirectX::XMMatrixIdentity();
}
Camera::~Camera()
{
}

void Camera::createCamera()
{
	DirectX::XMVECTOR cameraPos = { 0.0f, 1.0f, -10.0f };
	DirectX::XMVECTOR lookAt = { 0, 0, 0 };
	DirectX::XMVECTOR upVec = { 0, 1, 0 };

	float FOV = { 0.45f * DirectX::XM_PI };
	float ARO = (float)WIDTH / (float)HEIGHT;
	float nPlane = 0.1f;
	float fPlane = 500.0f;

	this->viewM = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(cameraPos, lookAt, upVec));
	this->projM = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(FOV, ARO, nPlane, fPlane));

}
void Camera::createCamera(	DirectX::XMVECTOR cameraPos, DirectX::XMVECTOR lookAt, DirectX::XMVECTOR upVec, float FOV, float ARO, float nPlane, float fPlane)
{
	this->viewM = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookToLH(cameraPos, lookAt, upVec));
	this->projM = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(FOV, ARO, nPlane, fPlane));
}

void Camera::moveCamera()
{
	
}