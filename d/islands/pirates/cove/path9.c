#include <std.h>
#include "../piratedefs.h"
inherit ROOM;

void create(){ 
   ::create();
   set_property("light",2);
   set_property("indoors",0);
   set_terrain(VILLAGE);
   set_travel(DIRT_ROAD);
   set_name("Road through the village");
   set_short("Road through the village");
   set_long("%^BOLD%^Road through the village%^RESET%^\n"
"Little wooden shacks and rough buildings are scattered along either side of the road as you pass by here, "
"some in better repair than others.  Pathways run between the buildings, leading in several directions.  All "
"sorts of shady figures brush past you as they carry on their way.  The %^BLACK%^%^BOLD%^cobblestone road "
"%^RESET%^beneath your feet leads both east and southwest, amongst the gathering of shacks and the "
"occasional shop.  To the northwest is a little shanty of a store, displaying all sorts of odd items in the "
"single dirty window.\n");
   set("night long","%^BOLD%^Road through the village%^RESET%^\n"
"Little wooden shacks and rough buildings are scattered along either side of the road as you pass by here, "
"some in better repair than others.  Pathways run between the buildings, leading in several directions into "
"%^BLUE%^darkness%^RESET%^.  All sorts of shady figures brush past you as they slip through the %^BLACK%^"
"%^BOLD%^night's shadows%^RESET%^.  The %^BLACK%^%^BOLD%^cobblestone road %^RESET%^beneath your feet leads "
"both east and southwest, amongst the gathering of shacks and the occasional shop.  To the northwest is a "
"little shanty of a store, displaying all sorts of odd items in the single dirty window.\n");
   set_smell("default","The salty smell of the ocean fills the air.");
   set_listen("default","The murmur and bustle of the village surrounds you.");

   set_items(([
     ({"village","settlement","shacks","buildings"}):"All around you on each side, little wooden shacks and "
"rough buildings are scattered, with small paths running between them.",
     ({"road","cobblestones","cobblestone road"}):"Beneath your feet is a simple road of %^BLACK%^%^BOLD%^"
"cobblestones%^RESET%^, leading eastward into the village itself.",
     ({"store","shop","shanty"}):"To the northwest is a little shanty of a store, displaying all sorts of "
"odd items in the single dirty window.  A sign over the doorway reads %^WHITE%^%^BOLD%^'The Wide Open Port'"
"%^RESET%^.",
    ]));

   set_exits(([
     "southwest":COVE"path8",
     "east":COVE"path10",
     "northwest":COVE"general"
   ]));
}
