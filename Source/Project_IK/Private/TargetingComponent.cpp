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


#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/DecalComponent.h"
#include "IKPlayerController.h"
#include "IKGameModeBase.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	is_targeting_ = false;
	current_mode_ = ETargetingMode::None;

	static ConstructorHelpers::FObjectFinder<UMaterial> HighlightMat(TEXT("/Game/Materials/SelectionMat.SelectionMat"));
	if (HighlightMat.Succeeded())
	{
		highlight_material_ = UMaterialInstanceDynamic::Create(HighlightMat.Object, this);
	}
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
			OnTargetDataSelected.Broadcast(current_target_data_);
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

void UTargetingComponent::StartSkillTargeting(AActor* invoker, ETargetingMode mode, float Range, float Radius)
{
	is_targeting_ = true;
	invoker_ = invoker;
	current_mode_ = mode;
	current_target_data_.range_ = Range;
	current_target_data_.radius_ = Radius;


	range_decal_->DecalSize = FVector(current_target_data_.range_);
	radius_decal_->DecalSize = FVector(current_target_data_.radius_);

	switch (mode)
	{
	case ETargetingMode::None:
		break;
	case ETargetingMode::Actor:
		player_controller_->CurrentMouseCursor = EMouseCursor::Crosshairs;
		radius_decal_->SetVisibility(false);
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

void UTargetingComponent::StartItemTargeting(ETargetingMode mode, float Range, float Radius)
{
	is_targeting_ = true;
	invoker_ = nullptr;
	current_mode_ = mode;
	current_target_data_.range_ = Range;
	current_target_data_.radius_ = Radius;


	range_decal_->DecalSize = FVector(current_target_data_.range_);
	radius_decal_->DecalSize = FVector(current_target_data_.radius_);

	switch (mode)
	{
	case ETargetingMode::None:
		break;
	case ETargetingMode::Actor:
		player_controller_->CurrentMouseCursor = EMouseCursor::Crosshairs;
		radius_decal_->SetVisibility(false);
		range_decal_->SetVisibility(false);
		break;
	case ETargetingMode::Location:
		player_controller_->CurrentMouseCursor = EMouseCursor::GrabHand;
		radius_decal_->SetVisibility(true);
		range_decal_->SetVisibility(false);
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

	FVector target_location = GetGroundLocation();
	AActor* closest_actor = FindClosestActor(target_location);

	current_target_data_.target_location_ = target_location;
	current_target_data_.target_actor_ = closest_actor;

	OnTargetDataSelected.Broadcast(current_target_data_);
	StopTargeting();
}

void UTargetingComponent::HandleLocationTargeting()
{
	FVector target_location = GetGroundLocation();

	current_target_data_.target_location_ = ClampingOntoInvoker(target_location);

	OnTargetDataSelected.Broadcast(current_target_data_);
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
	target_location = ClampingOntoInvoker(target_location);

	FVector invoker_location;
	if (invoker_)
	{
		invoker_location = invoker_->GetActorLocation();
	}
	else
	{
		// set its location to be logically invalid
		invoker_location = FVector(10000, 10000, 10000);
	}

	if (current_mode_ == ETargetingMode::Actor)
	{
		// @@ TODO: Set location of radius_decal_ to caster's location
		//radius_decal_->SetWorldLocation(target_location);
		range_decal_->SetWorldLocation(invoker_location);

		ApplyMaterialHighlight(FindClosestActor(GetGroundLocation()));
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
	if (previously_chosen_actor_)
	{
		USkeletalMeshComponent* previous_mesh = previously_chosen_actor_->FindComponentByClass<USkeletalMeshComponent>();
		for (int32 i = 0; i < previous_mesh->GetNumMaterials(); i++)
		{
			previous_mesh->SetMaterial(i, original_materials_[i]);
		}

		previously_chosen_actor_ = nullptr;
	}

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

FVector UTargetingComponent::ClampingOntoInvoker(FVector TargetLocation)
{
	// Check if location is within range
	if (invoker_)
	{
		FVector owner_location = invoker_->GetActorLocation();
		if (FVector::DistXY(owner_location, TargetLocation) >= current_target_data_.range_)
		{
			return ProjectPointOntoCircle(TargetLocation, owner_location, current_target_data_.range_);
		}
	}

	return TargetLocation;
}

AActor* UTargetingComponent::FindClosestActor(FVector TargetLocation)
{
	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!game_mode)
	{
		return nullptr;
	}

	auto characters = game_mode->GetHeroContainers();
	auto enemies = game_mode->GetEnemyContainers();
	AActor* closest_actor = nullptr;
	float closest_distance_sq = MAX_FLT;

	for (AActor* actor : characters)
	{
		if (actor)
		{
			float distance_sq = FVector::DistSquared(TargetLocation, actor->GetActorLocation());
			if (distance_sq < closest_distance_sq)
			{
				closest_distance_sq = distance_sq;
				closest_actor = actor;
			}
		}
	}

	for (AActor* actor : enemies)
	{
		if (actor)
		{
			float distance_sq = FVector::DistSquared(TargetLocation, actor->GetActorLocation());
			if (distance_sq < closest_distance_sq)
			{
				closest_distance_sq = distance_sq;
				closest_actor = actor;
			}
		}
	}

	return closest_actor;
}

void UTargetingComponent::ApplyMaterialHighlight(AActor* target)
{
	if (!target) return;

	if (previously_chosen_actor_ != target)
	{
		if (previously_chosen_actor_)
		{
			USkeletalMeshComponent* previous_mesh = previously_chosen_actor_->FindComponentByClass<USkeletalMeshComponent>();
			for (int32 i = 0; i < previous_mesh->GetNumMaterials(); i++)
			{
				previous_mesh->SetMaterial(i, original_materials_[i]);
			}
		}

		// Store original materials
		USkeletalMeshComponent* MeshComponent = target->FindComponentByClass<USkeletalMeshComponent>();
		if (MeshComponent)
		{
			original_materials_.Empty();
			for (int32 i = 0; i < MeshComponent->GetNumMaterials(); i++)
			{
				original_materials_.Add(MeshComponent->GetMaterial(i));
			}

			// Apply highlight material to all slots
			for (int32 i = 0; i < MeshComponent->GetNumMaterials(); i++)
			{
				MeshComponent->SetMaterial(i, highlight_material_);
			}
		}

		previously_chosen_actor_ = target;
	}
}
