// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeroUpgradeUI.generated.h"

class UCanvasPanel;
/**
 * 
 */
UCLASS()
class PROJECT_IK_API UHeroUpgradeUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UCanvasPanel* root_canvas_;
	
};
