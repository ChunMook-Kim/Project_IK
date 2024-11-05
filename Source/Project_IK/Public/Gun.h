/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GunInterface.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USphereComponent;
UCLASS()
class PROJECT_IK_API AGun : public AActor, public IGunInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	virtual void Reload() override;
	virtual void FireWeapon(FVector target_pos) override;

	bool IsMegazineEmpty() const;
	float GetFireInterval() const;
	void SetFireInterval(float Fire_Interval);
	float GetReloadDuration() const;
	void SetReloadDuration(float Reload_Duration);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* gun_mesh_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	USphereComponent* muzzle_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int max_megazine_ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int cur_megazine_ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float fire_interval_ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	float reload_duration_ = 0;
};
