#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H


#include <string>

using namespace std;

class ShaderLoader {
    public:
      ShaderLoader(const string& filePath="");
      ~ShaderLoader() = default;
      
      string& getData();
      string& getFilePath();

      string& loadFile();

      void clear();
      void setFilePath(const string& filePath);

    private:
      	string mFilePath;
	string mData;
};


#endif //SHADER_LOADER_H

