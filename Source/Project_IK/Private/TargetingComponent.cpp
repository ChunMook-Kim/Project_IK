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

	InitializeTargetingVisuals();
}

void UTargetingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (targeting_visual_actor_)
	{
		targeting_visual_actor_->Destroy();
		targeting_visual_actor_ = nullptr;
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

void UTargetingComponent::StartTargeting(AActor* invoker, ETargetingMode mode, float Range, float Radius)
{
	is_targeting_ = true;
	invoker_ = invoker;
	current_mode_ = mode;
	current_tarrget_data_.range_ = Range;
	current_tarrget_data_.radius_ = Radius;


	range_decal_->DecalSize = FVector(current_tarrget_data_.range_);
	radius_decal_->DecalSize = FVector(current_tarrget_data_.radius_);

	switch (mode)
	{
	case ETargetingMode::None:
		break;
	case ETargetingMode::Actor:
		player_controller_->CurrentMouseCursor = EMouseCursor::Crosshairs;
		range_decal_->SetVisibility(true);
		break;
	case ETargetingMode::Location:
		player_controller_->CurrentMouseCursor = EMouseCursor::GrabHand;
		radius_decal_->SetVisibility(true);
		range_decal_->SetVisibility(true);
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
		if (GetWorld()->LineTraceSingleByChannel(hit_result, world_location, trace_end, ECC_Visibility))
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
	FVector owner_location = invoker_->GetActorLocation();
	if (FVector::DistXY(owner_location, target_location) >= current_tarrget_data_.range_)
	{
		current_tarrget_data_.target_location_ = ProjectPointOntoCircle(target_location, owner_location, current_tarrget_data_.range_);
	}
	else
	{
		current_tarrget_data_.target_location_ = target_location;
	}
	OnTargetDataSelected.Broadcast(current_tarrget_data_);
	StopTargeting();
}

void UTargetingComponent::InitializeTargetingVisuals()
{
	AActor* owner = GetOwner();
	if (owner)
	{
		FActorSpawnParameters spawn_params;
		spawn_params.Owner = GetOwner();

		// Spawn an actor for visual aids
		// PlayerController itself does not have a visual child actors because they do not have body that have visuals.
		targeting_visual_actor_ = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, spawn_params);

		if (targeting_visual_actor_)
		{
			USceneComponent* root_component = NewObject<USceneComponent>(targeting_visual_actor_, TEXT("RootComponent"));
			targeting_visual_actor_->SetRootComponent(root_component);
			root_component->RegisterComponent();

			range_decal_ = NewObject<UDecalComponent>(targeting_visual_actor_);
			range_decal_->SetupAttachment(root_component);
			range_decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
			range_decal_->SetVisibility(false);
			if (range_material_)
			{
				range_decal_->SetDecalMaterial(range_material_);
			}
			range_decal_->RegisterComponent();

			radius_decal_ = NewObject<UDecalComponent>(targeting_visual_actor_);
			radius_decal_->SetupAttachment(root_component);
			radius_decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
			if (radius_material_)
			{
				radius_decal_->SetDecalMaterial(radius_material_);
			}
			radius_decal_->SetVisibility(false);
			radius_decal_->RegisterComponent();
		}
	}
}

void UTargetingComponent::UpdateTargetingVisuals()
{
	FVector target_location = GetGroundLocation();
	FVector invoker_location = invoker_->GetActorLocation();
	if (FVector::DistXY(invoker_location, target_location) >= current_tarrget_data_.range_)
	{
		target_location = ProjectPointOntoCircle(target_location, invoker_location, current_tarrget_data_.range_);
	}

	if (current_mode_ == ETargetingMode::Actor)
	{
		// @@ TODO: Set location of radius_decal_ to caster's location
		//radius_decal_->SetWorldLocation(target_location);
		range_decal_->SetWorldLocation(invoker_location);
	}
	if (current_mode_ == ETargetingMode::Location)
	{

		radius_decal_->SetWorldLocation(target_location);
		range_decal_->SetWorldLocation(invoker_location);
	}
	if (current_mode_ == ETargetingMode::Direction)
	{
		// @@ TODO: Visuallize sector based on arc
		//radius_decal_->SetWorldLocation(target_location);
		range_decal_->SetWorldLocation(invoker_location);
	}
}

void UTargetingComponent::CleanupTargetingVisuals()
{
	if (range_decal_)
	{
		range_decal_->SetVisibility(false);
	}
	if (radius_decal_)
	{
		radius_decal_->SetVisibility(false);
	}
}

FVector UTargetingComponent::ProjectPointOntoCircle(const FVector& Point, const FVector& Origin, float Radius)
{
	FVector direction = Point - Origin;

	direction.Normalize();

	FVector result = Origin + direction * Radius;

	return result;
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
