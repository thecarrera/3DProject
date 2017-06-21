#pragma once
#include "Includes.h"

class OBJ
{
private:
	struct Vertex
	{
		float Position[3];
		float Normal[3];
		float uv[2];
	};

	class Mesh
	{
	public:
		std::vector<Vertex> vertices;
		
		int vertexCount = 0;
		std::string group;
		std::string material;
		std::vector<std::string> shadingGroups;
	};

	struct Material
	{
		std::string albedoMap = "";
		std::string diffuseMap = "";
		std::string specularMap = "";
		//std::string ScalarMap = "";
		std::string bumpMap = "";

		//illumi
		int illuminance = 4;
		//Kd
		float diffuseColor[3] = { 0 };
		//Ka
		float ambientColor[3] = { 0 };
		//Ks
		float specularColor[3] = { 0 };
		//Tf
		float  transmissionFilter[3] = { 0 };
		//Ns
		float specularExponent = 0;
		//Sharpness
		float specularSharpness = 0;
		//Ni
		float meshOpacity = 0;
	};


public:
	ID3D11Debug* dbg = nullptr;

	ID3D11Buffer** gVertexBufferArray;
	std::vector<Mesh> meshes;
	std::vector<Material> materials;
	std::vector<std::string> materialNames;
	int meshCount = 0;
	int materialCount = 0;

public:
	~OBJ()
	{
		this->setDbg();

		if (dbg != nullptr)
		{
			dbg->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
			dbg = nullptr;
		}
	};
	void setDbg()
	{
		for (int i = 0; i < this->meshCount; i++)
		{

		}

	}
	void setDbgName(ID3D11DeviceChild* child, const std::string& name)
	{
		if (child != nullptr)
		{
			child->SetPrivateData(WKPDID_D3DDebugObjectName, name.size(), name.c_str());
		}
	}
	void setDbgName(ID3D11Device* child, const std::string& name)
	{
		if (child != nullptr)
		{
			child->SetPrivateData(WKPDID_D3DDebugObjectName, name.size(), name.c_str());
		}
	}
	void setDbgName(IDXGISwapChain* child, const std::string& name)
	{
		if (child != nullptr)
		{
			child->SetPrivateData(WKPDID_D3DDebugObjectName, name.size(), name.c_str());
		}
	}

	void loadOBJ(int fileCount, std::string fileName)
	{
		Mesh mesh;
		DirectX::XMFLOAT3 inputValues;
		DirectX::XMFLOAT2 inputTex;

		std::vector<DirectX::XMFLOAT3> VertexPos;
		std::vector<DirectX::XMFLOAT3> VertexNorm;
		std::vector<DirectX::XMFLOAT2> VertexTex;

		int faceCount = 0;

		std::string line;
		std::ifstream file(".//assets//obj//" + fileName, std::ifstream::in);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line[0] != '#' && line[0] != '\0' && line[0] != ' ')
				{
					if (line.substr(0, 7) == "mtllib ")
					{
						this->loadMtl(line.substr(7));
					}
					else if (line.substr(0,2) == "g ")
					{
						if (line.substr(2) == "default")
						{
							if (this->meshCount > 0)
							{
								this->meshes.push_back(mesh);

								mesh.vertices.clear();
								mesh.shadingGroups.clear();
								mesh.group = "";
								mesh.material = "";
								mesh.vertexCount = 0;
							}
							this->meshCount++;
						}
						else
						{
							mesh.group = line.substr(2);
						}
					}
					else if (line.substr(0,2) == "v ")
					{
						int lastSpace = 0;

						inputValues.x = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						inputValues.y = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						inputValues.z = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						inputValues.z = (inputValues.z * -1.0f);

						VertexPos.push_back(inputValues);
					}
					else if (line.substr(0, 3) == "vt ")
					{
						int lastSpace = 0;

						inputTex.x = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						inputTex.y = std::stof(line.substr(line.find(' ', lastSpace + 1)));

						VertexTex.push_back(inputTex);
					}
					else if (line.substr(0, 3) == "vn ")
					{
						int lastSpace = 0;

						inputValues.x = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						inputValues.y = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						inputValues.z = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						inputValues.z = (inputValues.z * -1.0f);

						VertexNorm.push_back(inputValues);
					}
					else if (line.substr(0, 2) == "s ")
					{
						mesh.shadingGroups.push_back(line.substr(2));
					}
					else if (line.substr(0, 7) == "usemtl ")
					{
						mesh.material = line.substr(7);
					}
					else if (line.substr(0, 2) == "f ")
					{

						Vertex temp_vert[3];
						int nextSpace = 0;
						int firstSlash = 0;
						int secoundSlash = 0;
						std::string index1;
						std::string index2;
						std::string index3;

						faceCount++;

						nextSpace = line.find(' ', nextSpace);

						for (int i = 0; i < 3; i++)
						{
							firstSlash = line.find('/', secoundSlash + 1);
							index1 = line.substr(nextSpace, firstSlash - nextSpace);
							index1 = index1.substr(1);

							secoundSlash = line.find('/', firstSlash + 1);
							index2 = line.substr(firstSlash, secoundSlash - firstSlash);
							index2 = index2.substr(1);

							nextSpace = line.find(' ', nextSpace + 1);
							index3 = line.substr(secoundSlash, nextSpace - secoundSlash);
							index3 = index3.substr(1);

							temp_vert[i].Position[0] = VertexPos.at(std::stoi(index1) - 1).x;
							temp_vert[i].Position[1] = VertexPos.at(std::stoi(index1) - 1).y;
							temp_vert[i].Position[2] = VertexPos.at(std::stoi(index1) - 1).z;

							temp_vert[i].Normal[0] = VertexNorm.at(std::stoi(index3) - 1).x;
							temp_vert[i].Normal[1] = VertexNorm.at(std::stoi(index3) - 1).y;
							temp_vert[i].Normal[2] = VertexNorm.at(std::stoi(index3) - 1).z;

							temp_vert[i].uv[0] = VertexTex.at(std::stoi(index2) - 1).x;
							temp_vert[i].uv[1] = VertexTex.at(std::stoi(index2) - 1).y;
						}

						for (int i = 2; i > -1; i--)
						{
							mesh.vertices.push_back(temp_vert[i]);
							mesh.vertexCount++;
						}
					}
				}
			}
		}
		file.close();

		this->meshes.push_back(mesh);

	};
	void loadMtl(std::string fileName)
	{
		Material tempMat;

		std::string line;

		std::ifstream file(".//assets//Obj//" + fileName, std::ifstream::in);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line.substr(0, 7) == "newmtl ")
				{	
					if (this->materialCount > 0)
					{
						this->materials.push_back(tempMat);
						this->flushTempMat(tempMat);
					}
					this->materialNames.push_back(line.substr(7));
					this->materialCount++;
				}
				else if (line[0] != '#' && line[0] != '\0' && line[0] != ' ')
				{
					if (line.substr(0,7) == "map_Ka ")
					{
						tempMat.albedoMap = line.substr(7);
					}
					else if (line.substr(0, 7) == "map_Kd ")
					{
						tempMat.diffuseMap = line.substr(7);
					}
					else if (line.substr(0, 7) == "map_Ks ")
					{
						tempMat.specularMap = line.substr(7);
					}
					else if (line.substr(0, 5) == "bump ")
					{
						tempMat.bumpMap = line.substr(5);
					}
					else if (line.substr(0, 6) == "illum ")
					{
						tempMat.illuminance = std::stoi(line.substr(6));
					}
					else if (line.substr(0, 3) == "Kd ")
					{
						float lastSpace = 0;

						tempMat.diffuseColor[0] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						tempMat.diffuseColor[1] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						tempMat.diffuseColor[2] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
					}
					else if (line.substr(0, 3) == "Ka ")
					{
						float lastSpace = 0;

						tempMat.ambientColor[0] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						tempMat.ambientColor[1] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						tempMat.ambientColor[2] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
					}
					else if (line.substr(0, 3) == "Ks ")
					{
						float lastSpace = 0;

						tempMat.specularColor[0] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						tempMat.specularColor[1] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						tempMat.specularColor[2] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
					}
					else if (line.substr(0, 3) == "Tf ")
					{
						float lastSpace = 0;

						tempMat.transmissionFilter[0] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						tempMat.transmissionFilter[1] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
						lastSpace = line.find(' ', lastSpace + 1);
						tempMat.transmissionFilter[2] = std::stof(line.substr(line.find(' ', lastSpace + 1)));
					}
					else if (line.substr(0, 3) == "Ns ")
					{
						tempMat.specularExponent = std::stof(line.substr(line.find(' ')));
					}
					else if (line.substr(0, 10) == "Sharpness ")
					{
						tempMat.specularSharpness = std::stof(line.substr(line.find(' ')));
					}
					else if (line.substr(0, 3) == "Ni ")
					{
						tempMat.meshOpacity = std::stof(line.substr(line.find(' ')));
					}
				}

			}
		}
		file.close();

		this->materials.push_back(tempMat);

	};
	void bindToBuffer(ID3D11Device* &gDevice)
	{
		HRESULT hr;

		gVertexBufferArray = new ID3D11Buffer*[this->meshCount];

		for (int i = 0; i < this->meshCount; i++)
		{
			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.ByteWidth = sizeof(Vertex) * this->meshes.at(i).vertexCount;

			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(data));
			data.pSysMem = this->meshes.at(i).vertices.data();
			hr = gDevice->CreateBuffer(&bufferDesc, &data, &gVertexBufferArray[i]);

			if (FAILED(hr))
			{
				exit(-1);
			}
		}

	}

	int getSizeOfVertex()
	{
		return sizeof(Vertex);
	};

	void flushTempMat(Material& tempMat)
	{
		tempMat.albedoMap = "";
		tempMat.diffuseMap = "";
		tempMat.specularMap = "";
		//tempMat.ScalarMap = "";
		tempMat.bumpMap = "";

		//illumi
		tempMat.illuminance = 4;
		//Kd
		tempMat.diffuseColor[3] = { 0 };
		//Ka
		tempMat.ambientColor[3] = { 0 };
		//Ks
		tempMat.specularColor[3] = { 0 };
		//Ns
		tempMat.specularExponent = 0;
		//Sharpness
		tempMat.specularSharpness = 0;
		//Tf
		tempMat.transmissionFilter[3] = { 0 };
		//Ni
		tempMat.meshOpacity = 0;
	};
	void flushAll()
	{
		this->materialCount = 0;
		this->materialNames.clear();
		this->meshCount = 0;
		this->materials.clear();
		this->meshes.clear();
	}
	void Clean()
	{
		for (int i = 0; i < this->meshCount; i++)
		{
			SAFE_RELEASE(this->gVertexBufferArray[i]);
		}
		SAFE_DELETE(this->gVertexBufferArray);
	};
};

class OBJfiles
{
public:
	std::vector<OBJ> files;
private:
	std::vector<std::string> fileNames;
	int fileCount;

public:
	OBJfiles() {};
	~OBJfiles()
	{
		for (int i = 0; i < this->fileCount; i++)
		{
			this->files.at(i).Clean();
		}
	};

	void loadFiles(ID3D11Device* &gDevice)
	{
		OBJ objFile;
		std::string line;
		std::ifstream file(".//assets//FileLoaders//objInput.txt", std::ifstream::in);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line[0] != '#' && line[0] != '\0' && line[0] != ' ' && line.substr(0, 5) != "Load:")
				{
					this->fileNames.push_back(line);
					this->fileCount++;
				}
			}
		}
		file.close();

		for (int i = 0; i < this->fileCount; i++)
		{
			objFile.loadOBJ(this->fileCount, this->fileNames.at(i));
			files.push_back(objFile);
			objFile.flushAll();
			this->files.at(i).bindToBuffer(gDevice);
		}
	}
	int getSizeOfVertex()
	{
		return files.at(0).getSizeOfVertex();
	};

	int getFileCount() { return this->fileCount; };

	int getMeshCount(int fileIndex)
	{
		return this->files.at(fileIndex).meshCount;
	}
	int getMeshVertexCount(int fileIndex, int meshIndex)
	{
		return this->files.at(fileIndex).meshes.at(meshIndex).vertexCount;
	};
};