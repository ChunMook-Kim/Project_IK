/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.19.2024
Summary : Source file for an actor that holds damage UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/DamageUI.h"

#include "Components/WidgetComponent.h"
#include "UI/DamageWidget.h"

// Sets default values
ADamageUI::ADamageUI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	widget_component_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	SetRootComponent(widget_component_);
	widget_component_->SetWidgetSpace(EWidgetSpace::Screen);
	widget_component_->SetDrawSize(FVector2D(100.0));

}

void ADamageUI::SetHealAmount(float HealAmount)
{
	if (damage_widget_class_)
	{
		UDamageWidget* widget = Cast<UDamageWidget>(widget_component_->GetWidget());
		widget->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f));
		widget->SetDamageAmount(HealAmount);
	}
}

void ADamageUI::SetDamageAmount(float DamageAmount)
{
	if (damage_widget_class_)
	{
		UDamageWidget* widget = Cast<UDamageWidget>(widget_component_->GetWidget());
		widget->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));
		widget->SetDamageAmount(DamageAmount);
	}
}

void ADamageUI::SetMissed()
{
	if (damage_widget_class_)
	{
		UDamageWidget* widget = Cast<UDamageWidget>(widget_component_->GetWidget());
		widget->SetMissed();
	}
}

// Called when the game starts or when spawned
void ADamageUI::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* widget = CreateWidget<UDamageWidget>(GetWorld(), damage_widget_class_);
	widget_component_->SetWidget(widget);
}

