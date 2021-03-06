
#include <std.h>
#include <rooms.h>
#include <daemons.h>
#include "/d/darkwood/yntala/yntala.h"
inherit ROOM;
int searched;
object ob;

void create()
{
::create();
   set_property("outdoors",0);
   set_property("light",3);
   set_property("no teleport",1);
   set_terrain(MEADOWLANDS);
   set_travel(FOOT_PATH);
   set_name("End of the rainbow");
   set_short("%^YELLOW%^A very bright room%^RESET%^%^");
   set_long((:TO,"ldesc":));
   set_smell("default","%^BOLD%^%^GREEN%^You smell nothing but spring grass.%^RESET%^");
   set_listen("default","You don't hear anything.");
   set_items(([
      "rainbow":"%^YELLOW%^This is a very pretty and bright %^MAGENTA%^r%^RED%^a%^BLUE%^i%^YELLOW%^n%^GREEN%^b%^RED%^o%^CYAN%^w.    %^YELLOW%^It is quite a bit larger than any other you've seen before, and its %^MAGENTA%^radiance %^YELLOW%^encompasses the entire area.%^RESET%^",
      "clovers":"%^BOLD%^%^GREEN%^That's strange, every single clover here is a four-leaf clover.",
      "pot":"%^BOLD%^%^BLACK%^This is the fabled pot of"
" %^YELLOW%^gold. %^BLACK%^On it's side, written in "
"%^YELLOW%^golden %^BLACK%^letters is the following "
"inscription:\n%^YELLOW%^Beware this wee lil' pot o' gold,\n"
"For only once shall this be told;\nLeave ye now to the rainbows"
   " end,\nAnd don't ye ever come back again.\nOnce Laklier is"
" called to here,\nThe exit out shall disappear.\nYou will die, "
"never to return,\nThus your possessions will be lost...\n"
"as ye shall learn.%^RESET%^",
      ({"bunnies","bunny","rabbit"}):"%^BOLD%^%^WHITE%^These cute and playful bunnies have floppy ears, fluffy tails and are pure white.  They playfully hop around the base of the rainbow.%^RESET%^",
      "skeletons":"%^RESET%^These skeletons hang off of the pot of gold with a stupid grin continuously etched upon their faces. The rabbits hop around them as if they were a play structure, bouncing in and out of the chest cavities and from one to the next without a care in the world.",
]));
   set_exits(([
"rainbow":INRMS+"forest33",
]));
   set_pre_exit_functions(({"rainbow"}),({"gorain"}));
   set_search("pot", (: TO, "search_pile" :) );
}
void reset() {
  ::reset();
  searched = 1;
}
int gorain() {
    if(present("leprachaun")) {
        write("%^BOLD%^%^GREEN%^The leprachaun keeps you from leaving!%^RESET%^");
        return 0;
    }
    else return 1;
}
void search_pile() {
     if(searched <= 0) {               
	  tell_object(TP,"It looks like this area has been searched already.");
        return ;
     }
     if (searched == 1) {  
        write("%^YELLOW%^You dig out some coins from the %^BLACK%^pot of %^YELLOW%^gold!%^RESET%^\n");
        tell_room(TO,"%^YELLOW%^"+TPQCN+" pulls out a large pile of coins from the %^BLACK%^pot of %^YELLOW%^gold%^RESET%^.",TP);
        ob = new("/std/obj/coins");
        ob->set_money("gold", random(5000)+1000);
        ob->move(TO);
       if(TP->query_highest_level() < 16) {
          new(TMONDIR+"lak.c")->move(TO);
          searched = 0;
          return;
       }
       if(TP->query_highest_level()>=16&&TP->query_highest_level()<17) {
          new(TMONDIR+"lak2.c")->move(TO);
          searched = 0;
          return;
       }
       if(TP->query_highest_level()>=17&&TP->query_highest_level()<23){
          new(TMONDIR+"lepking.c")->move(TO);
          searched = 0;
          return ;
       }
       if(TP->query_highest_level()>=23){
          new(TMONDIR+"lepking.c")->move(TO);
          new(TMONDIR+"gfigure.c")->move(TO);
          searched = 0;
          return ;
       }
       return ;   
   }
}
string ldesc(string str){
   return("%^BOLD%^%^GREEN%^You have been taken to a very"
" strange place. Green grass rolls on for as far as you can see,"
" and a bright %^YELLOW%^r%^RED%^a%^WHITE%^i%^GREEN%^n%^BLUE%^"
"b%^MAGENTA%^o%^CYAN%^w %^GREEN%^ends right in the center here. "
" %^WHITE%^Fluffy white bunnies %^GREEN%^hop around a large"
" %^BLACK%^pot %^GREEN%^that sits at the base of the"
" %^YELLOW%^r%^RED%^a%^WHITE%^i%^GREEN%^n%^BLUE%^b%^MAGENTA%^"
"o%^CYAN%^w, %^GREEN%^and clovers grow in abundance.  This place"
" would give you an overwhelming sense of peace, except for the"
" fact that a few %^RESET%^skeletons %^BOLD%^%^GREEN%^hang off"
" of the %^BLACK%^pot %^GREEN%^of %^YELLOW%^gold, %^GREEN%^and"
" the %^WHITE%^bunnies %^GREEN%^seem to hop in and out of the"
" chest cavities as if they were a bunny playground.%^RESET%^\n");
} 


