#include <std.h>
#include "../area_stuff.h"

inherit WESTOASIS;

void create()
{
    ::create();
    set_exits(([
        "south" : ELROOMSW+"11",
        "east" : ELROOMSW+"13",
        //"north" : ELROOMSW+"12",
        "west" : ELROOMSW+"7",
    ]));
}
