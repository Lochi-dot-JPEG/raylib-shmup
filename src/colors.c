
#include <raylib.h>

Color background_color;
Color text_color;
Color selected_text_color;

void col_Init() {
  // background_color = GetColor(0xdcd7baff);
  // text_color = GetColor(0x252322ff);
  background_color = GetColor(0xa63c29ff);
  selected_text_color = GetColor(0x252322ff);
  text_color = GetColor(0xdcd7baff);
}
