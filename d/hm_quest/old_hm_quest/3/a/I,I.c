#include "/d/hm_quest/maze.h"

inherit "/d/hm_quest/maze";

create()
{
  ::create();
  new_disc(3);
  set_exits( ([
                "south" : MAZEDIR+"3/a/I,II",
                "east"  : MAZEDIR+"3/a/II,I"
           ]) );
}
