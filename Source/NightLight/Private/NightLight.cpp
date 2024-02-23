// Copyright Epic Games, Inc. All Rights Reserved.

#include "NightLight.h"
#include "NightLightStyle.h"
#include "NightLightCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"
#include "Engine/PostProcessVolume.h"
#include "Editor/EditorEngine.h"

static const FName NightLightTabName("NightLight");

#define LOCTEXT_NAMESPACE "FNightLightModule"

void FNightLightModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FNightLightStyle::Initialize();
	FNightLightStyle::ReloadTextures();

	FNightLightCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FNightLightCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FNightLightModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNightLightModule::RegisterMenus));
}

void FNightLightModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FNightLightStyle::Shutdown();

	FNightLightCommands::Unregister();
}

void FNightLightModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
    // ボタンクリック後のメッセージ
	FText DialogText = FText::FromString("Changing scene to Night");
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);

	// 関数の実行
	AActor* FoundActor;
	FoundActor = FindObject(ADirectionalLight::StaticClass());

	if (FoundActor) 
	{
		// DirectionalLightの自動設定
		ADirectionalLight* Sun = Cast<ADirectionalLight>(FoundActor);
		Sun->GetLightComponent()->SetIntensity(1.f);
	}

	FoundActor = FindObject(APostProcessVolume::StaticClass());

	APostProcessVolume* PPVol;

	if (!FoundActor)
	{
		// PPVoがなければ作成
		DialogText = FText::FromString("PostProcessVolume Not Found, Creating One");
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		FoundActor = AddObject(APostProcessVolume::StaticClass());
	}

	PPVol = Cast<APostProcessVolume>(FoundActor);
	PPVol->Settings.AutoExposureBias = -3.f;
	PPVol->Settings.bOverride_AutoExposureBias = true;
	PPVol->bUnbound = true;
}

void FNightLightModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FNightLightCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FNightLightCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

AActor* FNightLightModule::FindObject(TSubclassOf<AActor> ActorClass)
{
	// Actorの検索
	TArray<AActor* > FoundActors;
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World) 
	{
		UGameplayStatics::GetAllActorsOfClass(World, ActorClass, FoundActors);
		if (FoundActors.Num() > 0) 
		{
			return FoundActors[0];
		}
	}
	return nullptr;
}

AActor* FNightLightModule::AddObject(TSubclassOf<AActor> ActorClass)
{
	// Actorの追加
	ULevel* Level = GEditor->GetEditorWorldContext().World()->GetCurrentLevel();
	return GEditor->AddActor(Level, ActorClass, FTransform());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNightLightModule, NightLight)