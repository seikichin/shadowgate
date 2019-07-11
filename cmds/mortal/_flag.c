/*=====================================================
flag command 
    supports turning off exp - flag noexp - gain no exp at all 
    supports modifying character improvement tax percent - flag ctp % flag ctp 100
    supports setting up a RPFlag for current environment that will remain as long as
    players are still there - flag rpflag 
    rpflag will show up on rumors/a short description of the room on the who list 
    pkflag 
=====================================================*/
#include <daemons.h>
#include <std.h>
#include <security.h>

#define SUPPORTEDFLAGS ({"experience gain", "character improvement tax", "roleplay flag", "player kill", "scaled level", "feature", "simple inventory"})
inherit DAEMON;
void help();

varargs void do_flag_display(object who, object targ)
{
    int x, j, remaining;
    string *activeEvents, eventName, notification, eventMsg, *featureVoting, featureName;
    string yesVotes = "", noVotes = "", featureAuthor, ExpiresIn, ETA;
   
    if(!objectp(who)) return notify_fail("Something went wrong...");
    if(!objectp(targ) || !avatarp(targ)) targ = who;
    if(objectp(targ) && avatarp(targ) && targ != who)
    {
        tell_object(targ, "Flags for "+who->query_cap_name()+" as followed:\n");
    }
    tell_object(targ, "\n"+arrange_string("%^BOLD%^%^WHITE%^Flag ", 30) + "Setting\n");    
    for(x = 0;x < sizeof(SUPPORTEDFLAGS);x++)
    {
        if(SUPPORTEDFLAGS[x] == "feature") 
        {
            j = 30 - strlen("feature notifications");
            tell_object(targ, "%^BOLD%^%^WHITE%^Feature notifications"+ arrange_string(" ", j)+ "%^RESET%^"+"/daemon/user_d.c"->get_flag(who, "feature notifications"));
            continue;
        }
        j = 30 - strlen(SUPPORTEDFLAGS[x]);
        tell_object(targ, "%^BOLD%^%^WHITE%^"+capitalize(SUPPORTEDFLAGS[x]) + arrange_string(" ", j)+ "%^RESET%^"+"/daemon/user_d.c"->get_flag(who, SUPPORTEDFLAGS[x]));
        continue;
    }
    if(pointerp(activeEvents = WORLD_EVENTS_D->parsable_world_events(who)))
    {
        tell_object(targ, "\n%^BOLD%^%^CYAN%^Currently active events:%^RESET%^");
        tell_object(targ, "\n"+arrange_string("%^BOLD%^%^WHITE%^Event Title ", 34) + arrange_string("Time ", 18) + "Event Affect\n");
        
        for(x = 0;x < sizeof(activeEvents);x++)
        {
            eventName = activeEvents[x];
            j = 34 - strlen(eventName);
            if(!stringp(notification = WORLD_EVENTS_D->query_event_notification(eventName))) { notification = "Currently Active"; }
            if(!intp(remaining = WORLD_EVENTS_D->event_time_remaining(eventName))) { remaining = -1; }
            eventMsg = "%^BOLD%^%^WHITE%^"+eventName + arrange_string(" ", j);
            j = 18 - strlen(parse_time(remaining));//strlen(remaining + " mins");
            eventMsg += parse_time(remaining) + arrange_string(" ", j) + notification;
            tell_object(targ, eventMsg);            
        }        
    }
    if(pointerp(featureVoting = FEATURE_D->parsable_features(who)) && sizeof(featureVoting))
    {
        tell_object(targ, "\n%^BOLD%^%^CYAN%^Current features being voted on:%^RESET%^");
        tell_object(targ, "\n"+arrange_string("%^BOLD%^%^WHITE%^Feature Name ", 20) + arrange_string("Author", 10) + arrange_string("Yes", 4) + arrange_string("No", 4) + arrange_string("ETA", 10) + arrange_string("Expires In", 10)+"\n");
        for(x = 0;x < sizeof(featureVoting);x++)
        {
            featureName = featureVoting[x];            
            j = 20 - strlen(featureName);
            eventMsg = "%^BOLD%^%^WHITE%^"+featureName + arrange_string(" ", j);
            featureAuthor = FEATURE_D->get_feature_information(featureName, "Feature Author");
            j = 10 - strlen(featureAuthor);
            eventMsg += featureAuthor + arrange_string(" ", j);
            yesVotes = "";
            yesVotes += FEATURE_D->get_feature_information(featureName, "Yes Votes");
            j = 4 - strlen(yesVotes);
            eventMsg += yesVotes + arrange_string(" ", j);
            noVotes = "";
            noVotes += FEATURE_D->get_feature_information(featureName, "No Votes");
            j = 4 - strlen(noVotes);
            eventMsg += noVotes + arrange_string(" ", j);
            ETA = "";
            ETA += FEATURE_D->get_feature_information(featureName, "ETA");
            j = 10 - strlen(ETA);
            eventMsg += ETA + arrange_string(" ", j);
            ExpiresIn = "";
            ExpiresIn = FEATURE_D->get_feature_information(featureName, "Voting Expires In");
            j = 10 - strlen(ExpiresIn);
            eventMsg += ExpiresIn + arrange_string(" ", j);
            tell_object(targ, eventMsg);            
            continue;
        }        
    }
    return 1;
}

int cmd_flag(string str)
{
    object target;
    string mycommand, myplayer;
    string targ, arg, subarg, myVote, *pieces;
    int perc, base, res;
    if(!str)
    {
        do_flag_display(TP);
        return 1;
    }
    if(sscanf(str, "%s | %s", targ, arg) == 2)
    {
        targ = lower_case(targ);
        if(member_array(targ, SUPPORTEDFLAGS) == -1)
        {
            tell_object(TP, "\n%^BOLD%^%^WHITE%^Supported flags are currently : \n\n\t"+implode(SUPPORTEDFLAGS, "\n\t")+"%^RESET%^");
            return 1;
        }
        switch(targ)
        {            
            case "feature":
                if(arg == "add")
                {
                    if(!wizardp(TP)) return 0;
                    res = FEATURE_D->can_insert_feature(TP, "testcheckfeature");
                    if(res == -1) 
                    {
                        tell_object(TP, "Error.");
                        return 1;
                    }
                    else if(res == -2)
                    {
                        tell_object(TP, "Only immortals above the apprentice rank are allowed to "+
                        "add features for voting.");
                        return 1;
                    }
                    else if(res == 1)
                    {
                        new("/cmds/mortal/obj/featureadd.c")->move(TP);
                        return 1;
                    }
                    tell_object(TP, "Error.");
                    return 1;
                }
                if(sscanf(arg, "%s %s", arg, subarg) != 2)
                {
                    tell_object(TP, help());
                    return 1;
                }
                if(arg == "view")
                {
                    FEATURE_D->view_feature(TP, subarg);
                    return 1;
                }
                if(arg == "remove")
                {
                    res = FEATURE_D->kill_feature(TP, subarg);
                    if(res == -1)
                    {
                        tell_object(TP, "Invalid object trying to remove a feature.");
                        return 1;
                    }
                    if(res == -4)
                    {
                        tell_object(TP, capitalize(subarg)+" is an invalid feature.");
                        return 1;
                    }
                    if(res == -7)
                    {
                        tell_object(TP, "Invalid access to remove feature "+subarg+".");
                        return 1;
                    }
                    if(res == 1)
                    {
                        tell_object(TP, "Voting for feature "+subarg+" has been removed. "+
                        "It will be cleared from the daemon on the next check. Or you can do "+
                        "eval FEATURE_D->check_features() to remove it now.");
                        return 1;
                    }
                }
                if(arg == "notifications" || arg == "notification")
                {
                    if(subarg == "Off" || subarg == "off")
                    {
                        TP->set("feature notifications", 1);
                        tell_object(TP, "You will no longer periodically be notified "+
                        "about features you can still vote on or when feature voting "+
                        "ends.");
                        return 1;
                    }
                    if(subarg == "On" || subarg == "on")
                    {
                        TP->delete("feature notifications");
                        tell_object(TP, "You will now be periodically notified about "+
                        "features you can still vote on and when feature voting ends.");
                        return 1;
                    }
                    tell_object(TP, "Please specify on or off for feature notifications.");
                    return 1;
                }
                if(arg == "vote")
                {
                    pieces = explode(subarg, " ");
                    myVote = pieces[sizeof(pieces)-1];
                    if(myVote != "Yes" && myVote != "yes" && myVote != "no" && myVote != "No" && myVote != "abstain" && myVote != "Abstain")
                    {
                        tell_object(TP, "Please vote yes, no, or abstain on a feature name. Thank you.");
                        return 1;
                    }
                    subarg = implode(pieces[0..(sizeof(pieces)-2)], " ");
                    res = FEATURE_D->can_vote_on_feature(TP, subarg, myVote);
                    if(res == -8)
                    {
                        tell_object(TP, "Voting for "+subarg+" has ended.");
                        return 1;
                    }
                    if(res == -1)
                    {
                        tell_object(TP, "Error on voting.");
                        return 1;
                    }
                    else if(res == -4)
                    {
                        tell_object(TP, capitalize(subarg) + " is not a valid feature currently up for voting.");
                        return 1;
                    }
                    else if(res == -5)
                    {
                        tell_object(TP, "It looks like you have already voted for "+subarg+". Thank you for the vote! "+
                        "(Please Note: It is possible to get this notification in error if someone from your same ip "+
                        "address has already voted.)");
                        return 1;
                    }
                    else if(res == -6)
                    {
                        tell_object(TP, "Something has broken and your vote was not recorded. Please notify saide with "+
                        "the syntax you used to vote.");
                        return 1;
                    }
                    else if(res == 1)
                    {
                        tell_object(TP, "Thank you for voting "+myVote+" on the feature "+subarg+". Please note that "+
                        "when considering features in the future immortals will give consideration to player votes, but "+
                        "that votes alone may or may not dictate the installation of a particular feature.");
                        return 1;
                    }
                    else
                    {
                        tell_object(TP, "Something has broken and your vote was not recorded. Please notify saide with "+
                        "the syntax you used to vote.");
                        return 1;
                    }
                }
                break;                
            case "experience gain":
                if(arg != "off" && arg != "on")
                {
                    tell_object(TP, "Valid arguments for the Experience gain are on or off.");
                    return 1;
                }
                if(arg == "off" && "/daemon/user_d.c"->no_exp(TP))
                {
                    tell_object(TP, "Your experience gain is already disabled.");
                    return 1;
                }
                else if(arg == "on" && !"/daemon/user_d.c"->no_exp(TP))
                {
                    tell_object(TP, "Your experience gain is already enabled.");
                    return 1;
                }
                "/daemon/user_d.c"->toggle_no_exp(TP);
                return 1;
                break;
            case "simple inventory":
                if(arg != "off" && arg != "on")
                {
                    tell_object(TP, "Valid arguments for the simple inventory are on or off.");
                    return 1;
                }
                if(arg == "off")
                {
                    if("/daemon/user_d.c"->get_flag(TP, "simple inventory") == "Off") 
                    {
                        tell_object(TP, "You are already using the normal inventory display.");
                        return 1;
                    }
                    else 
                    {
                        tell_object(TP, "Switching to the original inventory display.");
                        TP->delete("simple inventory");
                        return 1;
                    }
                }
                if(arg == "on")
                {
                    if("/daemon/user_d.c"->get_flag(TP, "simple inventory") == "On")
                    {
                        tell_object(TP, "You are already using the simplified inventory system.");
                        return 1;
                    }
                    else 
                    {
                        tell_object(TP, "Switching to the simple inventory display.");
                        TP->set("simple inventory", 1);
                        return 1;
                    }
                }
                return 1;
                break;
            case "character improvement tax":
                perc = to_int(arg);
                if(perc < 50)
                {
                    tell_object(TP, "You cannot lower your character improvement tax below 50%.");
                    return 1;
                }
                if(perc > 100)
                {
                    tell_object(TP, "You cannot raise your character improvement tax above 100%.");
                    return 1;
                }
                "/daemon/user_d.c"->set_character_improvement_tax_percent(TP, perc);
                return 1;
            case "roleplay flag":
                if(arg != "on")
                {
                    tell_object(TP, "The only valid argument for a roleplay flag is on. If you "+
                    "decide that you need to log out or move on, just leave the area and the flag "+
                    "will adjust automatically.");
                    return 1;
                }
                if(!"/daemon/user_d.c"->setup_rp_flag(TP))
                {
                    tell_object(TP, "Something went wrong when setting up the roleplay flag.");
                    return 1;
                }
                tell_object(TP, "You are now flying a RP flag!");
                return 1;
            case "player kill":
                if(arg != "off")
                {
                    tell_object(TP, "You are only able to turn off your pkill protection.");
                    return 1;
                }
                if(!TP->query("no pk"))
                {
                    tell_object(TP, "Your PK immunity has already been dropped.");
                    return 1;
                }
                if(TP->query("pk_death_time") > time())
                {
                    tell_object(TP, "You are not yet able to remove your PK immunity.");
                    return 1;
                }
                TP->delete("no pk");
                tell_object(TP,"%^YELLOW%^You are no longer flagged for PK immunity.  You are welcome to engage in PK with any "+
                "other player who is not flagged for PK immunity.%^RESET%^");
                message("info","%^YELLOW%^"+capitalize(TP->query_name())+"'s %^MAGENTA%^PK immunity %^YELLOW%^has just been removed.%^RESET%^\n",users());
                "/cmds/avatar/_note.c"->cmd_note("ckpt "+capitalize(TP->query_name())+" %^BOLD%^%^CYAN%^chose to remove PK immunity.%^RESET%^");
                return 1;
                break;          
            case "scaled level":
                //tell_object(TP, "This is temporarily disabled, pending finishing the code that "+
                //"manipulates items to scale down with you.");
               // return 1;
                if(!ETP->query_property("training"))
                {
                    tell_object(TP, "You must be in a place that allows you to advance in order to use "+
                    "level scaling.");
                    return 1;
                }
                base = TP->query_base_character_level();
                if(arg == "revert" || arg == "normal")
                {
                    "/daemon/user_d.c"->scale_level_to(TP, base);
                    return 1;
                }
                perc = to_int(arg);               
                if(perc < 6)
                {
                    tell_object(TP, "You cannot currently scale your level below level 6.");
                    return 1;
                }                
                if(perc > base)
                {
                    tell_object(TP, "You cannot currently scale your level above your total "+
                    "character level of "+base+ " (please note: this does not include level adjusted "+
                    "races).");
                    return 1;                    
                }
                if(perc == base)
                {
                    "/daemon/user_d.c"->scale_level_to(TP, base);
                    return 1;
                }
                "/daemon/user_d.c"->scale_level_to(TP, perc);
                return 1;
        }
        return 1;
    }
    if(!avatarp(TP)) { help(); return 1;}
    if(!find_player(str))
    {
        tell_object(TP, "No such player "+str+" found.");
        return 1;
    }
    do_flag_display(find_player(str), TP);
    return 1;    
}

void help() 
{
    write("Syntax: flag\n"
    "\tflag experience gain | <on> or <off>\n"
    "\tflag character improvement tax | <amount>\n"
    "\tflag roleplay flag | <on>\n"
    "\tflag player kill | <off>\n"
    "\tflag scaled level | <level> or <normal>\n"
    "\tflag simple inventory | <on> or <off>\n"
    "\tflag feature | vote <feature name> Yes, No, or Abstain\n"
    "\tflag feature | view <feature name>\n"
    "\tflag feature | notifications <on> or <off>\n");
    if(objectp(TP) && wizardp(TP))
    {
        write("\tflag feature | remove <feature name>\n"
        "\tflag feature | add\n");
    }
write("\nThis command lets you adjust some various flags about your character.\n"
"flag by itself will show all flags and their current settings. \n\n"
"flag experience gain | <on> or <off> will enable or disable your experience gain "
"should you want to turn it off to remain a certain level longer. \n\n"
"flag character improvement tax | <amount> will let you adjust the percentage "
"of your experience gained that you want to apply toward your character "
"improvement tax, should you have one. This cannot be less than 50 or greater than "
"100.\n\n"
"flag roleplay flag | <on> will fly a RP flag in your current environment. This will "
"cause your current room to show up on the who list as a RP FLAG and will show up "
"in the rumors command.\n"
);

write("\nflag simple inventory | <on> or <off> will set whether or not you want to use a "
"less cluttered inventory. This is off by default. Turning it <on> will set is so that "
"only items you are not either wearing or wielding will show up with the <inventory> command. "
"You are able to use the <eq> command to see only items which you are currently wielding or wearing. "
"As of now (August, 2017) this does not impact the 'place' items are in your inventory. For example, "
"if you are wielding a sword and are carrying another sword, which sword is the first or second sword ONLY "
"depends on the way that it was moved into your inventory - IE the first sword (regardless of whether or not is is wielded) "
"is sword 1.\n\n");

write("flag scaled level | level will allow you to scale your level down to the specified "
"<level> in order to adventure with or take part in plots with lower level characters. It is highly "
"experimental, so use at your own risk, it is likely that it will tweaked as "
"issues become apparent. You cannot go below level 6 or above your own base character level. "
"Using <normal> instead of a level will revert you back to your normal non scaled level.\n\n"
"flag player kill | <off> will disable your pk immunity and allow you to take part in player "
"kill interactions. Once you are killed out of player kill this flag will automatically turn back "
"on and have a delay before it can be turned back off again, currently the delay is one week of "
"real life time.\n");

write("flag feature | vote <feature name> <yes>, <no>, or <abstain> - this lets you cast your vote, either yes "
"or no for a feature with the name <feature name> that is currently up for vote.\n\n"
"flag feature | view <feature name> - this lets you view more information about the feature name "
"that you specify. Most notably the long description of it, IE what it will actually mean.\n\n"
"flag feature | notifications <on> or <off> - by default you will get notifications about features that "
"you have not yet voted for or notifications when features up for vote expire and are no longer up for "
"vote.\n");

if(objectp(TP) && wizardp(TP))
{
    write("flag feature | add - this will let you add a feature for player voting. You will be put into an "
    "editor and will be allowed to specify the parameters of the feature.\n"
    "flag feature | remove 'feature name' - this will let you remove a feature so that it is no longer up for "
    "vote. You can only remove features that you personally add for voting unless you are an admin.\n");
}
write("See also: help pkilling, threaten");
}
