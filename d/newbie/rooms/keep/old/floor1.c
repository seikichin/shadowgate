#include <std.h>
#include "keep.h"
inherit ROOM;

void create()
{
   ::create();
   set_terrain(STONE_BUILDING);
   set_travel(PAVED_ROAD);
   set_property("indoors",1);
   set_property("light",1);
   set_short("Guard Barracks");
   set_long(
   "You are standing in the guard barracks on the second floor of a ruined keep."+
   " There are two sets of bunk beds in the room, both of which are rotted and"+
   " the bedding is filled with mildew. The floor is covered in dust and you"+
   " doubt that anyone has been up here in some time. Back to the west are the"+
   " stairs that lead down to the first floor, to the south and east are more"+
   " barrack rooms."
   );
   set_smell("default","The beds stink of mildew.");
   set_listen("default","Everything is fairly quiet here.");
   set_items(([
   "floor" : "The floor is covered in dust.",
   ({"beds","bunk beds"}) : "There are two sets of bunk beds here, both against"+
   " the northern wall.",
   "bedding" : "The mattress, sheets, blankets, and pillows that are on the"+
   " bunk beds are completely covered in mildew.",
   ]));
   set_exits(([
   "west" : ROOMS+"stair2",
   "east" : ROOMS+"floor2",
   "south" : ROOMS+"floor3",
   ]));
}


void init()
{
   ::init();
   do_random_encounters(({MONS+"spider"}),30,1);
}
