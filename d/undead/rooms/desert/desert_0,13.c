#include "../../undead.h"

inherit INH+"desert_one.c";

void create() 
{
    ::create();

    set_exits(([
        "east"      :DES+"desert_0,14",
        "south"     :DES+"desert_1,13",
        "west"      :DES+"desert_0,12"
             ]));
}