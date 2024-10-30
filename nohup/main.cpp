/*
Напишите программу, запускающую другую программу и отвязывающую ее от управляющего терминала (аналог nohup).
Ввод-вывод запускаемой программы должен быть перенаправлен в /dev/null
Максимальный балл - 5.
*/

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

void nohup(const char* path, char ** args )
{
    pid_t pid = fork();

    if (pid < 0) {
        exit(1);
    } else if (pid > 0) {
        exit(0);
    }

    if (setsid() < 0) { 
        exit(1);
    }

    int dev_null = open("/dev/null", O_RDWR);
    
    dup2(dev_null, STDIN_FILENO);
    dup2(dev_null, STDOUT_FILENO);
    dup2(dev_null, STDERR_FILENO);

    close(dev_null);

    execvp(path, args);
}

int main(int argc, char** argv) 
{
    if(argc < 2)
    {
        cout << "Program required!" << "\n";
        return 0;
    }

    nohup(argv[1], &argv[1]);

    return 0;
}
