#include <std.h>
#include "/d/deku/inherits/forest.h"

inherit CAT_HW_F;

void create() 
{
	::create();
	set_long(TO->query_long() + "  %^YELLOW%^The tunnel continues northward and "+
	"southward here.");
	set_exits(([
	"north" : CAT_ROOMS"cat_hw_first_6",
	"south" : CAT_ROOMS"cat_hw_first_4"
	] )); 
}
