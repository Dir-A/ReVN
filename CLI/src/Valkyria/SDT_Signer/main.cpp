#include <print>
#include <iostream>
#include <ZxArg/Parser.h>
#include <ZxMem/ZxMem.h>
#include <ZxFS/Core.h>
#include <ZxFS/Walker.h>
#include <RxValkyria/Core/SDT_Signer.h>


auto main(void) -> int
{
	try
	{
		ZQF::ZxArg::Parser arg;
		arg.AddCmd("-dir", "sdt file dir");
		arg.AddCmd("-sav", "sav dir");
		arg.AddCmd("-key", "key string");
		arg.AddCmd("-len", "game title bytes");
		arg.AddExample("-key VAL-0064 -len 0x20 -dir data06/ -sav data06_sig/");
		if (arg.Parse() == false) { return 0; }

		const auto game_key_str = arg["-key"].Get<std::string_view>();
		const auto game_title_len = arg["-len"].Get<std::size_t>();
		const auto sdt_org_dir = arg["-dir"].Get<std::string_view>();
		const auto sdt_sav_dir = arg["-sav"].Get<std::string_view>();

		//const auto key = "VAL-0064";
		//const auto len = 0x20;
		//const auto dir_path = "data06/";
		//const auto sav_path = "data06_sig/";

		ZQF::ZxMem cache;
		ZQF::ZxFS::DirMake(sdt_sav_dir, true);
		ZQF::RxValkyria::SDT::Signer signer{ game_key_str, game_title_len };
		for (ZQF::ZxFS::Walker walker{ sdt_org_dir }; walker.NextFile(); )
		{
			const auto org_path = walker.GetPath();
			const std::string sav_path = std::string{ sdt_sav_dir }.append(walker.GetName());

			cache.Load(org_path);
			signer.Sign(cache);
			cache.Save(sav_path);
			
			std::println("sig -> {} | sav -> {}", org_path, sav_path);
		}
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}
