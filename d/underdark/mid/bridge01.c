#include <std.h>
#include "../defs.h"
inherit INH+"bridge";

void create(){ 
   ::create();
   set_long("%^MAGENTA%^A bridge crossing the Wailing Chasm%^RESET%^\n"+ ::query_long() +"%^BLUE%^  Just to "
"the west, the bridge meets the %^WHITE%^dull stone wall %^BLUE%^of the chasm itself.%^RESET%^\n");
   set_exits(([
     "southwest":MID"chasm27",
     "northeast":MID"bridge02",
   ]));
   set_pre_exit_functions(({"southwest","northeast"}),({"GoThroughDoor","GoThroughDoor"}));
}
