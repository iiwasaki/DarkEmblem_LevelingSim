/* Header file for the actual leveling simulator. 

RenderUI handles all of the actual calculation and the window that you see. All of the code is in the implementation in the .cpp file.

ResolveRoll() will roll a dice (with advantage, if advantage is true) and return a value from 1-20 given the outcome of the roll(s).

Initialize()'s only job is to initialize the global random seed. 
*/

#pragma once
#include <vector>
#include "DE_Class.h"

namespace LevelSim
{	
	void RenderUI(std::vector<LevelSim::DE_Class> classes);

	int ResolveRoll(bool advantage);

	void Initialize();

}