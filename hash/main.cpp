/*
Напишите программу, выполняющую взлом хэша md5 с возможностью параллельного расчета в нескольких процессах. 
Значение хэша передайте в качестве аргумента командной строки. Количество процессов дожно выбираться автоматически. 
Для расчета хеша можно исполользовать библиотеку openssl. 
Максимальный балл — 15.

F2 - fe5c3684dce76cdd9f7f4243868aa74
hgf - d187535d40b96a60387e8dff44b0c491
14 - aab3238922bcc25a6f606eb525ffdc56

*/

#include <iostream>
#include <sstream>
#include <string>
#include <future>
#include <thread>
#include <optional>
#include <vector>
#include <openssl/evp.h>
#include <openssl/md5.h>

using namespace std;


static string md5(string content) 
{
    unsigned char md_value[EVP_MAX_MD_SIZE];
    EVP_MD_CTX* mdctx = EVP_MD_CTX_create();
    unsigned int md_len;

    EVP_DigestInit(mdctx, EVP_md5());
    EVP_DigestUpdate(mdctx, content.c_str(), content.length());
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);

    std::stringstream ss;

    for (int i = 0; i < md_len; i++)
    {
        ss << std::hex << static_cast<int>(md_value[i]);
    }

    return ss.str();     
}

static string iteration_data(int i)
{
    int base = 256;

    string result;

    if (i == 0) return "0";

    while(i > 0)
    {
        char c = i % base;

        result = c + result;

        i /= base;
    }

    return result;
}

optional<string> hack(int iteration, string targetHash)
{
    optional<string> result;

    string data = iteration_data(iteration);

    if (md5(data) == targetHash)
    {
        result = data;
    }

    return result;
}



int main(int argc, char** argv)
{
    
    if (argc < 2)
    {
        cout << "Hash required!" << "\n";
        return 0;
    }

    string hash = argv[1];

    optional<string> result;

    vector<future<optional<string>>*> futures;

    int i = 0;

    while (true)
    {
        string payload1(hash);
        string payload2(hash);

        future<optional<string>> task1 = async(launch::async,
            [i, payload1]()
            {
                return hack(i, payload1);
            });

        i += 1;

        future<optional<string>> task2 = async(launch::async,
            [i, payload2]()
            {
                return hack(i, payload2);
            });

        i += 1;

        optional<string> localresult1 = task1.get();
        if (localresult1.has_value())
        {
            cout << localresult1.value() << endl;
            return 0;
        }

        optional<string> localresult2 = task2.get();
        if (localresult2.has_value())
        {
            cout << localresult2.value() << endl;
            return 0;
        }
    }

    return 0;
}