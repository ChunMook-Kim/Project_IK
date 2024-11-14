/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Source file for Player Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/IKPlayerController.h"

#include "Components/TargetingComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IKHUD.h"

AIKPlayerController::AIKPlayerController()
	: Super::APlayerController()
{
	targeting_component_ = CreateDefaultSubobject<UTargetingComponent>(TEXT("Targeting Component"));
}

void AIKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(player_input_mapping_context, 0);
	}
	
}

void AIKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(InputComponent))
	{
		enhanced_input_component->BindAction(toggle_map_action, ETriggerEvent::Triggered, this, &AIKPlayerController::ToggleMap);
	}
}

UTargetingComponent* AIKPlayerController::GetTargetingComponent()
{
	return targeting_component_;
}

void AIKPlayerController::ToggleMap()
{
	AIKHUD* HUD = Cast<AIKHUD>(GetHUD());

	if (HUD)
	{
		HUD->ToggleMapWidget();
	}
}
