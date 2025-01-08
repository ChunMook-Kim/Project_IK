/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.08.2025
Summary : Source file for Player Controller in GotchaLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/GotchaWorld/IKGotchaPlayerController.h"

void AIKGotchaPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Enable the mouse cursor
    bShowMouseCursor = true;
    SetInputMode(FInputModeGameAndUI());
}
