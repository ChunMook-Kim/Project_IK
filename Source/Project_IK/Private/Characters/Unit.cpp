/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for unit.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WidgetComponent.h"

#include "UI/HitPointsUI.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	character_stat_component_ = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CharacterStatComponent"));
	hp_UI_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP UI"));
	
	hp_UI_->SetWidgetSpace(EWidgetSpace::Screen);
	hp_UI_->SetDrawSize({100, 50});
	hp_UI_->SetupAttachment(RootComponent);

	character_stat_component_->Die.AddDynamic(this, &AUnit::Die);

	//UI를 위한 경로가 문자열로 되어있으므로, UI BP의 경로 변경시 같이 변경해야 한다.
	static ConstructorHelpers::FClassFinder<UHitPointsUI> UI_BP(TEXT("/Game/__BluePrints/BP_HitPointsUI"));
	if(UI_BP.Succeeded() && UI_BP.Class != nullptr)
	{
		hp_UI_->SetWidgetClass(UI_BP.Class);
	}
}

UCharacterStatComponent* AUnit::GetCharacterStat() const
{
	return character_stat_component_;
}

FVector AUnit::GetForwardDir() const
{
	return forward_dir_;
}

void AUnit::SetForwardDir(const FVector& Forward_Dir)
{
	forward_dir_ = Forward_Dir;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	Cast<UHitPointsUI>(hp_UI_->GetWidget())->BindCharacterStat(character_stat_component_);
}

void AUnit::GetDamage(float damage, TWeakObjectPtr<AActor> attacker)
{
	character_stat_component_->GetDamage(damage, attacker);
}

void AUnit::Die()
{
	Destroy();
}
