#include<iostream>
#include<string>
#include<unistd.h>
#include<vector>

using namespace std;

int main(){
    string cmdArgv;
    int run = 1;
    while(run){
        cout<<"osh>";
        cin>>cmdArgv;
        if(cmdArgv == "exit"){
            run = 0;
        }
    }
    return 0;
}