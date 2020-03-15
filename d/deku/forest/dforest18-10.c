#include <std.h>
#include "/d/deku/inherits/forest.h"
inherit NTFTRAIL;

void create() {
    ::create();

    set_exits(([
       "east" : F_ROOMS"17-10",
       "north" : F_ROOMS"18-11",
       "northeast" : F_ROOMS"17-11",
       "west" : F_ROOMS"19-10",
       "northwest" : F_ROOMS"19-11",
    ] ));
}
