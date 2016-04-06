#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include "fbxSDK.h"
#include "BRFImporterStructs.h"


class MaterialHandler
{
public:
	MaterialHandler();
	~MaterialHandler();

	void GetMaterialData(FbxNode* pNode);

private:
	void ProcessData(FbxSurfaceMaterial* pMaterial, unsigned int matCount);

	//get RG(B) values
	void GetDiffuse(FbxSurfaceMaterial* pMaterial, double *pTargetDiffuse);
	void GetSpecular(FbxSurfaceMaterial* pMaterial, double *pTargetSpecular);

	//getMaps
	void GetTextureMap(FbxProperty diffProp, unsigned int mapCount);
	void GetSpecularMap(FbxProperty specProp, unsigned int mapCount);
	void GetNormalMap(FbxProperty normMapProp, unsigned int mapCount);
	void GetGlowMap(FbxProperty glowMapProp, unsigned int mapCount)
};


#endif // !MATERIALHANDLER_H