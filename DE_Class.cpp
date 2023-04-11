#include "DE_Class.h"

namespace LevelSim
{
	void DE_Class_Init(DE_Class& cl, const char* className, std::vector<int> stats, std::vector<int> grates)
	{
		cl.name = className;
		if (stats.size() != 7 || grates.size() != 7) 
		{
			return;
		}
		cl.HP = stats[0];
		cl.MP = stats[1];
		cl.mgt = stats[2];
		cl.dex = stats[3];
		cl.spd = stats[4];
		cl.def = stats[5];
		cl.res = stats[6];
		cl.g_HP = grates[0];
		cl.g_MP = grates[1];
		cl.g_mgt = grates[2];
		cl.g_dex = grates[3];
		cl.g_spd = grates[4];
		cl.g_def = grates[5];
		cl.g_res = grates[6];
	}
}