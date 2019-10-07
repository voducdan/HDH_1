#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <stdio.h>
using namespace std;

string const SEPERATOR = " ";
vector<string> historyCmd;

vector<string> split(string str)
{
    vector<string> tokens;
    int findPos;
    string tempStr = str;
    while (tempStr.find(SEPERATOR) != -1)
    {
        findPos = tempStr.find(SEPERATOR);
        tokens.push_back(tempStr.substr(0, findPos));
        tempStr = tempStr.substr(findPos + 1, tempStr.length());
    }
    tokens.push_back(tempStr);
    return tokens;
}
vector<string> findstr(vector<string> cmd, string str)
{
    vector<string> result;
    for (int i = 0; i < cmd.size(); i++)
    {
        if (cmd[i].find(str) != -1)
        {
            result.push_back(to_string(i) + "   " + cmd[i]);
        }
    }
    return result;
}
int isNumber(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]) == false)
        {
            return 0;
        }
    }
    return 1;
}

void historyFeature(string cmd)
{
    vector<string> splitedCmd = split(cmd);
    if (splitedCmd[0] == "history" && splitedCmd.size() == 1)
    {
        if (historyCmd.size() == 0)
        {
            cout << "No commands in history" << endl;
            historyCmd.push_back(cmd);
            return;
        }
        else
        {
            historyCmd.push_back(cmd);
            for (int i = 0; i < historyCmd.size(); i++)
            {
                cout << i + 1 << "   " << historyCmd[i] << endl;
            }
            return;
        }
    }
    if (splitedCmd[0] == "history" && splitedCmd[1] == "|")
    {
        if (splitedCmd[2] == "grep")
        {
            if (splitedCmd.size() == 3)
            {
                cout << "Usage: grep [OPTION]... PATTERN [FILE]..." << endl;
                historyCmd.push_back(cmd);
                return;
            }
            vector<string> result = findstr(historyCmd, splitedCmd[3]);
            for (int i = 0; i < result.size(); i++)
            {
                cout << result[i] << endl;
            }
            historyCmd.push_back(cmd);
            return;
        }
        if (splitedCmd[2] == "tail")
        {
            if (splitedCmd.size() == 3)
            {
                int count = 0;
                for (int i = historyCmd.size() - 1; i >= 0; i--)
                {
                    if (count < 10)
                    {
                        cout << historyCmd.size() - i << "   " << historyCmd[i] << endl;
                        count++;
                    }
                    else
                    {
                        break;
                    }
                }
                historyCmd.push_back(cmd);
                return;
            }
            if (splitedCmd[3] == "-n" && splitedCmd.size() == 4)
            {
                cout << "tail: option requires an argument -- 'n'" << endl;
                cout << "Try 'tail --help' for more information." << endl;
                historyCmd.push_back(cmd);
                return;
            }
            int count = 0;
            for (int i = historyCmd.size() - 1; i >= 0; i--)
            {
                if (count < atoi(splitedCmd[4].c_str()))
                {
                    cout << i << "   " << historyCmd[i] << endl;
                    count++;
                }
                else
                {
                    break;
                }
            }
            historyCmd.push_back(cmd);
            return;
        }
        else
        {
            historyCmd.push_back(cmd);
            return;
        }
    }
    if (splitedCmd[0] == "!!")
    {
        system(historyCmd[historyCmd.size() - 1].c_str());
        historyCmd.push_back("history");
        historyCmd.push_back(historyCmd[historyCmd.size() - 1]);
        return;
    }
    string temp = splitedCmd[0].substr(1, splitedCmd[0].length());
    if (isNumber(temp) == 1)
    {
        if (splitedCmd.size() == 1 && atoi(temp.c_str()) >= 0 && atoi(temp.c_str()) < historyCmd.size())
        {
            system(historyCmd[atoi(temp.c_str())].c_str());
            historyCmd.push_back(cmd);
            return;
        }
        system(cmd.c_str());
        historyCmd.push_back(cmd);
        return;
    }
    historyCmd.push_back(cmd);
}

int main()
{
    string cmdArgv;
    int run = 1;
    while (run)
    {
        cout << "osh>";
        getline(cin, cmdArgv);
        if (cmdArgv == "exit")
        {
            run = 0;
        }
        historyFeature(cmdArgv);
    }
    return 0;
}