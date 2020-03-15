#include <std.h>
#include <objects.h>

inherit ROOM;

void create() {
    room::create();
    set_property("light",2);
    set_property("indoors",0);
     set_short("Eastern pines");
    set_long("%^BLUE%^%^BOLD%^
You are among the huge trees of the great eastern pines, just east of
the city of %^RED%^Sanctuary%^BLUE%^.  The forest extends in all directions, with
the trail winding among the trunks of the trees leading deeper into the
errie forest.
    ");
    set_exits(([
       "north" : "/d/dragon/forest/forest05",
       "west" : "/d/dragon/forest/forest03"
    ] ));
    set_items(([
    ] ));
}
