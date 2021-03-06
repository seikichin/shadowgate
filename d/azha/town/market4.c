// Inside Market Square, Azha
// Thorn@ShadowGate
// 4/8/95
// Town of Azha

#include <std.h>
#include "/d/azha/azha.h"
#include "/d/tsarven/include/southern.h"

inherit "//d/azha/town/market1";

void create()
{
    ::create();
    set_terrain(CITY);
    set_travel(PAVED_ROAD);
    set_light(2);
    set_indoors(0);
    set_exits(([
                   "south" : "/d/azha/town/market1",
                   "east" : "/d/azha/town/market5",
                   "southeast" : "/d/azha/town/market2",
                   ]));
    set_items(([
                   "booths" : "The booths are of many shapes: tents, wooden stalls, or sometimes just piles of goods, marked by a sign.\n",
                   ]));
}

reset()
{
    ::reset();
    AOVER->setup_monsters(TO, "public");
    AOVER->always_add_monster(TO, AMONDIR + "bokara", 1);
//          AOVER->add_monster(TO, AMONDIR+"murad", 1);
}
