// Copyright Epic Games, Inc. All Rights Reserved.

#include "NightLightCommands.h"

#define LOCTEXT_NAMESPACE "FNightLightModule"

void FNightLightCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "NightLight", "Execute NightLight action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
