// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PassiveSkill.h"
#include "DronePlugIn.generated.h"

class ADrone;

UCLASS()
class PROJECT_IK_API ADronePlugIn : public APassiveSkill
{
	GENERATED_BODY()
public:
	ADronePlugIn();
	virtual void Initialize(AActor* caster) override;

private:
	//드론 플러그인은 패시브 스킬에서 추가적으로 드론을 참조한다.
	AActor* owner_hero_;
	AActor* owner_drone_;
};
