// midlevel necromancy school specialty spell. Nienne, 08/09.
#include <spell.h>
#include <magic.h>
#include <rooms.h>
#include <daemons.h>
#include <skills.h>
inherit SPELL;

int clevel,bonus,i;

void create() {
    ::create();
    set_spell_name("eyebite");
    set_spell_level(([ "mage" : 6, "bard" : 6 ]));
    set_spell_sphere("necromancy");
    set_syntax("cast CLASS eyebite on TARGET");
    set_description("With this spell caster imbues her eyes with dread power, glancing upon her enemies she curses them. This curse works its worst on weaker enemies, paralyzing them in fear.

Second tier will kick in if target's LVL-10+1d20 < CLEVEL - 10.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
}

string query_cast_string() {
    return "%^BLUE%^A dark aura threads its way around "+caster->QCN+"'s eyes as "+
	caster->QS+" intones a spell.%^RESET%^";
}

void spell_effect(int prof) {
    int duration;
    if(target == caster) {
        tell_object(caster, "%^CYAN%^You realise your error in cursing yourself, and let your spell fade away.%^RESET%^");
        tell_room(place,"%^CYAN%^The aura around "+caster->QCN+"'s hands weakens and then fades away.%^RESET%^",caster);
        TO->remove();
        return;
    }
    if(do_save(target)){
        tell_object(target,"%^CYAN%^You manage to shake off the dark aura that starts to grow around you, and it fades "
"away to nothing!%^RESET%^");
        tell_room(place,"%^CYAN%^A mirroring aura starts to grow around "+target->QCN+", but then it fades away to "
"nothing.%^RESET%^",target);
        TO->remove();
        return;
    }
    bonus = clevel/10;
    duration = ROUND_LENGTH * clevel/5;
    tell_object(target,"%^BLUE%^A mirroring aura starts to grow around you, seeping into your skin to taint it a %^RESET%^"
"sic%^GREEN%^k%^RESET%^ly %^BLUE%^pallid hue.  An overwhelming feeling of weakness comes over you.%^RESET%^");
    tell_room(place,"%^BLUE%^A mirroring aura starts to grow around "+target->QCN+", seeping into "+target->QP+" skin to taint it a %^RESET%^sic%^GREEN%^k%^RESET%^ly %^BLUE%^pallid hue.%^RESET%^",target);
    target->add_damage_bonus((-1)*bonus);
    target->add_attack_bonus((-1)*bonus);
    target->set_property("empowered",(-1)*bonus);
    for(i=0;i<sizeof(CORE_SKILLS);i++) caster->add_skill_bonus(CORE_SKILLS[i],(-1)*bonus);
    caster->add_saving_bonus("all",(-1)*bonus);
    if(target->query_character_level()-10+roll_dice(1,20)<clevel-10)
    {
        tell_object(target,"%^BOLD%^%^BLUE%^Unable to contain "+
                    "your terror, you cower before "+caster->QCN+"!%^RESET%^");
        tell_room(environment(target),"%^BOLD%^%^BLUE%^"+
                  ""+target->QCN+" cowers in terror!%^RESET%^",target);
        target->force_me("flee");        
        target->set_paralyzed(clevel/5,"You cannot contain your fear to do that!");
    }
    call_out("dest_effect",duration);
    spell_successful();
}

void dest_effect() {
    if(objectp(target)) {
        tell_object(target,"%^CYAN%^The feeling of weakness finally lifts, and with it fades the sickly color of your "
"skin.%^RESET%^");
        tell_room(environment(target),"%^CYAN%^The sickly color of "+target->QCN+"'s skin fades back into a more healthy "
"shade.%^RESET%^",target);
        target->add_damage_bonus(bonus);
        target->add_attack_bonus(bonus);
        target->set_property("empowered",bonus);
        for(i=0;i<sizeof(CORE_SKILLS);i++) caster->add_skill_bonus(CORE_SKILLS[i],bonus);
        caster->add_saving_bonus("all",bonus);
        target->remove_property("cursed");
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
