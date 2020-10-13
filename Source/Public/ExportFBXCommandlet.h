#pragma once
 
#include "Commandlets/Commandlet.h"
#include "ExportFBXCommandlet.generated.h"
 
UCLASS()
class UCommandletExportFBXCommandlet : public UCommandlet
{
    GENERATED_BODY()
 
    virtual int32 Main(const FString& Params) override;
};