#include "tile.cpp"

class tilePlain : public tile
{
public:
    int movementCost = 1;

    using tile::tile;
};
