#pragma optimize
//#pragma save_binary

#include <room.h>
#include <ansi.h>
#include <combat.h>
#include <armor.h>

// flag of func:look_all_inventroy_of_room/ret_str
#define SHOW_IMMEDIATELY        0
#define RETURN_RESULT           1

inherit F_CLEAN_UP;

//����
#include <locate.h>

int look_room(object me, object env, int brief);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string look_equiped(object me, object obj, string pro);
string look_all_inventory_of_room(object me, object env, int ret_str);


string gettof(object me, object obj);
string getdam(object me, object obj);
string tough_level(int power);

string *tough_level_desc = ({
        BLU "����һ��" NOR,
        BLU "��������" NOR,
        BLU "����ҳ�" NOR,
        BLU "��ѧէ��" NOR,
        BLU "��֪һ��" NOR,
        HIB "��ͨƤë" NOR,
        HIB "�����ž�" NOR,
        HIB "����ǿǿ" NOR,
        HIB "ƽƽ����" NOR,
        HIB "����é®" NOR,
        CYN "ƽ������" NOR,
        CYN "��������" NOR,
        CYN "����ͨͨ" NOR,
        CYN "��������" NOR,
        CYN "����С��" NOR,
        HIC "����С��" NOR,
        HIC "������Ⱥ" NOR,
        HIC "�������" NOR,
        HIC "�������" NOR,
        HIC "�ڻ��ͨ" NOR,
        HIG "�������" NOR,
        HIG "¯����" NOR,
        HIG "��Ȼ����" NOR,
        HIG "���д��" NOR,
        HIG "���д��" NOR,
        YEL "��Ȼ��ͨ" NOR,
        YEL "�������" NOR,
        YEL "�޿�ƥ��" NOR,
        YEL "����Ⱥ��" NOR,
        YEL "����似" NOR,
        HIY "�����뻯" NOR,
        HIY "��ͬ����" NOR,
        HIY "����Ⱥ��" NOR,
        HIY "�Ƿ��켫" NOR,
        HIY "�����ױ�" NOR,
        RED "��������" NOR,
        RED "һ����ʦ" NOR,
        RED "�������" NOR,
        RED "�񹦸���" NOR,
        RED "������˫" NOR,
        WHT "��������" NOR,
        WHT "���춯��" NOR,
        WHT "������" NOR,
        WHT "������ʥ" NOR,
        WHT "�������" NOR,
        HIW "��ǰ����" NOR,
        HIW "���˺�һ" NOR,
        MAG "��ز�¶" NOR,
        HIM "��ɲ�" NOR,
        HIR "��豹���" NOR
});
string *heavy_level_desc= ({
        "����",
        "����",
        "����",
        "����",
        "����",
        "����"
});
/*
//���Դ��뿪ʼ���ѳɹ���
string locate(string file)
{
        string domain_file;
        string *all_place;
        string the_place;
        
       if (sscanf(file, "/f/%*s")) 
               return "����";

       domain_file = domain_file(file);
        
        if (! undefinedp(place[domain_file]))
        {
                all_place = place[domain_file][1];
                the_place = place[domain_file][0];
                if (member_array(file, all_place) != -1)                       
                        return the_place;
        }
        
        if (! undefinedp(region_names[domain_file]))
                return region_names[domain_file];
        
        return "δ֪����";
}


//���Դ������
*/

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj;
        object env;
        int result;
        string objid, where;

        if (! arg) result = look_room(me, environment(me), 0);
        else
        {
                if (sscanf(arg, "%s of %s", objid, where) == 2)
                {
                        if (where == "here")
                                obj = present(objid, environment(me));
                        else
                        if (where == "me")
                                obj = present(objid, me);
                        else
                        {
                                env = present(where, environment(me));
                                if (! objectp(env))
                                        return notify_fail("��Ҫ������Ķ�����\n");
                                obj = present(objid, env);
                                if (env->is_character() && env != me)
                                {
                                        if (! objectp(obj) ||
                                            ! obj->query("equipped") &&
                                            env->query_temp("handing") != obj)
                                                return notify_fail("���˺���û��©�������뿴�Ķ�������\n");
                                        message("vision", me->name() + "�������" + obj->name() +
                                                "����һ�������֪���ڴ�ʲô���⡣\n", env);
                                        message("vision", me->name() + "����" + env->name() + "��" +
                                                obj->name() + "����һ�������֪���ڴ�ʲô���⡣\n",
                                                environment(me), ({ me, env }));
                                }
                        }

                        if (! obj)
                                return notify_fail("����û������������\n");
                }        

                if( obj || (obj = present(arg, environment(me))) || (obj = present(arg, me)) )
                {
                        if( obj->is_character() && ! obj->is_corpse()) result = look_living(me, obj);
                        else result = look_item(me, obj);
                } else result = look_room_item(me, arg);
        }

        return result;
}

int look_room(object me, object env, int brief)
{
        int i;
        mapping exits;
        string str, *dirs;

        if( !env ) {
                tell_object(me, "������ܻ����ɵ�һƬ��ʲôҲû�С�\n");
                return 1;
        }

        if( !brief )
        {
                str = sprintf( HIC + "%s" + NOR + "%s\n    %s%s" + NOR,
                        env->short(),
                        wizardp(me)? " - " + file_name(env): " - ",
                        env->long(),
                        env->query("outdoors") ? NATURE_D->outdoor_room_description() : "");
        } else
        {
                str = sprintf( HIC + "%s" + NOR + "%s\n" + NOR,
                        env->short(),
                        wizardp(me)? " - " + file_name(env): "");
        }


        if (mapp(exits = env->query("exits")))
	{
                dirs = keys(exits);
                for(i=0; i<sizeof(dirs); i++)
                        if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
                                dirs[i] = 0;
                dirs -= ({ 0 });
                if (sizeof(dirs) == 0)
                        str += "    ����û���κ����Եĳ�·��\n";
                else if (sizeof(dirs) == 1)
                        str += "    ����Ψһ�ĳ����� " + BOLD +
			       dirs[0] + NOR + "��\n";
                else
                        str += sprintf("    �������Եĳ����� " + BOLD + "%s" + NOR + " �� " + BOLD + "%s" + NOR + "��\n",
                                implode(dirs[0..sizeof(dirs)-2], "��"), dirs[sizeof(dirs)-1]);
        }

        str += look_all_inventory_of_room(me, env, RETURN_RESULT);
        tell_object(me, str);
        
        return 1;
}

string desc_of_objects(object *obs)
{
        int i;

        string  str;
        mapping count;
        mapping unit;
        string  short_name;
        string  *dk;
        string league_name;

        if (obs && sizeof(obs) > 0)
        {
                str = "";
                count   = ([]);
                unit    = ([]);
    
                for (i = 0; i < sizeof(obs); i++)
                {
                        if (stringp(league_name = obs[i]->query("league/league_name")))
                        {
                               short_name = HIG + "��" + league_name + "��" + NOR + obs[i]->short();
                        }
                        else   short_name = obs[i]->short();
                        if (undefinedp(count[short_name]))
                        {
                                count += ([ short_name : 1 ]);
                                unit += ([ short_name : obs[i]->query("unit") ]);
                        }
                        else
                                count[short_name] += 1;
                }
    
                dk = sort_array(keys(count), 1);
                for (i = 0; i < sizeof(dk); i++)
                {
                        str += "  ";
                        if (count[dk[i]] > 1)
                                str += chinese_number(count[dk[i]]) + unit[dk[i]];
                        str += dk[i] + "\n";
                }
                return str;
        }

        return "";
}

string look_all_inventory_of_room(object me, object env, int ret_str)
{
        object *inv;
        object *obs;

        string  str;

        if (! env || ! me) return "";

        str = "";

        inv = all_inventory(env);
        if (! sizeof(inv)) return str;

        obs = filter_array(inv, (: $(me) != $1 && userp($1) && $(me)->visible($1) :));
        str += desc_of_objects(obs);

        obs = filter_array(inv, (: $(me) != $1 && ! userp($1) && $1->is_character() &&
                                   $(me)->visible($1) :));
        str += desc_of_objects(obs);

        obs = filter_array(inv, (: ! $1->is_character() :), me);
        str += desc_of_objects(obs);

        if (! ret_str)
                tell_object(me, str);

        return str;
}





int look_item(object me, object obj)
{
        object hob;
        mixed *inv;
        mapping count;
        mapping equiped;
        mapping unit;
        //mapping *inset;
        string short_name;

        string str;
        string *desc;
        string *dk;
        //mapping special_prop, applied_prop;
        mapping special_prop;
        mapping applied_prop;
        //string *apply, *apply1, *apply2, *apply3;
        string *apply;
        string *apply1;
        string *apply2;
        string *apply3;
        int i;
        int f;
        //int n;

        count   = ([]);
        unit    = ([]);
        equiped = ([]);
        special_prop = ([]);
        applied_prop = ([]);
        apply = ({});
        apply1 = ({});
        apply2 = ({});
        apply3 = ({});
                
        str = obj->long();
 /*if (obj->query("no_identify"))
        {
                str += "-------------------------------------\n";
                str += HIC "����Ʒδ����\n" NOR;
                str += "-------------------------------------\n";
        } else*/
        if (mapp(obj->query("weapon_prop")) ||mapp(obj->query("armor_prop")))
           {
                if (obj->query("skill_type"))
                        applied_prop = obj->query("weapon_prop");
                else
                if (obj->query("armor_type"))
                        applied_prop = obj->query("armor_prop");
                  /*      
                if (arrayp(apply1) && sizeof(apply1) > 0) {
                        str += "---------------��������--------------\n";
                        for (i = 0; i<sizeof(apply1); i++)
                        {
                                f = obj->query("enchase/wspe_data")[apply1[i]];
                                desc = ENCHASE_D->special_desc(apply1[i]);

                                str += sprintf(HIC "%s%5s%-5d\n" NOR, desc,
                                 //              f > 0 ? "+" : "-", abs(f));
                                  f > 0 ? "+" : "",f);
                        }
                        str += "\n";
                }

                if (arrayp(apply2) && sizeof(apply2) > 0) {
                        str += "---------------���߸���--------------\n";
                        for (i = 0; i<sizeof(apply2); i++)
                        {
                                f = obj->query("enchase/aspe_data")[apply2[i]];
                                desc = ENCHASE_D->special_desc(apply2[i]);

                                str += sprintf(HIC "%s%5s%-5d\n" NOR, desc,
                                 //              f > 0 ? "+" : "-", abs(f));
                                  f > 0 ? "+" : "",f);
                        }
                        str += "\n-------------------------------------\n";
                }
          if (mapp(obj->query("enchase/spe_data")))
                        special_prop += obj->query("enchase/spe_data");
                     */   
                if (mapp(applied_prop) && sizeof(applied_prop) > 0)
                        apply3 = keys(applied_prop);                        
                if (arrayp(apply3) && sizeof(apply3) > 0)
                {
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                if (undefinedp(special_prop[apply3[i]]))
                                        special_prop[apply3[i]] = applied_prop[apply3[i]];
                                else
                                        special_prop[apply3[i]] += applied_prop[apply3[i]];
                        }
                }
                if (mapp(special_prop) && sizeof(special_prop) > 0)
                        apply = keys(special_prop);
                if (arrayp(apply) && sizeof(apply) > 0) {
                        str += "---------------��������--------------\n";
                        for (i = 0; i<sizeof(apply); i++)
                        {
                                f = special_prop[apply[i]];
                                desc = ENCHASE_D->special_desc(apply[i]);

                    		str += sprintf(HIC "%s%10s%-5d\n" NOR, desc,
                         //                      f > 0 ? "+" : "-", abs(f));
                         f > 0 ? "+" : "-",abs(f));//����abs����ֵ�������ѿ���������
                        }
                }
                str += "-------------------------------------\n";
        }
       
        while (mapp(obj->query_temp("daub")))
        {
                if (! obj->query_temp("daub/poison/remain"))
                        // no poison remain now
                        break;

                if (obj->query_temp("daub/poison/id") == me->query("id"))
                {
                        str += HIG "�㷢�������滹�������Ƶ�" +
                               obj->query_temp("daub/poison/name") +
                               HIG "�ء�\n" NOR;
                        break;
                }

                if (obj->query_temp("daub/who_id") == me->query("id"))
                {
                        str += HIG "�����滹�������ֲ��µ�" +
                               obj->query_temp("daub/poison/name") +
                               HIG "�ء�\n" NOR;
                        break;
                }

                if (random(4) && random((int)me->query_skill("poison", 1)) < 30)
                        // nothing was worked out
                        break;

                str += HIG "��Ȼ���㷢�������ƺ�����һЩ����ӫ��";
                if (me->query_skill("poison", 1) >= 120)
                {
                        str += "��������" + obj->query_temp("daub/poison/name");
                }

                str += "��\n" NOR;
                break;
        }

        if (obj->query("consistence"))
                str += sprintf("�;öȣ�" WHT "%d%%\n" NOR, obj->query("consistence"));

        inv = all_inventory(obj);
        if (! sizeof(inv))
        {
                message("vision", str, me);
                return 1;
        }

        if (obj->is_corpse())
        {
                if (objectp(hob = obj->query_temp("handing")))
                {
                        if (hob->query_amount())
                                str += "���л���������һ" + hob->query("base_unit") +
                                       hob->name() + "��";
                        else
                                str += "���л���������һ" + hob->query("unit") +
                                       hob->name() + "��";
                        inv -= ({ hob });
                        if (! sizeof(inv))
                                str += "û��ʲô���������ˡ�\n";
                        else
                                str += "����������У�\n";
                } else
                        str += "����������У�\n";
        } else
                str += "�����У�\n";

        for (i = 0; i < sizeof(inv); i++)
        {
                short_name = inv[i]->short();
                if (undefinedp(count[short_name]))
                {
                        count += ([ short_name : 1 ]);
                        unit += ([ short_name : inv[i]->query("unit") ]);
                }
                else
                        count[short_name] += 1;

                if (inv[i]->query("equipped"))
                        equiped[short_name] = 1;
        }

        dk = keys(count);
        dk = sort_array(dk, 1);
        for (i = 0; i < sizeof(dk); i++)
        {
            if (equiped[dk[i]])
                str += HIC "  ��" NOR;
            else
                str += "    ";

            if (count[dk[i]] > 1)
                str += chinese_number(count[dk[i]]) + unit[dk[i]];
            str += dk[i] + "\n";
        }

        if (strlen(str) > 4096)
                me->start_more(str);
        else
                message("vision", str, me);
        return 1;
}

string look_equiped(object me, object obj, string pro)
{
        mixed *inv;
        string str;
        string subs;
        object hob;
        int i;
        int n;

        inv = all_inventory(obj);
        n = 0;

        str = "";
        subs = "";
        for (i = 0; i < sizeof(inv); i++)
        {
                switch (inv[i]->query("equipped"))
                {
                case "wielded":
                        n++;
                        subs = HIC "  ��" NOR + inv[i]->short() + "\n" + subs;
                        break;

                case "worn":
                        n++;
                        subs += HIC "  ��" NOR + inv[i]->short() + "\n";
                        break;

                default:
                        break;
                }
        }

        if (n)
                str += pro + "װ���ţ�\n" + subs;

        if (objectp(hob = obj->query_temp("handing")))
        {
                int mad;

                // dress nothing but handing a cloth !
                mad = (! objectp(obj->query_temp("armor/cloth")) &&
                       hob->query("armor_type") == "cloth");

                str = pro + "����" + (mad ? "ȴ" : "" ) + "����һ" +
                      (hob->query_amount() ? hob->query("base_unit")
                                           : hob->query("unit")) +
                      hob->name() +
                      (mad ? "�����ˣ�һ���Ƿ��ˣ�\n" : "��\n") + str;
        }

        if (playerp(obj) &&
            ! objectp(obj->query_temp("armor/cloth")))
        {
                str = pro + "����û�д��·�����\n" + str;
        }

        return str;
}

string getdam(object me, object obj)
{

        int level;
        level = obj->query_temp("apply/damage");
        level = level / 50;
                        if( level >= sizeof(heavy_level_desc) )
                                level = sizeof(heavy_level_desc)-1;
                        return heavy_level_desc[((int)level)];
}
string gettof(object me, object ob)
{
        object weapon;
        string skill_type,parry_type;
        int attack_points;
        if( objectp(weapon = ob->query_temp("weapon")) )
        {
                skill_type = weapon->query("skill_type");
                parry_type = "parry";
        }
        else
        {
                skill_type = "unarmed";
                parry_type = "unarmed";
        }

          attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK)/25;
        return  tough_level(attack_points);
}
string tough_level(int power)
{

        int lvl;
        int rawlvl;
        int grade = 1;
        if(power<0) power=0;
        rawlvl = (int) pow( (float) 1.0 * power, 0.3);
        lvl = to_int(rawlvl/grade);
                        if( lvl >= sizeof(tough_level_desc) )
                                lvl = sizeof(tough_level_desc)-1;
                        return tough_level_desc[((int)lvl)];
}

string description(object obj)
{
        if (playerp(obj))
        {
            int per;
            int age;
            per = obj->query_per();
            age = obj->query("age");
            if (obj->query("special_skill/youth")) age = 14;
            if ((string) obj->query("gender") == "����" || (string) obj->query("gender") == "����")
            {
                    if (per >=40) 
                        return HIW"����һ���������ȣ��ɷ���ǣ���ֹ������\n"NOR;
                if (per <= 39 && (per > 38))
                        return HIG"����������ˬ���Ǹ����棬�������ˡ�\n"NOR;
                if (per <= 38 && (per > 37))
                        return HIG"���ڷ����ʣ��������������������ٷ硣\n"NOR;
                if (per <= 37 && (per > 36))
                        return HIG"����Ʈ�ݳ������������ס�\n"NOR;
                if (per <= 36 && (per > 35))
                        return HIG"�����������񣬷�ױ����������������\n"NOR;
                if (per <= 35 && (per > 34))
                        return HIG"���ڷ�������Ŀ�����ǣ����˹�Ŀ������\n"NOR;
                if (per <= 34 && (per > 33))
                        return HIY"���ڷ����촽�����˿��Σ���ֹ�������ޡ�\n"NOR;
                if (per <= 33 && (per > 32))
                        return HIY"����˫Ŀ���ǣ�ü�Ҵ��飬�������޲�Ϊ֮�Ķ���\n"NOR;
                if (per <= 32 && (per > 31))
                        return HIY"���ھٶ���������ˮ�����̷��飬������������Ŀ�⡣\n"NOR;
                if (per <= 31 && (per > 30))
                        return HIY"����˫�۹⻪Ө��͸���������ǵĹ�â��\n"NOR;
                if (per <= 30 && (per > 29))
                        return HIY"����Ӣ���������������Ρ�\n"NOR;
                if (per <= 29 && (per > 28))
                        return MAG"����Ŀ�Ƶ��ᣬ�ߴ�ͦ���������Ķ���\n"NOR;
                if (per <= 28 && (per > 27))
                        return MAG"�����������£�����˹�ģ���ֹ�ʶȡ�\n"NOR;
                if (per <= 27 && (per > 26))
                        return MAG"���ý�ü��Ŀ��Ӣ�˲������Ǳ�������\n"NOR;
                if (per <= 26 && (per > 25))
                        return MAG"��������Ũ�ף����۱��ǣ��������ݣ������㵹��\n"NOR;
                if (per <= 25 && (per > 24))
                        return MAG"����ü��˫�����������ǣ�Ӣͦ���ڡ�\n"NOR;
                if (per <= 24 && (per > 23))
                        return CYN"���û���������׳��������Ӣ�˲�����\n"NOR;
                if (per <= 23 && (per > 22))
                        return CYN"���÷�ɫ��𪣬�촽ī����˹������\n"NOR;
                if (per <= 22 && (per > 21))
                        return CYN"����Ũü���ۣ��ߴ�ͦ�Σ�����������\n"NOR;
                if (per <= 21 && (per > 20))
                        return CYN"���ñ�ֱ�ڷ��������������Գ������Ը�\n"NOR;
                if (per <= 20 && (per > 19))
                        return CYN"����üĿ���㣬�����󷽣�һ���˲š�\n"NOR;
                if (per <= 19 && (per > 18))
                        return YEL"������Բ���������ڷ����Ǹ񲻷���\n"NOR;
                if (per <= 18 && (per > 17))
                        return YEL"������òƽƽ�������������ʲôӡ��\n"NOR;
                if (per <= 17 && (per > 16))
                        return YEL"���ð����Բ���������⣬���ζ��ࡣ\n"NOR;
                if (per <= 16 && (per > 15))
                        return YEL"�����ͷ���룬����һ���Ͳ����øС�\n"NOR;
                if (per <= 15 && (per > 14))
                        return YEL"����������ݣ�����ݹǣ�����Ҫ�����Ρ�\n"NOR;
                if (per <= 14 && (per > 13))
                        return RED"���÷�ͷ�������Բ��ģ��ֽŶ̴֣����˷�Ц��\n"NOR;
                if (per <= 13 && (per > 12))
                        return RED"������ü���ۣ��������ߣ�������״��\n"NOR;
                if (per <= 12 && (per > 11))
                        return RED"���������Ƥ��ͷ�����������˲����ٿ��ڶ��ۡ�\n"NOR;
                if (per <= 11 && (per > 10))
                        return RED"�����������죬������ף�����ޱȡ�\n"NOR;
                if (per <= 10)
                        return RED"����ü����б����ͷѢ�ţ�����������\n"NOR;
            } else
            {
               if (per >=40) 
                        return HIW"�������������ܣ������ƻã��Ѳ����Ƿ�������\n"NOR;
                if (per <= 39 && (per > 38))
                        return HIG"�����������ɣ���մһ˿�̳���\n"NOR;
                if (per <= 38 && (per > 37))
                        return  HIG"���ڲ�����ϼ���������񣬻����������ӡ�\n"NOR;
                if (per <= 37 && (per > 36))
                        return HIG"�����������������Ż���ɽ�����˼�֮���ס�\n"NOR;
                if (per <= 36 && (per > 35))
                        return HIG"���ڷ����۰ף�ӣ��С�ڣ�üĿ���飬�·�̫�����١�\n"NOR;
                if (per <= 35 && (per > 34))
                        return HIG"�����������ģ����ȷ�����������Σ��۹�֬�ޡ�\n"NOR;
                if (per <= 34 && (per > 33))
                        return HIY"�����������ã�ü��ī���������Ұ꣬Ŀ���ﲨ��\n"NOR;
                if (per <= 33 && (per > 32))
                        return HIY"���ڷ�����ü�����溬�����������ݣ�ת�ζ��顣\n"NOR;
                if (per <= 32 && (per > 31))
                        return HIY"����üĿ�续������ʤѩ�����ν�����߻���\n"NOR;
                if (per <= 31 && (per > 30))
                        return HIY"���ڽ����������������£�����ܳ������㡣��\n"NOR;
                if (per <= 30 && (per > 29))
                        return HIY"�����о���毻���ˮ���ж����������磬��̬��ǧ��\n"NOR;
                if (per <= 29 && (per > 28))
                        return MAG"���ý�С���磬��������������������ˡ�\n"NOR;
                if (per <= 28 && (per > 27))
                        return MAG"����Ѽ��������������ü���ڷ����٣��������֡�\n"NOR;
                if (per <= 27 && (per > 26))
                        return MAG"��������ϸ�����������������Ķ��ˣ�������ɡ�\n"NOR;
                if (per <= 26 && (per > 25))
                        return MAG"���÷���ϸ������欶��ˣ�����һ�����������ѡ�\n"NOR;
                if (per <= 25 && (per > 24))
                        return MAG"���÷��۰���������ҩ���̣����￴����\n"NOR;
                if (per <= 24 && (per > 23))
                        return CYN"������������Ŀ����ˮ��ǧ�����ġ�\n"NOR;
                if (per <= 23 && (per > 22))
                        return CYN"�����������ģ�����Ө͸��������˼��\n"NOR;
                if (per <= 22 && (per > 21))
                        return CYN"������Ц��Ȼ����Լ���ˡ�\n"NOR;
                if (per <= 21 && (per > 20))
                        return CYN"�������滨��¶������������\n"NOR;
                if (per <= 20 && (per > 19))
                        return CYN"���÷��˳������������ˡ�\n"NOR;
                if (per <= 19 && (per > 18))
                        return YEL"���ü���΢�ᣬ�ŵ��������¿��ˡ�\n"NOR;
                if (per <= 18 && (per > 17))
                        return YEL"�����䲻���£���Ҳ�׾�����Щ����֮����\n"NOR;
                if (per <= 17 && (per > 16))
                        return YEL"����������С�������޹⣬��������\n"NOR;
                if (per <= 16 && (per > 15))
                        return  YEL"���øɻƿ��ݣ���ɫ���ƣ�����Ů��ζ��\n"NOR;
                if (per <= 15 && (per > 14))
                        return YEL"������������Ƥɫ�ֺڣ���ª������\n"NOR;
                if (per <= 14 && (per > 13))
                        return RED"����һ�����������һ����û�øС�\n"NOR;
                if (per <= 13 && (per > 12))
                        return RED"������С�綹��üëϡ�裬�����צ������������\n"NOR;
                if (per <= 12 && (per > 11))
                        return RED"���ð���ü�������ۣ���Ƥ�Ʒ�������һ�������¡�\n"NOR;
                if (per <= 11 && (per > 10))
                        return RED"�������б�ۣ���ɫ�Ұܣ�ֱ�����һ�㡣\n"NOR;
                if (per <= 10)
                        return RED"���ú������е�����Ү��\n"NOR;
            }
        } else
        if (! obj->query("can_speak") && living(obj))
        {
                if (! obj->query_temp("owner"))
                        return "��һֻδ��ѱ�����������۹������ǽ��ĺ͵��⡣\n";
                else
                        return "��һֻ��" + obj->query_temp("owner_name") +
                               "ѱ����������һ������ѱ�����ӡ�\n";
        }

        return "";
}

int look_living(object me, object obj)
{
        int per;
        //int spi;
        int age;
        //int weight;
        string str, pro, desc;
        //mixed *inv;
        mapping my_fam, fam;
        int me_shen, obj_shen;
        string league_name;

        obj_shen = (int)obj->query("shen");
        per = obj->query_per();
        age = obj->query("age");
        pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

        if (playerp(obj) && ! (obj->query("born")))
        {
                tell_object(me, pro + "��û��Ͷ̥��ֻ��һ��Ԫ��ʲô��������Ү��\n");
                return 1;
        }

        me_shen = (int)me->query("shen");
        if (me != obj)
	{
                message("vision", me->name() + "�������㿴����֪���ڴ�"
			"ʲô���⡣\n", obj);
		message("vision", me->name() + "����" + obj->name() +
			"����һ�������֪���ڴ�ʲô���⡣\n", 
			environment(me), ({ me, obj }));
	}

        if (stringp(league_name = obj->query("league/league_name")))
        {
                  str = HIG + "��" + league_name + "��" + NOR + obj->long();
        }
        else str = obj->long();
        if (me != obj && objectp(obj->query_temp("is_riding")))
                str += sprintf("%s������%s�ϣ���ͷ�����㡣\n", pro, obj->query_temp("is_riding")->name());

        if (obj->is_character() &&
            obj->query("can_speak"))
        {
                // �������ɫ
                if (age >= 25 && obj->query("special_skill/youth"))
                        str += pro + "��������͵Ĵ�С������ֻ�ж�ʮ���ꡣ\n";
                else
                {
                        if (age >= 200)
                                str += pro + "��������ͺܴ��ˣ����Թ��ơ�\n";
                        else
                        if (age < 10)
                                str += pro + "������������ס�\n";
                        else
                                str += pro + "��������" + chinese_number(age / 10 * 10) +
                                       "���ꡣ\n";
                }
        }

        desc = description(obj);
        if (desc && desc != "")
                str += pro + desc;

       	// �������Ĵ����������
       	if (obj->is_character()
       	   && obj->query("tattoo"))
       	{
       		str += pro;

                // ����ɫ�����Ĵ������
       	        if (obj->query("tattoo/face_long"))
       	        {
       	                str += "�����ϴ���" +  obj->query("tattoo/face_long") + "��\n";

       	        	if (((obj->query("tattoo/chest_long")
       	           	   || obj->query("tattoo/back_long"))
       	           	   && ! objectp(obj->query_temp("armor/cloth")))
       	           	   || obj->query("tattoo/leftarm_long")
       	           	   || obj->query("tattoo/rightarm_long"))
                        	str += pro;
                }


                // �������ǰ��Ĵ�����������һ������������
       	        if ((obj->query("tattoo/chest_long")
       	           == obj->query("tattoo/back_long"))
       	           && obj->query("tattoo/chest_long")
       	           && obj->query("tattoo/back_long")
       	           && ! objectp(obj->query_temp("armor/cloth")))
       	        {
       	                str += "��¶�����ؿںͱ���������" +
       	                       obj->query("tattoo/chest_long") + "��\n";
       	        } else
       	        {
       	        	if (obj->query("tattoo/chest_long")
       	                   && ! objectp(obj->query_temp("armor/cloth")))
       	                	str += "��¶�����ؿ��ϴ���" +
       	                               obj->query("tattoo/chest_long") + "��\n";

       	        	if (obj->query("tattoo/back_long")
       	                   && ! objectp(obj->query_temp("armor/cloth")))
       	        	{
       	                	if (obj->query("tattoo/chest_long"))
       	                        	str += "��" + pro + "�ı���������" +
       	                                       obj->query("tattoo/back_long") + "��\n";
       	                	else
       	                        	str += "��¶���ı�������" +
       	                                       obj->query("tattoo/back_long") + "��\n";
       	        	}
       	        }

                // ��������ֱ۵Ĵ�����������һ������������
       	        if ((obj->query("tattoo/leftarm_long")
       	           == obj->query("tattoo/rightarm_long"))
       	           && obj->query("tattoo/leftarm_long")
       	           && obj->query("tattoo/rightarm_long"))
       	        {
       	                str += "��ʵ��˫���϶�����" +
       	                       obj->query("tattoo/leftarm_long") + "��\n";
       	        } else
                {
       	        	if (obj->query("tattoo/leftarm_long"))
       	                	str += "��ʵ������ϴ���" +
       	                               obj->query("tattoo/leftarm_long");

       	        	if (obj->query("tattoo/rightarm_long"))
       	        	{
       	                	if (obj->query("tattoo/leftarm_long"))
       	                        	str += "�����ұ������" +
       	                                       obj->query("tattoo/rightarm_long") + "��\n";
       	                	else
       	                        	str += "��ʵ���ұ��ϴ���" +
       	                                       obj->query("tattoo/rightarm_long") + "��\n";
       	        	} else
       	        	if (obj->query("tattoo/leftarm_long"))
       	                	str += "��\n";
       	        }
       	}
		str +=sprintf("%s�书����������", pro);
		str+=gettof(me,obj);
		str += sprintf("��");
		str +=sprintf("�����ƺ�");
		str +=getdam(me,obj);
		str += sprintf("��\n");
        //check about wife and husband
        if (obj->query("id")== me->query("couple/id"))
        {
                // ���޹�ϵ
                if ((string)me->query("gender") == "Ů��")
                        str += sprintf("%s������ķ����\n", pro);
                else
                        str += sprintf("%s����������ӡ�\n", pro);
        } else
        if (obj->is_brother(me))
        {
                // �ֵ�
                if (obj->query("gender") == "Ů��")
                {
                        if (obj->query("mud_age") > me->query("mud_age"))
                                str += sprintf("%s�������㡣\n", pro);
                        else
                                str += sprintf("%s����Ľ������ӡ�\n", pro);
                } else
                {
                        if (obj->query("mud_age") > me->query("mud_age"))
                                str += sprintf("%s����Ľ����ֳ���\n", pro);
                        else
                                str += sprintf("%s�������ܡ�\n", pro);
                }
        } else
        if (obj != me && obj->query("league") &&
            obj->query("league/league_name") == me->query("league/league_name"))
        {
                str += sprintf("%s�������%s��ͬ����ʿ��\n", pro,
                               obj->query("league/league_name"));
        }

        // If we both has family, check if we have any relations.
        if (obj != me &&
            mapp(fam = obj->query("family")) &&
            mapp(my_fam = me->query("family")) &&
            fam["family_name"] == my_fam["family_name"])
        {

                if (fam["generation"] == my_fam["generation"])
                {

                        if ((string)obj->query("gender") == "����" ||
                                (string)obj->query("gender") == "����")
                                str += sprintf( pro + "�����%s%s��\n",
                                        my_fam["master_id"] == fam["master_id"]? "": "ͬ��",
                                        my_fam["enter_time"] > fam["enter_time"] ? "ʦ��": "ʦ��");
                        else
                                str += sprintf( pro + "�����%s%s��\n",
                                        my_fam["master_id"] == fam["master_id"]? "": "ͬ��",
                                        my_fam["enter_time"] > fam["enter_time"] ? "ʦ��": "ʦ��");
                } else
                if (fam["generation"] < my_fam["generation"])
                {
                        if (my_fam["master_id"] == obj->query("id"))
                                str += pro + "�����ʦ����\n";
                        else
                        if (my_fam["generation"] - fam["generation"] > 1)
                                str += pro + "�����ͬ�ų�����\n";
                        else
                        if (fam["enter_time"] < my_fam["enter_time"])
                                str += pro + "�����ʦ����\n";
                        else
                                str += pro + "�����ʦ�塣\n";
                } else
                {
                        if (fam["generation"] - my_fam["generation"] > 1)
                                str += pro + "�����ͬ��������\n";
                        else
                        if (fam["master_id"] == me->query("id"))
                                str += pro + "����ĵ��ӡ�\n";
                        else
                                str += pro + "�����ʦֶ��\n";
                }
        }

        if (obj->is_chatter())
        {
                message("vision", str, me);
                return 1;
        }

        if (stringp(obj->query_temp("eff_status_msg")))
        {
                str += obj->query_temp("eff_status_msg") + "\n";
        } else
        if (obj->query("max_qi"))
                str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_qi")* 100 / (int)obj->query("max_qi")) + "\n";

        if (obj->query_temp("daub/poison/remain") &&
            (me == obj || random((int)me->query_skill("poison", 1)) > 80))
        {
                str += pro + HIG "��������" + (me == obj ? "" : "�ƺ�") +
                       "����" + (me == obj ? obj->query_temp("daub/poison/name") : "��") +
                       NOR "��\n";
        }

        str += look_equiped(me, obj, pro);
        message("vision", str, me);

        if (obj != me
           && living(obj)
           && ! me->is_brother(obj)
           && ! obj->query_condition("die_guard")
           && ! me->query_condition("die_guard")
           && me->query("couple/id") != obj->query("id")
           && (((me_shen < 0) && (obj_shen > 0))
           || ((me_shen > 0) && (obj_shen < 0)))
           && (((me_shen - obj_shen) > ((int)obj->query("max_neili") * 20))
           || ((obj_shen - me_shen) > ((int)obj->query("max_neili") * 20))))
        {
                tell_object(me, obj->name() + "ͻȻת��ͷ������һ�ۡ�\n");
                if (obj->query("age") > 15 && me->query("age") > 15)
                   if (! wizardp(obj) && ! wizardp(me))
                        COMBAT_D->auto_fight(obj, me, "berserk");
        }
        return 1;
}

int look_room_item(object me, string arg)
{
        object env;
        mapping item, exits;

        if (! objectp(env = environment(me)))
                return notify_fail("����ֻ�л����ɵ�һƬ��ʲôҲû�С�\n");
        if (mapp(item = env->query("item_desc")) && !undefinedp(item[arg]))
	{
                if (stringp(item[arg]))
                        tell_object(me, item[arg]);
                else
		if(functionp(item[arg]))
                        tell_object(me, (string)(*item[arg])(me));

                return 1;
        }
        if (mapp(exits = env->query("exits")) && ! undefinedp(exits[arg]))
	{
                if (objectp(env = find_object(exits[arg])))
                        look_room(me, env, 0);
                else
		{
                        call_other(exits[arg], "???");
                        look_room(me, find_object(exits[arg]), 0);
                }
                return 1;
        }
        return notify_fail("��Ҫ��ʲô��\n");
}

int help(object me)
{
        write(@HELP
ָ���ʽ: look [<��Ʒ>|<����>|<����>]

���ָ������鿴�����ڵĻ�����ĳ����Ʒ��������Ƿ������
��lookָ������в��������Ȳ쿴�����Ƿ��и���Ʒ�����û�����
�������ڵĻ������Ƿ��и���Ʒ�������������ϵ���Ʒ��������
�Ļ�����ID��ͬ����Ʒ�������ָ��look ??? of me/here ��ָ����
��Ҫ�쿴�Լ����ϵ���Ʒ���Ǹ��������е���Ʒ��ͬʱ�����ʹ����
�� look ??? of <id> ���Կ����˵�װ����������������Ʒ��

HELP
);
        return 1;
}