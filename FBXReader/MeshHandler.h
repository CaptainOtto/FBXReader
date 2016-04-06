#pragma once
#include "fbxSDK.h"
class MeshHandler
{
public:
	MeshHandler();
	~MeshHandler();

	void GetMeshData(FbxNode* pNode);

private:
	void ProcessData(FbxMesh* pMesh);
	void GetVertPositions(FbxMesh* pMesh, int index, float* targetPos);
	void GetVertNormals(FbxGeometryElementNormal* pNElement, int index, float* targetNormal);
	void GetVertBiNormals(FbxGeometryElementBinormal* pBNElement, int index, float* targetBiNormal);
	void GetVertTangents(FbxGeometryElementTangent* pTElement, int index, float* targetTangent);
	void GetVertTextureUV(FbxGeometryElementUV* uvElement, int index, float* targetUV);
};

