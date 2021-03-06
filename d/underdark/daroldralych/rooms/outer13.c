#include <std.h>
#include "../defs.h"
inherit INH+"street";

void create(){ 
   ::create();
   set_long("%^BOLD%^%^BLACK%^City street%^RESET%^\n"
"%^BLUE%^This large street is obviously a major thoroughfare, part of the one that circuits the city's outer limits.  "
"Smooth %^ORANGE%^s%^BOLD%^%^BLACK%^t%^RESET%^%^ORANGE%^o%^BOLD%^%^BLACK%^n%^RESET%^%^ORANGE%^e %^BLUE%^forms the ground "
"beneath your feet, allowing for ease in walking, though it lacks the cleanliness here of the rest of the city.  Only "
"%^MAGENTA%^d%^BOLD%^%^BLACK%^ar%^RESET%^%^MAGENTA%^kn%^BOLD%^%^BLACK%^es%^RESET%^%^MAGENTA%^s%^BLUE%^ fills the air "
"above you, the ceiling too high up to be seen by any form of normal vision.  At short intervals along the length of the "
"street are slender carved posts of %^BLACK%^%^BOLD%^ob%^RESET%^si%^BOLD%^%^BLACK%^dian%^RESET%^%^BLUE%^, each supporting "
"a globe of pale %^MAGENTA%^fae%^BOLD%^r%^RESET%^%^MAGENTA%^ie fire%^BLUE%^ that sheds faint light around it.  Rising up "
"on the southern side of the road are the walls of the cavern, dotted with the occasional mid- or lower-class drow house "
"carved into the dull surface of the rock itself.  The road continues east through what might pass for the city's slums, "
"while further west it intersects with another street.%^RESET%^\n");

   add_item(({"houses","buildings"}),"%^BLUE%^Upon the northern side of the road rise enclosed buildings, probably "
"belonging to the lowest-ranked houses.  They bear little of interest, none standing out against another; if nothing else"
", they bear less of the magnificent architecture seen elsewhere in the city, and some are clearly empty of occupants.  "
"No doubt you stand within a lower-class section of town.");
   add_item(({"street","streets"}),"%^BLUE%^The stone street is smooth beneath your feet, although it seems a little more "
"%^ORANGE%^gru%^BOLD%^%^BLACK%^b%^RESET%^%^ORANGE%^by %^BLUE%^here than elsewhere in the city.%^RESET%^");
   add_item(({"wall","walls"}),"%^BLUE%^The southern side of the road is bordered by the walls of the cavern, which rise "
"up and disappear into the %^MAGENTA%^da%^BOLD%^%^BLACK%^r%^RESET%^%^MAGENTA%^ke%^BOLD%^%^BLACK%^ne%^RESET%^%^MAGENTA%^d "
"%^BLUE%^limits of your vision above.  The occasional signs of a mid- or lower-class drow house are dotted across its "
"stony surface, carved into the face of the rock itself.  If anything, there seem far more living spaces situated within "
"this vast cavern's walls than upon its floor, sign perhaps that only the most prestigious of lineages are afforded the "
"central space.%^RESET%^");
   set_exits(([
     "east":ROOMS"outer14",
     "west":ROOMS"outer12",
   ]));
}
