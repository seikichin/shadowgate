#include <std.h>
#include <terrain.h>
#include "../tecqumin.h"
inherit ZIG_HIGH;

void create() {
  ::create();
  set_exits( ([ "north" : ROOMS + "zighigh203" ,
	          "east" : ROOMS + "step6"]) );

  set_climb_exits(([
       "climb":({ROOMS + "zigzenith",5,6,20}),
       "descend":({ROOMS + "zighigh108",5,6,20}),
  ]));
}
