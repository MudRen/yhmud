
int permit_recruit(object ob)
{
        if (ob->query("detach") || ob->query("betrayer"))
        {
                command("say �ٺ٣�����ĺ��֮��һ����ȥ��");
                return 0;
        }

        if (ob->query("family/family_name")
           && ob->query("family/family_name") != "��������")
        {
                command("say ���Ȼ�Ѿ�������ʦָ�㣬�������Ÿ�ʲô��");
                return 0;
        }
        return 1;
}
