/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Passive Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PassiveMechanics.generated.h"

class AGun;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UPassiveMechanics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPassiveMechanics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ActivePassiveSkill();
	bool IsPassiveAvailable() const;
	float GetHoldTime() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveMechanics", meta = (AllowPrivateAccess = "true"))
	float duration_ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveMechanics", meta = (AllowPrivateAccess = "true"))
	float cool_down_ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveMechanics", meta = (AllowPrivateAccess = "true"))
	float hold_time_ = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveMechanics", meta = (AllowPrivateAccess = "true"))
	bool is_activated_ = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveMechanics", meta = (AllowPrivateAccess = "true"))
	UClass* passive_class_ = nullptr;
};
