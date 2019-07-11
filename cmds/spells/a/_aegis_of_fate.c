//Removing delay to bring it more in line with other
//domain spells ~Circe~ 4/24/08 also increasing its 
//effect as it's 6th level.  Rebalancing domains
#include <std.h>
inherit SPELL;

//#define DELAY 1800

int prevAc,magRes;
int counter;

void create(){
    ::create();
    set_spell_name("aegis of fate");
    set_spell_level(([ "cleric" : 6 ]));
    set_spell_sphere("enchantment_charm");
    set_spell_domain("fate");
    set_syntax("cast CLASS aegis of fate on TARGET");
    set_description("This spell alters the fate of the target, creating an ever-fluctuating shield about the target.  The "
"shield swirls in a chaotic display, offering some protection from both physical and magical effects to the target.  How "
"much protection is dependent on the caster's level and, well, the fates themselves.");
    set_verbal_comp();
    set_target_required(1);
	set_helpful_spell(1);
}

int preSpell(){
    if(!objectp(target)){
        tell_object(caster,"This spell requires a target.");
        return 0;
    }
/*
    if ((int)target->query_property("shield of fortune time")+DELAY > time()){
        tell_object(caster,"%^BOLD%^%^MAGENTA%^Your god would look unkindly upon trying "
            "to change that one's luck so soon.");
         return 0;
    }
*/
    if (target->query_property("shield of fortune")){
        tell_object(caster,"Your target has already had that spell cast upon them.");
        return 0;
    }
    return 1;
}

string query_cast_string(){
    tell_object(caster,"%^BOLD%^%^GREEN%^Laying a kiss on your holy symbol,"+
        " you begin to chant.%^RESET%^");
    tell_room(place,"%^BOLD%^"+caster->QCN+" lays a kiss on "+
        ""+caster->QP+" holy symbol, then "+caster->QS+" begins"+
        " to chant.%^RESET%^",caster);
	return "display";
}

void spell_effect(int prof){    
    tell_object(caster,"%^BOLD%^%^GREEN%^You chant in random words, turning"+
		" your hands in a circle before you.");
    tell_object(caster,"%^BOLD%^%^GREEN%^You put your hopes and desires to the whims of fate.");
    tell_room(place,"%^BOLD%^%^MAGENTA%^"+caster->QCN+" starts to chant, but the words seem to be "
        "random and without purpose.",caster);
    tell_object(target,"%^BOLD%^%^GREEN%^You feel a varying, random surge encompass you.");
    if (target != caster){        
        tell_object(caster,"%^BOLD%^%^GREEN%^You send out a random varying energy "
            "toward "+target->QCN+",");
    }
    prevAc = random(clevel/8)+1;
    target->add_ac_bonus(prevAc);
    magRes = random(clevel/3)+1;
    target->set_property("magic resistance",(magRes));
    addSpellToCaster();
    target->set_property("spelled",({TO}));
//    target->set_property("shield of fortune time",time());
    spell_successful();
}

void execute_attack(){
    if (!objectp(target)){
        dest_effect();
        return;
    }
    ::execute_attack();    
    if(!random(10)){
        tell_room(place,"%^BOLD%^%^MAGENTA%^"+target->QCN+" shimmers brightly.", target);
        tell_object(target,"%^BOLD%^%^MAGENTA%^You shimmer brightly.");    
        target->add_ac_bonus(-1 * prevAc);
        prevAc = random(clevel/8)+1;
        target->add_ac_bonus(prevAc);
        target->set_property("magic resistance",(-1 * magRes));
        magRes = random(clevel/3)+1;
        target->set_property("magic resistance",(magRes));
        counter++;
    }
    if (counter > clevel){
        dest_effect();
        return;
    }
    environment(target)->addObjectToCombatCycle(TO,1);
}

void dest_effect(){
    if (objectp(target)){
        target->add_ac_bonus(-1 * prevAc);
        target->remove_property("shield of fortune");
        tell_object(target,"%^BOLD%^%^MAGENTA%^You shimmer brightly, but then feel the energy flee.");
        tell_room(place,"%^BOLD%^%^MAGENTA%^"+target->QCN+" shimmers brightly.", target);
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}