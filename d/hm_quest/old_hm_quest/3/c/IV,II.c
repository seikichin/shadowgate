#include "/d/hm_quest/maze.h"

inherit "/d/hm_quest/maze";

create()
{
  ::create();
  new_disc(3);
  set_exits( ([
                "north" : MAZEDIR+"3/c/IV,I",
                "south" : MAZEDIR+"3/c/IV,III",
                "west"  : MAZEDIR+"3/c/III,II"
           ]) );
}
