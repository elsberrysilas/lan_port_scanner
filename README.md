# C++ LAN Port Scanner (Windows)

## Description
This project is a multithreaded LAN port scanner written in C++. It allows the user to input a starting and ending IP address, then scans each host in that range to detect open ports.
I built this project to better understand network programming and learn how port scanners work from a programing perspective.

## Technologies Used
- C++
- Standard C++ Libraries
- Winsock2 (Windows Sockets API)
- Multithreading

## How to Run
### 1. Clone the repository
```bash
git clone https://github.com/elsberrysilas/lan_port_scanner.git
```
### 2. Compile
```bash
g++ lan_port_scanner.cpp -o lan_prot_scanner -lws2_32
```
### 3. Run
```bash
./lan_port_scanner
```
### 4. Enter IP range
```bash
Enter starting IP: 192.168.1.1
Enter ending IP: 192.168.1.20
```
## Demo
```bash
PS M:\VsCode\C++> g++ lan_port_scanner.cpp -o lan_port_scanner -lws2_32
PS M:\VsCode\C++> ./lan_port_scanner


============================
*** LAN Port Scanner ***
============================
WARNING: Only scan networks and devices you own or have permission to test.
Unauthorized scanning may be illegal.

NOTE: This program may take some time to complete,
especially when scanning large IP ranges.
============================

Enter starting IP: 192.168.88.1
Enter ending IP: 192.168.88.20

Scanning IPs 192.168.88.1-192.168.88.20

Port 22 is open on 192.168.88.5
Port 80 is open on 192.168.88.5
Port 443 is open on 192.168.88.5
Port 22 is open on 192.168.88.1
Port 23 is open on 192.168.88.5
Port 80 is open on 192.168.88.1
Port 443 is open on 192.168.88.1
Port 23 is open on 192.168.88.1
Port 443 is open on 192.168.88.16
PS M:\VsCode\C++> 
```
## What I learned
- How to use sockets in C++ with Winsock
- How TCP connections work
- How TCP connections work at a low level
- Implementing multithreading

## Future Improvements
- Add support for scanning user-defined ports
- Improve output formatting
- Add a scan progress indicator
- Add timeout handling to prevent long delays on unresponsive hosts
