//A rip from the flint object (/d/common/obj/misc/flint.c 
//Makes much more sense this way - and it's a command that 
//should simply further RP - Saide 

#include <std.h>

inherit DAEMON;

void help() {
    write("Usage:  <gather>\n");
    write("This command will let you attempt to gather "+
    "firewood.  There are checks involved and you obviously "+
    "can't gather wood indoors.");
}

int cmd_gather(string str) {
    int wood, diff, terrain_type;
    object ob;
    string terrain;

    if(ETP->query_property("no sticks")) {
        write("You don't seem to find any usable sticks.");
        tell_room(ETP, TPQCN+" seems to be poking around for something.", TP);
        return 1;
    }
    if(ETP->query_property("indoors")) {
	    write(" There is no wood indoors!");
	    return 1;
    }
 
    if(present("wood 3")) {
	    write("You already have a lot of wood gathered.");
	    return 1;
    }
    terrain = ETP->query_terrain();
    terrain_type = TERRAIN_GROUPS[terrain];
    switch(terrain_type) {
      	case 0 :	diff = 3;	break;
      	case 1 :	diff = 5;	break;
      	case 2 :	diff = 7;	break;
      	case 3 :	diff = 7;	break;
      	case 4 :	diff = 11;	break;
      	case 5 :	diff = 15;	break;
      	case 6 :	diff = 15;	break;
      	case 7 : 	diff = 13;	break;
      	case 8 : 	diff = 9;	break;
      	case 9 :	diff = 18;	break;
      	case 10:	diff = 20;	break;
      	default:  	diff = 10;	break;
    }
    if(random(diff) > 1) {
	    write("You search around but don't find any suitable firewood.");
        tell_room(ETP, TPQCN+" seems to be poking around for something.", TP);
    	return 1;
    }
// if all succeeds....        
	write("You gather up some wood for a fire.");
	tell_room(ETP, TPQCN+" gathers up some pieces of wood.", TP);
	new("/d/common/obj/misc/wood")->move(TP);
//	wood=1;	  wasn't being used
	return 1;
}