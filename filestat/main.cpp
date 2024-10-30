/*
filestat. Напишите программу, выводящую в стандартный поток вывода информацию о количестве файлов каждого типа в текущей директории. Максимальный балл - 5.
*/

#include <iostream>
#include <dirent.h>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<int, string> stringMapping;

    stringMapping[DT_REG] = "File";
    stringMapping[DT_DIR] = "Directory";
    stringMapping[DT_LNK] = "Symbol link";
    stringMapping[DT_SOCK] = "Socket";
    stringMapping[DT_WHT] = "Link";
    stringMapping[DT_FIFO] = "Pipeline";
    stringMapping[DT_CHR] = "Character Equipment";
    stringMapping[DT_BLK] = "Block device";

    map<int, int> result;

    for(auto it : stringMapping) result[it.first] = 0;
    
    DIR* CurrentDir = opendir(".");

    while (dirent* file = readdir(CurrentDir))
    {
        result[file->d_type]++;
    }

    for(auto itResult : result) 
    {
        if(itResult.second > 0) cout << stringMapping[itResult.first] << ": " << itResult.second << "\n";
    }
  
}