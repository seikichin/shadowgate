
#include <std.h>

inherit "/d/attaya/tower/spec/tower";


void create(){
      ::create();
	set_property("light",3);
	set_property("indoors",1);
   set_property("no teleport",1);
       set_short("Northeast guard tower");
        set_long("
    This is a round room with open doors to the south and east.  It has been set up as a guard tower in the midst of the chamber.
    A wooden plank is nailed to the floor here and extends to the south to a metal catwalk.
");
     set_listen("default", "Water roars around far below this room.");
       set_exits(([
       "out" : "/d/attaya/tower/floor8",
       "east" : "/d/attaya/tower/floor6",
]));
       set_items(([
    "ceiling" : "Blue-gray tiles make up the ceiling.",
    "floor" : "Blue-gray tiles make up the floor.",
    "walls" : "Molded plaster rises half way up the brick walls.",
     "water" : "The dark waters are about 100 feet beneath you and rush in powerful currents into black holes.",
     "catwalk" : "The iron mesh catwalk stretches from the west wall to the east wall.  It is connected by heavy grade rope to large eyelets in the ceiling.  100 feet beneath you is watery chaos.",
    "intruder" : "You are not sure if your mind is playing tricks on you.",
]));
	
}
void init() {
  ::init();
   add_action("look", "look");
}
int look(string str) {
  if(str=="over the edge") {
 write("%^BOLD%^You almost lose your balance!  You purposely fall backwards and remain on the platform.",TP);
  say((string)this_player()->query_cap_name()+" gets too close to the edge and nearly falls to "+this_player()->query_possessive()+" doom.\n");
    return 1;
}
    return 0;
}
