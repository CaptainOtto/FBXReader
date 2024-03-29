#include "FbxImport.h"
#include "BRFImporterStructs.h"




FbxImport::FbxImport()
{

}


FbxImport::~FbxImport()
{
	if(ios)
		ios->Destroy();
	
	if(scene)
		scene->Destroy();
	if(fbxManager)
		fbxManager->Destroy(); //destroy the manager. do this last
}

void FbxImport::ConvertFbxToFile(BrfExporter * outputFile)
{

	GetMaterialData(this->rootNode, outputFile->GetMatRef());
	for (int i = 0; i < this->rootNode->GetChildCount(); i++)
	{
		GetMeshData(this->rootNode->GetChild(i), outputFile->GetMeshesRef());
		GetCameraData(this->rootNode->GetChild(i),outputFile->GetCamerasRef());
		GetSkeletonData(this->rootNode->GetChild(i), outputFile->GetSkeletonRef());
		GetGroupData(this->rootNode->GetChild(i), outputFile->GetGroupsRef());
		GetLightData(this->rootNode->GetChild(i), outputFile->GetLightsRef());
		//GetAttributeData(this->rootNode->GetChild(i), outputFile->GetAttributesRef());
	}

	GetMorphData(this->rootNode, outputFile->GetMorphAnimRef(), outputFile->GetMeshesRef());
}

void FbxImport::LoadFbxFile(const char * fileName)
{

	fbxManager = FbxManager::Create(); //create the manager, This handles memory management



	/*To import the contents of an FBX file, a FbxIOSettings object and a FbxImporter object must be created.
	A FbxImporter object is initialized by providing the -
	- filename of the file to import along with a FbxIOSettings object that has been appropriately configured to suit the importing needs (see I/O Settings).*/


	//Create IO settings object
	 ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);

	//Create the importer using the SDK manager
	FbxImporter* fImporter = FbxImporter::Create(fbxManager, "");

	//use the first argument as the filename for the importer

	if (!fImporter->Initialize(fileName, -1, fbxManager->GetIOSettings()))
	{
		std::cout << "Error loading file" << std::endl;

		std::cout << fImporter->GetStatus().GetErrorString() << std::endl;
		throw int(1);
		return;
		
	}

	std::cout << " THE FILE IS FOUND, HALLELUJA" << std::endl << std::endl;




	//Create a new scene so that the information can be loaded into it from the file
	//The FbxScene object acts as a container for elements existing within the scene.
	scene = FbxScene::Create(fbxManager, "myScene");

	fImporter->Import(scene);

	//the file is imported. Destroy the importer
	
	fImporter->Destroy();



	rootNode = scene->GetRootNode();
	
}

void FbxImport::PrintNode(FbxNode * pNode)
{
	this->printer.PrintNode(pNode);
}

void FbxImport::PrintScene()
{
	if (rootNode)
	{

		//PrintNode(rootNode);
		for (int i = 0; i < rootNode->GetChildCount(); i++)
		{
			PrintNode(rootNode->GetChild(i));
			
		}
	}

}

void FbxImport::GetMeshData(FbxNode * pNode, std::vector<MeshExport*>* outputMeshes)
{
	meshHandler.GetMeshData(pNode, outputMeshes, &this->sceneMap); //Extract all the meshes.
}

void FbxImport::GetMaterialData(FbxNode* pNode, MaterialExport* outputMat)
{
	materialHandler.GetMaterialData(pNode, outputMat,&this->sceneMap);
}

void FbxImport::GetCameraData(FbxNode* pNode, CameraExporter* outputCameras)

{
	cameraHandler.GetCameraData(pNode, outputCameras);
}

void FbxImport::GetSkeletonData(FbxNode * pNode, std::vector<SkeletonExport*>* outputSkeletons)
{
	skeletonHandler.GetSkeletonData(pNode, outputSkeletons);


	//skeletonHandler.GetSkeletonData(pNode);
}

void FbxImport::GetAttributeData(FbxNode * pNode, AttributesExport* outPutAttributes)
{
	attributeHandler.GetAttrData(pNode, outPutAttributes);
}

//void FbxImport::GetAnimationData(FbxNode * pNode, BrfExporter * outputClass)
//{
//}

void FbxImport::GetLightData(FbxNode * pNode, LightExport* lights)
{
	lightHandler.GetLightData(pNode,lights);

}

void FbxImport::GetMorphData(FbxNode * pNode, std::vector<MorphAnimExport*>* outputMorphs, std::vector<MeshExport*>* outputMeshes)
{
	morphAni.GetMorphAnimation(pNode, outputMorphs,outputMeshes);
	//morphHandler.GetMorphData(pNode, outputMorphs);
}

void FbxImport::GetGroupData(FbxNode * pNode, std::vector<GroupExport*>* outputGroups)
{

	groupHandler.GetGroupData(pNode,outputGroups);

}






void FbxImport::MapMeshes(FbxNode * pNode)
{


}

void FbxImport::MapCameras(FbxNode * pNode)
{


}

void FbxImport::MapSkeletons(FbxNode * pNode)
{

}

void FbxImport::MapMaterials(FbxNode * pNode)
{
	materialHandler.MapMaterials(pNode, &this->sceneMap);

}

void FbxImport::MapLights(FbxNode * pNode)
{


}

void FbxImport::MapMorphAnim(FbxNode * pNode)
{


}

void FbxImport::MapGroups(FbxNode * pNode)
{


}


