/*
Author: Jiahao Sun
Class: ECE 6122 QSZ
Last Modified Date: 11/20/2022

Discription:
 This is a console program that takes as a single command line argument the port number on
 which the TCP Server will listen for connection requests.
 The clients will be sending text string messages that the server will save in a file called server.log in the same directory as the
 server application.
*/
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// header file
#include "inputCheck.h"

int main(int argc, char* argv[])
{
    // initialize some veriables
    unsigned long port = 61000;
    const char *weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thurs", "Fri", "Sat"};
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
    
    if (argc != 2)
        {
            // if the argument is less than 2, it is invalid
            printf("Invalid command line argument detected: %s %s %s \n", argv[0], argv[1], argv[2]);
            printf("Please check your values and press any key to end the program! \n");
            std::cin.ignore(10000, '\n');
            return 0;
        }
    else
    {
        if (inputCheck(argv[1], port))
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
    
    // Create a server socket to accept new connections
    sf::TcpListener listener;
    listener.listen(port);
    // Create a list to store the future clients
    std::list<sf::TcpSocket*> clients;
    // Create a selector
    sf::SocketSelector selector;
    // Add the listener to the selector
    selector.add(listener);
    
    // Listen to the given port for incoming connections
    if (listener.listen(port) != sf::Socket::Done)
    {
        // Listen to the given port for incoming connections
        return 1;
    }
    //std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;
    
    // Create a socket to listen to new connections
    sf::TcpSocket socket;
    
    // Create a file
    fstream myFile;

    while (1)
    {
        // Make the selector wait for data on any socket
        if (selector.wait())
        {
            // Test the listener
            if (selector.isReady(listener))
            {
                // The listener is ready: there is a pending connection
                sf::TcpSocket* client = new sf::TcpSocket;
                
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    // Add the new client to the clients list
                    clients.push_back(client);
                    // Add the new client to the selector so that we will
                    // be notified when he sends something
                    selector.add(*client);
                    
                    //std::cout << "Client connected: " << client->getRemotePort() << std::endl;
                    
                    time_t now = time(0);
                    tm *ltm = localtime(&now);
                    
                    myFile.open("server.log", ios::app);
                    myFile << weekDays[ltm->tm_wday] << " ";
                    myFile << months[1 + ltm->tm_mon] << " ";
                    myFile << ltm->tm_mday << " ";
                    myFile << ltm->tm_hour << ":";
                    myFile << ltm->tm_min << ":";
                    if (ltm->tm_sec < 10)
                    {
                        // if second is less than 10, add a 0 infront of it
                        myFile << "0" << ltm->tm_sec << " ";
                    }
                    else
                    {
                        // if second is greater than 10, just send it
                        myFile << ltm->tm_sec << " ";
                    }
                    myFile << 1900 + ltm->tm_year << " ";
                    myFile << " :: ";
                    myFile << client->getRemoteAddress();
                    myFile << " :: ";
                    myFile << "Connected" << "\n";
                    myFile.close();
                }
                else
                {
                    // Error, we won't get a new connection, delete the socket
                    delete client;
                }
            }
            else
            {
                // The listener socket is not ready, test all other sockets (the clients)
                int quit = 0;
                for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket& client = **it;
                    // Receive a message back from the client
                    char in[128];
                    std::size_t received;
                    if (selector.isReady(client) && (client.receive(in, sizeof(in), received) == sf::Socket::Done))
                    {
                        // The client has sent some data, we can receive it
                        sf::Packet packet;
                        unsigned long oldPort = 0;
                        unsigned long newPort = client.getRemotePort();
                            
                        do
                        {
                            // Receive a message back from the client
                            oldPort = newPort;
                            
                            string strIn(in);
                            
                            if (strIn != "quit")
                            {
                                // if not detect a "quit"
                                time_t now = time(0);
                                tm *ltm = localtime(&now);
                                
                                myFile.open("server.log", ios::app);
                                myFile << weekDays[ltm->tm_wday] << " ";
                                myFile << months[1 + ltm->tm_mon] << " ";
                                myFile << ltm->tm_mday << " ";
                                myFile << ltm->tm_hour << ":";
                                myFile << ltm->tm_min << ":";
                                if (ltm->tm_sec < 10)
                                {
                                    // if second is less than 10, add a 0 infront of it
                                    myFile << "0" << ltm->tm_sec << " ";
                                }
                                else
                                {
                                    // if second is greater than 10, just send it
                                    myFile << ltm->tm_sec << " ";
                                }
                                myFile << 1900 + ltm->tm_year << " ";
                                myFile << " :: ";
                                myFile << client.getRemoteAddress();
                                myFile << " :: ";
                                myFile << in << "\n";
                                myFile.close();
                            }
                            else if (strIn == "quit")
                            {
                                // if detect a "quit"
                                quit = 1;
                                
                                time_t now = time(0);
                                tm *ltm = localtime(&now);
                                
                                myFile.open("server.log", ios::app);
                                myFile << weekDays[ltm->tm_wday] << " ";
                                myFile << months[1 + ltm->tm_mon] << " ";
                                myFile << ltm->tm_mday << " ";
                                myFile << ltm->tm_hour << ":";
                                myFile << ltm->tm_min << ":";
                                if (ltm->tm_sec < 10)
                                {
                                    // if second is less than 10, add a 0 infront of it
                                    myFile << "0" << ltm->tm_sec << " ";
                                }
                                else
                                {
                                    // if second is greater than 10, just send it
                                    myFile << ltm->tm_sec << " ";
                                }
                                myFile << 1900 + ltm->tm_year << " ";
                                myFile << " :: ";
                                myFile << client.getRemoteAddress();
                                myFile << " :: ";
                                myFile << "Disconnected" << "\n";
                                myFile.close();
                            }
                        } while(!quit && (oldPort != newPort));
                    }
                }
            }
        }
    }
}




