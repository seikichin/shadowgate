#include <std.h>
#include "../dragon.h";

inherit BSEWER;

void create() {
    ::create();
    set_property("light",-1);
    set_property("indoors",1);
    set_short("Sanctuary Sewers");
    set_long(
      "%^BOLD%^%^BLACK%^These are the disgusting sewers under the city of Sanctuary. They are"+
      " filled with many strange objects. The tunnel stretches off for miles"+
      " toward the south. The dark walls are covered with disgusting slime"+
      " mold from the many decades of sewage that flowed within here."
    );
    set_exits(([
       "north" : SEWER+"sewer23",
       "south" : SEWER+"sewer25"
    ] ));
    set_items(([
       "sewers":"The disgusting tunnels of waste under Sanctuary."
    ] ));
    set_smell("default","The smell of human and demi-human waste is becoming overwhelming.");
}
