/**
 * @author      : Serhii Bura (serhiibura@gmail.com)
 * @file        : GreeterLevel
 * @created     : Sunday Jul 31, 2022 15:48:40 EEST
 */

#ifndef __GREETER_LEVEL_H__
#define __GREETER_LEVEL_H__

#include "IGameLevelFactory.h"

class GreeterLevel : public IGameLevelFactory
{
public:
	GreeterLevel();
	virtual ~GreeterLevel();

	virtual bool GenerateLevel() override;
	virtual void ProcessActor(AActor* actor) override;

private:
	AActor* pTextActor;
};

#endif /* __GREETER_LEVEL_H__ */
