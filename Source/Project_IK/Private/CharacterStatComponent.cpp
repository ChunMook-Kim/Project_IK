/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Source file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "CharacterStatComponent.h"

// Sets default values
ACharacterStatComponent::ACharacterStatComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterStatComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

