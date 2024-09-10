#include <print>
#include <iostream>
#include <Zut/ZxFS.h>
#include <Zut/ZxArg.h>
#include <Zut/ZxMem.h>
#include <Zut/ZxJson.h>
#include <Zut/ZxCvt.h>
#include <ReVN/RxGSD/Core/SPT_File.h>
#include <ReVN/RxGSD/Core/SPT_Global.h>

namespace RxGSD { using namespace ZQF::ReVN::RxGSD; }


static auto Export(const std::vector<std::string>& vcName, const std::string_view msSptPath, const std::string_view msJsonPath, const std::size_t nCodePage) -> bool
{
	RxGSD::SPT::File spt{ msSptPath };

	ZxCvt cvt;
	ZxJson::JArray_t msg_json;
	for (auto& code : spt.GetCodeList())
	{
		if (code.GetArgType0().GetType0TextLen() == 0) { continue; };

		ZxJson::JValue msg_obj;

		const auto char_name_seq{ code.GetArgType0().GetNameSeq() };
		if (char_name_seq != static_cast<std::uint32_t>(-1))
		{
			msg_obj["chr"] = vcName[char_name_seq];
		}

		const auto msg_text{ cvt.MBCSToUTF8(code.GetArgType0().GetType0Text(), nCodePage) };
		msg_obj["msg_raw"] = msg_text;
		msg_obj["msg_tra"] = msg_text;

		msg_json.emplace_back(std::move(msg_obj));
	}

	if (msg_json.empty())
	{
		std::println("not find text: -> {}", msSptPath);
		return false;
	}

	ZxJson::StoreViaFile(msJsonPath, ZxJson::JValue{ std::move(msg_json) }, true, true);
	std::println("export -> {}", msSptPath);

	return true;
}

static auto Import(const std::string_view msSptPath, const std::string_view msJsonPath, const std::string_view msSptNewPath, const std::size_t nCodePage) -> bool
{
	RxGSD::SPT::File spt{ msSptPath };

	const auto msg_json_doc{ ZxJson::LoadViaFile(msJsonPath) };
	const auto& msg_vec{ msg_json_doc.GetArray() };

	ZxCvt cvt;
	std::size_t msg_idx{};
	for (auto& code : spt.GetCodeList())
	{
		if (code.GetArgType0().GetType0TextLen() == 0) { continue; };

		const auto text_u8{ msg_vec.at(msg_idx).At("msg_tra").GetStrView() };
		const auto text_ansi{ cvt.UTF8ToMBCS(text_u8, nCodePage) };
		code.GetArgType0().SetType0Text(text_ansi);
		msg_idx++;
	}

	if (msg_idx == 0)
	{
		std::println("not find text: -> {}", msSptPath);
		return false;
	}

	if (msg_idx != msg_vec.size())
	{
		std::println("text count mismatch: -> {}", msSptPath);
		return false;
	}

	spt.Make().Save(msSptNewPath);
	std::println("import -> {}", msSptNewPath);

	return true;
}


auto main(void) -> int
{
	try
	{
		ZxArg::Parser arg;
		arg.AddOption("-spt", "spt file path");
		arg.AddOption("-new", "new spt file path");
		arg.AddOption("-txt", "json file path");
		arg.AddOption("-global", "global.dat file path");
		arg.AddOption("-code", "codepage");
		arg.AddOption("-mode", "mode: single | batch");
		arg.AddOption("-way", "way: export | import");
		arg.AddExample("-mode single -way export -global global.dat -spt 0scene_pro001.spt -txt 0scene_pro001.json -code 932");
		arg.AddExample("-mode single -way import -global global.dat -spt 0scene_pro001.spt -txt 0scene_pro001.json -new 0scene_pro001.spt.new -code 932");
		arg.AddExample("-mode batch -way export -global global.dat -spt spt/ -txt spt_txt/ -code 932");
		arg.AddExample("-mode batch -way import -global global.dat -spt spt/ -txt spt_txt/ -new spt_new/ -code 932");
		if (arg.Parse() == false) { return 0; }

		const auto mode{ arg["-mode"].Get<std::string_view>() };
		const auto way{ arg["-way"].Get<std::string_view>() };
		const auto code_page{ arg["-code"].Get<std::size_t>() };
		

		RxGSD::SPT::Global global;
		global.Load(arg["-global"].Get<std::string_view>());
		std::vector<std::string> name_list{ global.GetStrTable(code_page) };

		if (mode == "single")
		{
			const auto spt_path{ arg["-spt"].Get<std::string_view>() };
			const auto json_path{ arg["-txt"].Get<std::string_view>() };

			if (way == "export")
			{
				::Export(name_list, spt_path, json_path, code_page);
				return 0;
			}
			else if (way == "import")
			{
				::Import(spt_path, json_path, arg["-new"].Get<std::string_view>(), code_page);
				return 0;
			}
		}
		else if (mode == "batch")
		{
			const auto spt_dir{ arg["-spt"].Get<std::string_view>() };
			const auto json_dir{ arg["-txt"].Get<std::string_view>() };

			if (way == "export")
			{
				ZxFS::DirMake(json_dir, true);
				for (ZxFS::Walker walker{ spt_dir }; walker.NextFile();)
				{
					if (walker.IsSuffix(".spt") == false) { continue; }
					const auto json_file_path{ std::string{json_dir}.append(ZxFS::FileNameStem(walker.GetName())).append(".json") };
					::Export(name_list, walker.GetPath(), json_file_path, code_page);
				}
				return 0;
			}
			else if (way == "import")
			{
				const auto spt_new_folder{ arg["-new"].Get<std::string_view>() };
				ZxFS::DirMake(spt_new_folder, true);;
				for (ZxFS::Walker walker{ json_dir }; walker.NextFile();)
				{
					if (walker.IsSuffix(".json") == false) { continue; }
					const auto spt_file_path{ std::string{ spt_dir }.append(ZxFS::FileNameStem(walker.GetName())).append(".spt") };
					const auto spt_file_save_path{ std::string{ spt_new_folder }.append(ZxFS::FileNameStem(walker.GetName())).append(".spt") };
					::Import(spt_file_path, walker.GetPath(), spt_file_save_path, code_page);
				}
				return 0;
			}
		}

		std::println("unknown command!");
	}
	catch (const std::exception& err)
	{
		std::println(std::cerr, "std::exception: {}", err.what());
	}
}
