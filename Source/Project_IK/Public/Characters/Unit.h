/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for unit. Every object which have status should inherit this class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Damageable.h"

#include "Unit.generated.h"


class UObjectPoolComponent;
class UWidgetComponent;
class UCharacterStatComponent;
class UDamageUI;

UCLASS()
class PROJECT_IK_API AUnit : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();
	const UCharacterStatComponent* GetCharacterStat() const;
	FVector GetForwardDir() const;
	void SetForwardDir(const FVector& Forward_Dir);

	UFUNCTION()
	virtual void GetDamage(float damage, TWeakObjectPtr<AActor> attacker) override;

	UFUNCTION(BlueprintCallable)
	void Heal(float heal);

	UFUNCTION(BlueprintCallable)
	void ApplyBuff(FBuff buff);

	UFUNCTION(BlueprintCallable)
	bool RemoveBuff(FName BuffName);

	UFUNCTION()
	virtual void GetStunned();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void Die() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UCharacterStatComponent* character_stat_component_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UWidgetComponent* hp_UI_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	FVector forward_dir_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* stunned_montage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageUI", meta = (AllowPrivateAccess = "true"))
	UObjectPoolComponent* object_pool_component_;
};
