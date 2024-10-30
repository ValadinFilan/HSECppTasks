/*
Напишите программу, запускающую другую программу, переданную ей в качестве аргумента.
Стандартный вывод запускаемой программы должен быть перенаправлен в файл out.txt, стандартный поток ошибок - в файл err.txt. 
Файлы должны создаваться в текущем рабочем каталоге.
Максимальный балл - 5.
*/

#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv) 
{
    if(argc < 2)
    {
        cout << "Program required!" << "\n";
        return 0;
    }
    
    freopen("out.txt","w",stdout);
    freopen("err.txt","w",stderr);

    execvp(argv[1], &argv[1]);

    return 0;
}