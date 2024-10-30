/*
hide. Напишите программу, скрывающую файл, заданный в качестве аргумента, в "темном" каталоге. Имя файла передайте с помощью аргументов командной строки
Имя каталога - фиксированное. Максимальный балл - 5.
*/

#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <format>

using namespace std;

const string HIDE_DIR_NAME = "hide";  

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "Filename required!" << "\n";
        return 0;
    }

    string filename = argv[1];
    mkdir(HIDE_DIR_NAME.c_str(), 0311);
    rename(filename.c_str(), (HIDE_DIR_NAME + "/" + filename).c_str());
}