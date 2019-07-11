//    /bin/dev/_I.c
//    From the Nightmare mudlib
//    An inventory command that gives more info.  Originally by Valodin
//    but revamped by Daroki.  Refixed by Val
//    Styx (SG) added to show enchantment 04/22/02

#include <ansi.h>
#include <std.h>

inherit DAEMON;

int cmd_I(string str) {
   object ob;
   object *inv;
   int lcv, i, size_inv, ansistatus;
   string short, filename, trash, borg;
   int ac, wc, value, weight, enchant;
   int *wca;
   string store;
   
   if(!str)
      str = this_player()->query_name();
   ob = to_object(str);
   if(!ob)
   {
      write("Can't find " + str + ".\n");
      return 1;
   }
   if(archp(ob) && (int)ob->query_invis() == 1) return notify_fail("Can't find "+str+".\n\n");
   if(ansistatus = this_player()->query_ansi())
     this_player()->toggle_ansi();    /* Toggle off ansi for a sec */
   write("Inventory of " + capitalize(str));
   write("\t" + ob->query_short() + " contains :");

   size_inv = sizeof(inv = all_inventory(ob));
   for(lcv = 0; lcv < size_inv; lcv++)
   {
      message("Nwrite", lcv + ".  ", this_player());
      if (lcv < 10) message("Nwrite", " ", this_player());
      if (!(short = inv[lcv]->query_short()))
        short = "(Invisible Object)";
      if (strlen(short) > 35)
         short = short[0..33] + "~";
      else
         for (i = strlen(short); i < 36; i++)
           short = short + " ";
      weight = (int)inv[lcv]->query_weight();
      filename = file_name(inv[lcv]);
      borg = geteuid(inv[lcv]);
      if (strlen(filename) > 35)
      {
         while(strlen(filename) > 50)
            sscanf(filename, "%s/%s", trash, filename);
         filename = "~" + filename;
      }
      write(short + "  " + filename + " ("+borg+")");
      message("Nwrite", "     ", this_player());
      if (pointerp(wca = inv[lcv]->query_wc())) {
         message("Nwrite", "WC [", this_player());
         for(i=0;i<sizeof(wca);i++){
            store = wca[i];
            if(i==0) message("Nwrite",""+store+"",this_player());
            if(i!=0) message("Nwrite",","+store+"",this_player());
         }
         message("Nwrite", "]\t", this_player());
      }
      else if (wc = inv[lcv]->query_wc()) 
         message("Nwrite", "WC ["+wc+"]\t", this_player());
      else 
         message("Nwrite", "WC [None]\t", this_player());
      if (ac = inv[lcv]->query_ac())
         message("Nwrite", "AC ["+ac+"]\t   ", this_player());
      else
         message("Nwrite", "AC [None]  ", this_player());
      if (value = inv[lcv]->query_value())
         message("Nwrite", "Value ["+value+"]\t", this_player());
      else
         message("Nwrite", "Value [None]\t", this_player());
      if (weight = inv[lcv]->query_weight())
         message("Nwrite", "Weight ["+weight+"]\t", this_player());
      else
         message("Nwrite", "Weight [None]\t", this_player());
      if (enchant = inv[lcv]->query_property("enchantment"))
         write("Enchant. ["+enchant+"]");
      else
         write("Enchant. [None]");
   }
   if (ansistatus) 
      this_player()->toggle_ansi();   /* retoggle ansi */
   return 1;
}

int help()
{
   message("help", "Command: I\nSyntax: I <object>\n\nThis command lists all"
	   " the items in an object's inventory along with their short(),"
	   " filename, AC, WC, weight, and value.  Without an argument, I "
	   "lists your own inventory.", this_player());
   message("help", "See also: format, dest, patch, ss, sc, refs, inven", 
	   this_player());
   return 1;
}
