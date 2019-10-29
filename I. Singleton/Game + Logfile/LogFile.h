#pragma once
#include <fstream>

class LogSingleton;

class LogDestroyer {
	LogSingleton *p_instance;
public:
	void initialize(LogSingleton* p) { p_instance = p; }
	~LogDestroyer();
};

class LogSingleton {
	static LogSingleton *p_instance;
	static LogDestroyer destroyer;
protected:
	LogSingleton() { Logfile << "Start of new game: " << std::endl; }

	LogSingleton(const LogSingleton&) = delete;
	LogSingleton &operator=(LogSingleton&) = delete;

	~LogSingleton() {
		Logfile << "End of game " << std::endl;
		Logfile << "==========================" << std::endl;
		Logfile.close();
	}
public:
	static std::ofstream Logfile;

	static LogSingleton &getInstance() {
		if (!p_instance) {
			p_instance = new LogSingleton();
			destroyer.initialize(p_instance);
		}
		return *p_instance;
	}

	friend class LogDestroyer;
};

std::ofstream LogSingleton::Logfile("Logfile.txt", std::ios::app);
LogSingleton *LogSingleton::p_instance = nullptr;
LogDestroyer LogSingleton::destroyer;

LogDestroyer::~LogDestroyer() {
	delete p_instance;
}