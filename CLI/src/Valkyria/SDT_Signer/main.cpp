#include <print>
#include <iostream>
#include <Zut/ZxArg.h>
#include <Zut/ZxMem.h>
#include <Zut/ZxFS.h>
#include <ReVN/RxValkyria/Core/SDT_Signer.h>

namespace RxValkyria { using namespace ZQF::ReVN::RxValkyria; }


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-dir", "sdt file dir");
		arg.AddOption("-sav", "sav dir");
		arg.AddOption("-key", "key string");
		arg.AddOption("-len", "game title bytes");
		arg.AddExample("-key VAL-0064 -len 0x20 -dir data06/ -sav data06_sig/");
		if (arg.Parse() == false) { return 0; }

		const auto game_key_str = arg["-key"].GetStrView();
		const auto game_title_len = arg["-len"].GetNum();
		const auto sdt_org_dir = arg["-dir"].GetStrView();
		const auto sdt_sav_dir = arg["-sav"].GetStrView();

		//const auto key = "VAL-0064";
		//const auto len = 0x20;
		//const auto dir_path = "data06/";
		//const auto sav_path = "data06_sig/";

		ZxMem cache;
		ZxFS::DirMakeRecursive(sdt_sav_dir);
		RxValkyria::SDT::Signer signer{ game_key_str, game_title_len };
		for (ZxFS::Walker walker{ sdt_org_dir }; walker.NextFile(); )
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
