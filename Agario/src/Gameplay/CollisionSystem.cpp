#include "Agario/Gameplay/CollisionSystem.h"

#include "Agario/Actors/Cell.h"
#include "Agario/Actors/Food.h"
#include "Agario/Config/Settings.h"
#include "Agario/World/AgarioWorld.h"
#include "Engine/Math/MathUtils.h"

#include <algorithm>
#include <cstddef>
#include <cmath>

namespace Agario
{
    void CollisionSystem::Resolve(AgarioWorld& world)
    {
        const auto& cells = world.GetAllActorsOfClass<Cell>();

        for (std::size_t cellIndex = 0; cellIndex < cells.size(); ++cellIndex)
        {
            Cell* cell = cells[cellIndex];
            if (cell == nullptr || !cell->IsActive())
            {
                continue;
            }

            ResolveFoodCollision(world, *cell);

            for (std::size_t otherCellIndex = cellIndex + 1; otherCellIndex < cells.size(); ++otherCellIndex)
            {
                Cell* otherCell = cells[otherCellIndex];
                if (otherCell == nullptr || !otherCell->IsActive())
                {
                    continue;
                }

                ResolveCellCollision(*cell, *otherCell);
            }
        }
    }

    void CollisionSystem::ResolveFoodCollision(AgarioWorld& world, Cell& cell)
    {
        auto* cellCollision = cell.GetCollision();

        world.GetChunkGrid().ForEachFoodInRadius(cell.GetActorPosition(), cell.GetRadius(), [&](Food* food)
        {
            if (food == nullptr || !food->IsActive())
            {
                return;
            }

            auto* foodCollision = food->GetCollision();
            if (!cellCollision->FullyCovers(*foodCollision))
            {
                return;
            }

            cell.Grow(food->GetMass());
            food->GetTransform().SetPosition(world.GetRandomPositionInBounds(food->GetRadius()));
            foodCollision->OnBeginOverlap.Broadcast(&cell, cellCollision);
            cellCollision->OnBeginOverlap.Broadcast(food, foodCollision);
        });
    }

    void CollisionSystem::ResolveCellCollision(Cell& cellA, Cell& cellB)
    {
        if (cellA.GetTeamId() != -1 && cellA.GetTeamId() == cellB.GetTeamId())
        {
            ResolveTeamCollision(cellA, cellB);
            return;
        }

        ResolveEnemyCollision(cellA, cellB);
    }

    void CollisionSystem::ResolveTeamCollision(Cell& cellA, Cell& cellB)
    {
        const sf::Vector2f centerA = cellA.GetCollision()->GetWorldCenter();
        const sf::Vector2f centerB = cellB.GetCollision()->GetWorldCenter();

        const float minDistance = cellA.GetRadius() + cellB.GetRadius();
        const float distSq = Engine::Math::DistanceSquared(centerA, centerB);

        if (distSq >= minDistance * minDistance)
        {
            return;
        }

        if (cellA.CanMerge() && cellB.CanMerge())
        {
            Cell* largerCell = &cellA;
            Cell* smallerCell = &cellB;

            if (cellB.GetMass() > cellA.GetMass())
            {
                largerCell = &cellB;
                smallerCell = &cellA;
            }

            largerCell->Grow(smallerCell->GetMass());
            smallerCell->Die(*largerCell);
            return;
        }

        const bool centersOverlap = distSq < 0.1f;
        const float dist = centersOverlap ? 0.f : std::sqrt(distSq);
        const sf::Vector2f normal = centersOverlap ? sf::Vector2f{1.f, 0.f} : (centerA - centerB) / dist;
        const float mergeProgress = std::max(cellA.GetMergeProgress(), cellB.GetMergeProgress());
        const float collisionStrength = 1.f - mergeProgress;
        const sf::Vector2f separation = normal * ((minDistance - dist) * .5f * collisionStrength);

        cellA.GetTransform().Move(separation);
        cellB.GetTransform().Move(-separation);
    }

    void CollisionSystem::ResolveEnemyCollision(Cell& cellA, Cell& cellB)
    {
        Cell* largerCell = &cellA;
        Cell* smallerCell = &cellB;

        if (cellB.GetMass() > cellA.GetMass())
        {
            largerCell = &cellB;
            smallerCell = &cellA;
        }

        if (!largerCell->CanConsume(*smallerCell))
        {
            return;
        }

        auto* largerCollision = largerCell->GetCollision();
        auto* smallerCollision = smallerCell->GetCollision();
        if (!largerCollision->FullyCovers(*smallerCollision))
        {
            return;
        }

        largerCell->Grow(smallerCell->GetMass() * Settings.gameplay.consume.massGainFactor);
        smallerCell->Die(*largerCell);
        largerCollision->OnBeginOverlap.Broadcast(smallerCell, smallerCollision);
    }
}
