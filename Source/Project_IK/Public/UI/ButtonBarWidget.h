/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Header file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonBarWidget.generated.h"

class UButton;
class USkillContainer;
class UItemInventory;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UButtonBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnSkillButtonClicked0();

	UFUNCTION()
	void OnSkillButtonClicked1();

	UFUNCTION()
	void OnSkillButtonClicked2();

	UFUNCTION()
	void OnSkillButtonClicked3();

	UFUNCTION()
	void OnItemButtonClicked0();

	UFUNCTION()
	void OnItemButtonClicked1();

	UFUNCTION()
	void OnItemButtonClicked2();

	UFUNCTION()
	void InvokeSkills(const FTargetData& TargetData);

	UFUNCTION()
	void FindCharacters();

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* skill_button_0_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* skill_button_1_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* skill_button_2_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* skill_button_3_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* item_button_0_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* item_button_1_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* item_button_2_;

	UPROPERTY(VisibleAnywhere)
	class UTargetingComponent* targeting_component_;

	UPROPERTY()
	TArray<AActor*> characters_;

	UPROPERTY()
	TArray<USkillContainer*> skill_containers_;

	int32 selected_item_index_;
	int32 caster_;

	UPROPERTY(VisibleAnywhere, meta = (PrivateAccessAllow))
	TWeakObjectPtr<UItemInventory> item_inventory_;
};