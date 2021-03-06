//psdragon.c

#include <std.h>

inherit WEAPONLESS;

void create(){
	::create();
	
	set_name("pseudodragon");
	set_id(({"pseudodragon","dragon","psuedo","psdragon"}));
	set_short("A very small dragon");
	set_long(
@OLI
	You look at this dragon which stands about 1.5 feet tall and 
think how cute. Then you get over it's relative size and notice 
the sharp teeth in it's mouth and the horns protruding from it's
neck area. It's scales are small overlapping in such a way that 
it almost looks like skin at a casual glance. Everynow and the 
you notice that it's skin is changing color.
OLI
	);
	set_hd(8,8);
	set_hp(54);
	set_attack_limbs(({"mouth"}));
	set_damage(1,9);
	set_attacks_num(1);
	set_base_damage_type("piercing");
	set_exp(5000);
	set_body_type("dragon");
	set_race("pseudodragon");
	set_gender("male");
	set_funcs(({"tail"}));
	set_func_chance(50);
	set_alignment(1);
  set_max_level(20);
	}

void tail(object targ){
	
	if(random(20)+5 > (int)("daemon/bonus_d"->monster_thaco( TO->query_hd()) )-(int)(targ->query_ac())){
		
		tell_room(ETO,"%^BOLD%^%^RED%^Launching himself into the air the small dragon turns and dives toward "+targ->query_cap_name()+" and lashes at "+targ->query_objective()+" with his tail!",targ);
		tell_object(targ,"%^BOLD%^%^YELLOW%^The small dragon lauches himself into the air and turns on you lashing at you with it's tail!!\n");
		tell_room(ETO,"%^BOLD%^%^RED%^The glaive like tip of the tail cuts deeply into "+targ->query_cap_name()+"!",targ);
		tell_object(targ,"%^BOLD%^%^YELLOW%^The glaive like tip of the tail cuts deeply into you!\n");
		targ->do_damage(targ->return_target_limb(),roll_dice(2,4));
		if("daemon/saving_d"->saving_throw(targ,"paralyzation_poison_death",-5)){
			targ->set_paralyzed(60,"%^BOLD%^You feel the poison creeping toward your heart and brain!");
			call_out("kill_em",61,targ);
		}
	} else {
		tell_room(ETO,"%^BOLD%^%^RED%^Launching himself into the air the small dragon turns and dives toward "+targ->query_cap_name()+" and lashes at "+targ->query_objective()+" with his tail!",targ);
		tell_object(targ,"%^BOLD%^%^YELLOW%^The small dragon lauches himself into the air and turns on you lashing at you with it's tail!!\n");
		tell_room(ETO,"%^BOLD%^%^GREEN%^The tail whips around and misses it's target, the dragon however recovers quickly and resumes the attack!");
	}
}

void kill_em(object targ){
	if(!objectp(targ)) return;
	if(random(100) < 35){
		tell_object(targ,"%^BOLD%^%^RED%^The poison reaches your heart and you feel it slow to stopping.\n");
		tell_object(targ,"%^BOLD%^%^RED%^Your lungs seem to be colapsing there is no more air in the world.\n");
		tell_object(targ,"%^BOLD%^%^RED%^Your brain slow shuts down! You slip from conciousness..........and life!");
		targ->do_damage(targ->return_target_limb(),100000);
		targ->set_attackers(({TO}));
		targ->continue_attack();
		return;
	} else {
		tell_object(targ,"%^BOLD%^%^CYAN%^You feel your body fighting off the poison flowing through it!\n");
		tell_object(targ,"%^BOLD%^%^CYAN%^You feel you will live!");
	}
}

void init(){
	::init();
	
	if(ALIGN->is_evil(TP))
		kill_ob(TP,1);
}

int kill_ob(object victim, int which){
	object *inven;
	int i,k;
	if(!swarm){
  	if(victim == TP && interactive(TP)){

           swarm = 1;
                inven = all_inventory(environment(TO));
                k = sizeof(inven);
                for(i=0;i<k;i++){
                        if(living(inven[i])){
                            if(ALIGN->is_good(inven[i])){
                            	if(inven[i] != TP)
                                 	inven[i]->kill_ob(TP,1);
                             }
                        }
                }
        }
        swarm = 0;
     }
	return ::kill_ob(victim,which);
}
