/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.05.2024
Summary : Header file for texture manager.
					It loads all textures using in the game at the beginning of the game.
					Provide when codes needed.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TextureManager.generated.h"

UENUM(BlueprintType)
enum class ETextureID : uint8
{
	CheckIcon UMETA(DisplayName = "CheckIcon"),
	DamageIcon UMETA(DisplayName = "DamageIcon"),
	DefaultPortrait UMETA(DisplayName = "DefaultPortrait"),
	EnemyIcon UMETA(DisplayName = "EnemyIcon"),
	FireRange UMETA(DisplayName = "FireRange"),
	FireRateBurst UMETA(DisplayName = "FireRateBurst"),
	HighlightImage UMETA(DisplayName = "HighlightImage"),
	HPPotion UMETA(DisplayName = "HPPotion"),
	MissileItem UMETA(DisplayName = "MissileItem"),
	TakeItButton UMETA(DisplayName = "TakeItButton"),
};

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UTextureManager : public UObject
{
	GENERATED_BODY()
public:
	void InitializeTextures();

	UTexture2D* GetTexture(ETextureID Key) const;
private:
	TMap<ETextureID, UTexture2D*> textures_;
};
