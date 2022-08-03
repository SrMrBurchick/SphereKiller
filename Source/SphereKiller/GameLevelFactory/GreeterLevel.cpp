/**
 * @author      : Serhii Bura (serhiibura@gmail.com)
 * @file        : GreeterLevel
 * @created     : Sunday Jul 31, 2022 15:54:02 EEST
 */

#include "GreeterLevel.h"

GreeterLevel::GreeterLevel()
	: IGameLevelFactory()
{
	pTextActor = nullptr;
}

GreeterLevel::~GreeterLevel()
{
}

bool GreeterLevel::GenerateLevel()
{
	if (nullptr == mActorList) {
		UE_LOG(LogTemp, Error, TEXT("Actor list not initialized!"));

		return false;
	}

	return true;
}

void GreeterLevel::ProcessActor(AActor* actor)
{
	if (nullptr == mActorList) {
		UE_LOG(LogTemp, Error, TEXT("Actor list not initialized!"));

		return;
	}

}
