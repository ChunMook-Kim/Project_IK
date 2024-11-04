/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for PassiveSkillBase.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PassiveSkill.generated.h"

UCLASS()
class PROJECT_IK_API APassiveSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APassiveSkill();
	void Initialize(AActor* caster);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	float GetCoolTime() const;
	void SetCoolTime(float Cool_Time);
	float GetDuration() const;
	void SetDuration(float Duration);
	float GetHoldTime() const;
	void SetHoldTime(float Hold_Time);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float cool_time_ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float duration_ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float hold_time_ = 0.f;
	
	AActor* caster_;
};
