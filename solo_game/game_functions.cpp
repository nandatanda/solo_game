#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <limits>
#include <fstream>
#include "game_functions.h"

int roll_die(int die_sides)
{
	int die_result = rand() % die_sides + 1;
	return die_result;
}
bool check_hit(int attack, int evasion)
{
	bool hit_result;
	int attack_roll = (roll_die(100) + attack);
	(attack_roll > evasion) ? hit_result = true : hit_result = false;
	return hit_result;
}
bool check_win(int health)
{
	bool win_occurs;
	if (health <= 0)
	{
		win_occurs = true;
	}
	else
	{
		win_occurs = false;
	}
	return win_occurs;
}
bool flip_coin(void)
{
	bool coin_result;
	if (roll_die(2) == 1)
	{
		coin_result = true;
	}
	else
	{
		coin_result = false;
	}
	return coin_result;
}
std::string get_player_name(void)
{
	std::string player_name;
	std::cout << "-  What is your name, brave adventurer?\n\n>  ";
	std::cin >> player_name;
	return player_name;
}
int check_damage(int damage, int defense, int condition_damage)
{
	int damage_result = (damage / defense) + condition_damage;
	return damage_result;
}
int reduce_health(int health, int damage)
{
	int health_result = health - damage;
	return health_result;
}
int get_damage_roll(bool attsck_succeeds, int power)
{
	int damage_roll;
	(attsck_succeeds)
		? damage_roll = 5 * (roll_die(100) + power)
		: damage_roll = 0;
	return damage_roll;
}
std::string get_player_profession(void)
{
	int player_profession_selection = 0;
	std::string player_profession;
	std::cout << "-  Which profession strikes your fancy?\n\n1) Warrior\n2) Rogue\n3) Mage\n\n>  ";
	std::cin >> player_profession_selection;
	while (!std::cin >> player_profession_selection || player_profession_selection < 1 || player_profession_selection > 4)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\n>  ";
		std::cin >> player_profession_selection;
	}

	switch (player_profession_selection)
	{
	case 1: player_profession = "warrior";
		break;
	case 2: player_profession = "rogue";
		break;
	case 3: player_profession = "mage";
		break;
	}
	return player_profession;
}
std::string get_story(int line_number)
{
	std::string line_contents;
	std::ifstream game_story;

	game_story.open("game_story.txt");
	if (game_story.is_open())
	{
		for (int i = 0; i < line_number; i++)
		{
			std::getline(game_story, line_contents);
		}
		game_story.close();
		return line_contents;
	}
	else
	{
		std::cout << "-  Please check if all files are included in game drectory.";
		return "File not found.";
	}
}
std::string make_space(int number_of_lines)
{
	std::string divider;
	for (int i = 0; i < number_of_lines; i++)
	{
		std::cout << "\n";
	}
	return divider;
}
void read_info_bar(std::string name, int level, int health, int conditions)
{
	std::cout << "-  [" << name << " | " << level << "]\n\t\t\t\t" << health << "  |  " << conditions;
}
void read_story_lines(int starting_line, int ending_line)
{
	for (int i = starting_line; i < ending_line + 1; i++)
	{
		(ending_line - starting_line == 0 || i == ending_line)
			? std::cout << get_story(i)
			: std::cout << get_story(i) << "\n";
	}
	getchar();
}
void read_story_scene(int chapter, int stage, int scene)
{
	if (chapter == 1)
	{
		if (stage == 1)
		{
			if (scene == 1)
			{
				read_story_lines(1, 1);
				getchar();
				make_space(1);
				read_story_lines(3, 5);
				make_space(1);
				read_story_lines(7, 7);
				make_space(1);
				read_story_lines(9, 9);
			}
			if (scene == 2)
			{
				read_story_lines(11, 12);
			}
		}
		if (stage == 2)
		{
			if (scene == 1)
			{
				read_story_lines(14, 14);
			}
		}

	}
}
void read_combat_hit(std::string attacker_name, std::string defender_name, int damage)
{
	std::cout << "-  " << attacker_name << " hit " << defender_name << " for " << (damage) << " damage.";
}
void read_combat_miss(std::string attacker_name, std::string defender_name)
{
	std::cout << "-  " << attacker_name << " missed " << defender_name << ", dealing no damage.";
}
void read_combat_conditions(std::string name, int damage)
{
	std::cout << "   " << name << " took " << damage << " damage from status effects.";
}
void read_combat_draw(std::string player_name, std::string enemy_name)
{
	std::cout << "-  In a twist of fate, " << player_name << " and " << enemy_name << " have slain one another! With this, the quest is no more.";
}
void read_combat_win(std::string player_name, std::string enemy_name)
{
	std::cout << "\n-  " << player_name << " has slain " << enemy_name << "!";
}
void read_combat_loss(std::string player_name, std::string enemy_name)
{
	std::cout << "\n- " << player_name << " has been slain by " << enemy_name << "!";
}
int get_evasion(std::string profession, int level)
{
	int evasion_result = 0;
	if (profession == "warrior")
	{
		evasion_result = 10 + (2 * level);
	}
	else if (profession == "mage")
	{
		evasion_result = 10 + (1 * level);
	}
	else if (profession == "rogue")
	{
		evasion_result = 10 + (4 * level);
	}
	else if (profession == "goblin")
	{
		evasion_result = 10 + (3 * (level / 2));
	}
	return evasion_result;
}
int get_attack(std::string profession, int level)
{
	int attack_result = 0;
	if (profession == "warrior")
	{
		attack_result = 10 + (2 * level);
	}
	else if (profession == "mage")
	{
		attack_result = 10 + (3 * level);
	}
	else if (profession == "rogue")
	{
		attack_result = 10 + (4 * level);
	}
	else if (profession == "goblin")
	{
		attack_result = 10 + (3 * (level / 2));
	}
	return attack_result;
}
int get_maximum_health(std::string profession, int level)
{
	int get_maximum_health = 0;
	if (profession == "warrior")
	{
		get_maximum_health = 10 + (4 * level);
	}
	else if (profession == "mage")
	{
		get_maximum_health = 10 + (2 * level);
	}
	else if (profession == "rogue")
	{
		get_maximum_health = 10 + (3 * level);
	}
	else if (profession == "goblin")
	{
		get_maximum_health = 10 + (3 * (level / 2));
	}
	return get_maximum_health;
}
int get_defense(std::string profession, int level)
{
	int get_player_defense = 0;
	if (profession == "warrior")
	{
		get_player_defense = 10 + (4 * level);
	}
	else if (profession == "mage")
	{
		get_player_defense = 10 + (2 * level);
	}
	else if (profession == "rogue")
	{
		get_player_defense = 10 + (1 * level);
	}
	else if (profession == "goblin")
	{
		get_player_defense = 10 + (3 * (level / 2));
	}
	return get_player_defense;
}
int get_power(std::string profession, int level)
{
	int get_power = 0;
	if (profession == "warrior")
	{
		get_power = 10 + (2 * level);
	}
	else if (profession == "mage")
	{
		get_power = 10 + (4 * level);
	}
	else if (profession == "rogue")
	{
		get_power = 10 + (1 * level);
	}
	else if (profession == "goblin")
	{
		get_power = 10 + (3 * (level / 2));
	}
	return get_power;
}