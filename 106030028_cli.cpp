#include <iostream>
#include <winsock2.h>

using namespace std;

int main()
{
    WSADATA WSAData;
    SOCKET serverSock;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    //addr.sin_addr.s_addr = inet_addr("192.168.0.8"); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);

    connect(serverSock, (SOCKADDR *)&addr, sizeof(addr));
    cout << "Connected to server!" << endl;

    // cout << "--Menu--"<<endl;
    // cout << "a. Read all existing message."<<endl;
    // cout << "b. Write a new message."<<endl;
    // cout << "c. Disconnect with server."<<endl;
    // cout << "Please type a,b or c to select an option :"<<endl;

    //char buffer[1024]={'h', 'e', 'l', 'l', 'o', '.'};
    char request[1024];
    char message[10][1024]={0};
    char Menu[5][1024] = {0};
    char instruct;
    int mescnt = 0;

     for(int k=0; k<5; k++){
        recv(serverSock, Menu[k], sizeof(Menu[k]), 0);
        cout << Menu[k] <<endl;
    }


    for(int i=0; i<10; i++)
    {
        cout << "type option : ";
        cin >> instruct;
        if(instruct == 'a')
        {
            request[i] = instruct;
            send(serverSock, request, sizeof(request), 0);
            cout << "instruct to server "<< request[i] <<" sent!" << endl;
            //memset(request, 0, sizeof(request));
            cout << "All messages : "<<endl;
            for(int i=0; i<mescnt;i++){
               recv(serverSock, message[i], sizeof(message[i]), 0);
               cout << message[i] <<endl;
            }
        }
        else if(instruct == 'b')
        {
            mescnt++;
            request[i] = instruct;
            send(serverSock, request, sizeof(request), 0);
            cout << "instruct to server "<< request[i] <<" sent!" << endl;

            char writemes[1024];
            cout << "write message : ";
            cin >> writemes;
            send(serverSock, writemes, sizeof(writemes), 0);

        }
        else if(instruct == 'c')
        {
            //cout << "Message sent!" << endl;
            request[i] = instruct;
            send(serverSock, request, sizeof(request), 0);
            closesocket(serverSock);
            WSACleanup();
            cout << "Socket closed." << endl << endl;
            break;
        }
        cout<<endl;
    }
}
