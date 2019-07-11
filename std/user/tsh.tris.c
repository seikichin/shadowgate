//      /std/user/tsh.c
//      from the Nightmare Mudlib
//      tsh- the TMI-shell or Tru-shel
//      created by Truilkan@TMI 920205
//      bug in $h & $H options fixed by Pallando@Nightmare 930709

#include <adt_defs.h>
#include <commands.h>
#include <tsh.h>

#define DEFAULT_PROMPT "%^BOLD%^%^BLACK%^-%^RED%^> "
#define MAX_HIST_SIZE  50
#define MIN_HIST_SIZE  20
#define MAX_PUSHD_SIZE 50

private inherit CSTACK_ADT;       /* for pushd and popd */

private static string tsh_prompt;
private static int cur, hist_size, pushd_size, custom_prompt, aBlock, timeBlock;

string do_nicknames(string arg);
string do_alias(string arg);
string handle_history(string arg);
int tsh(string file);

int do_new() {
    string d1, d2;

	tsh_prompt = (string)this_object()->getenv("prompt");
	tsh_prompt = !tsh_prompt ? DEFAULT_PROMPT : tsh_prompt + " ";
	custom_prompt = (tsh_prompt != DEFAULT_PROMPT);

	d1 = (string)this_object()->getenv("pushd");
	pushd_size = 0;
	if (d1)
		sscanf(d1,"%d",pushd_size);
	if (pushd_size > MAX_PUSHD_SIZE)
		pushd_size = MAX_PUSHD_SIZE;

	d1 = (string)this_object()->getenv("history");
	hist_size = 0;
	if (d1)
		sscanf(d1,"%d",hist_size);
	if (hist_size > MAX_HIST_SIZE)
		hist_size = MAX_HIST_SIZE;
    if (!hist_size)
       hist_size = MIN_HIST_SIZE;
	return 1;
}

int pushd(string arg) {
    string path;

    path = (string)this_object()->get_path();
    if((int)CD->cmd_cd(arg) && cstack::enqueue(path) == -1) {
        cstack::dequeue();
        cstack::enqueue(path);
    }
    return 1;
}

int popd() {
    mixed dir;

    dir = cstack::pop();
    if((int)dir == -1) write("Directory stack is empty.\n");
    else CD->cmd_cd((string)dir);
    return 1;
}

void initialize() {
    string rcfile;

    do_new();
    if(pushd_size) cstack::alloc(pushd_size);
    if(hist_size) history::alloc(hist_size);
    rcfile = user_path((string)this_player()->query_name()) + ".login";
    if(file_size(rcfile) > -1) this_object()->tsh(rcfile);
}

string write_prompt()
{
    string path, prompt, tmp;

    if( custom_prompt )
    {
        prompt = tsh_prompt;
        path = (string)this_player()->get_path();
        tmp = user_path((string)this_player()->query_name());
        tmp = tmp[0 .. strlen(tmp)-2];
        if(stringp(path) && sscanf(path, "/realms/%s", tmp) == 1)
	    path = "~" + tmp;
       if(!stringp(path)) path = ">";
        prompt = replace_string( prompt, "$D", path );
        prompt = replace_string( prompt, "$h",
            "" + (int)this_player()-> query_hp() );
        prompt = replace_string( prompt, "$H",
            "" + (int)this_player()-> query_max_hp() );
        prompt = replace_string( prompt, "\\n", "\n" );
        prompt = replace_string( prompt, "$N", lower_case(mud_name()) );
     prompt = replace_string(prompt, "$L", " "+this_object()->query_spoken());
        prompt = replace_string( prompt, "$C", ""+query_cmd_num() );
        prompt = replace_string(prompt, "$S", ""+this_object()->query_condition_string());
        prompt += " ";
    } else {
        prompt = DEFAULT_PROMPT;
    }
    message("prompt", prompt, this_object());
    return prompt;
}

int adminBlock(){
    if (archp(this_object())) {
        return 0;
    }
    return aBlock || (timeBlock < time());
}

nomask string process_input(string arg) {
    if (adminBlock()) {
        arg = "";
    }
    if(arg && arg != "") return do_alias(do_nicknames(handle_history(arg)));
    else return arg;
}

int tsh(string file) {
   string contents, *lines;
   int j, len, finished;

   if (geteuid(previous_object()) != geteuid()) return 0;
   if (!file) {
      notify_fail("usage: tsh filename\n");
      return 0;
   }
   contents = read_file(resolv_path((string)this_object()->get_path(),file));
   if (!contents) {
      notify_fail("tsh: couldn't read " + file + "\n");
      return 0;
   }
   lines = explode(contents,"\n");
   len = sizeof(lines);
   finished = 0;
   for (j = 0; j < len && !finished; j++) {
      command(lines[j]);
   }
   write("Script "+file+": ended successfully.\n");
   return 1;
}

varargs void setAdminBlock(int length){
    if (!length) {
        aBlock = 1;
    } else {
        timeBlock = time() + (length*1000);
    }

}

void removeAdminBlock(){
    aBlock = 0;
    timeBlock = 0;
}

int queryTimeBlock(){
    return timeBlock;
}

int queryAdminBlock(){
    return aBlock;
}
