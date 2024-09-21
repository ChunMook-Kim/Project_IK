/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for game mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "IKGameModeBase.h"

#include "Project_IK/Public/IKHUD.h"

AIKGameModeBase::AIKGameModeBase()
{

	static ConstructorHelpers::FClassFinder<AHUD> hud_class(TEXT("/Game/MyIKHUD"));
	if (hud_class.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully find a HUD class!"));
		HUDClass = hud_class.Class;
	}
	else
	{
		HUDClass = AIKHUD::StaticClass();
	}
}
