/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.03.2024
Summary : Header file for Targeting component.
					Before skills invoked, it helps to choose target.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"

UENUM(BlueprintType)
enum class ETargetingMode : uint8
{
	None,
	Actor,
	Location,
	Direction,
};

USTRUCT(BlueprintType)
struct FTargetData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	AActor* target_actor_ = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	FVector target_location_ = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	FRotator target_rotation_ = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	float range_ = 1000.f;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	float radius_ = 0.f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetDataSelected, const FTargetData&, TargetData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetingCanceled);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(BlueprintAssignable, Category = "Targeting")
	FOnTargetDataSelected OnTargetDataSelected;

	UPROPERTY(BlueprintAssignable, Category = "Targeting")
	FOnTargetingCanceled OnTargetingCanceled;

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void StartTargeting(ETargetingMode mode, float Range = 1000.f, float Radius = 0.f);
	UFUNCTION(BlueprintCallable, Category="Targeting")
	void StopTargeting();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UMaterialInterface* targeting_decal_material_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UStaticMesh* aoe_indicator_mesh_;

private:
	ETargetingMode current_mode_;
	bool is_targeting_;
	APlayerController* player_controller_;
	FTargetData current_tarrget_data_;

	// Components for visuul feedback
	UDecalComponent* targeting_decal_;
	UStaticMeshComponent* aoe_indicator_;

	void HandleActorTargeting();
	void HandleLocationTargeting();
	
	void UpdateTargetingVisuals();
	void CleanupTargetingVisuals();

	bool IsValidTarget(AActor* target) const;
	FVector GetGroundLocation() const;
};
