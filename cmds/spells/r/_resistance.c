//updated to add psions and psywarrior to streamline spells - replaces biofeedback ~Circe~ 10/26/19
#include <priest.h>
#include <daemons.h>
inherit SPELL;

int bonus;

void create(){
   ::create();
   set_spell_name("resistance");
   set_spell_level(([ "bard" : 1,"druid" : 1, "paladin" : 1, "mage" : 1, "cleric" : 1, "psywarrior" : 1, "psion" : 2 ]));
   set_spell_sphere("alteration");
   set_syntax("cast CLASS resistance");
   set_damage_desc("clevel/12 but no more than 4 to saving throws");
   set_description("By this spell, the caster imbues themselves with a small amount of resistance to harm.  The spell grants small bonus to will, fortitude and reflex.");
   set_verbal_comp();
   set_somatic_comp();
   set_helpful_spell(1);
}

string query_cast_string(){
   return "%^CYAN%^"+caster->QCN+" hums a few soft notes.%^RESET%^";
}

spell_effect(int prof) {
   if(!objectp(caster)){
      dest_effect();
      return;
   }
   if(interactive(caster)){
      tell_object(caster, "%^GREEN%^As the last note fades, you feel a light prickling of protection across your skin.");
      tell_room(place,"%^GREEN%^The last note fades as "+caster->QCN+" glances around.",caster);
   }
   bonus = clevel/12;
   bonus = bonus<1?1:bonus;
   bonus = bonus>4?4:bonus;

   caster->add_saving_bonus("all",bonus);
   spell_successful();
   addSpellToCaster();
}

void dest_effect(){
   if(objectp(caster)){
      caster->add_saving_bonus("all",-bonus);
   }
   ::dest_effect();
   if(objectp(TO)) TO->remove();
}
