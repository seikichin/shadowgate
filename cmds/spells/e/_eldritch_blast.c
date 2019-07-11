// please note: at present touch attacks are not being used on these spells as it makes the class
// too unreliable. It may be possible down the track to balance it with a proper ranged attack
// roll, but current lib doesn't support one well. Can be considered at a later date! N, 1/16.
#include <spell.h>
#include <magic.h>
#include <daemons.h>
inherit SPELL;

#define SECONDARYOBS "/d/magic/obj/eldritch_effects/"
string blasttype, element;
int lifesteal, washealed;
void do_secondary(object victim);
void do_hellfire_damage(object victim, string potency);
string get_descript();

void create() {
    ::create();
    set_author("nienne");
    set_spell_name("eldritch blast");
    set_spell_level(([ "warlock" : 1 ]));
    set_syntax("cast CLASS eldritch blast on TARGET");
    set_description("This is the core spell-like ability of the warlock - the ability to invoke "
"pure planar energy and hurl it at a foe. As it is cast as a ray, it requires a successful ranged "
"touch attack to hit, and is subject to the usual restrictions of spells and spell-like abilities "
"(eg/ magic resistance). While initially unremarkable, an accomplished warlock can learn to reshape "
"such a blast, or to imbue it with various essences.\nSee also: <help blasttype>.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
}

int preSpell() {
    int flag = 0;
    if(target == caster) {
      tell_object(caster,"%^BOLD%^%^WHITE%^You can't channel your own power into yourself!%^RESET%^");
      return 0;
    }
// this just makes hybrids cumbersome, to lose the weapon and have to cast a spell and then re-cast the weapons. Removing for now. N, 3/17.
/*    while(present("eldritch_weapon_xxx",caster)) {
      caster->force_me("unwield eldritch_weapon_xxx");
      flag = 1;
    }
    if(flag) {
      if(flag > 1) tell_object(caster,"%^CYAN%^You reshape your eldritch blast and the weapons disappear!%^RESET%^");
      else tell_object(caster,"%^CYAN%^You reshape your eldritch blast and the weapon disappears!%^RESET%^");
    } */
    return 1;
}

string query_cast_string() {
    blasttype = (string)caster->query("warlock_blast_type");
    switch(blasttype) {
      case "utterdark": case "beshadowed":
        tell_object(caster,"%^MAGENTA%^You bring your hands together, and they start to %^BOLD%^%^BLACK%^g%^RESET%^%^MAGENTA%^l%^BOLD%^%^BLACK%^ow %^RESET%^%^MAGENTA%^as you draw energy from within.%^RESET%^");
        tell_room(place,"%^MAGENTA%^"+caster->QCN+" brings "+caster->QP+" hands together, and they start to %^BOLD%^%^BLACK%^g%^RESET%^l%^BOLD%^%^BLACK%^ow %^RESET%^%^MAGENTA%^with energy.%^RESET%^",caster);
      break;
      case "vitriolic": case "lifedrinker":
        tell_object(caster,"%^MAGENTA%^You bring your hands together, and they start to %^RESET%^%^GREEN%^g%^BOLD%^%^GREEN%^l%^YELLOW%^o%^RESET%^%^GREEN%^w %^MAGENTA%^as you draw energy from within.%^RESET%^");
        tell_room(place,"%^MAGENTA%^"+caster->QCN+" brings "+caster->QP+" hands together, and they start to %^RESET%^%^GREEN%^g%^BOLD%^%^GREEN%^l%^YELLOW%^o%^RESET%^%^GREEN%^w %^MAGENTA%^with energy.%^RESET%^",caster);
      break;
      case "glacial": case "binding":
        tell_object(caster,"%^MAGENTA%^You bring your hands together, and they start to %^CYAN%^g%^BOLD%^%^WHITE%^l%^BOLD%^%^CYAN%^o%^RESET%^%^CYAN%^w %^MAGENTA%^as you draw energy from within.%^RESET%^");
        tell_room(place,"%^MAGENTA%^"+caster->QCN+" brings "+caster->QP+" hands together, and they start to %^CYAN%^g%^BOLD%^%^WHITE%^l%^BOLD%^%^CYAN%^o%^RESET%^%^CYAN%^w %^RESET%^%^MAGENTA%^with energy.%^RESET%^",caster);
      break;
      case "brimstone":
        tell_object(caster,"%^MAGENTA%^You bring your hands together, and they start to %^RED%^g%^YELLOW%^l%^BOLD%^%^RED%^o%^RESET%^%^RED%^w %^MAGENTA%^as you draw energy from within.%^RESET%^");
        tell_room(place,"%^MAGENTA%^"+caster->QCN+" brings "+caster->QP+" hands together, and they start to %^RED%^g%^YELLOW%^l%^BOLD%^%^RED%^o%^RESET%^%^RED%^w %^RESET%^%^MAGENTA%^with energy.%^RESET%^",caster);
      break;
      case "frightful":
        tell_object(caster,"%^MAGENTA%^You bring your hands together, and they start to %^BLUE%^g%^BOLD%^%^BLACK%^l%^RESET%^%^MAGENTA%^o%^BLUE%^w %^MAGENTA%^as you draw energy from within.%^RESET%^");
        tell_room(place,"%^MAGENTA%^"+caster->QCN+" brings "+caster->QP+" hands together, and they start to %^BLUE%^g%^BOLD%^%^BLACK%^l%^RESET%^%^MAGENTA%^o%^BLUE%^w %^MAGENTA%^with energy.%^RESET%^",caster);
      break;
      default:
        tell_object(caster,"%^MAGENTA%^You bring your hands together, and they start to g%^BOLD%^%^MAGENTA%^l%^BOLD%^%^WHITE%^o%^RESET%^%^MAGENTA%^w as you draw energy from within.%^RESET%^");
        tell_room(place,"%^MAGENTA%^"+caster->QCN+" brings "+caster->QP+" hands together, and they start to g%^BOLD%^%^MAGENTA%^l%^BOLD%^%^WHITE%^o%^RESET%^%^MAGENTA%^w with energy.%^RESET%^",caster);
      break;
    }
    return "display";
}

void spell_effect(int prof) {
    int damage;
    string descriptor;

    if(!objectp(target)) {
        tell_object(caster,"Your target has eluded you!");
        dest_effect();
        return;
    }
    if (environment(caster) != environment(target)) {
        tell_object(caster,"Your target has eluded you!");
        dest_effect();
        return;
    }
    spell_successful();
    damage = sdamage;
    lifesteal = damage*2/3;
    if(lifesteal < 1) lifesteal = 1;
    lifesteal = lifesteal * -1;
    element = "untyped";
    if(blasttype == "glacial") element = "cold";
    if(blasttype == "brimstone") element = "fire";
    if(blasttype == "lifedrinker") element = "negative energy";
    if(blasttype == "vitriolic") element = "acid";
    descriptor = get_descript();

//    if(caster->Thaco(1,target,0) <= roll_dice(1,20) || blasttype == "vitriolic") {
// we're not using this for now as it makes the class incredibly difficult to balance against the rest.
// we can maybe sub this out for the rangedTouchAC(target) function once it's working pl0x!

      tell_object(caster,"%^MAGENTA%^In a single motion you direct a blast of "+descriptor+" to strike "+target->QCN+" squarely!%^RESET%^");
      tell_object(target,"%^MAGENTA%^"+caster->QCN+" directs a blast of "+descriptor+" to strike you!%^RESET%^");
      tell_room(place,"%^MAGENTA%^"+caster->QCN+" directs a blast of "+descriptor+" to strike "+target->QCN+" squarely!%^RESET%^",({ caster, target}) );

      damage_targ(target, target->return_target_limb(), damage, element);
      if(FEATS_D->usable_feat(caster,"hellfire blast")) do_hellfire_damage(target,"full");
      do_secondary(target);
/*    }
    else {
      tell_object(caster,"%^MAGENTA%^In a single motion you direct a blast of "+descriptor+" at "+target->QCN+", but it misses!%^RESET%^");
      tell_object(target,"%^MAGENTA%^"+caster->QCN+" directs a blast of "+descriptor+" at you, but it misses!%^RESET%^");
      tell_room(place,"%^MAGENTA%^"+caster->QCN+" directs a blast of "+descriptor+" at "+target->QCN+", but it misses!%^RESET%^",({ caster, target}) );
    } */
    dest_effect();
}

void dest_effect() {
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}

void do_secondary(object victim) {
    int duration;
    object secondary;
    if(!objectp(victim)) return;

    switch(blasttype) { // secondary effects! These will be tracked & maintained by objects on the target, to prevent glitches.
      case "frightful":
        set_save("will");
        if(!do_save(victim,0)) {
          tell_object(victim,"%^BOLD%^%^WHITE%^The impact of the blast leaves you shaking and fearful!%^RESET%^");
          tell_room(environment(victim),"%^BOLD%^%^WHITE%^The impact of the blast leaves "+victim->QCN+" shaking!%^RESET%^",victim);
          duration = 60/ROUND_LENGTH; // shaken, 1min
          secondary = present("eldritch_frightful_xxx",victim);
          if(!objectp(secondary)) {
            secondary = new(SECONDARYOBS"eldritch_frightful");
            secondary->move(victim);
          }
          secondary->activate(duration);
        }
      break;
      case "glacial":
        set_save("fort");
        if(!do_save(victim,0)) {
          tell_object(victim,"%^BOLD%^%^CYAN%^The icy blast chills you to the bone, slowing your movements!%^RESET%^");
          tell_room(environment(victim),"%^BOLD%^%^CYAN%^The icy blast chills "+victim->QCN+" and slows "+victim->QP+" movements!%^RESET%^",victim);
          duration = 600/ROUND_LENGTH; // -4 dex, 10min
          secondary = present("eldritch_glacial_xxx",victim);
          if(!objectp(secondary)) {
            secondary = new(SECONDARYOBS"eldritch_glacial");
            secondary->move(victim);
          }
          secondary->activate(duration);
        }
      break;
      case "brimstone":
        set_save("reflex");
        if(!do_save(victim,0)) {
          tell_object(victim,"%^BOLD%^%^RED%^The searing blast sets you aflame!%^RESET%^");
          tell_room(environment(victim),"%^BOLD%^%^RED%^The searing blast sets "+victim->QCN+" aflame!%^RESET%^",victim);
          duration = (clevel/5)+1; // 2d6 dmg, 1 round per 5 lvls of warlock
          secondary = present("eldritch_brimstone_xxx",victim);
          if(!objectp(secondary)) {
            secondary = new(SECONDARYOBS"eldritch_brimstone");
            secondary->move(victim);
          }
          secondary->activate(duration,clevel);
        }
      break;
      case "lifedrinker":
        if(!washealed) { // need this to only trigger once per cast. Else it will be off the charts!!
          tell_object(caster,"%^BOLD%^%^GREEN%^The blast leeches the life of its target, restoring your health!%^RESET%^");
          damage_targ(caster,"torso",lifesteal,"positive energy");
          washealed = 1;
        }
      break;
      case "vitriolic":
        tell_object(victim,"%^BOLD%^%^GREEN%^The noxious blast burns into your skin!%^RESET%^");
        tell_room(environment(victim),"%^BOLD%^%^GREEN%^The noxious blast burns into "+victim->QCN+"'s skin!%^RESET%^",victim);
        duration = (clevel/5)+1; // 2d6 dmg, 1 round per 5 lvls of warlock
        secondary = present("eldritch_vitriolic_xxx",victim);
        if(!objectp(secondary)) {
          secondary = new(SECONDARYOBS"eldritch_vitriolic");
          secondary->move(victim);
        }
        secondary->activate(duration,clevel);
      break;
      case "beshadowed":
        set_save("fort");
        if(!do_save(victim,0)) {
          tell_object(victim,"%^BOLD%^%^WHITE%^The blast of shadowy energy washes over your vision, blacking out the world around you!%^RESET%^");
          tell_room(environment(victim),"%^BOLD%^%^WHITE%^"+victim->QCN+" blinks and stares about sightlessly!%^RESET%^",victim);
          victim->set_temporary_blinded(1); // blinded, 1 round
        }
      break;
      case "binding":
        set_save("will");
        if(!do_save(victim,0)) {
          tell_object(victim,"%^BOLD%^%^WHITE%^Your limbs sieze up as the blast impacts you!%^RESET%^");
          tell_room(environment(victim),"%^BOLD%^%^WHITE%^"+victim->QCN+"'s limbs appear to sieze up as the blast impacts "+victim->QO+"!%^RESET%^",victim);
          victim->set_paralyzed(((ROUND_LENGTH-1) * 2),"You can't get your body to move!"); // stunned, 1 round - paralyze is x/2+1 duration in seconds.
        }
      break;
    }
}

void do_hellfire_damage(object victim, string potency) {
    if(!objectp(victim)) return;

    tell_room(environment(victim),"%^BOLD%^%^BLACK%^The eldritch blast blazes with %^RESET%^%^RED%^in%^BOLD%^%^RED%^f%^RESET%^%^RED%^ern%^BOLD%^%^RED%^a%^RESET%^%^RED%^l %^BOLD%^%^BLACK%^power!%^RESET%^");
    if(potency == "full") damage_targ(victim, victim->return_target_limb(), roll_dice(10,6), "untyped");
    else damage_targ(victim, victim->return_target_limb(), roll_dice(5,6), "untyped");
}

string get_descript() {
    string myreturn;
    switch(blasttype) {
      case "frightful": myreturn = "%^BLUE%^ma%^MAGENTA%^l%^BLUE%^ign%^BOLD%^%^BLACK%^an%^RESET%^%^BLUE%^t e%^MAGENTA%^n%^BOLD%^%^BLACK%^e%^RESET%^%^BLUE%^r%^RESET%^g%^BLUE%^y%^MAGENTA%^"; break;
      case "glacial": myreturn = "%^CYAN%^c%^BOLD%^%^CYAN%^r%^RESET%^%^CYAN%^a%^RESET%^c%^BOLD%^%^WHITE%^k%^BOLD%^%^BLUE%^l%^RESET%^%^CYAN%^i%^BOLD%^%^CYAN%^n%^RESET%^%^CYAN%^g e%^BOLD%^%^BLUE%^n%^BOLD%^%^CYAN%^e%^RESET%^%^CYAN%^r%^BOLD%^%^WHITE%^g%^RESET%^%^CYAN%^y%^MAGENTA%^"; break;
      case "brimstone": myreturn = "%^RED%^s%^BOLD%^%^RED%^e%^YELLOW%^a%^RESET%^%^RED%^r%^MAGENTA%^i%^BOLD%^%^RED%^n%^RESET%^%^RED%^g e%^BOLD%^%^RED%^n%^BOLD%^%^WHITE%^e%^RESET%^%^RED%^r%^BOLD%^%^RED%^g%^RESET%^%^RED%^y%^MAGENTA%^"; break;
      case "lifedrinker": myreturn = "%^GREEN%^s%^BOLD%^%^GREEN%^ee%^RESET%^%^GREEN%^th%^BOLD%^%^GREEN%^i%^RESET%^%^GREEN%^ng e%^BOLD%^%^GREEN%^n%^RESET%^%^GREEN%^er%^BOLD%^%^GREEN%^g%^RESET%^%^GREEN%^y%^MAGENTA%^"; break;
      case "vitriolic": myreturn = "%^GREEN%^n%^BOLD%^%^WHITE%^o%^BOLD%^%^GREEN%^x%^RESET%^%^GREEN%^i%^CYAN%^o%^BOLD%^%^GREEN%^u%^RESET%^%^GREEN%^s e%^YELLOW%^n%^BOLD%^%^GREEN%^e%^RESET%^%^GREEN%^r%^CYAN%^g%^GREEN%^y%^RESET%^%^MAGENTA%^"; break;
      case "beshadowed": myreturn = "%^BOLD%^%^BLACK%^te%^RESET%^n%^BOLD%^%^BLACK%^ebr%^RESET%^%^BLUE%^o%^BOLD%^%^BLACK%^us e%^RESET%^ne%^BOLD%^%^BLACK%^rgy%^RESET%^%^MAGENTA%^"; break;
      case "binding": myreturn = "%^BOLD%^%^BLUE%^s%^BOLD%^%^WHITE%^u%^BOLD%^%^CYAN%^r%^BOLD%^%^WHITE%^g%^RESET%^%^CYAN%^i%^BOLD%^%^CYAN%^n%^BOLD%^%^GREEN%^g %^BOLD%^%^WHITE%^e%^BOLD%^%^BLUE%^n%^BOLD%^%^CYAN%^e%^BOLD%^%^WHITE%^r%^RESET%^%^CYAN%^g%^BOLD%^%^CYAN%^y%^RESET%^%^MAGENTA%^"; break;
      case "utterdark": myreturn = "m%^BOLD%^%^BLACK%^al%^RESET%^%^MAGENTA%^ef%^RESET%^i%^MAGENTA%^c e%^BOLD%^%^BLACK%^n%^RESET%^e%^MAGENTA%^rgy"; break;
      default: myreturn = "e%^BOLD%^%^MAGENTA%^n%^RESET%^%^MAGENTA%^e%^BOLD%^%^WHITE%^r%^BOLD%^%^MAGENTA%^g%^RESET%^%^MAGENTA%^y"; break;
    }
    return myreturn;
}
