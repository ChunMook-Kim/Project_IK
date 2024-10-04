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
#include "Components/Button.h"
#include "SkillBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API USkillBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void TMP(const FTargetData& TargetData);

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* skill_button_;

	UPROPERTY(VisibleAnywhere)
	class UTargetingComponent* targeting_component_;
};
