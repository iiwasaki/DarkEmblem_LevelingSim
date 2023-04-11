#include "imgui.h"
#include <stdlib.h>
#include <time.h>
#include "DE_LevelSim.h"
#include "DE_Class.h"

namespace LevelSim
{
	void Initialize()
	{
		srand(time(NULL));
	}

	int ResolveRoll(bool useAdvantage) 
	{
		int roll = rand() % 20 + 1;
		if (useAdvantage)
		{
			int roll2 = rand() & 20 + 1;
			roll = (roll2 > roll) ? roll2 : roll;
		}
		return roll;

	}
	void RenderUI(std::vector<LevelSim::DE_Class> classes)
	{
		
		
		static int roll = 0;
		static int adv_roll = 0;
		static int total = 0;
		static int HP = classes[0].HP;
		static int MP = classes[0].MP;
		static int mgt = classes[0].mgt;
		static int dex = classes[0].dex;
		static int spd = classes[0].spd;
		static int def = classes[0].def;
		static int res = classes[0].res;
		static int g_HP = classes[0].g_HP;
		static int g_MP = classes[0].g_MP;
		static int g_mgt = classes[0].g_mgt;
		static int g_dex = classes[0].g_dex;
		static int g_spd = classes[0].g_spd;
		static int g_def = classes[0].g_def;
		static int g_res = classes[0].g_res;

		static bool advantage = false;
		static int max_level = 10;
		static int sim_count = 100;

		static double end_HP = 0.0;
		static double end_MP = 0.0;
		static double end_mgt = 0.0;
		static double end_dex = 0.0;
		static double end_spd = 0.0;
		static double end_def = 0.0;
		static double end_res = 0.0;

		static int hi_HP = 0;
		static int hi_MP = 0;
		static int hi_mgt = 0;
		static int hi_dex = 0;
		static int hi_spd = 0;
		static int hi_def = 0;
		static int hi_res = 0;

		static int lo_HP = 0;
		static int lo_MP = 0;
		static int lo_mgt = 0;
		static int lo_dex = 0;
		static int lo_spd = 0;
		static int lo_def = 0;
		static int lo_res = 0;

		ImGui::Begin("Leveler");

		static int selected = 0;

		ImGui::SeparatorText("Pick a Class: ");
		if (ImGui::BeginListBox("##"))
		{
			for (int n = 0; n < classes.size(); n++)
			{
				if (ImGui::Selectable(classes[n].name, selected == n))
				{
					selected = n;
					HP = classes[selected].HP;
					MP = classes[selected].MP;
					mgt = classes[selected].mgt;
					dex = classes[selected].dex;
					spd = classes[selected].spd;
					def = classes[selected].def;
					res = classes[selected].res;
					g_HP = classes[selected].g_HP;
					g_MP = classes[selected].g_MP;
					g_mgt = classes[selected].g_mgt;
					g_dex = classes[selected].g_dex;
					g_spd = classes[selected].g_spd;
					g_def = classes[selected].g_def;
					g_res = classes[selected].g_res;
				}
					
			}
			ImGui::EndListBox();
		}

		ImGui::SeparatorText("Edit Starting Stats: (Dbl click or drag slider)");
		if (ImGui::BeginTable("##", 2))
		{
			
			/* Row 1: Class Name*/
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text(classes[selected].name);
			ImGui::TableNextColumn();

			/* Row HP */
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::DragInt("HP", &HP, 0, 0, 100, "%d");
			ImGui::TableNextColumn();
			ImGui::DragInt("HP Growth", &g_HP, 0, 0, 100, "%d");
			
			/* Row MP */
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::DragInt("MP", &MP, 0, 0, 100, "%d");
			ImGui::TableNextColumn();
			ImGui::DragInt("MP Growth", &g_MP, 0, 0, 100, "%d");
			
			/* Row Might*/
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::DragInt("Might", &mgt, 0, 0, 100, "%d");
			ImGui::TableNextColumn();
			ImGui::DragInt("Might Growth", &g_mgt, 0, 0, 100, "%d");

			/* Row Dex */
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::DragInt("Dex", &dex, 0, 0, 100, "%d");
			ImGui::TableNextColumn();
			ImGui::DragInt("Dex Growth", &g_dex, 0, 0, 100, "%d");

			/* Row Speed*/
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::DragInt("Speed", &spd, 0, 0, 100, "%d");
			ImGui::TableNextColumn();
			ImGui::DragInt("Speed Growth", &g_spd, 0, 0, 100, "%d");
			
			/* Row Def */
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::DragInt("Defense", &def, 0, 0, 100, "%d");
			ImGui::TableNextColumn();
			ImGui::DragInt("Defense Growth", &g_def, 0, 0, 100, "%d");

			/* Row Resistance*/
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::DragInt("Resistance", &res, 0, 0, 100, "%d");
			ImGui::TableNextColumn();
			ImGui::DragInt("Res. Growth", &g_res, 0, 0, 100, "%d");

			ImGui::EndTable();
		}

		ImGui::SeparatorText("Configure Leveling Options");
		
		ImGui::Checkbox("Use \"Advantage\" Roll?", &advantage);
		ImGui::InputInt("Desired Ending Level", &max_level);
		ImGui::InputInt("Number of Simulations", &sim_count);

		ImGui::Separator();

		if (ImGui::Button("Begin Simulation"))
		{
			if (sim_count < 2 || max_level < 2 || sim_count > 10000000 || max_level > 100)
			{
				ImGui::OpenPopup("Error");
			}
			else 
			{
				end_HP = 0;
				end_MP = 0;
				end_mgt = 0;
				end_dex = 0;
				end_spd = 0;
				end_def = 0;
				end_res = 0;

				hi_HP = 0;
				hi_MP = 0;
				hi_mgt = 0;
				hi_dex = 0;
				hi_spd = 0;
				hi_def = 0;
				hi_res = 0;

				/* Could use limits but it's never going to get this high anyway*/
				lo_HP = 99999;
				lo_MP = 99999;
				lo_mgt = 99999;
				lo_dex = 99999;
				lo_spd = 99999;
				lo_def = 99999;
				lo_res = 99999;

				for (int i = 0; i < sim_count; i++)
				{
					int calc_HP = HP;
					int calc_MP = MP;
					int calc_mgt = mgt;
					int calc_dex = dex;
					int calc_spd = spd;
					int calc_def = def;
					int calc_res = res;

					/* Sim growth per level*/
					for (int j = 1; j < max_level; j++)
					{
						// HP
						roll = ResolveRoll(advantage);
						calc_HP += (roll > g_HP) ? 1 : 0;

						// MP
						roll = ResolveRoll(advantage);
						calc_MP += (roll > g_MP) ? 1 : 0;

						// Might
						roll = ResolveRoll(advantage);
						calc_mgt += (roll > g_mgt) ? 1 : 0;

						// Dexterity
						roll = ResolveRoll(advantage);
						calc_dex += (roll > g_dex) ? 1 : 0;

						// Speed
						roll = ResolveRoll(advantage);
						calc_spd += (roll > g_spd) ? 1 : 0;

						// Defense
						roll = ResolveRoll(advantage);
						calc_def += (roll > g_def) ? 1 : 0;

						// Resistance
						roll = ResolveRoll(advantage);
						calc_res += (roll > g_res) ? 1 : 0;
					}
					end_HP += calc_HP;
					end_MP += calc_MP;
					end_mgt += calc_mgt;
					end_dex += calc_dex;
					end_spd += calc_spd;
					end_def += calc_def;
					end_res += calc_res;

					hi_HP = (calc_HP > hi_HP) ? calc_HP : hi_HP;
					hi_MP = (calc_MP > hi_MP) ? calc_MP : hi_MP;
					hi_mgt = (calc_mgt > hi_mgt) ? calc_mgt : hi_mgt;
					hi_dex = (calc_dex > hi_dex) ? calc_dex : hi_dex;
					hi_spd = (calc_spd > hi_spd) ? calc_spd : hi_spd;
					hi_def = (calc_def > hi_def) ? calc_def : hi_def;
					hi_res = (calc_res > hi_res) ? calc_res : hi_res;

					lo_HP = (calc_HP < lo_HP) ? calc_HP : lo_HP;
					lo_MP = (calc_MP < lo_MP) ? calc_MP : lo_MP;
					lo_mgt = (calc_mgt < lo_mgt) ? calc_mgt : lo_mgt;
					lo_dex = (calc_dex < lo_dex) ? calc_dex : lo_dex;
					lo_spd = (calc_spd < lo_spd) ? calc_spd : lo_spd;
					lo_def = (calc_def < lo_def) ? calc_def : lo_def;
					lo_res = (calc_res < lo_res) ? calc_res : lo_res;
				}
				end_HP /= sim_count;
				end_MP /= sim_count;
				end_mgt /= sim_count;
				end_dex /= sim_count;
				end_spd /= sim_count;
				end_def /= sim_count;
				end_res /= sim_count;

				ImGui::OpenPopup("Simulate");
			}
		}

		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		if (ImGui::BeginPopupModal("Error", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Simulation error!");
			ImGui::Separator();
			ImGui::Text("Ending level must be in the range of 2-100 (at least 2, at most 100)");
			ImGui::Text("Number of simulations must be in the range of 2-10000000 (at least 2, at most 10,000,000)");
				

			if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::SetItemDefaultFocus();
				
			ImGui::EndPopup();
		}

		if (ImGui::BeginPopupModal("Simulate", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			
			ImGui::Text("Simulated %s from level 1 to %d %d times", classes[selected].name, max_level, sim_count);
			if (advantage) 
			{
				ImGui::Text("Advantage roll was used.");
			}
			else
			{
				ImGui::Text("Advantage roll was NOT used.");
			}

			ImGui::Separator();

			if (ImGui::BeginTable("##", 4))
			{
				/* Row HP */
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("HP:");
				ImGui::TableNextColumn();
				ImGui::Text("High: %d", hi_HP);
				ImGui::TableNextColumn();
				ImGui::Text("Low: %d", lo_HP);
				ImGui::TableNextColumn();
				ImGui::Text("Average: %.5f", end_HP);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("MP:");
				ImGui::TableNextColumn();
				ImGui::Text("High: %d", hi_MP);
				ImGui::TableNextColumn();
				ImGui::Text("Low: %d", lo_MP);
				ImGui::TableNextColumn();
				ImGui::Text("Average: %.5f", end_MP);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Might:");
				ImGui::TableNextColumn();
				ImGui::Text("High: %d", hi_mgt);
				ImGui::TableNextColumn();
				ImGui::Text("Low: %d", lo_mgt);
				ImGui::TableNextColumn();
				ImGui::Text("Average: %.5f", end_mgt);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Dexterity:");
				ImGui::TableNextColumn();
				ImGui::Text("High: %d", hi_dex);
				ImGui::TableNextColumn();
				ImGui::Text("Low: %d", lo_dex);
				ImGui::TableNextColumn();
				ImGui::Text("Average: %.5f", end_dex);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Speed:");
				ImGui::TableNextColumn();
				ImGui::Text("High: %d", hi_spd);
				ImGui::TableNextColumn();
				ImGui::Text("Low: %d", lo_spd);
				ImGui::TableNextColumn();
				ImGui::Text("Average: %.5f", end_spd);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Defense:");
				ImGui::TableNextColumn();
				ImGui::Text("High: %d", hi_def);
				ImGui::TableNextColumn();
				ImGui::Text("Low: %d", lo_def);
				ImGui::TableNextColumn();
				ImGui::Text("Average: %.5f", end_def);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Resistance:");
				ImGui::TableNextColumn();
				ImGui::Text("High: %d", hi_res);
				ImGui::TableNextColumn();
				ImGui::Text("Low: %d", lo_res);
				ImGui::TableNextColumn();
				ImGui::Text("Average: %.5f", end_res);

				ImGui::EndTable();
			}

			if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::SetItemDefaultFocus();

			ImGui::EndPopup();
		}

		ImGui::End();
	}

	
}