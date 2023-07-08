// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DemoPluginStyle.h"

class FDemoPluginCommands : public TCommands<FDemoPluginCommands>
{
public:

	FDemoPluginCommands()
		: TCommands<FDemoPluginCommands>(TEXT("DemoPlugin"), NSLOCTEXT("Contexts", "DemoPlugin", "DemoPlugin Plugin"), NAME_None, FDemoPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};