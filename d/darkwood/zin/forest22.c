//      Darkwood Forest
//      Zincarla@ShadowGate
//      04/06/95

#include <std.h>
#include "./zin.h"

inherit ROOM;

void create() {
    ::create();
    seteuid(getuid());
    set_smell("default", "It smells of decay and horrid death.");
    set_listen("default", "The wind whistles slowly through the trees.");
    set_property("indoors", 0);
    set_property("light", 1);
    set("short", "Darkwood Forest");
    set("long", "The presence of Darkwood Forest almost appears to be "+
        "closing in on you.  The ancient trees are unnaturally dense "+
        "which makes passage very slow.  High above you, the tree "+
        "branches are locked in a twisted battle of survival "+
        "effectivly blotting out the sky and any light or warmth it "+
        "provides.  You feel the presence of evil and chaos concield "+
        "in the many dark shadows cast all about forest.   The forest "+
        "floor is matted with many rotting leaves and old brittle "+
        "sticks.  There appears to be two passable gaps through the "+
        "maze of trees to the west and east.");
    set_items( ([
        "trees": "They are ancient and knotted with age.",
        "branches": "They are twisted together and block the sun.",
        "shadows": "They dance about...almost watching you...",
        "floor": "It is matted with many leaves and branches.",
        "leaves": "They are rotting and cover the entire ground.",
        "sticks": "The lie scattered about.",
    ]) );
    set_exits( ([
        "west": ROOM_DIR+"forest23",
        "east": ROOM_DIR+"forest21",
    ]) );
}

void init(){
  ::init();
  do_random_encounters(({MON_DIR+"nymph",MON_DIR+"dwarf",MON_DIR+"goblin"}),60,4);
}
