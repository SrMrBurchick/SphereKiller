// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereKillerUI.h"
#include "Components/TextBlock.h"

void USphereKillerUI::NativeOnInitialized()
{
	// Stub
}

void USphereKillerUI::setData(int spheresCount, int wavesCount)
{
	SPHERES_CNT->SetText(FText::AsNumber(spheresCount));
	WAVES_CNT->SetText(FText::AsNumber(wavesCount));
}
