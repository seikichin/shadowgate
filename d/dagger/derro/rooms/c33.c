#include <std.h>
#include "../derrodefs.h"
inherit ROOM;

void create(){
  ::create();
   set_terrain(BARREN);
   set_travel(FRESH_BLAZE);
  set_property("no teleport",1);
  set_property("light",2);
  set_name("Sea of lava");
  set_property("indoors",1);
  set_short("%^RED%^Swimming in the lava sea!%^RESET%^");
  set_long(
  "%^RED%^Swimming in the lava sea!%^RESET%^"
  "\n"
  "  You struggle to stay on top of the hardened lava crust but the heat is overwhelming!"
  "  You're going the wrong way, the path is to the west."
  "\n"
  );
  set_smell("default","Your clothes start to catch fire!");
  set_listen("default","The lava burns you!");
  set_items(([
  "lava":"It's all around and very hot.",
  ]));
  set_exits(([
  "northwest":ROOMS"c29",
  ]));
  set_heart_beat(3);
  set_property("continue heartbeat",1);
}
void heart_beat(){
  object *heat;
  int i, j;
  ::heart_beat();
  if(!random(4))  // too spammy and also too much stamina drain
	return;
  heat=all_living(TO);
  j=sizeof(heat);
  for(i=0;i<j;i++){
  if(heat[i]->query_true_invis())  continue;
  tell_object(heat[i],"%^BOLD%^%^RED%^The heat sears you!");
  heat[i]->do_damage(heat[i]->return_target_limb(),random(20)+5);
  heat[i]->add_attacker(TO);
  heat[i]->continue_attack();
  if(objectp(heat[i])) { heat[i]->remove_attacker(TO); }
  }
}
