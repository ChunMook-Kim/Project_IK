/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.05.2024
Summary : Source file for texture manager.
					It loads all textures using in the game at the beginning of the game.
					Provide when codes needed.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/TextureManager.h"

void UTextureManager::InitializeTextures()
{
	textures_.Add(ETextureID::CheckIcon, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/check_icon.check_icon")));
	textures_.Add(ETextureID::DamageIcon, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/damage_icon.damage_icon")));
	textures_.Add(ETextureID::DefaultPortrait, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/default_portrait.default_portrait")));
	textures_.Add(ETextureID::EnemyIcon, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/enemy_icon.enemy_icon")));
	textures_.Add(ETextureID::FireRange, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/fire_range.fire_range")));
	textures_.Add(ETextureID::FireRateBurst, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/fire_rate_burst.fire_rate_burst")));
	textures_.Add(ETextureID::HighlightImage, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/highlight_image.highlight_image")));
	textures_.Add(ETextureID::HPPotion, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/HP_potion.HP_potion")));
	textures_.Add(ETextureID::MissileItem, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/missile_item.missile_item")));
	textures_.Add(ETextureID::TakeItButton, LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/take_it_button.take_it_button")));
}

UTexture2D* UTextureManager::GetTexture(ETextureID Key) const
{
	if (textures_.Contains(Key))
	{
		return textures_[Key];
	}
	return nullptr;
}
