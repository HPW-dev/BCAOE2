#include "Tree.h"

// object - объект убийца дерева
void Tree::kill (Object* other)
{
	other->player->wood += this->hp_max;
}