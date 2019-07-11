#include <priest.h>
inherit SPELL;

int feattracker;

void create() {
    ::create();
    set_author("nienne");
    set_spell_name("spell turning");
    set_spell_level(([ "mage" : 7 ]));
    set_spell_sphere("abjuration");
    set_syntax("cast CLASS spell turning");
    set_description("The most skilled of abjurationists can use such a spell to raise a protective ward around themselves"
". While it holds, it will have a chance to reflect any spells which are directly aimed at the caster, regardless of "
"whether they are hostile or friendly. The ward will not reflect splash damage or AOE, but only direct-targetted spells. "
"This spell does not stack with the 'reflection' or 'spell reflection' feats.\n\nNon-specialized mages cannot cast this spell.");
    set_verbal_comp();
    set_somatic_comp();
     // school specific mage spell
    set_components(([
      "mage" : ([ "small silver mirror" : 1, "glass rod" : 1, ]),
    ]));
	set_helpful_spell(1);
}

int preSpell(){
   if(member_array("spell reflection",(string*)caster->query_temporary_feats()) != -1) {
      tell_object(CASTER,"You are already under the influence of such an effect.");
      return 0;
   }
   return 1;
}

string query_cast_string() {
    return "%^MAGENTA%^"+caster->QCN+" traces an elaborate pattern in the air before "+caster->QO+".%^RESET%^";
}

void spell_effect(int prof) {
    int i;
    if (!objectp(caster)) {
      dest_effect();
      return;
    }
    if (interactive(caster)) {
      tell_object(caster, "%^BOLD%^%^MAGENTA%^You trace a protective glyph in the air before you, which flares brightly "
"and then vanishes!%^RESET%^");
      tell_room(place,"%^BOLD%^%^MAGENTA%^A glyph appears in a bright flare of light before "+caster->QCN+", and then "
"vanishes!%^RESET%^",caster);
    }
    if(member_array("spell reflection",(string*)caster->query_temporary_feats()) == -1) {
      caster->add_temporary_feat("spell reflection");
      feattracker = 1;
    }
    call_out("dest_effect", 1800 + (clevel * 10));
    spell_successful();
    addSpellToCaster();
}

void dest_effect(){
    int i;
    if(objectp(CASTER)) {
      tell_object(caster,"%^MAGENTA%^You feel the protective spell ward fade from you.%^RESET%^");
      if(feattracker == 1) caster->remove_temporary_feat("spell reflection");
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}