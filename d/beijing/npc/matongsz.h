int do_ridesz()
{
        string hname;
        object ob = this_player();

        if (ob->query("family/family_name") != "������")
        {
                message_vision(CYN "��ͯһ����ס$n" CYN "������������������"
                               "�˰����и�" + RANK_D->query_rude(ob) + CYN
                               "Ҫ͵������\n" NOR, this_object(), ob);
                return 1;
        }
        if (ob->query_temp("is_riding"))
        {
               return notify_fail("���Ѿ��������ˣ��Լ�ֱ��rideto�������ˣ�\n");
        }
        switch (random(3))
        {
                case 1:
                        hname = MAG "������" NOR;
                        break;
                case 2:
                        hname = RED "�����" NOR;
                        break;
                default:
                        hname = HIY "������" NOR;
                        break;
        }
        message_vision(CYN "��ͯЦ������ǣ��һƥ" NOR + hname + CYN "����$N"
                       CYN "�������������ɡ�����\n" NOR "$N����Ծ����������"
                       "����������������\n", ob );
        message_vision(HIC "\nֻ��$N" HIC "����" NOR + hname + HIC "�����ھ�"
                       "�ﳤ��ȥ��̤��һ·������\n" NOR, ob);

        ob->move("/d/beijing/front_yard");
        tell_room(environment(ob), ob->query("name") + "����" + hname + "һ"
                       "·��ҡ���۶�����\n", ({ob}));

        ob->move("/d/beijing/gate");
        tell_room(environment(ob), ob->query("name") + "����" + hname + "һ"
                       "·��ҡ���۶�����\n", ({ob}));

        ob->move("/d/beijing/di_anmen");
        tell_room(environment(ob), ob->query("name") + "����" + hname + "һ"
                       "·��ҡ���۶�����\n", ({ob}));

        ob->move("/d/suzhou/canlangting");
        tell_room(environment(ob), ob->query("name") + "����" + hname + "һ"
                       "·��ҡ���۶�����\n", ({ob}));

        ob->move("/d/suzhou/beidajie1");
        tell_room(environment(ob), ob->query("name") + "����" + hname + "һ"
                       "·��ҡ���۶�����\n", ({ob}));

        ob->move("/d/suzhou/majiu");
        tell_room(environment(ob), ob->query("name") + "����" + hname + "һ"
                       "·��ҡ���۶�����\n", ({ob}));

        message_vision("\n$N����һת��Ծ����������̬ʮ������������Ҳ��$Nһ��"
                       "�壡\n", ob);
        return 1;
}