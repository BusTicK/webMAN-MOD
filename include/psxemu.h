#ifdef COBRA_ONLY

#define PLAYSTATION      "PLAYSTATION "

static u32 detect_cd_sector_size(char *buffer)
{
	int sec_size[4] = {2048, 2336, 2368, 2448};
	for(int n = 0; n < 4; n++)
	{
		if(!strncmp(buffer + ((sec_size[n]<<4) + 0x20), PLAYSTATION, 0xC)) return sec_size[n];
	}

	return 2352;
}

static u32 default_cd_sector_size(size_t discsize)
{
	if(!(discsize % 0x930)) return 2352;
	if(!(discsize % 0x920)) return 2336;
	if(!(discsize % 0x940)) return 2368; // not supported by Cobra
	if(!(discsize % 0x990)) return 2448;
	if(!(discsize % 0x800)) return 2048;

	return 2352;
}

static void select_ps1emu(const char *path)
{
	webman_config->ps1emu = pad_select_netemu(path, webman_config->ps1emu);

	sys_map_path("/dev_flash/ps1emu/ps1_netemu.self", NULL);
	sys_map_path("/dev_flash/ps1emu/ps1_emu.self"   , NULL);

	char msg[50];

	if(webman_config->ps1emu)
	{
		sys_map_path("/dev_flash/ps1emu/ps1_netemu.self", "///dev_flash/ps1emu/ps1_emu.self");
		sys_map_path("/dev_flash/ps1emu/ps1_emu.self"   , "///dev_flash/ps1emu/ps1_netemu.self");

		sprintf(msg, "%s %s", "ps1_netemu.self", STR_ENABLED);
	}
	else
	{
		sprintf(msg, "%s %s", "ps1_emu.self", STR_ENABLED);
	}

	if(pad_data.len > 0) show_msg(msg);
}
#endif
