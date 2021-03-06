#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <limits>
#include <fstream>

#include "game_functions.h"

void main()
{
	int player_experience = 0;
	int player_level = 0;
	int player_conditions = 1;
	int player_evasion = 0;
	int player_attack = 0;
	int player_current_health = 0;
	int player_defense = 0;
	int player_power = 0;
	int player_maximum_health = 0;
	int player_condition_damage = 0;
	int enemy_level = 0;
	int enemy_conditions = 1;
	int enemy_evasion = 0;
	int enemy_current_health = 0;
	int enemy_attack = 0;
	int enemy_defense = 0;
	int enemy_power = 0;
	int enemy_maximum_health = 0;
	int enemy_condition_damage = 0;
	int damage_this_turn = 0;
	int damage_roll = 0;
	int story_chapter = 0;
	int story_stage = 0;
	int story_scene = 0;
	std::string player_name;
	std::string enemy_name;
	std::string enemy_profession;
	std::string player_profession;
	bool attack_succeeds = true;
	bool is_player_turn = true;
	bool player_wins = false;
	bool enemy_wins = false;
	bool combat_continues = true;
	bool story_continues = true;
	bool game_clear = false;

	srand((unsigned int)time(NULL));

	player_name = get_player_name();
	make_space(2);
	player_profession = get_player_profession();
	make_space(5);

	story_chapter = 1;
	story_stage = 1;
	story_scene = 1;

	while (story_continues)
	{
		if (story_scene > 2)
		{
			story_scene = 1;
			story_stage++;			
		}
		if (story_stage > 10)
		{
			story_stage = 1;
			story_chapter++;
		}

		read_story_scene(story_chapter, story_stage, story_scene);
		story_scene++;

		enemy_name = "Goblin Recruit";
		enemy_profession = "goblin";

		player_level = 30;
		player_evasion = get_evasion(player_profession, player_level);
		player_attack = get_attack(player_profession, player_level);
		player_maximum_health = get_maximum_health(player_profession, player_level);
		player_defense = get_defense(player_profession, player_level);
		player_power = get_power(player_profession, player_level);
		player_current_health = player_maximum_health;

		enemy_level = 30;
		enemy_evasion = get_evasion(enemy_profession, enemy_level);
		enemy_attack = get_attack(enemy_profession, enemy_level);
		enemy_maximum_health = get_maximum_health(enemy_profession, enemy_level);
		enemy_defense = get_defense(enemy_profession, enemy_level);
		enemy_power = get_power(enemy_profession, enemy_level);
		enemy_current_health = enemy_maximum_health;

		combat_continues = true;
		is_player_turn = flip_coin();

		make_space(3);

		while (combat_continues)
		{
			if (is_player_turn)
			{
				make_space(2);
				read_info_bar(enemy_name, enemy_level, enemy_current_health, enemy_conditions);
				make_space(2);
				read_info_bar(player_name, player_level, player_current_health, player_conditions);
				getchar();

				//player attack selection will go here
				attack_succeeds = check_hit(player_attack, enemy_evasion);
				damage_roll = get_damage_roll(attack_succeeds, player_power);
				
				player_condition_damage = player_conditions * 2;
				enemy_condition_damage = enemy_conditions * 2;
				damage_this_turn = check_damage(damage_roll, enemy_defense, enemy_condition_damage);

				player_current_health = reduce_health(player_current_health, player_condition_damage);
				enemy_current_health = reduce_health(enemy_current_health, damage_this_turn);
				player_wins = check_win(enemy_current_health);
				enemy_wins = check_win(player_current_health);

				if (attack_succeeds)
				{
					make_space(2);
					read_combat_hit(player_name, enemy_name, damage_this_turn - enemy_condition_damage);
				}
				else
				{
					make_space(1);
					read_combat_miss(player_name, enemy_name);
				}

				getchar();

				if (player_conditions)
				{
					read_combat_conditions(player_name, player_condition_damage);
					getchar();
				}
				if (enemy_conditions)
				{
					read_combat_conditions(enemy_name, enemy_condition_damage);
					getchar();
				}
				if (player_wins && enemy_wins)
				{
					make_space(1);
					read_combat_draw(player_name, enemy_name);
					combat_continues = false;
					story_continues = false;
				}
				else
				{
					if (player_wins)
					{
						read_combat_win(player_name, enemy_name);
						combat_continues = false;
						getchar();
					}
					if (enemy_wins)
					{
						read_combat_loss(player_name, enemy_name);
						combat_continues = false;
						story_continues = false;
						getchar();
					}
				}

				is_player_turn = false;
			}
			else
			{
				make_space(2);
				read_info_bar(enemy_name, enemy_level, enemy_current_health, enemy_conditions);
				make_space(2);
				read_info_bar(player_name, player_level, player_current_health, player_conditions);
				getchar();
				make_space(2);

				//enemy attack selection will go here
				attack_succeeds = check_hit(enemy_attack, player_evasion);
				damage_roll = get_damage_roll(attack_succeeds, enemy_power);
				


				player_condition_damage = player_conditions * 2;
				enemy_condition_damage = enemy_conditions * 2;
				damage_this_turn = check_damage(damage_roll, player_defense, player_condition_damage);

				player_current_health = reduce_health(player_current_health, damage_this_turn);
				enemy_current_health = reduce_health(enemy_current_health, enemy_condition_damage);
				player_wins = check_win(enemy_current_health);
				enemy_wins = check_win(player_current_health);

				if (attack_succeeds)
				{
					read_combat_hit(enemy_name, player_name, damage_this_turn - enemy_condition_damage);
				}
				else
				{
					read_combat_miss(player_name, enemy_name);
				}

				getchar();
				
				if (enemy_conditions)
				{
					read_combat_conditions(enemy_name, enemy_condition_damage);
					getchar();
				}
				if (player_conditions)
				{
					read_combat_conditions(player_name, player_condition_damage);
					getchar();
				}
				if (player_wins && enemy_wins)
				{
					make_space(1);
					read_combat_draw(player_name, enemy_name);
					combat_continues = false;
					story_continues = false;
				}
				else
				{
					if (player_wins)
					{
						read_combat_win(player_name, enemy_name);
						combat_continues = false;
						getchar();
					}
					if (enemy_wins)
					{
						read_combat_loss(player_name, enemy_name);
						combat_continues = false;
						story_continues = false;
						getchar();
					}
				}

				is_player_turn = true;
			}
		}

		make_space(5);
		read_story_scene(story_chapter, story_stage, story_scene);
		story_scene++;
		make_space(5);
	}
}
