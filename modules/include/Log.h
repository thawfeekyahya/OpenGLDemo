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
          
          template <typename... Args>
          bool restart_gl_log(Args... args) {
          
	    using namespace std;

	    input_file.open(GL_LOG_FILE);

	    if (!input_file.is_open()) {
		std::cerr<<"could not open log %s for writting"<<GL_LOG_FILE<<endl;
		return false;
	    }

	    auto now = chrono::system_clock::now();
	    time_t now_time = chrono::system_clock::to_time_t(now);

	    tm local_time = *localtime(&now_time);

	    input_file << "Local time at -> "<<put_time(&local_time,"%Y-%m-%d %H:%M:%S")<<endl;
	    
	    ((input_file<<args<<" "),...);
	    
	    input_file<<"\n";
	    
	    input_file.close();
	    
	    return true;
	  }
	  
	  template <typename... Args>
	  void appendLog(Args... args) {
	       ouput_file.open(GL_LOG_FILE);
	       
	       if(!ouput_file.is_open()) {
	       	  std::cerr<<"could not open the file "<<GL_LOG_FILE<<std::endl;
	       }
	       
	       std::string str,tmp;
	       //while(getline(ouput_file,tmp)) {
	       //	    str += tmp;
	       //}
	       str += "\n";
	       
	       ouput_file.close();
	       
	       input_file.open(GL_LOG_FILE);
	       ((input_file<<str<<args<<" "),...);
	       input_file.close();
	       
	  }

          
    private:
        std::ofstream input_file;
        std::ifstream ouput_file;
	
};
#endif //LOG_H
