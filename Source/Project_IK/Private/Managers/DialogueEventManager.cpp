/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.23.2024
Summary : Source file for Dialogue Event Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/DialogueEventManager.h"

void UDialogueEventManager::RunEvent(EDialogueEventType event_type) const
{
	switch (event_type)
	{
	case EDialogueEventType::GetRandomItem:
		GetRandomItem();
		break;
		
	case EDialogueEventType::GetRandomDP:
		GetRandomDP();
		break;
		
	case EDialogueEventType::GetFireRateBurstDP:
		GetFireRateBurstDP();
		break;
		
	case EDialogueEventType::GetFireRangeDP:
		GetFireRangeDP();
		break;
	}
}

void UDialogueEventManager::GetRandomDP() const
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueEventManager::GetRandomDP"));
}

void UDialogueEventManager::GetRandomItem() const
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueEventManager::GetRandomItem"));
}

void UDialogueEventManager::GetFireRateBurstDP() const
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueEventManager::GetFireRateBurstDP"));
}

void UDialogueEventManager::GetFireRangeDP() const
{
	UE_LOG(LogTemp, Warning, TEXT("UDialogueEventManager::GetFireRangeDP"));
}
