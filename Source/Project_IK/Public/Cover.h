/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Cover.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "Damageable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cover.generated.h"

class UCharacterStatComponent;
class USphereComponent;
class UBoxComponent;

UCLASS()
class PROJECT_IK_API ACover : public AActor, public IDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACover();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void OnDie();
	bool HasCoveringOwner() const;
	void SetCoveringOwner(bool bHas_Covering_Owner);
	bool IsBroken() const;
	void SetIsBroken(bool bIs_Broken);
	virtual void GetDamage(float damage) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* cover_collider_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	USphereComponent* cover_position_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* cover_mesh_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	UCharacterStatComponent* character_stat_component_;
	
	bool has_covering_owner_ = false;
	bool is_broken_ = false;
};
