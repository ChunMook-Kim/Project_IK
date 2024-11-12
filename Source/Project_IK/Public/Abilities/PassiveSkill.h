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
	
	virtual void Initialize(AActor* caster);
	//StartPassiveSkill은 PassiveMechanics, 혹은 DroneMechanics에서 호출되도록 설계되어 있다.
	virtual void StartPassiveSkill();
	virtual void FinishPassiveSkill();

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
	bool IsActivated() const;
	void SetActivated(bool bActivated);
	bool IsPassiveAvailable() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float cool_time_ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float left_time_ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float duration_ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float left_duration_ = 0.f;

	//HoltTime은 패시브 발동 시 같이 발동되는 애니메이션이 있을 경우, 애니메이션을 위해 멈춰있어야 하는 시간을 말한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float hold_time_ = 0.f;

	//HoltTime은 패시브 발동 시 같이 발동되는 애니메이션이 있을 경우, 애니메이션을 위해 멈춰있어야 하는 시간을 말한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	bool activated_;
	
	AActor* caster_;
};
