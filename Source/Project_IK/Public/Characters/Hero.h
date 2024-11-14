/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Header file for Hero.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "PassiveSkillGunner.h"
#include "Hero.generated.h"
class USphereComponent;
class ADrone;

UCLASS()
class PROJECT_IK_API AHero : public APassiveSkillGunner
{
	GENERATED_BODY()

public:
	AHero();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	AActor* GetDrone();
	
protected:
	void Die() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	UClass* drone_bp_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	USphereComponent* drone_location_;

	AActor* drone_;
};
