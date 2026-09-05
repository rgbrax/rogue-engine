#pragma once
#include "Data/ItemDef.h"

namespace rogue
{
	/* enum class ActorLevelType //#tbd move this to progression somewhere? idk
	{
		Static,
		ScalePlayerMultiply, //#tbd: please rename this good lord; i.e. 1.1x the player's level; use this and set to 1.0 for player's level
		ScalePlayerMinMax, //same as above, but with a min and max; i.e. a dragon's min level would be 30, a skeleton's max level would be 5
		RandomMinMax, //frick it, we ball		
	};

	//#tbd: move to progression or ruleset; this will vary by game; this specific example is more elder-scrolls like; prob wouldn't be an enum
	enum class ActorClass 
	{
		Warrior,
		Rogue,
		Archer,
		Thief,
		Battlemage,
		Wizard,
		Necromancer,
		Conjurer,
		Healer,
		Paladin
	};

	class ActorDef : public Def
	{
	public:
		std::string displayName = "";
		uint32_t health = 0; //#tbd: uint32 or float?;
		uint32_t level = 1; //use for Static ActorLevelType; 1 = default, 0 = unused
		uint32_t levelMin = 0; //use for ScaleMinMax ActorLevelType; 0 = unused or default
		uint32_t levelMax = 0; //use for ScaleMinMax ActorLevelType; 0 = unused or default
		float levelScale = 0.0f; //use for ScalePlayerMultiply; 0.0f = unused
		ActorClass characterClass = ActorClass::Warrior; //#tbd: rename?
		ActorLevelType characterLevelType = ActorLevelType::Static;
		bool isUnique = false;
		//#tbd: add abilities, skills, etc, etc.

		static const Schema& StaticSchema();
		const Schema& GetSchema() const override
		{
			return StaticSchema();
		}
	};*/
}
