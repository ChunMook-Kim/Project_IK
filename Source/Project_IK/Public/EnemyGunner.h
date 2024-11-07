/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Header file for enemy gunner.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Gunner.h"
#include "EnemyGunner.generated.h"
UCLASS()
class PROJECT_IK_API AEnemyGunner : public AGunner
{
	GENERATED_BODY()

protected:
	void Die() override;
};
