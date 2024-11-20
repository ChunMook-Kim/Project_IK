/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for enemy base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/EnemyBase.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

void AEnemyBase::Die()
{
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveEnemy(this);
	Super::Die();
}
