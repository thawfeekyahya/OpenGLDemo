#include "Log.h"

#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <iostream>


Log::Log() {
    using namespace std;

    file.open(GL_LOG_FILE);

    if (!file.is_open()) {
	std::cerr<<"could not open log %s for writting"<<GL_LOG_FILE<<endl;
    } else {
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	tm local_time = *localtime(&now_time);
	
        file << "Local time at -> "<<put_time(&local_time,"%Y-%m-%d %H:%M:%S")<<endl;
    }
    
    //file.close();
}


Log::~Log() {
    file.close();
}




