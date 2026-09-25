For now I will combine rules, notes, and to-do in the same document. I may separate these later or move them off the repo.
## 1. Rules:
#### General:
Some simple ideas to remember, may change and develop as time goes on.
1. We are not aiming for pure ECS. Components are to-be defined, but will not strictly contain data.
2. Unlike almost every other engine project, we will not focus on rendering first. Instead we will first make a basic def-ref architecture and runtime, then immediately focus on role-playing game data and systems.
	1. With this approach, the same data and systems could easily be ported into any existing engine such as Unreal or Unity. This lets me work on the "fun stuff" sooner than later, and gives me usable code for making RPG games even if I abandon the project. That is what professionals would call, self-awareness.
#### Style Guide:
My personal style guide is a bit convoluted and I'm sure I will contradict it multiple times between commits, so instead of publishing it and compelling myself to clean it up, I will post a summary below.
##### Summary:
- Base of Microsoft style; No published doc, but viewable through various source code and documentation. I.e. implied style.
- `PascalCase` types and methods
- `I` for interfaces
- `enum class` : when applicable, choose size-appropriate numerical
	- I.e. less than 255 types? then `enum class Types : uint8_t`
- `m_camelCase` private members
- `camelCase` local members
- `PascalCase` constants
- `UPPER_SNAKE` macros
- Allman braces
	- The superior indentation style
- Tabs, tabs everywhere
- Left-aligned pointers
	- data type gets the asterisk / pointer, not the variable name
- `#pragma once` headers
	- No precompiled headers
- `PascalCase` filenames
- `lowercase` namespaces
- `kebab-case` repos
- The last three are the least important. This is just what I've gotten used to.
## 2. File Hierarchy:
1. **Core/** : Base objects that require no other engine-defined data
2. **Data/** : Authored or authorable engine data
3. **World/** : In-world or runtime data and systems
4. **Platform/** : OS utility functions, that don't fit elsewhere. Some don't belong in the engine atm
5. **Console/** : Clone of my cmd-handler repo. Console mainly used for testing
6. **ThirdParty/** : Self explanatory
#### Data Files:
1. Defs
2. DefTable / DefRegistry (would be a separate class to handle creation, if we do so)
3. Module, ModuleLoader, ~something defining load order
4. Serializer (JSON read/write data machinery / system)
5. (TBD) Field-bag and FieldPatch / FieldOverride / other related. For holding dynamic list of fields
#### World Files:
1. Components
	1. Component base virtualized object, Component.h
	2. /Components/ component child objects
2. 
## 3. To-Do:
1. Create InstanceTable
2. Create Component base
	1. Create some components
3. Create World class and data
4. Create RPG character sheet data
	1. Perks, Classes, Rulesets, Abilities, etc.
5. Create a basic runtime
	1. The faster we can simulate Actors and basic World data, the faster we can better test and physically see what we are building. I.e. building stat and character data is boring when there are no characters to test