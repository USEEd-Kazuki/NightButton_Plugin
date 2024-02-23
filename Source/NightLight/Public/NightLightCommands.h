// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "NightLightStyle.h"

class FNightLightCommands : public TCommands<FNightLightCommands>
{
public:

	FNightLightCommands()
		: TCommands<FNightLightCommands>(TEXT("NightLight"), NSLOCTEXT("Contexts", "NightLight", "NightLight Plugin"), NAME_None, FNightLightStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
