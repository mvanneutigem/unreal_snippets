// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoPluginCommands.h"

#define LOCTEXT_NAMESPACE "FDemoPluginModule"

void FDemoPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "DemoPlugin", "Bring up DemoPlugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
