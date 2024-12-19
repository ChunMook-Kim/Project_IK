/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.19.2024
Summary : Header file for an actor that holds damage UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageUI.generated.h"

class UDamageWidget;
class UWidgetComponent;

UCLASS(Blueprintable)
class PROJECT_IK_API ADamageUI : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageUI();

	UFUNCTION(BlueprintCallable)
	void SetHealAmount(float HealAmount);

	UFUNCTION(BlueprintCallable)
	void SetDamageAmount(float DamageAmount);

	UFUNCTION(BlueprintCallable)
	void SetMissed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage UI")
	TSubclassOf<UDamageWidget> damage_widget_class_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage UI", meta = (AllowPrivateAccess = true))
	UWidgetComponent* widget_component_;

};
