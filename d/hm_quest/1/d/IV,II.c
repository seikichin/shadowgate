#include "/d/hm_quest/maze.h"

inherit "/d/hm_quest/maze";

create()
{
  ::create();
  set_exits( ([
                "south" : MAZEDIR+"1/d/IV,III",
                "east"  : pass_exit("2","I,II"),
                "west"  : MAZEDIR+"1/d/III,II"
           ]) );
  set_pre_exit_functions( ({"east"}) , ({"go_east"}) );
}

int go_east()
{
  set_exits( ([
                "south" : MAZEDIR+"1/d/IV,III",
                "east"  : pass_exit("2","I,II"),
                "west"  : MAZEDIR+"1/d/III,II"
           ]) );
  return 1;
}
