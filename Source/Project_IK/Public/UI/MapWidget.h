/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.05.2024
Summary : Header file for displaying maps.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

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
	
public:
	UMapWidget(const FObjectInitializer& object_initializer);
	virtual bool Initialize() override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:
	virtual void NativeConstruct() override;

	void InitializeWidgetTree();
	void InitializeButtons();
	inline FVector2D CalculateButtonPosition(int32 row, int32 col, const FVector2D& buttonSize) const;
	inline FVector2f CalculateButtonCenterPosition(const FVector2D& position, const FVector2D& buttonSize) const;

	UFUNCTION()
	void OpenLevel();

	UPROPERTY()
	UCanvasPanel* canvas_panel_;
	TArray<UButton*> buttons_;
	const UIKMaps* maps_;

	TArray<FVector2f> path_points_;
};
