#include <iostream>
#include <winsock2.h>

using namespace std;

int main()
{

    WSADATA WSAData;
    SOCKET serverSock, clientSock;
    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);

    bind(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

    listen(serverSock, 0);

    char message[10][1024] = {0};
    char request[1024];
    char Menu[5][1024] = {
        {'-','-','M','e','n','u','-','-'},
        {'a','.',' ','R','e','a','d',' ','a','l','l',' ','e','x','i','s','t','i','n','g',' ','m','e','s','s','a','g','e'},
        {'b','.',' ','W','r','i','t','e',' ','a',' ','n','e','w',' ','m','e','s','s','a','g','e'},
        {'c','.',' ','D','i','s','c','o','n','n','e','c','t',' ','w','i','t','h',' ','s','e','r','v','e','r'},
        {'P','l','e','a','s','e',' ','t','y','p','e',' ','a',',','b',' ','o','r',' ','c',' ','t','o',' ','s','e','l','e','c','t',' ','a','n',' ','o','p','t','i','o','n',' ',':'}
    };
    int clientAddrSize = sizeof(clientAddr);
    int mescnt = 0;//count how many times client request the server
    cout << "Listening for incoming connections..." << endl;

    if((clientSock = accept(serverSock, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {
        cout << "Client connected!" << endl;

        for(int k=0; k<5; k++){
             send(clientSock, Menu[k], sizeof(Menu[k]), 0);
             //cout << Menu[k] <<endl;
        }

        for(int i=0; i<10; i++)
        {
            recv(clientSock, request, sizeof(request), 0);

            //memset(request, 0, sizeof(request));
            if(request[i] == 'a')
            {
                cout << "request is : " << request[i] <<endl;
                //cout << "All messages: "<<endl;
                for(int j=0; j<mescnt; j++)
                {
                    send(clientSock, message[j], sizeof(message[j]), 0);
                    //cout << message[j] <<endl;
                }
                //memset(request, 0, sizeof(request));
            }
            else if(request[i] == 'b')
            {
                //cout<< " value : "<<mescnt<<endl;
                cout << "request is : " << request[i] << endl;
                recv(clientSock, message[mescnt], sizeof(message[mescnt]), 0);
                cout << "Writen message : " << message[mescnt] << endl;
                mescnt++;
                //memset(message, 0, sizeof(message));
                //memset(request, 0, sizeof(request));
            }
            else if(request[i] == 'c')
            {
                cout << "request is : " << request[i] << endl;
                memset(request, 0, sizeof(request));
                memset(message, 0, sizeof(message));
                closesocket(clientSock);
                cout << "Client disconnected." << endl;
                break;
            }

            //cout<<i<<endl;
        }
    }

}
