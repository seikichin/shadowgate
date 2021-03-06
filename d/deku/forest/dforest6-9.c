#include <std.h>
#include "/d/deku/inherits/forest.h"
inherit FTRAIL;

void create() {
    ::create();
    set_long(TO->query_long()+"  %^BOLD%^%^BLACK%^The %^RESET%^"+
    "wall%^BOLD%^%^BLACK%^ of a large structure has risen "+
    "up directly to the northwest.%^RESET%^");
    add_item("wall","%^BOLD%^%^BLACK%^This large wall is made "+
    "of black bricks and towers some twenty feet high.  It is "+
    "the apparent outer defense of a large structure.%^RESET%^");
    set_exits(([
       "west" : F_ROOMS"7-9",
       "east" : F_ROOMS"5-9",
       "north" : F_ROOMS"6-10",
       "south" : F_ROOMS"6-8",
       "southeast" : F_ROOMS"5-8",
       "southwest" : F_ROOMS"7-8",
       "northeast" : F_ROOMS"5-10",
    ] ));
}
