/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for WeaponMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponMechanics.generated.h"

class AUnit;
class UCharacterStatComponent;
class AGun;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UWeaponMechanics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponMechanics();

public:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void OnDestroy();
	
	void BeginFire(AActor* target);
	void OnFire(AActor* target);
	void FireWeapon(AActor* target);
	void FinishFire();
	
	void Reload();
	void OnReload();
	
	bool IsMagazineEmpty() const;
	float GetFireInterval() const;
	float GetReloadDuration() const;

	void OnStunned();
	
	UFUNCTION()
	void SetWeaponOwner(TWeakObjectPtr<AActor> gun_owner);
	
private:
	void EquipWeapon();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true", AllowedClasses = "Gun"))
	UClass* weapon_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName head_socket_name_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName gun_socket_name_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName owned_cover_key_name_;

	UPROPERTY(Transient)
	FTimerHandle fire_timer_handle_;

	UPROPERTY(Transient)
	FTimerHandle reload_timer_handle_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* fire_montage_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* reload_montage_;
	
	UPROPERTY(Transient)
	AGun* weapon_ref_ = nullptr;
	
	UPROPERTY(Transient)
	AUnit* gunner_ref_ = nullptr;
};
