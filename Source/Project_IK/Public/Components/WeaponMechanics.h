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

public:
	void OnDestroy();
	void FireWeapon(AActor* target);
	void Reload();
	bool IsMagazineEmpty() const;
	float GetFireInterval() const;
	float GetReloadDuration() const;
	UFUNCTION()
	void SetWeaponOwner(TWeakObjectPtr<AActor> gun_owner);
	
	
private:
	void EquipWeapon();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	UClass* weapon_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName head_socket_name_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName gun_socket_name_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FName owned_cover_key_name_;
	
	AGun* weapon_ref_ = nullptr;
	ACharacter* character_ref_ = nullptr;
};
