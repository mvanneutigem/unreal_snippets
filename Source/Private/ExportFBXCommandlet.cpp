
#include "ExportFBXCommandlet.h"
#include "ExportFBX.cpp"

DEFINE_LOG_CATEGORY_STATIC(LogCommandletExportFBX, Log, All);
 
int32 UCommandletExportFBXCommandlet::Main (const FString& Params)
{
	// Parse args
	TArray<FString> Tokens, Switches;
	ParseCommandLine(*Params, Tokens, Switches);
	UE_LOG(LogCommandletExportFBX, Display, TEXT("Switches: %s"), *Switches[0]);
	UE_LOG(LogCommandletExportFBX, Display, TEXT("Tokens: %s"), *Tokens[0]);

	if (Tokens.Num() == 1)
	{
		// Execute code
		//FString LevelNameStr = Tokens[0];
		FString LevelNameStr = "Primitives";
		ExportLevelAsFBX(LevelNameStr);
		// WIP for some the above line always throws an error, 
		// i suspect because the editor hasnt fully loaded yet at this point... :(
	}
	
    return 0;
}