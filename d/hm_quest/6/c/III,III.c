#include "/d/hm_quest/maze.h"

inherit "/d/hm_quest/maze.c";

create()
{
  ::create();
  new_disc(6);
  set_exits( ([
                "east"  : MAZEDIR+"6/c/IV,III",
		"west"  : MAZEDIR+"6/c/II,III"
           ]) );
}

