//metal.c
// values tweaked by Styx 3/21/03 with T's agreement to adjust
// with the adj. for quality being a mult of 10 for high, made making things far too expensive and also made for potential fencing imbalance
// I'm going to recommend that only mithril and adamantium be able to be enchanted, or at least have a higher success rate
//updated it to make good quality metal harder to find to help balance out the player made armor ac problem and drive prices up 7/11/04 -Tsera

#include <std.h>
#include <materials.h>

inherit MATERIAL;

string metalType;


void set_metal_type(string type)
{
    if(member_array(lower_case(type),METAL_TYPES) == -1) { error("Invalid metal type."); return; } 
    TO->set_subtype(lower_case(type));
    TO->set_name(""+query_subtype()+" metal");
    TO->set_id(({"billet",query_subtype(),"metal"}));
    TO->set_short("A billet of "+query_subtype()+" metal");
    TO->set_long("This is a billet of "+query_quality()+" "+query_subtype()+".");
    return;
}

void set_metal_quality(int quality)
{
    if(quality < 1 || quality > 10) { error("You must enter a number between 1 and 10 for quality"); return; }
    TO->set_quality_type(quality);
    TO->set_long("This is a billet of "+query_quality()+" "+query_subtype()+".");
    return;
}

void set_metal_quantity(int quantity)
{
    if(quantity < 1) { error("You must enter a number greater than 0 for quantity"); return; }
    TO->set_uses(quantity);
    return;
}


string getMetalType(){
    switch(random(116)){
    case 0..30:
        return "iron";
    case 31..50:
        return "copper";
    case 51..70:
        return "bronze";
    case 71..80:
        return "steel";
    case 81..85:
        return "electrum";
    case 86..90:
	return "silver";
    case 91..93:
        return "gold";
    case 94..95:
        return "platinum";
    case 96..97:
        return "titanium";
    case 98..101:
        return "darksteel";
    case 102..104:
        return "fever iron";
    case 105..107:
        return "arandur";
    case 108..110:
        return "dlaran";
    case 111..113:
        return "palladium";
    case 114:
        return "mithril";
    case 115:
        return "adamantium";
    }
}

void create(){
    int quality;
    ::create();
    quality = random(51);
    switch(quality){
       case 0..20:
       quality = 1;
       break;
       case 21..25:
       quality = 2;
       break;
       case 26..30:
       quality = 3;
       break;
       case 31..35:
       quality = 4;
       break;
       case 36..40:
       quality = 5;
       break;
       case 41..43:
       quality = 6;
       break;
       case 44..45:
       quality = 7;
       break ;
       case 46..47:
       quality = 8;
       break;
       case 48..49:
       quality = 9;
       break; 
       case 50:
       quality = 10;
       break;
    }

    set_type("metal");
    metalType = METAL_TYPES[random(sizeof(METAL_TYPES))];
    set_subtype(metalType);
    set_quality_type(quality);
    set_uses(random(10)+4);
    set_name(metalType+" metal");
    set_id(({"billet",metalType,"metal"}));
    set_short("A billet of "+query_subtype()+" metal");
    set_long("This is a billet of "+query_quality()+" "+query_subtype()+".");
    set_weight(5);
    set_cointype("gold");
    set_property("treasure_type", "5C");
}

int query_value() {
	switch(query_subtype()) {
   	case "iron":
		return query_uses()*query_quality_type()*15;   // was 75
    	case "copper":
		return query_uses()*query_quality_type()*20;   // was 80
    	case "bronze": 
		return query_uses()*query_quality_type()*30;   // was 85
	case "steel":
		return query_uses()*query_quality_type()*35;   // was 90
	case "electrum":
		return query_uses()*query_quality_type()*40;  // was=bronze but is rarer
     	case "silver":
		return query_uses()*query_quality_type()*50;   // was 110
     	case "gold":
		return query_uses()*query_quality_type()*80;   // was 110
   	case "platinum":
		return query_uses()*query_quality_type()*175;  // was 450
   	case "titanium":
		return query_uses()*query_quality_type()*175;  // was 275
/* Values adjusted by Styx after discussion with Tristan and player concerns about costs of making armor 3/13/03 - platinum and titanium are equally rare so making them the same
I was going to try to make coin types comparable proportions but makes it too skewed and I realized that the coin sizes might be different anyway (i.e. copper coins may be very small, so far less material than a gold coin as well as cheaper material)
*/
        case "darksteel":
                return query_uses()*query_quality_type()*100;
        case "fever iron":
                return query_uses()*query_quality_type()*100;
        case "arandur":
               return query_uses()*query_quality_type()*120;
        case "dlaran":
               return query_uses()*query_quality_type()*120;
        case "palladium":
               return query_uses()*query_quality_type()*140;
        case "mithril":
		return query_uses()*query_quality_type()*190;  // was 475
   	case "adamantium":
		return query_uses()*query_quality_type()*200;   // was 475
	default:
		return query_uses()*query_quality_type()*50;   // was 75
 	}
}
