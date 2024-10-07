/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.03.2024
Summary : Source file for Targeting component.
					Before skills invoked, it helps to choose target.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "TargetingComponent.h"

#include "GameFramework/PlayerController.h"
#include "Components/DecalComponent.h"
#include "IKPlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	is_targeting_ = false;
	current_mode_ = ETargetingMode::None;
}


// Called when the game starts
void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	player_controller_ = Cast<AIKPlayerController>(GetOwner());
	
	AActor* owner = GetOwner();
	if (owner)
	{
		targeting_decal_ = NewObject<UDecalComponent>(owner);
		targeting_decal_->SetDecalMaterial(targeting_decal_material_);
		targeting_decal_->RegisterComponent();
		targeting_decal_->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		targeting_decal_->DecalSize = FVector(500.f, 500.f, 500.f);
		targeting_decal_->SetVisibility(true);

		aoe_indicator_ = NewObject<UStaticMeshComponent>(owner);
		aoe_indicator_->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		aoe_indicator_->SetStaticMesh(aoe_indicator_mesh_);
		aoe_indicator_->RegisterComponent();
		aoe_indicator_->SetVisibility(true);
	}
}


// Called every frame
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!is_targeting_ || !player_controller_)
	{
		return;
	}

	UpdateTargetingVisuals();

	if (player_controller_->WasInputKeyJustPressed(EKeys::RightMouseButton))
	{
		OnTargetingCanceled.Broadcast();
		StopTargeting();
		return;
	}

	if (player_controller_->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		switch (current_mode_)
		{
		case ETargetingMode::None:
			OnTargetDataSelected.Broadcast(current_tarrget_data_);
			StopTargeting();
			break;
		case ETargetingMode::Actor:
			HandleActorTargeting();
			break;
		case ETargetingMode::Location:
			HandleLocationTargeting();
			break;
		case ETargetingMode::Direction:
			break;
		default:
			break;
		}
	}
}

void UTargetingComponent::StartTargeting(ETargetingMode mode, float Range, float Radius)
{
	is_targeting_ = true;
	current_mode_ = mode;
	current_tarrget_data_.range_ = Range;
	current_tarrget_data_.radius_ = Radius;

	switch (mode)
	{
	case ETargetingMode::None:
		break;
	case ETargetingMode::Actor:
		player_controller_->CurrentMouseCursor = EMouseCursor::Crosshairs;
		break;
	case ETargetingMode::Location:
		player_controller_->CurrentMouseCursor = EMouseCursor::GrabHand;
		if (Radius > 0.f)
		{
			if (aoe_indicator_)
			{
				aoe_indicator_->SetVisibility(true);
				aoe_indicator_->SetWorldScale3D(FVector(Radius / 50.f));
			}
		}
		else
		{
			targeting_decal_->SetVisibility(true);
		}
		break;
	case ETargetingMode::Direction:
		break;
	default:
		break;
	}
}

void UTargetingComponent::StopTargeting()
{
	is_targeting_ = false;
	current_mode_ = ETargetingMode::None;
	player_controller_->CurrentMouseCursor = EMouseCursor::Default;
	CleanupTargetingVisuals();
}

void UTargetingComponent::HandleActorTargeting()
{
	FHitResult hit_result;
	FVector world_location, world_direction;

	if (player_controller_->DeprojectMousePositionToWorld(world_location, world_direction))
	{
		FVector trace_end = world_location + (world_direction * current_tarrget_data_.range_);
		if(GetWorld()->LineTraceSingleByChannel(hit_result, world_location, trace_end, ECC_Visibility))
		{
			if (AActor* hit_actor = hit_result.GetActor())
			{
				if (IsValidTarget(hit_actor))
				{
					current_tarrget_data_.target_actor_ = hit_actor;
					current_tarrget_data_.target_location_ = hit_result.Location;
					OnTargetDataSelected.Broadcast(current_tarrget_data_);
					StopTargeting();
				}
			}
		}
	}
}

void UTargetingComponent::HandleLocationTargeting()
{
	FVector target_location = GetGroundLocation();

	// Check if location is within range
	FVector owner_location = GetOwner()->GetActorLocation();
	if (FVector::DistXY(owner_location, target_location) <= current_tarrget_data_.range_)
	{
		current_tarrget_data_.target_location_ = target_location;
		OnTargetDataSelected.Broadcast(current_tarrget_data_);
		StopTargeting();
	}
}

void UTargetingComponent::UpdateTargetingVisuals()
{
	if (current_mode_ == ETargetingMode::Location)
	{
		FVector target_location = GetGroundLocation();

		if (current_tarrget_data_.radius_ > 0.f)
		{
			aoe_indicator_->SetWorldLocation(target_location);
		}
		else
		{
			targeting_decal_->SetWorldLocation(target_location);
		}
	}
}

void UTargetingComponent::CleanupTargetingVisuals()
{
	if (targeting_decal_)
	{
		targeting_decal_->SetVisibility(false);
	}
	if (aoe_indicator_)
	{
		aoe_indicator_->SetVisibility(false);
	}
}

bool UTargetingComponent::IsValidTarget(AActor* target) const
{
	return false;
}

FVector UTargetingComponent::GetGroundLocation() const
{
	FHitResult hit_result;
	FVector world_location, world_direction;

	if (player_controller_->DeprojectMousePositionToWorld(world_location, world_direction))
	{
		FVector trace_end = world_location + (world_direction * 10000.f);
		FCollisionQueryParams query_params;
		query_params.AddIgnoredActor(GetOwner());

		if (GetWorld()->LineTraceSingleByChannel(hit_result, world_location, trace_end, ECC_Visibility, query_params))
		{
			return hit_result.Location;
		}
	}
	return FVector::ZeroVector;
}
