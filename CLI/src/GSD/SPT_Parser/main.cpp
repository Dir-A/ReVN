#include <print>
#include <iostream>
#include <Zut/ZxFS.h>
#include <Zut/ZxArg.h>
#include <Zut/ZxMem.h>
#include <Zut/ZxJson.h>
#include <ReVN/RxGSD/Core/SPT_File.h>

namespace RxGSD { using namespace ZQF::ReVN::RxGSD; }


static auto SptToJson(const std::string_view msSptPath, const std::string_view msJsonPath, const std::size_t nCodePage) -> void
{
	RxGSD::SPT::File spt_file{ msSptPath };
	const auto spt_json{ spt_file.Make(nCodePage) };
	ZxJson::StoreViaFile(msJsonPath, spt_json, true, true);
	std::println("spt_to_json -> {}", msSptPath);
}

static auto JsonToSpt(const std::string_view msJsonPath, const std::string_view msSptPath, const std::size_t nCodePage) -> void
{
	const auto spt_json{ ZxJson::LoadViaFile(msJsonPath) };
	RxGSD::SPT::File spt_file{ spt_json, nCodePage };
	spt_file.Make().Save(msSptPath);
	std::println("json_to_spt -> {}", msJsonPath);
}


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-spt", "spt file path");
		arg.AddOption("-json", "json file path");
		arg.AddOption("-dir", "spt dir path");
		arg.AddOption("-code", "codepage");
		arg.AddOption("-mode", "mode: single | batch");
		arg.AddOption("-way", "way: spt2json[spt to json] | json2spt[json to spt]");
		arg.AddExample("-mode single -way spt2json -spt 0scene_pro001.spt -json 0scene_pro001.spt.json -code 932");
		arg.AddExample("-mode single -way json2spt -json 0scene_pro001.spt.json -spt 0scene_pro001.spt.new -code 932");
		arg.AddExample("-mode batch -way spt2json -dir spt/ -json spt_json/ -code 932");
		arg.AddExample("-mode batch -way json2spt -dir spt_json/ -spt spt_new/ -code 932");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].GetStrView() };
		const auto way{ arg["-way"].GetStrView() };
		const auto code_page{ arg["-code"].GetNum() };

		if (mode == "single")
		{
			if (way == "spt2json")
			{
				::SptToJson(arg["-spt"].GetStrView(), arg["-json"].GetStrView(), code_page);
			}
			else if (way == "json2spt")
			{
				::JsonToSpt(arg["-json"].GetStrView(), arg["-spt"].GetStrView(), code_page);
			}
		}
		else if (mode == "batch")
		{
			if (way == "spt2json")
			{
				const auto spt_dir{ arg["-dir"].GetStrView() };
				const auto save_dir{ arg["-json"].GetStrView() };
				ZxFS::DirMakeRecursive(save_dir);
				for (ZxFS::Walker spt_walk{ spt_dir }; spt_walk.NextFile();)
				{
					if (spt_walk.IsSuffix(".spt") == false) { continue; }
					const auto json_file_path{ std::string{ save_dir }.append(ZxFS::FileNameStem(spt_walk.GetName())).append(".json") };
					::SptToJson(spt_walk.GetPath(), json_file_path, code_page);
				}
			}
			else if (way == "json2spt")
			{
				const auto json_dir{ arg["-dir"].GetStrView() };
				const auto save_dir{ arg["-spt"].GetStrView() };
				ZxFS::DirMakeRecursive(save_dir);
				for (ZxFS::Walker json_walk{ json_dir }; json_walk.NextFile();)
				{
					if (json_walk.IsSuffix(".json") == false) { continue; }
					const auto spt_file_path{ std::string{ save_dir }.append(ZxFS::FileNameStem(json_walk.GetName())).append(".spt") };
					::JsonToSpt(json_walk.GetPath(), spt_file_path, code_page);
				}
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
