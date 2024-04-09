#pragma once

namespace ImgRes
{
	// Player
	const std::string_view player_idle				= "player_idle";
	const std::string_view player_idle_to_run_anim  = "player_idle_to_run";
	const std::string_view player_run_to_idle_anim  = "player_run_to_idle";
	const std::string_view player_jump				= "player_jump";

	// TitleLevel
	const std::string_view title_background			= "spr_title_background.png";
	const std::string_view title_fence				= "spr_title_fence_0.png";
	const std::string_view title_plant				= "Plants";

	// FactoryLevel
	const std::string_view factory_background1		= "spr_background_factory_1.png";
	const std::string_view factory_background2		= "spr_background_factory_2.png";
	const std::string_view factory_background3		= "spr_background_factory_3.png";
	const std::string_view factory_background4	 	= "spr_background_factory_4.png";
	const std::string_view factory_background5		= "spr_background_factory_5.png";

	// HeadHunterLevel
	const std::string_view headhunter_background1	= "spr_background_headhunter1.png";
	const std::string_view headhunter_background2	= "spr_background_headhunter2.png";
}

namespace Anim
{
	const std::string_view player_idle_anim			= "player_idle";
	const std::string_view player_idle_to_run_anim	= "player_idle_to_run";
	const std::string_view player_run_to_idle_anim	= "player_run_to_idle";
	const std::string_view player_jump				= "player_jump";
}