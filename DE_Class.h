/* Declares DE_Class struct. Implemented in the DE_Class.cpp. */

#pragma once
#include <vector>

namespace LevelSim 
{
	struct DE_Class
	{
		const char* name;
		/* Standard values */
		int HP;
		int MP;
		int mgt;
		int dex;
		int spd;
		int def;
		int res;

		/* Growth rates */
		int g_HP;
		int g_MP;
		int g_mgt;
		int g_dex;
		int g_spd;
		int g_def;
		int g_res;
	};

	void DE_Class_Init(DE_Class& cl, const char* className, std::vector<int> stats, std::vector<int> grates);
}
