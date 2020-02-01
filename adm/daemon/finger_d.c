//      /bin/daemon/fingerd.c
//      Nightmare Mudlib finger daemon
//      based on finger daemon from the TMI mudlib coded by
//      Sulam, Jubal, Brian, and Buddha (12.8.91 - 3.8.92)
//      written by Descartes of Borg 22 November 1992
//  removed marriage info. and did a little other security cleanup *Styx* 11/25/06

#include <objects.h>
#include <dirs.h>
#include <daemons.h>
#include <conf.h>
#include <clock.h>
#include <std.h>
#define AVA_D "/daemon/avatar_d.c"
#define SGUILDS ({"Watcher"})

inherit OB_USER;
string true_name;
string myclass;

string alig_str(string what, int x);
string query_title();
string query_last_on();
string query_hah(object ob, int verbose);
static void complete_variables();

void create() {
    seteuid(getuid());
}

string general_finger_display() {
    string finger;
    object *who;
    int i;
    string level;

    finger = " %^BOLD%^%^CYAN%^                 Members of the "+mud_name()+" Reality\n";
    finger += "   %^CYAN%^"+mud_name()+" has been up since PDT "+ctime(time()-uptime())+"\n";
    finger += "   %^CYAN%^"+mud_name()+" runs "+version()+" driver with "+mudlib()+"\n";
    finger += "%^YELLOW%^"+alig_str("Player", 15);
    finger += "%^BOLD%^%^CYAN%^"+alig_str("Real Name", 30);
    finger += "%^BOLD%^%^MAGENTA%^"+alig_str("Idle", 5);
    finger += "\n";
    finger += "%^BOLD%^%^BLUE%^-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
    who = users();
    for (i=0; i<sizeof(who); i++) {
        if (who[i]->query_quietness() && wizardp(who[i])) continue;
        if (!who[i]->query_name()) continue;
        if (avatarp(who[i]) && ((string)who[i]->query_vis_name() != (string)who[i]->query_name())) {
            finger += "%^YELLOW%^"+alig_str(capitalize((string)who[i]->query_vis_name()), 15);
            finger += "%^BOLD%^%^CYAN%^"+alig_str("Unknown", 30);
            finger += "%^BOLD%^%^MAGENTA%^"+alig_str(parse_time(query_idle(who[i])), 8);
            finger += "\n";
        } else {
            finger += "%^YELLOW%^"+alig_str(capitalize((string)who[i]->query_name()), 15);
            finger += "%^BOLD%^%^CYAN%^"+alig_str((string)who[i]->query_rname(), 30);
            finger += "%^BOLD%^%^MAGENTA%^"+alig_str(parse_time(query_idle(who[i])), 8);
            finger += "\n";
        }
    }
    finger += "%^BOLD%^%^BLUE%^-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
    return finger;
}



string user_finger_display(string who) {
    mapping mail_stat;
    string tmp;
    string pos;
    object ob;
    string uh_oh;
    string finger, position;
    string level, *tmp9;
    int invis, quiet, castwiz, obwiz, gi;
    int birth2;

    if (!who) return "You must specify whom you wish to finger.\n";
    true_name = lower_case(who);
    ob = find_player(lower_case(who));
    tmp = true_name;
    who = sprintf("%s/%s/%s", DIR_USERS, tmp[0..0], tmp);
    if (file_size(who + ".o") < 0)
        return "No such member of the Shadow Gate World.\n";
    restore_object(who);
    mail_stat = (mapping)LOCALPOST_D->mail_status(tmp);
    if (ob) {
        finger =""+query_title()+"\n";
        if (file_exists("/d/save/background/"+query_true_name()+".htm"))
            finger += "Background on file.\n";
        else
            finger += "No background on file.\n";
        if(pointerp(tmp9 = (string *)ob->query_shguild()) && sizeof(tmp9)){
            finger += "Member of:\n";
            for(gi=0;gi<sizeof(tmp9);gi++){
                finger += "  " + tmp9[gi] + "\n";
            }
        }
        uh_oh = capitalize((string)ob->query_gender()) + " ";
        uh_oh += (string)ob->query_race() + " ";
        finger += alig_str(uh_oh, 45);
        position = ob->query_position();
        if (wizardp(ob)) {
            switch (position) {
            case "apprentice":
                level = "Apprentice"; break;
            case "creator":
                level = "Creator"; break;
            case "developer":
                level = "Developer"; break;
            case "Developer":
                level = "Developer"; break;
            case "overseer":
                level = "Overseer"; break;
            case "Overseer":
                level = "Overseer"; break;
            case "Admin":
                level = "Game Admin"; break;
            default:
                level = "Immortal"; break;
            }
        }
        if (!wizardp(ob)) {
            level = "" + (int)ob->query_level() + "";
        }
        if (wizardp(ob))
            finger += "Level: "+level;
        finger += "\n";
        //finger += "In real life: ";
        //finger += alig_str((string)ob->query_rname(), 31);
// making marriage info. avatar only *Styx* 11/25/06
        if(avatarp(TP)) {
          finger += "Immortal eyes only - ";
          if (!ob->query_married())
            finger += "Single\n";
          else
            finger += "Married to " + capitalize((string)ob->query_married()) +"\n";
	}
        birth = (int)ob->query_birthday();
        birth2 = birth - (int)ob->query_start_age() * YEAR;
        if (this_player() && archp(this_player()))
            if ((uh_oh = (string)ob->query_email()) != "")
                finger += "Email: " + uh_oh + "\n";
        invis = (int)ob->query_invis();
        quiet = (int)ob->query_quietness();
        castwiz = wizardp(this_player());
        obwiz= wizardp(ob);
        if(invis && ob != TP || (quiet && obwiz && !castwiz ) )
            finger += "Last on: ";
        else {
            uh_oh = query_hah(ob, 1);
            if (uh_oh != "")
                finger += uh_oh + "\n";
            finger += "On since: ";
        }
        finger += query_last_on() + "\n";

        /* if (this_player() && archp(this_player())) */
        /*         finger += " from:  " + (string)ob->query_ip() + "\n"; */
        /*     else */
        /*         finger += "\n";    */

        if (!mail_stat["unread"])
            finger += "No unread mail.\n";
        else if (mail_stat["unread"] == 1)
            finger += "1 unread piece of mail.\n";
        else
            finger += mail_stat["unread"] + " unread pieces of mail.\n";
        if(wizardp(ob)) {
          tmp = user_path(tmp);
          if (file_size(tmp + ".project") >= 0)
            finger += "Project: "+read_file(tmp+".project");
          if (file_size(tmp+".plan") >= 0)
            finger += "Plan:\n"+read_file(tmp+".plan");
          else
            finger += "No plan.\n";
        }
    } else {
        complete_variables();
        finger = query_title()+ "\n";
        if (get_perma_death() > 0 && get_perma_death() > time()){
            finger += "%^BOLD%^%^YELLOW%^DECEASED%^RESET%^\n";
        }
        if (file_exists("/d/save/background/"+query_true_name()+".htm"))
            finger += "Background on file.\n";
        else
            finger += "No background on file.\n";
        if(pointerp(tmp9 = query_shguild()) && sizeof(tmp9)){
            finger += "Member of:\n";
            for(gi=0;gi<sizeof(tmp9);gi++){
                finger += "  " + tmp9[gi] + "\n";
            }
        }
        uh_oh = capitalize(query_gender());
        uh_oh += " " + query_race() + " ";
        //if (query_guild_string() && query("show guild"))
        finger += alig_str(uh_oh, 45);
        if (member_array(query_position(), MORTAL_POSITIONS)==-1) {
            position = query_position();
            switch (position) {
            case "apprentice":
                level = "Apprentice"; break;
            case "creator":
                level = "Creator"; break;
            case "developer":
                level = "Developer";break;
            case "overseer":
                level = "Overseer";break;
            case "Admin":
                level = "Game Admin"; break;
            default:
                level = "Immortal"; break;
            }
            finger += "Level: "+level+"\n";   // 1 nov 93 for offline
        } else finger += "Level: Unknown\n";
        //finger += "In real life: ";
        //finger += alig_str(query_rname(), 31);
// making marriage info. avatar only *Styx* 11/25/06
        if(avatarp(TP)) {
          finger += "Immortal eyes only - ";
          if (query_married())
            finger += "Married to "+capitalize(query_married())+"\n";
          else
            finger += "Single\n";
	}
        birth = query_birthday();
        birth2 = birth - query_start_age()*YEAR;
        /* finger += "Birthday: "+date(birth)+" "+capitalize(month(birth))+", "+year(birth2)+" SG\n"; */
        if (this_player() && archp(this_player()))
            if ((uh_oh = query_email()) != "")
                finger += "Email: " + uh_oh + "\n";
        if (this_player() && archp(this_player()))
            finger += "Last on: " + query_last_on() + "\n";
        else finger += "Last on: "+query_last_on()+"\n";
        // "from "+
	// (query_property("where block") ? "Anonymous" : query_ip())+"\n";
        // ((1) ? "Anonymous" : query_ip())+"\n";
        //finger += query_cap_name() + " has ";
        if (!mail_stat["unread"])
            finger += "No unread mail.\n";
        else if (mail_stat["unread"] == 1)
            finger += "1 unread piece of mail.\n";
        else
            finger += mail_stat["unread"]+" unread pieces of mail.\n";
//        if(wizardp(ob)) {
        if((member_array(query_position(), MORTAL_POSITIONS)==-1) || wizardp(ob)) {
          tmp = user_path(tmp);
          if (file_size(tmp+".project") >= 0)
            finger += "Project: "+read_file(tmp+".project");
          if (file_size(tmp+".plan") >= 0)
            finger += "Plan:\n" + read_file(tmp + ".plan");
          else
            finger += "No plan.\n";
        }
    }
    if(query("ooc contact"))
    {
        finger += query("ooc contact");
    }
    return finger;
}

string query_hah(object ob, int verbose) {
    int time, tmp;
    string line;

    if (!ob) return 0;
    if (!interactive(ob)) {
        if (verbose) return "Disconnected.";
        else return "disconnected";
    }
    line = "";
    time = query_idle(ob);
    if (time < 60) return line;
    tmp = time / 86400;
    if (tmp) {
        if (!verbose) return tmp + " d";
        else line += tmp + " day" + (tmp>1 ? "s " : " ");
    }
    tmp = (time%86400)/3600;
    if (tmp) {
        if (!verbose) {
            if (tmp>9) return tmp+" h";
            else line += tmp+":";
        } else line += tmp + " hour"+(tmp>1 ? "s " : " ");
    }
    tmp = (time%3600)/60;
    if (tmp) {
        if (!verbose) {
            if (strlen(line)>0 && tmp < 10) line += "0";
            line += tmp;
        } else line += tmp+ " minute"+(tmp>1 ? "s " : " ");
    }
    if (verbose) line += "idle time";
    else line += "idle";
    return line;
}

string query_last_on() {
    if (!query_invis()) return real_last_on;
    return last_on;
}

/*
string query_title() {
    string pre, post;
    if (!getenv("TITLE")) return query_cap_name();
    if (sscanf(getenv("TITLE"), "%s $N %s", pre, post) != 2) {
        if (sscanf(getenv("TITLE"), "$N %s", post) != 1) return
            capitalize(query_true_name());
        else return capitalize(query_true_name())+" "+post;
    }
    return pre+" "+capitalize(query_true_name())+" "+post;
}
*/

string alig_str(string what, int x) {
    int y;
    string out;

    out = "";
    if (!what) return 0;
    y = strlen(what);
    out += what;
    if (y>x) {
        out = what[0..x-1] + " ";
        return out;
    }
    x = x-y;
    if (x<1) return out;
    for (y=0; y<=x; y++) out += " ";
    return out;
}

string query_cap_name() {
    return capitalize(query_true_name());
}

void restore_player_file(string file) {
    restore_object(file);
}

void save_player(string file) {
    save_object(file);
}

static void complete_variables() {
    if (!true_name) true_name = "";
    if (!real_name) real_name = "???";
    if (!myclass) myclass = "child";
        if (!last_on) last_on = "no record";
    if (!ip) ip = "nowhere";
    if (!level) level = -1;
    //if (!race) race = "Unborn";
    if (!player_age) player_age = 0;
}
