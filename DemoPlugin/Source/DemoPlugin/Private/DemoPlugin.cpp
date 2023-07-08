// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoPlugin.h"
#include "DemoPluginStyle.h"
#include "DemoPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "ToolMenus.h"


#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Factories/BlueprintFactory.h"
#include "IContentBrowserSingleton.h"


static const FName DemoPluginTabName("DemoPlugin");

#define LOCTEXT_NAMESPACE "FDemoPluginModule"

void FDemoPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDemoPluginStyle::Initialize();
	FDemoPluginStyle::ReloadTextures();

	FDemoPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDemoPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FDemoPluginModule::PluginButtonClicked),
		FCanExecuteAction());


	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDemoPluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DemoPluginTabName, FOnSpawnTab::CreateRaw(this, &FDemoPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FDemoPluginTabTitle", "DemoPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FDemoPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDemoPluginStyle::Shutdown();

	FDemoPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DemoPluginTabName);
}

TSharedRef<SDockTab> FDemoPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
// Spawn plugin tab window
{
	FText LabelText = FText::FromString("This is a button:");
	FText LabelText2 = FText::FromString("This is a checkbox:");
	FText ButtonText = FText::FromString("Create blueprint asset");

	TSharedRef<SDockTab> dockableTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.ToolTipText(FText::FromString("Demo tab tooltip"))
		[
			SNew(SUniformGridPanel)
			.SlotPadding(FMargin(5.0f))
			+ SUniformGridPanel::Slot(0, 0)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(LabelText)
			]
			+ SUniformGridPanel::Slot(1, 0)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SNew(SBox)
				.WidthOverride(200)
				.HeightOverride(20)
				[
					SNew(SButton)
					.Text(ButtonText)
					.OnClicked_Raw(this, &FDemoPluginModule::DoSomething)// class inherit from interface which is not shared
				]
			
			]
			+ SUniformGridPanel::Slot(0, 1)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(LabelText2)
			]
			+ SUniformGridPanel::Slot(1, 1)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SNew(SBox)
				.WidthOverride(20)
				.HeightOverride(20)
				[
					SNew(SCheckBox)
					.OnCheckStateChanged(FOnCheckStateChanged::CreateRaw(this, &FDemoPluginModule::CheckboxFlipped))// class inherit from interface which is not shared
				]
			]
		];

	return dockableTab;
}

void FDemoPluginModule::CheckboxFlipped(ECheckBoxState InState)
{
	// Write to the output log
	UE_LOG(LogTemp, Log, TEXT("Checkbox flipped!"));
}

FReply FDemoPluginModule::DoSomething()
{
	// Write to the output log
	UE_LOG(LogTemp, Log, TEXT("Clicked button!"));

	// Load modules
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	// Generate a unique asset name
	FString Name, PackageName;
	AssetToolsModule.Get().CreateUniqueAssetName(TEXT("/Game/CPPBluePrint"), TEXT(""), PackageName, Name);
	const FString PackagePath = FPackageName::GetLongPackagePath(PackageName);

	// Create object and package
	UPackage* package = CreatePackage(*PackageName);
	UBlueprintFactory* MyFactory = NewObject<UBlueprintFactory>(UBlueprintFactory::StaticClass()); // Can omit, and a default factory will be used
	UObject* NewObject = AssetToolsModule.Get().CreateAsset(Name, PackagePath, UBlueprint::StaticClass(), MyFactory);
	UPackage::Save(package, NewObject, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()));

	// Inform asset registry
	AssetRegistry.AssetCreated(NewObject);

	// Tell content browser to show the newly created asset
	TArray<UObject*> Objects;
	Objects.Add(NewObject);
	ContentBrowserModule.Get().SyncBrowserToAssets(Objects);

	return FReply::Handled();
}


void FDemoPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(DemoPluginTabName);
}

// Editor Preferences->General->Miscellaneous->Display UI Extension Points => True
void FDemoPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("mvanTools");
			Section.AddMenuEntryWithCommandList(FDemoPluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("mvanTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDemoPluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}


	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("Sequencer.MainToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("mvanTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDemoPluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDemoPluginModule, DemoPlugin)