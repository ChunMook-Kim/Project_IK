// Fill out your copyright notice in the Description page of Project Settings.

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void OnDestroy();
	void FireWeapon(AActor* target);
	void Reload();
	
private:
	void EquipWeapon();
	
private:
	//weapon_class는 Default로 Rifle로 지정되어 있음. BP를 통해 변경 가능하게 하는것이 좋을듯.
	UClass* weapon_class_;
	FName head_socket_name_;
	FName owned_cover_key_name_;
	
	//TODO: 이거 SharedPtr이나 Weak Ptr로 해야 하나?
	AGun* weapon_ref_ = nullptr;
	ACharacter* character_ref_ = nullptr;
};
