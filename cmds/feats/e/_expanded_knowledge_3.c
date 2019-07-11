#include <std.h>
#include <daemons.h>

inherit FEAT;

void create() {
    ::create();
    feat_type("permanent");
    feat_category("Psionics");
    feat_name("expanded knowledge 3");
    feat_desc("This feat allows a psionic character to master an additional power of any level up to one less than he can cast. The selected power may be from any psionic power list, even those normally reserved for a specific discipline.");
    feat_prereq("Psywarrior L21, Psion L21");
    permanent(1);
    psionic(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob) {
    if(!objectp(ob)) { return 0; }
    if(ob->query_class_level("psywarrior") < 21 && ob->query_class_level("psion") < 21) {
        dest_effect();
        return 0;
    }    
    if(!FEATS_D->has_feat(ob,"expanded knowledge 2")){
        dest_effect();
        return 0;
    }
    return ::prerequisites(ob);
}


void execute_feat() {
    ::execute_feat();
    dest_effect();
}

void permanent_effects(object ob) {
    ::permanent_effects(ob);
    dest_effect();
    return;
}

void reverse_permanent_effects(object ob) {
    ::reverse_permanent_effects(ob);
    dest_effect();
    return;
}

void dest_effect() {
    ::dest_effect();
    remove_feat(TO);
    return;
}

