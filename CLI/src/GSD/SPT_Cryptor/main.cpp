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

		const auto mode{ arg["-mode"].GetStrView() };

		if (mode == "single")
		{
			ZxMem spt_file{ arg["-spt"].GetStrView() };
			RxGSD::SPT::Cryptor::Decode(spt_file.Span(), arg["-able"].GetBool());
			spt_file.Save(arg["-save"].GetStrView());
			std::println("cryptor done!");
		}
		else if (mode == "batch")
		{
			const auto is_readbale{ arg["-able"].GetBool() };
			const auto save_path{ arg["-save"].GetStrView() };
			for (ZxFS::Walker walker{ arg["-dir"].GetStrView() }; walker.NextFile();)
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
