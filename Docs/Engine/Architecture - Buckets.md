# Engine Buckets:
Bucket is a general term to categorize "types" of content or code while developing the engine. I.e. when you add something to the core engine, it goes into one of these buckets.
## 1. Def
- Saved or authored content on-disk.
- Located in `/Data/Defs/.`
- Contained by `DefTable`.
- Named like `ExampleDef`.
- Example: `WeaponDef`, `ActorDef`, `QuestDef`.
## 2. Sub-record
- Fields or object inside of a Def.
- Located in owning-Defs header file.
- Named plain noun.
- Example: `QuestStage`, `LootTableEntry`, `DialogueBranch`.
## 3. Instance
- Runtime root object.
- Located in `/World/`.
- Named `Instance`.
- Contained by `InstanceTable`.
## 4. Component
- Functionality-defining data added to an Instance.
- Located in `/World/Components/`.
- Contained by Instance's components list.
- Named like `ExampleComponent`.
- Example: `HealthComponent`, `VelocityComponent`.
## 5. State
- Saved fields and data on World.
- Located in `/World/State/`.
- Contained by World.
- Named like `ExampleState`.
- Example: `QuestState`, `FactionsState`.
## 6. Service
- On-demand functions. Not per-tick.
- Located in `/World/Services/`.
- Live in their own files, scoped engine-wide, not containerized atm.
- Named like `ExampleService` file, verb functions.
- Example: `InventoryService` file, `TransferItem`, `ApplyDamage`, `RollLoot` functions.
## 7. System
- Per-tick functions. Registered and expandable.
- Located in `/World/Systems/`.
- Live in `SystemRegistry`.
- Named like `ExampleSystem`. Contains `UpdateExample` or `Update` function(s).
- Example: `MovementSystem`, `CombatSystem`; `UpdateMovement`, `UpdateCombat`.
## Outside of the buckets:
- The buckets only sort the engine / game model. Or as defined above, engine or game content. Plumbing for engine core functionality would not be content. Example being the renderer or OS code. That isn't content.
- Example externals:
	- /Render/
		- Rendering, texture handling, etc.
	- /Platform/
		- Native OS code like window / file / input handling, etc.
	- /Console/
		- Console and command handler
	- /Core/
		- Basic ids and math data.
## Decision tree: Where does new content go?
Below are some basic questions that can help you decide where content goes. You will see quite a bit of repetition between this section, the buckets, and the glossary. Which is hopefully consistent.
### 1. Code or data?
- Code that runs every tick belongs in a new or existing System.
- Code called on-demand that touches several objects is a Service.
- Code that only uses a single Component's data, can be added to that Component itself.
	- Example on HealthComponent, this.IsAlive()
### 2. Authored in the editor?
- If something points at it by name, it's a Def.
- If it only exists inside of another Def, it's a Sub-record
### 3. Runtime and in-world?
- Will exist in-world as an Instance.
- What every Instance has, are fields on Instance.
- What only some Instances have, are fields on a Component.
### 4. Runtime data with no position?
- State data, stored in World.
### 5. None of the above?
- Would likely be defined as plumbing.
- Plumbing exists outside of /World/ and /Data/, and should not be included by anything in /World/.
	- Plumbing is what will start and manage the engine core or World. Therefore World cannot include plumbing.
