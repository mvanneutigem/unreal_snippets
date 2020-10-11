// 
#include "Misc/AutomationTest.h"
#include "AutomationTesting/Public/ExportFBX.cpp"

namespace FeatTest
{
#define TEST_NAME_ROOT "Feat.Tests.Export"
	constexpr const uint32 TestFlags = EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::EngineFilter;

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(FExportFBXLevelTest, TEST_NAME_ROOT ".ExportFBXLevel", TestFlags)
		bool FExportFBXLevelTest::RunTest(const FString& Parameters)
	{
		FAssetData* level = ExportLevelAsFBX();
		TestTrue(TEXT("Failed to find level to export!"), level != nullptr);
		return true;
	}
}