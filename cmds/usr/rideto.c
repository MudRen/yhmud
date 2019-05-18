// Copyright (C) 2003, by Lonely. All rights reserved.
// Modified by Ivy (2013-11-30 22:56:59)
// rideto.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

mapping places = ([
        "baituo"   : "/d/baituo/guangchang",       
        "beijing"  : "/d/beijing/tiananmen",
        "changan"  : "/d/changan/bridge2",
        "chengdu"  : "/d/city3/guangchang",
        "dali"     : "/d/dali/center",
        "emei"     : "/d/emei/huayanding",
        "foshan"   : "/d/foshan/street3",
        "fuzhou"   : "/d/fuzhou/dongjiekou",
        "gc"       : "/d/city/guangchang",
        "guanwai"  : "/d/guanwai/jishi",
        "guiyun"   : "/d/guiyun/taihu",
        "gumu"     : "/d/gumu/mumen",
        "hangzhou" : "/d/hangzhou/road10",
        "heimuya"  : "/d/heimuya/shimen",
        //"henyang"  : "/d/henshan/hengyang",
        "hengyang"  : "/d/henshan/hengyang",
        "huashan"  : "/d/huashan/shaluo",
        "jiaxing"  : "/d/quanzhou/jiaxing",
        "jingzhou" : "/d/jingzhou/guangchang",
        "kaifeng"  : "/d/kaifeng/zhuque",
        "kunlun"   : "/d/kunlun/klshanlu",
        "kunming"  : "/d/kunming/jinrilou",
        "lanzhou"  : "/d/lanzhou/guangchang",
        "lingjiu"  : "/d/lingjiu/jian",
        "lingzhou" : "/d/lingzhou/center",
        "luoyang"  : "/d/luoyang/center",
        "mingjiao" : "/d/mingjiao/shanjiao",
        "murong"   : "/d/yanziwu/hupan",
        "nanhai"   : "/d/xiakedao/haibin",
        "nanyang"  : "/d/shaolin/nanyang",
        "quanzhen" : "/d/quanzhen/damen",
        "quanzhou" : "/d/quanzhou/zhongxin",
        "shaolin"  : "/d/shaolin/shanmen",
        "suzhou"   : "/d/suzhou/canlangting",
        "taishan"  : "/d/taishan/taishanjiao",
        "wudang"   : "/d/wudang/jiejianyan",
        "wugong"   : "/d/quanzhen/zhongxin",
        "xiangyang": "/d/xiangyang/guangchang",
        "xiaoyao"  : "/d/xiaoyao/xiaodao4",        
        "xingxiu"  : "/d/xingxiu/xxh1",
        "xuedao"   : "/d/xuedao/wangyougu",
        "xueshan"  : "/d/xuedao/nroad4",
        "yangzhou" : "/d/city/guangchang",
        "yanziwu"  : "/d/yanziwu/bozhou",
        "yongdeng" : "/d/huanghe/yongdeng",
        "zhongnan" : "/d/quanzhen/shanjiao",
        "zhongzhou": "/d/zhongzhou/shizhongxin",
        	//������ɽ 2017-02-11
        "hengshan" : "/d/henshan/nantian",
        	//��������ȡ�����ɽ 2017-02-18
        "jueqing"  : "/d/jueqing/shanjiao",
        "tiezhang" : "/d/tiezhang/shanjiao",
		//�����һ����� 2018-06-02
		"taohua"   : "/d/taohua/haitan",
        	
        // "hujia"    : "/d/guanwai/xiaoyuan",
        // "tangmen"  : "/d/tangmen/",
        // "yaowang"  : "/d/yaowang/",
]);

int main(object me, string arg)
{
        object riding, room;
        string where;

        if (! arg) return help(me);

        if (me->over_encumbranced()) 
                return notify_fail("��ĸ��ɹ��أ��������á�\n"); 
        
        if (me->query_encumbrance() < 0) 
                return notify_fail("��ĸ��ɳ��ֹ��ϣ��������á�\n"); 

        if (me->query_temp("sleeped")) 
                return notify_fail("�������������ء�\n");

        if (me->is_in_prison())   
                return notify_fail("�����������أ������ʲô����\n");
                                
        if (me->is_fighting()) 
                return notify_fail("����������ս����\n");

        if (me->is_busy() || me->query("doing")) 
                return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
                
        if (! objectp(riding = me->query_temp("is_riding")))
                return notify_fail("�㻹û�����\n"); 
        
        if (! present(riding->query("id"), me))
                return notify_fail("������ﲻ������ߣ�\n");

        /*
        if (present("letter", me)) 
                return notify_fail("�����ϴ����ܺ���\n");

        if (! environment(me)->query("outdoors")) 
                return notify_fail("�ڷ����ﲻ�����ܣ�\n");
        */

        if (environment(me)->query("outdoors") == "gaochang") 
                return notify_fail("�㷢��������������������ָ�ӣ�\n");

        if (environment(me)->query("no_ride") ||
            environment(me)->query("maze"))
                return notify_fail("�㷢�������е�Ź֣����������������ָ�ӣ�\n");                

        if (me->query_condition("killer"))
                return notify_fail("�������������أ��������޼ɵ����ڹٵ�������\n");

        //if (member_array(arg, keys(places)) == -1 && arg != "home") 
        //����family����
        if (member_array(arg, keys(places)) == -1 && arg != "home" && arg != "family")
                return notify_fail("����ط��޷�������ȥ��\n");
                
        if (arg == "home" && ! me->query("private_room/position")) 
                return notify_fail("�㻹û��ס���أ�\n");

        if (arg == "home" && stringp(me->query("private_room/position")) &&
           file_size(me->query("private_room/position") + ".c") > 0)
                room = get_object(me->query("private_room/position"));else
                
         //�¼�family by н������
        // ���⣺��Ĺ2���������2��������ǧ�ߺ��Զ�ת�����ưʵ�������ư���������
//��������С���ɲ��ܣ��ѱ��رյ����ɲ��ܡ�

         if (arg == "family") 
         	{
         		if (! me->query("family/family_name")) 
         			return notify_fail("�㻹û�����ɣ�����ʹ�� rideto family ָ�\n");else
         			//if (me->query("combat_exp") < 1000000) return notify_fail("�������ڵľ��黹����ʹ�� rideto family ָ�\n");
         			//ת����ȡ��100��exp����
         			if (me->query("combat_exp") < 800000 && !me->query("reborn")) 
         				return notify_fail("�������ڵľ��黹����ʹ�� rideto family ָ�\n");
         				else 
         					{ if (me->query("family/family_name")=="������") room = get_object("/d/shaolin/fzlou2");else
         						if (me->query("family/family_name")=="Ľ������") room = get_object("/d/yanziwu/canheju");else
         						if (me->query("family/family_name")=="ŷ������") room = get_object("/d/baituo/dating");else
         						if (me->query("family/family_name")=="��ڤ��") room = get_object("/d/xuanminggu/xuanmingfeng");else
         						if (me->query("family/family_name")=="������") room = get_object("/d/kunlun/tieqinju");else
         						if (me->query("family/family_name")=="��ң��") room = get_object("/d/xiaoyao/qingcaop");else
         						if (me->query("family/family_name")=="������") room = get_object("/d/beijing/zhengting");else
         						if (me->query("family/family_name")=="������") room = get_object("/d/xingxiu/riyuedong");else
         					  if (me->query("family/family_name")=="������") room = get_object("/d/xueshan/neidian");else
         						if (me->query("family/family_name")=="�嶾��") room = get_object("/d/wudu/huating1");else
         						if (me->query("family/family_name")=="�һ���") room = get_object("/d/taohua/dating");else
         						if (me->query("family/family_name")=="Ѫ����") room = get_object("/d/xuedao/shandong3");else
         					  if (me->query("family/family_name")=="���ư�") room = get_object("/d/tiezhang/wztang");else
         					  //if (me->query("family/family_name")=="�����") room = get_object("/d/jueqing/zizhuxuan");else
         						if (me->query("family/family_name")=="�䵱��") room = get_object("/d/wudang/xiaoyuan");else
         						if (me->query("family/family_name")=="÷ׯ") room = get_object("/d/meizhuang/houting");else
         						if (me->query("family/family_name")=="�������") room = get_object("/d/guanwai/xiaowu");else
         						if (me->query("family/family_name")=="ȫ���") room = get_object("/d/quanzhen/shiweishi");else
         						if (me->query("family/family_name")=="��ԭ���") room = get_object("/d/zhongzhou/miaojia_houting");else
         						if (me->query("family/family_name")=="�컨��") room = get_object("/d/kaifeng/hh_zhengting");else
         						if (me->query("family/family_name")=="���չ�") room = get_object("/d/lingjiu/dating");else
         						if (me->query("family/family_name")=="��ɽ��") room = get_object("/d/huashan/qunxianguan");else
         					  if (me->query("family/family_name")=="���ϻ���") room = get_object("/d/dali/neitang");else
         						if (me->query("family/family_name")=="ؤ��") room = get_object("/d/gaibang/undertre");else
         						if (me->query("family/family_name")=="��ɽ��") room = get_object("/d/henshan/zhurongfeng");else
         				    if (me->query("family/family_name")=="�������") room = get_object("/d/quanzhou/chating");else
         				    //������©�����̺Ͷ��� 2017-02-05
         				    if (me->query("family/family_name")=="����") room = get_object("/d/mingjiao/dadian");else
         				    if (me->query("family/family_name")=="������") room = get_object("/d/emei/hcahoudian");else
         				    //�������¿��ŵ���ɽ 2017-02-07
         				    if (me->query("family/family_name")=="��ɽ��") room = get_object("/d/songshan/fengchantai");else
							if (me->query("family/family_name")=="��������") room = get_object("/d/luoyang/zuixianlou4");else
         							//��Ĺ��֧
         						
         						if (me->query("family/family_name")=="��Ĺ��") 
         											{if (me->query("family/master_name") == "��Ī��") 
         												room = get_object("/d/gumu/liangong3");
         												else room = get_object("/d/gumu/mishi8");
         												}
         				    else
         				    	//�����֧					
         						if (me->query("family/family_name")=="�����") 
         											{if (me->query("family/master_name") == "��ǧ��") 
         												room = get_object("/d/jueqing/undertan");
         												else room = get_object("/d/jueqing/zizhuxuan");
         												}
         					
         						//��������С�����Լ��ѱ��رյ����ɡ�
         					 else	return notify_fail("�����ڵ������޷�ʹ�� rideto family ֱ������ʹ���ܡ�\n");
         					  //return notify_fail("�����ڵ������޷�ʹ�� rideto family ֱ������ʹ���ܡ�\n");																
         																					
         						}
         		}
         //�¼�family����
     
        else
        room = get_object(places[arg]);
        if (! room) return notify_fail("��о����ƺ��Ǹ��ط��е㲻�Ծ���\n");
        
        message("vision", me->name() + "���š�" + riding->name() + NOR "���Ҵ�ææ���뿪�ˡ�\n",
                environment(me), ({me}));
        
        where = room->query("short");
        
        tell_object(me, "��һ·��ͣ�㣬�糾���͵ĸϵ���" + where + "��\n");
        me->move(room);

        message("vision", me->name() + "���š�" + riding->name() + NOR "��һ·���۶�����\n",
                environment(me), ({me}));

        // me->receive_damage("qi", 10);

        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : rideto <�ص�>

�������ﵽ��ĳ���ص㡣Ŀǰ������������ȥ�ĵط��У�
baituo   : ����ɽ        beijing  : ��  ��        changan  : ��  ��
chengdu  : ��  ��        dali     : ��  ��        emei     : ��üɽ
foshan   : ��  ɽ        fuzhou   : ��  ��        guanwai  : ��  ��
guiyun   : ����ׯ        gumu     : ��  Ĺ        hangzhou : ��  ��
heimuya  : ��ľ��        hengyang : ��  ��        huashan  : ��  ɽ
jiaxing  : ��  ��        jingzhou : ��  ��        kaifeng  : ��  ��
kunlun   : ����ɽ        kunming  : ��  ��        lanzhou  : ��  ��
lingjiu  : ���չ�        lingzhou : ��  ��        luoyang  : ��  ��
mingjiao : ������        murong   : Ľ  ��        nanhai   : ��  ��
nanyang  : ��  ��        quanzhen : ȫ���        quanzhou : Ȫ  ��
suzhou   : ��  ��        taishan  : ̩  ɽ        wudang   : �䵱ɽ
wugong   : �书��        xiangyang: ��  ��        xiaoyao  : ��ң��
xingxiu  : ���޺�        xuedao   : Ѫ����        xueshan  : ѩ  ɽ
yangzhou : ��  ��        yanziwu  : ������        yongdeng : ��  ��
zhongnan : ����ɽ        zhongzhou: ��  ��        hengshan : ��  ɽ
jueqing  : �����        tiezhang : ����ɽ        family   : ����ʹ
home     : ס  ��

ע��rideto family ��ֱ����������ʹ��ֻ�������ɵ���ʹ�ã���exp��ﵽ80��

HELP
        );

        return 1;
}
 
