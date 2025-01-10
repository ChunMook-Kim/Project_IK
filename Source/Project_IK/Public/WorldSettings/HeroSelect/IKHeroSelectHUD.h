/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.07.2025
Summary : Header file for HUD that used in HeroSelectLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKHeroSelectHUD.generated.h"

class UMapWidget;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API AIKHeroSelectHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void OpenMapWidget();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UMapWidget> map_widget_class_;

protected:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TWeakObjectPtr<UMapWidget> map_widget_;

};
