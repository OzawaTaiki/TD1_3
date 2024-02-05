#include "UI_ToolKit_Defines.h"

void Transform::operator=(Vector2 _vec2)
{
    x = int(_vec2.x);
    y = int(_vec2.y);
}
