#include <std.h>
#include "../theater.h"
inherit BOX;
	void create(){ 
	::create();
	if(!present("thief")) 
{
	new(MOB"marion_thief")->move(TO) ;

}

	set_exits(([ "hallway" : ROOMDIR"mezz2",
	]));
	set_pre_exit_functions(({"hallway"}),({"GoThroughDoor"}));
}
int GoThroughDoor() {
int dex;
	dex = TP->query_stats("dexterity");
      	if(TP->query_true_invis()) return 1;
      	if(dex < random(16)) {
         		tell_object(TP,"%^MAGENTA%^With a groan and creak, the box seat"+
				" lurches foward sending you over its edge");
         		tell_room(TO,"%^MAGENTA%^The box seat groans and creaks, "+
				"lurching forward. "+TPQCN+" is knocked over the edge!",TP);
     					TP->add_attacker(TO);
        				TP->continue_attack();
        				if(objectp(TP))    TP->remove_attacker(TO);
					TP->move(ROOMDIR"dso2");
            			TP->force_me("look");
            			TP->set_tripped(2,"%^YELLOW%^You are recovering from your fall!");
						TP->cause_typed_damage(TP, "torso", roll_dice(1, 24) + 5, "bludgeoning");
	return 0;
		}else
			tell_object(TP,"%^MAGENTA%^With a groan and creak, "+
				"the box seat lurches foward.  Grabbing onto"+
				" the drapes for support, you are"+
				" able to save yourself from tumbling over its edge.");
			tell_room(TO,"%^MAGENTA%^The box seat groans and creaks, lurching"+
				" forward. "+TPQCN+" grabs the velvet drapes for "+
				"support, avoiding tumbling over the edge.",TP);
	return 1;
}
void reset()
{
    	::reset();
    		if(!present("thief")) 
{
	new(MOB"marion_thief")->move(TO) ;
    	return;
}
}