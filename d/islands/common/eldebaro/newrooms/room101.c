#include <std.h>
#include "../area_stuff.h"

inherit ELINH;

void create()
{
    ::create();
    set_exits(([
        
        "north" : ELROOMSD+"116",
        "east" : ELROOMSD+"102",
        //"south" : ELROOMSD+"22",
        "west" : ELROOMSD+"100",
        
    ]));
}
