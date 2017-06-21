#pragma once
#include "Includes.h"
#include "Camera.h"
#include "OBJImporter.hpp"


class Linker
{
public:
	Linker();
	~Linker();
	void Clean();

	Camera baseCamera;
	OBJfiles OBJ;
};