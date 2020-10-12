// FBX export helper functions
#include "AssetExportTask.h"
#include "AssetRegistryModule.h"
#include "Exporters/LevelExporterFbx.h"
#include "UObject/UObjectGlobals.h"

UFUNCTION(BlueprintCallable, Category = FBXExport)
static FAssetData* ExportLevelAsFBX()
{
	FName LevelName = FName(TEXT("Primitives"));

	// get asset registry
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked< FAssetRegistryModule >(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	// get level assets
	TArray< FAssetData > AssetList;
	AssetRegistry.GetAssetsByClass(FName(TEXT("World")), AssetList);

	// find level asset with given name
	FAssetData* LevelToExport = nullptr;
	for (auto Asset : AssetList)
	{
		if (Asset.AssetName == LevelName)
		{
			UE_LOG(LogClass, Log, TEXT("Asset: %s"), *Asset.AssetName.ToString());
			LevelToExport = &Asset;
			break;
		}
	}
	// return if level with given name was not found
	if (LevelToExport == nullptr)
	{
		return nullptr;
	}
	
	UAssetExportTask* ExportTask = NewObject<UAssetExportTask>();
	UE_LOG(LogClass, Log, TEXT("This is the level: %s"), *LevelToExport->AssetName.ToString());

	ExportTask->Filename = FString(TEXT("C:\\Users\\Marieke\\Documents\\Unreal_Testing\\out\\output_level_cpp.fbx"));
	UObject* asset = LevelToExport->FastGetAsset(true);
	ExportTask->Object = asset;
	UE_LOG(LogClass, Log, TEXT("Asset: %s"), *asset->GetPathName());
	

	ULevelExporterFBX::RunAssetExportTask(ExportTask);

	return LevelToExport;
}