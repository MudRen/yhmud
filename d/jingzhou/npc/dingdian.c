inherit NPC;

void destroying(object, object);

void create()
{
        set_name("����", ({ "ding dian", "ding" }));
        set("long", 
                "����������ף�ͷ��������ֱ���������������ò�������ֱ��ͬ��ɽ�е�Ұ�ˡ�\n");
        set("gender", "����");
        set("age", 35);

        set_skill("unarmed", 120);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("feiyan-zoubi", 120);
        set_skill("shenzhaojing", 120);
        map_skill("force","shenzhaojing");
        map_skill("dodge","feiyan-zoubi");
        map_skill("unarmed","shenzhaojing");
        prepare_skill("unarmed","shenzhaojing");
        set("max_neili",2000);
        set("neili",2000);
        set("jiali",100);

        set("combat_exp", 600000);
        set("shen_type", 1);
        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

int accept_object(object me, object obj)
{
        object key;
        if ((string)obj->query("id")=="lv juhua") {
                message("vision",me->name()+"������һ���̾ջ���\n",environment(me),
            ({me}));
        key = new("/clone/book/shenzhaojing");
        if (!key){
         command("say ���Ѿ����˰������˪���ˣ�����������ˡ�");
        return 0;
        }
        
        command("touch "+me->query("id"));
        command("say ��λ"+RANK_D->query_respect(me)+"��˪���������ŵİɡ�");
        key->move(me);
        add("book_count", -1);
        message_vision("$n�ݸ�$Nһ���顣\n", me, this_object() );
        command("say �Ȿ����������������õġ����վ���������ȥ����˪���ɡ�");
        command ("rumor "+me->query("name")+"Ū����һ�����վ���");
        remove_call_out("destroying");
        call_out("destroying", 1, this_object(), obj);
        return 1;
        }
        return 0;
}

void destroying(object me,object obj)
{
        destruct(obj);
        return;
}

