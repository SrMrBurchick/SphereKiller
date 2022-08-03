/**
 * @author      : Serhii Bura (serhiibura@gmail.com)
 * @file        : IGameLevelFactory
 * @description : Factory for creating and processing levels
 * @created     : Sunday Jul 31, 2022 14:59:06 EEST
 */

#ifndef __IGAME_LEVEL_FACTORY_H__
#define __IGAME_LEVEL_FACTORY_H__

#include <list>
#include <memory>

#include "GameFramework/Actor.h"

using ActorsList = std::shared_ptr<std::list<AActor*>>;

class IGameLevelFactory {
public:
	virtual ~IGameLevelFactory() = default;

	// Copy constructor and operator
	IGameLevelFactory& operator=(const IGameLevelFactory& factory);
	IGameLevelFactory(const IGameLevelFactory& factory);

	// Methods for subclasses
	virtual bool GenerateLevel() = 0;
	virtual void ProcessActor(AActor* actor) = 0;

	void InitGameActors(ActorsList list);

protected:
	IGameLevelFactory() = default;
	ActorsList mActorList;
};

#endif /* __IGAME_LEVEL_FACTORY_H__ */
