#include <std.h>
#include "../elf.h"
inherit INH"ruin";

void create(){
   ::create();
   set_exits(([ "north": ROOMS"shore/ruin2", 
   "south": ROOMS"/shore/ruin4",
   "west": ROOMS"/shore/ruin8",
     ]));

}