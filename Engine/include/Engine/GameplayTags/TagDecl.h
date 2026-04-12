#pragma once

#include "GameplayTag.h"

#define TAG(Name, Value) inline const ::Engine::GameplayTag Name{Value};
