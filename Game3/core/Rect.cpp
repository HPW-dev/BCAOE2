#include "../core/Rect.h"

bool rect::on_click(int mouse_x, int mouse_y) const {
    return
        (mouse_x >= x) &&
        (mouse_x < x + w) &&
        (mouse_y >= y) &&
        (mouse_y < y + h);
}
