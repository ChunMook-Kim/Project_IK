/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for Hero.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Hero.h"
#include "IKGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AHero::Die()
{
	auto test = UGameplayStatics::GetGameMode(this);
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveEnemy(this);
	Super::Die();
}
