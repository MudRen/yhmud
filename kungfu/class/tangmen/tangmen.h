int permit_recruit( object ob )
{
	
	 command("say �Բ��������ݲ���ͽ�������ʱ�������ɡ�");
	 return 0;
	 

	if ( ob->query( "detach/��������" ) || ob->query( "betrayer/��������" ) )
	{
		command( "say �㷴���޳����Ҳ�������Ϊͽ��" );
		return(0);
	}

	if ( ob->query( "betrayer/times" ) )
	{
		command( "say �ߣ���������������ʹ�޵ľ��ǲ��Ҳ���֮ͽ��" );
		return(0);
	}

	if ( ob->query( "born_family" ) != "��������" && !ob->query( "reborn/times" ) )
	{
		command( "hmm" );
		command( "say �����������������ҳ����������ˡ�" );
		return(0);
	}

	if ( ob->query( "family/family_name" ) &&
	     ob->query( "family/family_name" ) != "��������" )
	{
		command( "hmm" );
		command( "say ���Ȼ�Ѿ���Ұ�ʦ����Ӧ������Ϊ�����ܻ���������" );
		return(0);
	}

	return(1);
}
