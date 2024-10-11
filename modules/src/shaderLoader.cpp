#include <string>
#include <iostream>
#include <fstream>

#include "shaderLoader.h"

using namespace std;

ShaderLoader::ShaderLoader(const string& mFilePath): mFilePath(mFilePath) {
    
    loadFile();
}


string& ShaderLoader::loadFile() {
   fstream file;
   string line;

   file.open(mFilePath,ios::in);
	   
   mData.clear();


   if (file.is_open()) {

      while (getline(file,line)) {
	 mData.append(line).append("\n");
      }

   } else {
       cerr<<"Unable to file for reading";
   }


   return mData;
}


string& ShaderLoader::getData() {
   return mData;
}

string& ShaderLoader::getFilePath() {
    return mFilePath;
}


void ShaderLoader::clear() {
   mData.clear();
   mFilePath.clear();
}

void ShaderLoader::setFilePath(const string& filePath) {
    mFilePath = filePath;
    loadFile();
}
