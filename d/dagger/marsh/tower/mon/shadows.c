// removing buggy roam_fun, shouldn't be needed anyway
// adding objectp checks to the wrack function to prevent bugs and add_attacker stuff
// *Styx*  11/1/03, last change was 7/20/98

#include <std.h>
inherit WEAPONLESS;

void create() {
    :: create();
//    call_out("roam_fun",1);
    set_name("shadow");
    set_id(({ "shadow","mastiff", "figure","daggershadow0"}));
    set_short("%^RESET%^%^BLUE%^Shadowy figure%^RESET%^");
    set_long(
        "A shadowy shape which faintly resembles a humanoid being. It is "
	"extremely hard to make out any distiguishing features as it is "
	"constantly shrouded in a cloak of darkness."
    );
    set_level(25);
    set_hd(25,6);
    set_weight(80);
    set_attacks_num(3);
    set_damage(3,5);
    set_base_damage_type("slashing");
    set_overall_ac(-6);
set_property("magic",1);
    set_body_type("human");
    set_race("shadow");
    set_property("undead",1);
    add_limb("jaws","head",0,0,0);
    set_attack_limbs(({"right hand","left hand","jaws"}));
    set_class("fighter");
    set_guild_level("fighter",25);
    set_stats("strength",26);
    set_stats("constitution",24);
    set_stats("dexterity",26);
    set_stats("wisdom",25);
    set_stats("intelligence",25);
    set_stats("charisma",20);
    set_mob_magic_resistance("average");
    set_exp(22000);
    set("aggressive",random(15)+5);
    set_max_hp(290);
    set_hp(290);
    set_property("swarm",1);
    set_invis();
    add_money("gold",random(500)+500);
    set_emotes(1,({
        "%^BLUE%^The shadow shimmers and vanishes!%^RESET%^",
	"The shadow swirls around you.",
	"The shadow savagely lunges forward with its jaw wide open!",
    }),1);
    set_moving( 1 );
    set_speed ( 16 );
    set_funcs(({"breath"}));
    set_func_chance(20);
    set_resistance("negative energy",10);
    set_resistance("positive energy",-10);
}

void breath(object targ){
    if(!targ) return;
    tell_room(ETO,
	"%^BOLD%^%^BLUE%^The shadow summons the inner shadows to absorb "
	+targ->query_cap_name()+"!",targ);
    tell_object(targ,
	"%^BOLD%^%^BLUE%^The shadow summons the inner shadows to absorb you!");
    call_out("wrack",2,targ);
    call_out("wrack",5,targ);
    call_out("wrack",9,targ);
    call_out("wrack",12,targ);
    call_out("wrack",20,targ);
}

int wrack(object targ) {
    if(!objectp(TO) || !objectp(ETO))  return 1;
    if(!objectp(targ))  return 1;
    tell_object(targ,
	"%^BOLD%^%^BLUE%^Your body is wracked with seizing pains as the shadows "
	"attempt to rip your soul apart!%^RESET%^"
    );
    tell_room(ETO, "%^BOLD%^%^BLUE%^"+targ->query_cap_name()+" claws at "
	+targ->query_possessive()+" chest while screaming in pain!%^RESET%^",targ);
    targ->do_damage("torso",random(7)+3);
}

void set_paralyzed(int time,string message){return 1;}

void roam_fun() { ETO->init(); }
