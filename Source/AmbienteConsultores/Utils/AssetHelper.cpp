#include "AssetHelper.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

TArray<UObject*> UAssetHelper::LoadAssetsFromClass(UClass* Class)
{
	TArray<UObject*> LoadedAssets;

	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		const FPrimaryAssetType PrimaryAssetType(Class->GetFName());
		TSharedPtr<FStreamableHandle> Handle = Manager->LoadPrimaryAssetsWithType(PrimaryAssetType);
		if (Handle.IsValid())
		{
			Handle->WaitUntilComplete(0.0f, false);
        
			Handle->GetLoadedAssets(LoadedAssets);
		}
	}
	return LoadedAssets;
}