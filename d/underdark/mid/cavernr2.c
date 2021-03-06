#include <std.h>
#include "../defs.h"
inherit INH+"cavern";

void create(){ 
   ::create();
   set_long("%^BLUE%^A vast limestone cavern%^RESET%^\n"+ ::query_long() +"%^CYAN%^  Further southeast is what "
"appears to be a spreading pile of %^ORANGE%^rubble%^CYAN%^, heaped up against the cavern wall."
"%^RESET%^\n");
   add_item(({"pile","rubble"}),"%^CYAN%^Further southeast is what appears to be a spreading pile of "
"%^BOLD%^%^BLACK%^stones %^RESET%^%^CYAN%^and %^ORANGE%^debris%^CYAN%^, perhaps dislodged in some underground "
"tremor.  You'd have to get closer to get a better look at it.%^RESET%^");
   set_exits(([
     "west":MID"cavernp2",
     "northwest":MID"cavernp3",
     "south":MID"cavernr1",
   ]));
}
