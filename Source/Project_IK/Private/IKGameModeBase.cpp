/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for game mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "IKGameModeBase.h"

#include "Kismet/GameplayStatics.h"

#include "Project_IK/Public/IKHUD.h"

AIKGameModeBase::AIKGameModeBase()
	: Super::AGameModeBase()
{
	PopulateHeroContainer();
}

void AIKGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

TArray<AActor*> AIKGameModeBase::GetHeroContainers() noexcept
{
	return heroes_;
}

void AIKGameModeBase::PopulateHeroContainer()
{
	ConstructorHelpers::FClassFinder<AActor> BP_Hero_Finder(TEXT("/Game/__BluePrints/BP_Hero"));
	if (BP_Hero_Finder.Succeeded())
	{
		hero_class = BP_Hero_Finder.Class;
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), hero_class, heroes_);
}
