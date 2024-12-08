/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Header file for Self Explosion Enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Characters/MeleeEnemy.h"
#include "SelfExplosionEnemy.generated.h"

UCLASS()
class PROJECT_IK_API ASelfExplosionEnemy : public AMeleeEnemy
{
	GENERATED_BODY()
public:
	ASelfExplosionEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Explosion();

	UFUNCTION(BlueprintPure)
	float GetExplosionDelay();

	UFUNCTION(BlueprintPure)
	float GetExplosionRadius();

	UFUNCTION(BlueprintPure)
	float GetExplosionStartRadius();
	
private:
	float explosion_start_radius_;
	float explosion_radius_;
	float explosion_delay_;
};
