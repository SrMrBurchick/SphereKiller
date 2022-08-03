/**
 * @author      : Serhii Bura (serhiibura@gmail.com)
 * @file        : IGameLevelFactory
 * @created     : Sunday Jul 31, 2022 15:30:23 EEST
 */

#include "IGameLevelFactory.h"

// Copy constructor and operator
IGameLevelFactory& IGameLevelFactory::operator=(const IGameLevelFactory& factory)
{
	if (factory.mActorList != nullptr) {
		mActorList = factory.mActorList;
	}

	return *this;
}

IGameLevelFactory::IGameLevelFactory(const IGameLevelFactory& factory)
{
	if (factory.mActorList != nullptr) {
		mActorList = factory.mActorList;
	}
}

void IGameLevelFactory::InitGameActors(ActorsList list)
{
	if (nullptr == list) {
		UE_LOG(LogTemp, Log, TEXT("Invalid Actor list"));

		return;
	}

	mActorList = list;
}
