#include <print>
#include <iostream>
#include <Zut/ZxArg.h>
#include <Zut/ZxFS.h>
#include <Zut/ZxMem.h>
#include <ReVN/RxGSD/Core/SPT_Cryptor.h>

namespace RxGSD { using namespace ZQF::ReVN::RxGSD; }


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-spt", "spt file path");
		arg.AddOption("-dir", "spt dir path");
		arg.AddOption("-save", "save path");
		arg.AddOption("-able", "enable the engine to read unencrypted spt files.");
		arg.AddOption("-mode", "mode: single | batch");
		arg.AddExample("-mode single -able true -spt 0scene_pro001.spt -save 0scene_pro001.spt.dec");
		arg.AddExample("-mode batch -able true -dir spt/ -save spt_dec/");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].Get<std::string_view>() };

		if (mode == "single")
		{
			ZxMem spt_file{ arg["-spt"].Get<std::string_view>() };
			RxGSD::SPT::Cryptor::Decode(spt_file.Span(), arg["-able"].Get<bool>());
			spt_file.Save(arg["-save"].Get<std::string_view>());
			std::println("cryptor done!");
		}
		else if (mode == "batch")
		{
			const auto is_readbale{ arg["-able"].Get<bool>() };
			const auto save_path{ arg["-save"].Get<std::string_view>() };
			for (ZxFS::Walker walker{ arg["-dir"].Get<std::string_view>() }; walker.NextFile();)
			{
				ZxMem spt_file{ walker.GetPath() };
				RxGSD::SPT::Cryptor::Decode(spt_file.Span(), is_readbale);
				spt_file.Save(std::string{ save_path }.append(walker.GetName()));
				std::println("cryptor -> {}", walker.GetPath());
			}
		}
		else
		{
			std::println("unknown command!");
		}
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}
