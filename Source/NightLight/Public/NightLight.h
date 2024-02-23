// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FNightLightModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();
	AActor* FindObject(TSubclassOf<AActor> ActorClass);
	AActor* AddObject(TSubclassOf<AActor> ActorClass);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
