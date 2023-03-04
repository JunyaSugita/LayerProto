#include "Util.h"

bool CheckHitBoxAndBox(Vector2 pos, Vector2 length, Vector2 pos2, Vector2 length2)
{
	if (pos.x - length.x / 2.0f < pos2.x + length2.x / 2.0f &&
		pos2.x - length2.x / 2.0f < pos.x + length.x / 2.0f &&
		pos.y - length.y / 2.0f < pos2.y + length2.y / 2.0f &&
		pos2.y - length2.y / 2.0f < pos.y + length.y / 2.0f)
	{
		return true;
	}

	return false;
}
