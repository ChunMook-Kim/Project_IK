// Fill out your copyright notice in the Description page of Project Settings.


#include "MapWidget.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/IKGameInstance.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"

#include "Components/CanvasPanelSlot.h"
#include "Engine/Texture2D.h"
#include "IKMaps.h"

void UMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	canvas_panel_ = NewObject<UCanvasPanel>(this);
	
	if (canvas_panel_)
	{
		InitializeButtons();
	}

	
}

void UMapWidget::InitializeButtons()
{
	auto ik_game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	FVector2D button_size(50.f, 50.f);

	if (ik_game_instance)
	{
		maps_ = ik_game_instance->GetMapPtr();

		for (int32 i = 0; i < maps_->GetHeight(); i++)
		{
			for (int32 j = 0; j < maps_->GetWidth(); j++)
			{
				UButton* button = NewObject<UButton>();
				// @@TODO: Set widget styles properly to look like a image button
				//button->WidgetStyle.SetNormal()

				UCanvasPanelSlot* button_slot = canvas_panel_->AddChildToCanvas(button);
				if (button_slot)
				{
					FVector2D position = FVector2D(j * button_size.X, (maps_->GetHeight() - 1 - i) * button_size.Y);
					// @@TODO: Set anchors properly
					//button_slot->SetAnchors()
					button_slot->SetPosition(position);
					button_slot->SetSize(button_size);
				}

				buttons_.Add(button);
			}
		}
	}
}
