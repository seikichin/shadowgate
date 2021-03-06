#include "summoned_monster.h"

inherit MONSTER;

create() 
{
    ::create();
    set_name("Ogre");
    set_id(({"ogre"}));
    set_gender("male");
    set("race","ogre");
    set("short", "Ogre guard");
    set("long", "This ogre is like most others - ugly, smelly, crude, and repulsive "
    "to any civilized race.  He looks very evil and doesn't like intruders.");
    set_body_type("human");
    set_alignment(9);
    set_hd(9,2);
    set_stats("strength",8);
    set_stats("aggressive",16);
    set_stats("intelligence", 6);
    set_stats("wisdom", 5);
    set_stats("charisma",3);
    set_size(3);
    set_property("swarm",1);
    set_wielding_limbs(({"right hand","left hand"}));
    add_money("gold",random(50));
    set_overall_ac(4);
    set_hp(75);
    set_exp(450);
    set_max_level(15);
    "/d/common/daemon/randgear_d.c"->arm_me(TO,"clubm",0,0);

}