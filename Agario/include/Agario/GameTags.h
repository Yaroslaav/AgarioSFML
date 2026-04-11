#pragma once

#include "Engine/GameplayTags/GameplayTag.h"

#define TAG(Name, Value) inline const Engine::GameplayTag Name{Value};

namespace Agario::Tags
{
    TAG(Entity, "Entity")
    TAG(Entity_Player, "Entity.Player")
    TAG(Entity_Food, "Entity.Food")
    TAG(Entity_Virus, "Entity.Virus")

    TAG(Ability, "Ability")
    TAG(Ability_Split, "Ability.Split")
    TAG(Ability_EjectMass, "Ability.EjectMass")

    TAG(State, "State")
    TAG(State_Alive, "State.Alive")
    TAG(State_Dead, "State.Dead")
}
