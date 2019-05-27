// ����Ǭ����(Written by Lonely@chinamud.cn)
// Modified by Ivy@mud.ren 

#include <ansi.h>
#include <config.h>

inherit ITEM;
inherit F_NOCLONE;
inherit F_OBSAVE;

int is_item_make() { return 1; }
int is_depot_ob() { return 1; }
int clean_up() { return 1; }
int store_item(object me, object ob, int amount);

class store {
        string name, id, file;
      //string *ids;
        int amount;
}
STATIC_VAR_TAG class store *all = ({});

void create()
{
        set_name(HIW "����" HIG "Ǭ" HIY "��" HIC "��" NOR, ({ "ruyi dai", "ruyi", "dai" }));
        set_weight(100);
        set("long", HIC "    һ�����ܻ��������ع⻷������Ǭ�������������ַ������ɶ��칤��"
                    "��˵���Խ����������ƵĴ棨" NOR HIY "store" NOR HIC "����ȥ,���ᶪʧ��������ʲôʱ�򶼿���ȡ"
                    "��"NOR HIY "take" NOR HIC"��������\n" NOR);
        set("unit", "��");
        set("value",1000);
        set("no_drop", 1);
        set("no_steal", 1);
        set("no_store", 1);
        set("no_sell", "����Ǭ������Ҳ���������\n");
        setup();

        ::restore();
}
/*
string short()
{
    if(this_player())
         return HIC + this_player()->query("name") + HIW "��" HIM "����" HIG "Ǭ" HIY "��" HIB "��" NOR "(Ruyi Dai)"; 
}
*/
string extra_long()
{
        mixed ob_name_real_len;
        string msg;

        if( !all || sizeof(all) < 1 )
                return "\n�������Ǭ������û�д���κ���Ʒ��\n";

        msg = HIW "\n�������Ǭ�������ŵ���Ʒ�У�\n���  ��Ʒ                                      ����\n"
                  "����������������������������������������������������������������\n" NOR;
        for( int i=0; i<sizeof(all); i++ ) {

                ob_name_real_len = color_len(all[i]->name + "(" + all[i]->id + ")");

                //msg += sprintf("[%2d]  %-" + (36 + ob_name_real_len) + "s      %-11d\n",
                msg += sprintf("[%2d]  %-" + (36) + "s      %-11d\n",
                               i+1, all[i]->name + "(" + all[i]->id + ")",
                               all[i]->amount);
                if (all[i]->amount == 0)
                        all[i] = 0;
        }
        msg += HIW "����������������������������������������������������������������\n" NOR;
        all -= ({ 0 });
        return msg;
}

void init()
{
        add_action("do_store", "store");
        add_action("do_take",  "take");
}

int do_take(string arg)
{
        object me, ob;
        object *obs;
        int n, amount, num;
//      string *ks;
        string /*k,*/ un;

        me = this_player();

        if( me->is_busy() ) return notify_fail("����æ���ء�\n");

        if( !arg || sscanf(arg, "%d %d", n, amount) != 2 )
                return notify_fail("��ʽ�������� take ��� ���� ��ȡ����Ʒ��\n");

        if( amount < 1 || amount > 10000 )
                return notify_fail("ÿ��ȡ��Ʒ����������С��һͬʱҲ���ܴ���һ��\n");

        if( n < 1 ) return notify_fail("��Ҫȡ�ڼ�����Ʒ��\n");

        if( !all || sizeof(all) < 1 || n > sizeof(all) )
                return notify_fail("�������Ǭ������û�д��������Ʒ��\n");
        n--;
        if( amount > all[n]->amount )
                amount = all[n]->amount;

        if( !(ob = new(all[n]->file)) ) {
                all[n] = 0;
                all -= ({ 0 });
                tell_object(me, "�޷�ȡ������Ʒ��ϵͳ�Զ����֮��\n");
                return 1;
        }

        obs=filter_array(all_inventory(me),(:!$1->query("equipped"):));
        if (sizeof(obs) >= MAX_ITEM_CARRIED &&
            ! ob->can_combine_to(me))
                return notify_fail("�����ϵĶ���ʵ����̫���ˣ�û�����ö����ˡ�\n");

        if( me->query_encumbrance() + ob->query_weight() * amount > me->query_max_encumbrance() ) {
                tell_object(me, "��ĸ��ز������޷�һ��ȡ����ô����Ʒ��\n");
                destruct(ob);
                return 1;
        }

        if (ob->query("unit"))
                un = ob->query("unit");
        else
                un = ob->query("base_unit");

        if( ob->query_amount() ) {
                all[n]->amount -= amount;
                if( all[n]->amount == 0 ) {
                        all[n] = 0;
                        all -= ({ 0 });
                }
                ob->set_amount(amount);
                ob->move(me, 1);
                save();

                message_vision("$N������Ǭ������ȡ��һ" +
                                un + ob->query("name")+"��\n",me);
                return 1;
        }
        destruct(ob);

        if( amount > 100 ) amount = 100;
        all[n]->amount -= amount;
        num = amount;
        while( num-- ) {
                ob = new(all[n]->file);
                if( ob->query("equipped")) ob->delete("equipped");
                ob->move(me, 1);
        }

        message_vision("$N������Ǭ������ȡ��" + chinese_number(amount) +
                        un + ob->query("name")+"��\n",me);

        if( !wizardp(me) && random(2) )
                me->start_busy(3);

        if( all[n]->amount == 0 ) {
                all[n] = 0;
                all -= ({ 0 });
        }
        save();
        return 1;
}

int do_store(string arg)
{
        int i, n/*, k*/, amount;
        string item;
        object me, ob1, ob2, *inv;

        me = this_player();

        if( !arg ) return notify_fail("��Ҫ���ʲô������\n");

        if( me->is_busy() ) return notify_fail("������æ���أ�\n");

        n = 100;

        if( sizeof(all) >= n )
        {
                return notify_fail("������Ǭ������ " + n + " �����ؿռ�ȫ��ʹ���ˣ�������һ�°ɡ�\n");
        }

        if( arg == "all" ) {
                inv = all_inventory(me);
                inv -= ({ this_object() });
                inv -= ({ 0 });
                inv = filter_array(inv, (: $1->query_autoload() && !$1->is_item_make() &&
                                          !$1->query("equipped") && !$1->query("money_id") :));
                n = sizeof(inv);
                if( n > 100 )
                {
                        tell_object(me, "�����ϵ���Ʒ̫���ˣ������׸�죬�㻹��һ��һ����ɡ�\n");
                        return 1;
                }

                if( n < 1 )
                {
                        tell_object(me, "������û���κο��Ա������Ʒ��\n");
                        return 1;
                }

                for( i=0; i<n; i++ )
                {
                        do_store(inv[i]->query("id"));
                }
                return 1;
        } else if (sscanf(arg, "%d %s", amount, item) == 2) {
                if( !objectp(ob1 = present(item, me)) )
                        return notify_fail("������û������������\n");

                if( !ob1->query_amount() )
                        return notify_fail(ob1->name() + "���ܱ��ֿ���š�\n");

                if( amount < 1 )
                        return notify_fail("�涫��������������һ����\n");

                if( amount > ob1->query_amount() )
                        return notify_fail("��û����ô���" + ob1->name() + "��\n");

                if( amount == (int)ob1->query_amount() ) {
                        return store_item(me, ob1, amount);
                } else {
                        ob1->set_amount((int)ob1->query_amount() - amount);
                        ob2 = new(base_name(ob1));
                        ob2->set_amount(amount);
                        if( !store_item(me, ob2, amount) ) {
                                ob2->move(me, 1);
                                return 0;
                        }
                        return 1;
                }
        }

        if( !objectp(ob1 = present(arg, me)) )
                return notify_fail("������û������������\n");

        if( ob1->query_amount() )
                return do_store(ob1->query_amount() + " " + arg);

        store_item(me, ob1, 1);
        return 1;
}

int store_item(object me, object ob, int amount)
{
        class store item;
        int i, n;
        string file, name, id, un;

        if( !objectp(ob) ) {
                error("no this object!\n");
                return 0;
        }

        if( file_size(base_name(ob) + ".c") < 0 )
                return 0;

        if( inherits(F_SILENTDEST, ob) ) {
                tell_object(me,"����Ǭ����������" + ob->query("name")+"�������Լ����ƴ���\n");
                return 0;
        }

        if( inherits(F_UNIQUE, ob) ) {
                tell_object(me,"����Ǭ����������" + ob->query("name")+"�������Լ����ƴ���\n");
                return 0;
        }

        if( member_array(ITEM + ".c", deep_inherit_list(ob)) == -1 &&
            member_array(COMBINED_ITEM + ".c", deep_inherit_list(ob)) == -1 ) {
                tell_object(me,"����Ǭ����������" + ob->query("name")+"�������Լ����ƴ���\n");
                return 0;
        }

        if( ! ob->query_autoload()) {
                tell_object(me,"����Ǭ����������" + ob->query("name")+"�������Լ����ƴ���\n");
                return 1;
        }

        if( ob->query("money_id")) {
                tell_object(me,"��Ǯ����Ǯׯ�ϰ��(deposit)��\n");
                return 1;
        }

        if( ob->query("no_store") || ob->is_no_clone() || ob->query("no_put")){
                tell_object(me,"����Ǭ����������" + ob->query("name")+"�������Լ����ƴ���\n");
                return 0;
        }

        if( ob->is_character() || ob->is_item_make() || !clonep(ob) ) {
                tell_object(me,"����Ǭ����������" + ob->query("name")+"�������Լ����ƴ���\n");
                return 0;
        }

        switch( ob->query("equipped")){
        case "worn":
                tell_object(me, ob->name() + "���������������ܴ�š�\n");
                return 0;
        case "wielded":
                tell_object(me, ob->name() + "�����Ƚ��װ�����ܴ�š�\n");
                return 0;
        }

        if( sizeof(all_inventory(ob)) ) {
                tell_object(me,"�����Ȱ�" + ob->query("name")+"����Ķ������ó�����\n");
                return 0;
        }

        name = ob->query("name");
        file = base_name(ob);
        id = ob->query("id");
        if (ob->query("base_unit"))
                un = ob->query("base_unit");
        else
                un = ob->query("unit");

        n = sizeof(all);
        for( i=0; i<n; i++ ) {
                if( all[i]->file == file &&
                    all[i]->id == id &&
                    all[i]->name == name ) {
                        all[i]->amount += amount;
                        save();
                        message_vision("$N��"+chinese_number(amount) + un+
                                        ob->query("name")+"�浽����Ǭ�����\n",me);
                        destruct(ob);
                        return 1;
                }
        }

        item = new(class store);
        item->file = file;
        item->name = name;
        item->id = id;
      //item->ids = ob->parse_command_id_list();
        item->amount = amount;
        all += ({ item });
        save();
        message_vision("$N��"+chinese_number(amount) + un+
                        ob->query("name")+"�浽����Ǭ�����\n",me);
        destruct(ob);
        return 1;
}


int receive_summon(object me)
{
        object env;

        if( (env = environment()) && env == me ) {
                write(name() + "����������������ٻ���ʲô����\n");
                return 1;
        }

        if( env == environment(me) ) {
                message_vision(HIG "ֻ�����ϵ�" + name() +
                               HIG "����һ����â����Ծ��$N" HIW
                               "�����У�\n\n" NOR, me);
        } else {
                if( env ) {
                        if( env->is_character() && environment(env) )
                                env = environment(env);

                        message("vision", HIG "ͻȻ" + name() + HIG "����һ��"
                                HIG "��â��ʧ�ˣ�\n\n" NOR, env);

                        if( interactive(env = environment()) ) {
                                tell_object(env, HIM + name() +
                                                 HIM "��Ȼ�����ȥ�ˣ�\n" NOR);
                        }
                }

                message_vision(HIM "һ����â������ֻ��$N"
                               HIM "���ж���һ��$n" HIM "��\n" NOR,
                               me, this_object());
        }

        if( !this_object()->move(me) )
                tell_object(me, HIR "������ĸ���̫�ߣ�"+this_object()->name()+HIR "����һ����â����Ȼ�����ټ���\n" NOR);
        return 1;
}

int hide_anywhere(object me)
{
        if( me->query("jingli") < 100){
                tell_object(me, "����ͼ��" + name() +
                            "��ȥ�����Ǿ������ã����Է�������������\n");
                return 0;
        }
        me->add("jingli", -100);

        message_vision(HIB "$N" HIB "����һ���֣�" + name() +
                       HIB "��Ȼ�����ټ���\n" NOR, me);
        save();
        destruct(this_object());
        return 1;
}

/*
int receive_dbase_data(mixed data)
{
        if( !mapp(data) || sizeof(data) < 1 )
                return 0;

        if( data["all"] )
                all = data["all"];

        return 1;
}

mixed save_dbase_data()
{
        mapping data;

        data = ([]);

        if( sizeof(all) > 0 )
                data += ([ "all" : all ]);

        return data;
}
*/

// ���ܴ������ݵĽӿں���
int receive_dbase_data(mixed data)
{
        int i, n;
        class store item;

        if( !mapp(data) || sizeof(data) < 1 )
                return 0;

        n = sizeof(data);
        for( i=0; i<n; i++ ) 
        {
                item = new(class store);
                item->name = data["item" + i]["name"];
                item->id = data["item" + i]["id"];
                item->file = data["item" + i]["file"];
                item->amount = data["item" + i]["amount"];
                all += ({ item });
        }
        return 1;
}

// ���б������ݵĽӿں���
mixed save_dbase_data()
{
        mapping data,list;
        int i, n;
        data = ([]);

        if( sizeof(all) > 0 )
        {
                n = sizeof(all);
                for( i=0; i<n; i++ ) 
                {
                        list = ([]);
                        list["name"] = all[i]->name;
                        list["id"] = all[i]->id;
                        list["file"] = all[i]->file;
                        list["amount"] = all[i]->amount;
                        data += ([ "item" + i :list]); 
                }
        }
        return data;
}
