#include "com.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
namespace tools {
    //ִ�������в���������stdout
    string exec(const string cmd) {
        char buffer[128];
        std::string result = "";
        std::shared_ptr<FILE> pipe(_popen(cmd.c_str(), "r"), _pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())) {
            if (fgets(buffer, 128, pipe.get()) != NULL)
                result += buffer;
        }
        return result;
    }
    vector<string> split(const string &s, const string &seperator) {
        vector<string> result;
        typedef string::size_type string_size;
        string_size i = 0;

        while (i != s.size()) {
            //�ҵ��ַ������׸������ڷָ�������ĸ��
            int flag = 0;
            while (i != s.size() && flag == 0) {
                flag = 1;
                for (string_size x = 0; x < seperator.size(); ++x)
                    if (s[i] == seperator[x]) {
                        ++i;
                        flag = 0;
                        break;
                    }
            }

            //�ҵ���һ���ָ������������ָ���֮����ַ���ȡ����
            flag = 0;
            string_size j = i;
            while (j != s.size() && flag == 0) {
                for (string_size x = 0; x < seperator.size(); ++x)
                    if (s[j] == seperator[x]) {
                        flag = 1;
                        break;
                    }
                if (flag == 0)
                    ++j;
            }
            if (i != j) {
                result.push_back(s.substr(i, j - i));
                i = j;
            }
        }
        return result;
    }
}