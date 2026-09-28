#pragma once

namespace rogue
{
	//declarations of each system, in one file
	//for now, we will have a fixed list and make a SystemRegistry later for dynamic list

	class World;
	
	void UpdatePlayerControl(World& world, float deltaTime);
	void UpdateMovement(World& world, float deltaTime);
	void UpdateCombat(World& world, float deltaTime);
}