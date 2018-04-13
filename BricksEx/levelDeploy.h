#pragma once

class LVDeploy {
public:
	LVDeploy();
	static void finishLevel();
	static const size_t getLevel();
private:
	static size_t level;
};