#include <std.h>
#include "../inherit/ruins.h"
inherit BASE+"l1b";

void create() {
    ::create();
    set_long("%^ORANGE%^You are standing within an extensive hallway, set with strong pillars at " 
"regular intervals.  The roof reaches high above your head, supported by curved arches from these "
"pillars, decorated ornately but covered in a thick layer of %^BLACK%^%^BOLD%^dust%^RESET%^%^ORANGE%^.  "
"The floor beneath your feet is perfectly flat, without rubble or upturned stones to impede your "
"progress, though it is coated in still more %^BLACK%^%^BOLD%^dust%^RESET%^%^ORANGE%^.  To the north, "
"the hallway leads to an entrance of impressive size.  It seems very %^BLUE%^lifeless%^ORANGE%^ here, "
"though a heavy feeling rests upon your shoulders, making you feel a little uneasy.\n");
    set_exits(([
      "north" : ROOMS+"entry",
      "south" : ROOMS+"2-3",
      "east" : ROOMS+"1-4",
      "west" : ROOMS+"1-2",
    ]));
}