#include "/d/hm_quest/maze.h"

inherit "/d/hm_quest/maze";

create()
{
  ::create();
  new_disc(3);
  set_exits( ([
                "east"  : MAZEDIR+"3/a/III,IV",
                "west"  : MAZEDIR+"3/a/I,IV"
           ]) );
}
