// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapWidget.generated.h"

class UButton;
class UIKMaps;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UMapWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	void InitializeButtons();

	UPROPERTY()
	UCanvasPanel* canvas_panel_;
	TArray<UButton*> buttons_;
	const UIKMaps* maps_;
};
