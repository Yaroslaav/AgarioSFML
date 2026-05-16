#pragma once

namespace Agario
{
    class AgarioWorld;
    class Cell;

    class CollisionSystem
    {
    public:
        static void Resolve(AgarioWorld& world);

    private:
        static void ResolveFoodCollision(AgarioWorld& world, Cell& cell);
        static void ResolveCellCollision(Cell& cellA, Cell& cellB);
        static void ResolveTeamCollision(Cell& cellA, Cell& cellB);
        static void ResolveEnemyCollision(Cell& cellA, Cell& cellB);
    };
}
