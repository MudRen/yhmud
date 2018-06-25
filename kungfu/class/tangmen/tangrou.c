/*
 * Copyright (C) 2003-2004, by Lonely. All rights reserved.
 * This software can not be used, copied, or modified
 * in any form without the written permission from authors.
 */

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "tangmen.h"

void create()
{
	set_name( "����", ({ "tang rou", "tang" }) );
	set( "nickname", HIG "��������" NOR );
	set( "long", "���ǽ����Ĺ��ӵ����ģ�һ��Ĺ���ȴ�ǲ�����\n" );
	set( "gender", "����" );
	set( "age", 25 );
	set( "class", "tangmen" );
	set( "born_family", "��������" );
	set( "attitude", "peaceful" );
	set( "shen_type", 0 );
	set( "str", 30 );
	set( "int", 25 );
	set( "con", 24 );
	set( "dex", 28 );
	set( "max_qi", 8000 );
	set( "max_jingli", 1000 );
	set( "neili", 2000 );
	set( "max_neili", 2000 );
	set( "jiali", 100 );
	set( "shen", 2000 );
	set( "combat_exp", 100000 );
	set( "level", 8 );
	set( "score", 7000 );

	set_skill( "force", 80 );
	set_skill( "throwing", 80 );
	set_skill( "dodge", 80 );
	set_skill( "parry", 80 );
	set_skill( "literate", 80 );
	set_skill( "hand", 80 );
	set_skill( "sword", 80 );
	set_skill( "boyun-suowu", 80 );
	set_skill( "biyun-xinfa", 80 );
	set_skill( "qiulin-shiye", 80 );
	set_skill( "wuzhan-mei", 80 );
	set_skill( "poison", 80 );
	set_skill( "medical", 80 );
	set_skill( "tangmen-throwing", 80 );
	set_skill( "tangmen-poison", 80 );
	set_skill( "tangmen-medical", 80 );

	map_skill( "force", "biyun-xinfa" );
	map_skill( "throwing", "tangmen-throwing" );
	map_skill( "dodge", "qiulin-shiye" );
	map_skill( "parry", "boyun-suowu" );
	map_skill( "sword", "wuzhan-mei" );
	map_skill( "hand", "boyun-suowu" );
	map_skill( "medical", "tangmen-medical" );
	map_skill( "poison", "tangmen-poison" );

	prepare_skill( "hand", "boyun-suowu" );

	create_family( "��������", 3, "����" );

	set( "chat_chance_combat", 20 );
	set( "chat_msg_combat", ({
					 (: exert_function, "recover" :),
					 (: exert_function, "powerup" :),
					 (: perform_action, "throwing.san" :),
	                 /* ( : command("wield all") : ), */
				 }) );
	set( "inquiry", ([
				 "����"   : "Ҫ�����ţ���ͨ���ҵ�������",
			 ]) );
	set_temp( "apply/damage", 100 );
	set_temp( "apply/unarmed_damage", 100 );
	set_temp( "apply/armor", 200 );

	set( "master_ob", 2 );
	setup();
	carry_object( "/clone/misc/cloth" )->wear();
	set_temp( "handing", carry_object( "/d/tangmen/obj/jili" ) );
	carry_object( "/d/tangmen/obj/feidao" );
}

void attempt_apprentice( object ob )
{
	if ( !permit_recruit( ob ) )
		return;
	/*
	 * if( ob->query_str() < 30 ){
	 *    command("say " + RANK_D->query_respect(ob) + "������������������ذɡ�");
	 *   return;
	 * }
	 * if( ob->query("dex") < 30 )
	 * {
	 *    command("say �����������̫���ˣ���ôѧ���������ɵĹ��򣿣���\n");
	 *    return;
	 * }
	 * if( ob->query("int") < 28 )
	 * {
	 *    command("say ������������Բ����������������Ÿ���İ����ַ�����\n");
	 *    return;
	 * }
	 */
	if ( ob->query( "family/family_name" ) == "��������"
	     && ob->query( "family/master_name" ) != "����" )
	{
		command( "say ���������������ˣ��ҵĹ�����̫�ߵģ��㻹�����Ҵ�ʦ�ְ�!��\n" );
		return;
	}
	command( "say ���ðɣ��ӽ�������������ŵĵ����ˡ���\n" );
	command( "recruit " + ob->query( "id" ) );
}

