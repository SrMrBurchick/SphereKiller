// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "SphereKillerUI.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SPHEREKILLER_API USphereKillerUI : public UUserWidget
{
	GENERATED_BODY()	
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SPHERES_CNT;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WAVES_CNT;

	void setData(int spheresCount, int wavesCount);

protected:
	virtual void NativeOnInitialized() override;
};
