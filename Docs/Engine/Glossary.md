Definitions with examples, notes, etc.
Terms may change over time, as the project progresses.
## Terms:
#### Def
- An authored record made in the editor, saved to a Module file. Defs are loaded into the DefTable. Defs can be overridden by other Modules.
#### Instance
- In-world objects made from a Def. Contains list of Components.
#### Sub-Record
- Sub-object within a certain Def, does not have a DefId of its own.
- Example: QuestStage, LootTableEntry, DialogueBranch.
#### Component
- An object of functionality-defining fields attached to an Instance.
- Example: FactionComponent, InventoryComponent, HealthComponent, etc.
#### State
- Any game data progressed during runtime that would be saved. The diff between a freshly started game and a save file afterwards.
- Defs are authored content, Instance are objects in-memory, saved progression is State.
- Example: QuestState, FactionState, or all in GameState.
#### Archetype
- A Def that other Defs can inherit or use as a template.
- Example: bandit_base -> bandit_archer; skeleton_base -> skeleton_elite
#### Module
- A content file or folder holding Defs.
- Example: base.mod, expansion.mod, funmod.mod
- Modules may include Defs of the same EditorId, the later of which overrides the former.
	- I.e. Modules can be used in updates, DLC, or mods to override existing content.
#### Ruleset
- The game config that tells the engine which RPG elements and rules are active.
- Example:
	- Skyrim tells the engine to give xp by doing.
	- Fallout 4 tells the engine to give xp by quest completion and killing.
- The thought is we build out varying options within the engine, which is easier in our example by focusing on RPGs.
#### System
- Functionality-driven code that runs every tick, over Instances with certain components.
	- Any code running each tick, is in a System.
- Systems are registered in the SystemRegistry and can be overridden by other Modules, the same way that Defs can.
- Systems are ran in a fixed order.
- Example: MovementSystem, PhysicsSystem, etc.
#### Service
- Provided functions that can reach across varying object types, called on-demand.
- Engine-provided code that can interact with objects per functionality, that is NOT ran per-tick in a separate System.
- Example: InventoryService, StatResolverService, etc.
#### Policy
- A specific rule within a Ruleset.
- How a game customizes whether or not to utilize a core engine / game system, or change its functionality.
- Example: ProgressionPolicy, LevelUpPolicy, PerkPolicy
	- Does my RPG game have classes? What does class mean in this game? Does picking 'Wizard' just level magic abilities up faster, or completely lock me to only using magic?
	- Do I level up one-handed by slashing enemies? Or do I add attributes to a one-handed skill when I level up from quests?
#### Cell
- Area of game space that owns Instances, loading and unloading them as a unit.
- What other engines might call a "scene" or "level".
	- "scene" keyword will be reserved for If* we ever have a cutscene system, "level" is too generic in an RPG.
- Example: OpenWorldArea01, TestArea, ArenaDungeonBasement, etc.
#### World
- What this engine treats as the root for runtime data.
- Owns the InstanceTable, state data, per-tick / System order.
	- Reads the DefTable, but does not own it as that is not live data.
#### Actor
- Any character or creature with health, position, and an AI cycle.
#### Player
- The Actor with player controls.
- Not a separate class, but an Actor with a PlayerController component.
#### Faction
- Def for a group with ranks and relations to other groups.
