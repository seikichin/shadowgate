#include "/d/hm_quest/maze.h"

inherit "/d/hm_quest/maze";

create()
{
  ::create();
  new_disc(3);
  set_exits( ([
                "south" : MAZEDIR+"3/c/III,III",
                "east"  : MAZEDIR+"3/c/IV,II",
                "west"  : MAZEDIR+"3/c/II,II"
           ]) );
}