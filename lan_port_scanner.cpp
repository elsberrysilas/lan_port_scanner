//Compile with: g++ lan_port_scanner.cpp -o lan_port_scanner -lws2_32

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
mutex cout_mutex;

void port_scan_ip(uint32_t current_ip, int ports[], int port_count)
{
    // Converts our number back into a IP address
    in_addr current_addr;
    current_addr.s_addr = htonl(current_ip);
    char ip_text[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &current_addr, ip_text, INET_ADDRSTRLEN);

    // Iterates though the ports we want to scan
    for(int i = 0; i < port_count; i++)
    {
        //Create our socket, we are using IPv4 and TCP.
        SOCKET win_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        // Check if the socket was created
        if (win_socket == INVALID_SOCKET)
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Error occured when creating the socket" << endl;
            continue;
        };

        // This struct allows us to define an IP address and port number.
        sockaddr_in target_ip;

        target_ip.sin_family = AF_INET; // IPv4
        target_ip.sin_port = htons(ports[i]); // Ports
        inet_pton(AF_INET, ip_text, &target_ip.sin_addr);

        // Connect to port on ip address
        int result = connect(win_socket, (sockaddr*)&target_ip, sizeof(target_ip));

        // Tell the user the port is open if there is a connection
        if (result != SOCKET_ERROR)
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Port " << ports[i] << " is open on " << ip_text << endl;
        };
        closesocket(win_socket);
    };
};

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    // List of ports we want to scan for
    int ports[] = {22, 80, 443, 23};
    int port_count = sizeof(ports) / 4; // Number of ports we are scanning

    string starting_ip_string;
    string ending_ip_string;

    cout << "\n\n============================" << endl;
    cout << "*** LAN Port Scanner ***" << endl;
    cout << "============================" << endl;
    cout << "WARNING: Only scan networks and devices you own or have permission to test." << endl;
    cout << "Unauthorized scanning may be illegal.\n" << endl;
    cout << "NOTE: This program may take some time to complete," << endl;
    cout << "especially when scanning large IP ranges." << endl;
    cout << "============================\n" << endl;

    // Get the users ip range they want to scan
    cout << "Enter starting IP: ";
    cin  >> starting_ip_string;
    cout << "Enter ending IP: ";
    cin  >> ending_ip_string;

    // Converts the starting ip string into a real IPv4 address
    in_addr start_addr;
    if (inet_pton(AF_INET, starting_ip_string.c_str(), &start_addr) !=1)
    {
        cout << "Invalid starting IP address" << endl;
        WSACleanup();
        return 1;
    };

    // Converts the ending ip string into a real IPv4 address
    in_addr end_addr;
    if (inet_pton(AF_INET, ending_ip_string.c_str(), &end_addr) !=1)
    {
        cout << "Invalid ending IP address" << endl;
        WSACleanup();
        return 1;
    };

    // Convert IPs to numbers we can iterate through
    uint32_t starting_ip = ntohl(start_addr.s_addr);
    uint32_t ending_ip = ntohl(end_addr.s_addr);

    // Checks to make sure we entered a valid IP range
    if (starting_ip > ending_ip)
    {
        cout << "Starting IP must be smaller or equal to the ending IP" << endl;
        WSACleanup();
        return 1;
    };

    vector<thread> threads;

    for(uint32_t current_ip = starting_ip; current_ip <= ending_ip; current_ip++)
    {
        threads.push_back(thread(port_scan_ip, current_ip, ports, port_count));
    };

    for(int j =0; j < threads.size(); j++)
    {
        threads[j].join();
    };
    WSACleanup();
    return 0;
};