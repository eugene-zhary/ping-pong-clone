#include "game_options.h"

void setSoundVolume(int vol) {

	if (vol >= 0 && vol <= 100) {
		std::ifstream ifs(CONFIG_VOLUME);

		std::string str;
		std::vector<std::string> vec;

		for (int i = 0; i < 2; i++) {
			ifs >> str;
			if (str == "") {
				str.assign("0");
			}
			vec.push_back(str);
			str.clear();
		}

		ifs.clear();
		ifs.close();

		vec.at(0).assign(std::to_string(vol));

		std::ofstream ofs(CONFIG_VOLUME);


		ofs << vec.at(0) << "\n";
		ofs << vec.at(1) << "\n";

		ofs.clear();
		ofs.close();
		vec.clear();
	}
}

void setMusicVolume(int vol) {

	if (vol >= 0 && vol <= 100) {
		std::ifstream ifs(CONFIG_VOLUME);

		std::string str;
		std::vector<std::string> vec;

		for (int i = 0; i < 2; i++) {
			ifs >> str;
			if (str == "") {
				str.assign("0");
			}
			vec.push_back(str);
			str.clear();
		}

		ifs.clear();
		ifs.close();

		vec.at(1).assign(std::to_string(vol));

		std::ofstream ofs(CONFIG_VOLUME);

		ofs << vec.at(0) << "\n";
		ofs << vec.at(1) << "\n";

		ofs.clear();
		ofs.close();

		vec.clear();
	}
}

int getSoundVolume() {
	std::ifstream ifs(CONFIG_VOLUME);

	std::string str;
	ifs >> str;

	ifs.clear();
	ifs.close();

	int val = std::atoi(str.c_str());
	if (val != NULL)
		return val;
	else
		return 0;
}

int getMusicVolume() {
	std::ifstream ifs(CONFIG_VOLUME);

	std::string str;

	ifs >> str;
	str.clear();
	ifs >> str;

	ifs.clear();
	ifs.close();

	int val = std::atoi(str.c_str());

	if (val != NULL)
		return val;
	else
		return 0;
}

void setControl(bool control)
{
	std::ofstream ofs(CONFIG_CONTROL);
	ofs << std::to_string(control);

	ofs.clear();
	ofs.close();
}

bool getControl()
{
	std::ifstream ifs(CONFIG_CONTROL);

	std::string str;
	ifs >> str;

	ifs.clear();
	ifs.close();

	int val = std::atoi(str.c_str());

	return val;
}

void setScorePlayer(int score) {
	if (score >= 0 && score <= 5) {
		std::ifstream ifs(CONFIG_SCORE);

		std::string str;
		std::vector<std::string> vec;

		for (int i = 0; i < 2; i++) {
			ifs >> str;
			if (str == "") {
				str.assign("0");
			}
			vec.push_back(str);
			str.clear();
		}

		ifs.clear();
		ifs.close();

		vec.at(0).assign(std::to_string(score));

		std::ofstream ofs(CONFIG_SCORE);


		ofs << vec.at(0) << "\n";
		ofs << vec.at(1) << "\n";

		ofs.clear();
		ofs.close();
		vec.clear();
	}
}

void setScoreBot(int score) {
	if (score >= 0 && score <= 5) {
		std::ifstream ifs(CONFIG_SCORE);

		std::string str;
		std::vector<std::string> vec;

		for (int i = 0; i < 2; i++) {
			ifs >> str;
			if (str == "") {
				str.assign("0");
			}
			vec.push_back(str);
			str.clear();
		}

		ifs.clear();
		ifs.close();

		vec.at(1).assign(std::to_string(score));

		std::ofstream ofs(CONFIG_SCORE);


		ofs << vec.at(0) << "\n";
		ofs << vec.at(1) << "\n";

		ofs.clear();
		ofs.close();
		vec.clear();
	}
}

int getScorePlayer() {
	std::ifstream ifs(CONFIG_SCORE);

	std::string str;
	ifs >> str;

	ifs.clear();
	ifs.close();

	int val = std::atoi(str.c_str());
	if (val != NULL)
		return val;
	else
		return 0;
}

int getScoreBot() {
	std::ifstream ifs(CONFIG_SCORE);

	std::string str;

	ifs >> str;
	str.clear();
	ifs >> str;

	ifs.clear();
	ifs.close();

	int val = std::atoi(str.c_str());

	if (val != NULL)
		return val;
	else
		return 0;
}

void setTypeGame(bool game)
{
	std::ofstream ofs(CONFIG_GAME);
	ofs << std::to_string(game);

	ofs.clear();
	ofs.close();
}

bool getTypeGame()
{
	std::ifstream ifs(CONFIG_GAME);

	std::string str;
	ifs >> str;

	ifs.clear();
	ifs.close();

	int val = std::atoi(str.c_str());

	return val;
}
