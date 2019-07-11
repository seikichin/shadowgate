//      /bin/adm/_whobanished.c
//      from the Nightmare Mudlib
//      lists all names banished from usage
//      originally written by Shadowwolf@Nightmare 
//      rewritten for the new Nightmare security system by Descartes of Borg
//      930809

#include <std.h>
#include <security.h>
#include <daemons.h>

int cmd_whoretired(string str) {
    string *noms;

    if(!archp(previous_object())) return 0;
    seteuid(UID_BANISH);
    noms = (string *)BANISH_D->query_retired();
    seteuid(getuid());
    if(str) {
        if(member_array(lower_case(str), noms) == -1) 
          write(str+" is not currently a retired name.\n");
        else write(str+" is a retired name.\n");
    }
    else {
        write("These names are currently retired:\n");
    noms = sort_array(noms,"sort_em",this_object());
        this_player()->more(explode(format_page(noms, 4), "\n"));
    }
    return 1;
}

int sort_em(string one, string two) {
     return strcmp(one, two);
}

void help() {
    write("Syntax: <whoretired ([name])>\n\n"
      "Without an argument, this command lists all names currently\n"
      "listed as being retired.  Otherwise it will confirm whether\n"
      "the name is retired or not.\n"
    );
}
