/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.28.2024
Summary : Header file of HUD for Gotcha level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKGotchaHUD.generated.h"

class UGotchaWidget;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKGotchaHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UGotchaWidget> gotcha_widget_class_;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TWeakObjectPtr<UGotchaWidget> gotcha_widget_;
};
