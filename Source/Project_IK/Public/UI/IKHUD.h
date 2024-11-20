/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKHUD.generated.h"

class UCombatResultUI;
class ULevelEndUIManager;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKHUD : public AHUD
{
	GENERATED_BODY()
public:
	void ToggleMapWidget();
	
	UFUNCTION()
	void DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map);

protected:
	// Reference to the Widget Blueprint class to create
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> HUD_widget_class_;

	// Reference to the widget instance
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TWeakObjectPtr<UUserWidget> HUD_widget_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UCombatResultUI> combat_result_widget_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> map_widget_class_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TWeakObjectPtr<class ULevelEndUIManager> level_end_ui_manager_;

	virtual void BeginPlay() override;
};
