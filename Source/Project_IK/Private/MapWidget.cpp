// Fill out your copyright notice in the Description page of Project Settings.


#include "MapWidget.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/IKGameInstance.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Rendering/DrawElements.h"

#include "IKMaps.h"

UMapWidget::UMapWidget(const FObjectInitializer& object_initializer)
	: Super::UUserWidget(object_initializer)
{
	canvas_panel_ = nullptr;
}

bool UMapWidget::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		return false;
	}

	// I don't know reason why but it should be in this function.
	InitializeWidgetTree();


	return true;
}

int32 UMapWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// Call the parent implementation first
	int32 CurrentLayer = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	// Define the start and end points for the line
	FVector2D StartPoint = FVector2D(0, 0);  // Top-left corner
	FVector2D EndPoint = AllottedGeometry.GetLocalSize();  // Bottom-right corner based on widget size

	// Define color and thickness
	FLinearColor LineColor = FLinearColor::Red;
	float LineThickness = 2.0f;
	
	TArray<FVector2f> tmp;
	// Draw the line
	//FSlateDrawElement::MakeLines(OutDrawElements, CurrentLayer, AllottedGeometry.ToPaintGeometry(), tmp);

	// Increase the layer ID if you plan to add more elements later
	return CurrentLayer + 1;
	/*
	Super::NativePaint(context);

	FVector2D NodeA(0, 0);
	FVector2D NodeB(context.AllottedGeometry.GetLocalSize());

	FLinearColor LineColor = FLinearColor::Red;
	float LineThickness = 5.0f;

	UE_LOG(LogTemp, Warning, TEXT("OnPaint has been called!"));

	UWidgetBlueprintLibrary::DrawLine(context, NodeA, NodeB, LineColor, true, LineThickness);*/
}

void UMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeButtons();
}

void UMapWidget::InitializeWidgetTree()
{
	canvas_panel_ = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("TestPanel"));
	WidgetTree->RootWidget = canvas_panel_;
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
				const FMapNode& node = maps_->GetNode(j, i);
				if (node.type == NodeType::None)
				{
					continue;
				}

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