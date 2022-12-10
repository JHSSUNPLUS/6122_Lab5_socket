/*
Author: Jiahao Sun
Class: ECE 6122 QSZ
Last Modified Date: 11/20/2022

Discription:
 This is a client console program that takes as a command line argument the IP
 Address and port number of the server as shown below:
 ./a.out localhost 61717
*/
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

using namespace std;

// header file
#include "inputCheck.h"

int main(int argc, char* argv[])
{
    // initialize variable
    unsigned long port = 61000;
    
    if (argc != 3)
        {
            // if the argument is less than 2, it is invalid
            printf("Invalid command line argument detected: %s %s %s \n", argv[0], argv[1], argv[2]);
            printf("Please check your values and press any key to end the program! \n");
            std::cin.ignore(10000, '\n');
            return 0;
        }
    else
    {
        if (inputCheck(argv[2], port))
        {
            // if the input condition check pass
        }
        else
        {
            // if the input condition check fail, it is invalid
            printf("Invalid command line argument detected: %s %s %s \n", argv[0], argv[1], argv[2]);
            printf("Please check your values and press any key to end the program! \n");
            std::cin.ignore(10000, '\n');
            return 0;
        }
    }
    
    string strAddress(argv[1]);

    // Ask for the server address
    sf::IpAddress server;
    server = strAddress;

    // Create a socket for communicating with the server
    sf::TcpSocket socket;
    char text[128];

    // Connect to the server
    if (socket.connect(server, port) != sf::Socket::Done)
    {
        printf("Failed to connect to the server at %s on %s. \n", argv[1], argv[2]);
        printf("Please check your values and press any key to end program! \n");
        std::cin.ignore(10000, '\n');
        return 0;
    }
    
    sf::Packet packet;
    //std::cout << "Connected to server " << server << std::endl;

    bool quit = 0;
    
    do
    {
        // send message,
        // quit if enter "quit"
        cout << "Please enter a message:";
        cin.getline(text, 128);
        
        string strText(text);
        if (strText == "quit")
        {
            // if detect a "quit", set quit
            quit = 1;
        }
        socket.send(text, 128);
    } while(!quit);
    socket.disconnect();
}
