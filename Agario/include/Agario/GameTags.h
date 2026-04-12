#pragma once

#include "Engine/GameplayTags/TagDecl.h"

namespace Tags::Agario
{
    TAG(Entity, "Agario.Entity")
    TAG(Entity_Player, "Agario.Entity.Player")
    TAG(Entity_Food, "Agario.Entity.Food")
    TAG(Entity_Virus, "Agario.Entity.Virus")

    TAG(Ability, "Agario.Ability")
    TAG(Ability_Split, "Agario.Ability.Split")
    TAG(Ability_EjectMass, "Agario.Ability.EjectMass")

    TAG(State, "Agario.State")
    TAG(State_Alive, "Agario.State.Alive")
    TAG(State_Dead, "Agario.State.Dead")
}
