#ifndef LOG_H
#define LOG_H
#define GL_LOG_FILE "gl.log"

#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <string>

class Log {
    public:
          Log();
          ~Log();
	  
	  template <typename... Args>
	  void appendLog(Args... args) {

	       ((file<<args<<" "),...);
	       file<<std::endl;
	  }

          
    private:
        std::fstream file;
	
};
#endif //LOG_H
