/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Header file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterStatComponent.generated.h"

UCLASS()
class PROJECT_IK_API ACharacterStatComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterStatComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Scaling powers
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float attack_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float attack_speed_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float ability_power_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float magazine_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float hit_point_;

	// Fixed powers
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float fire_range_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float move_speed_;
};
