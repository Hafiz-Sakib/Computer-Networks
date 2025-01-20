#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Convert an integer to dotted decimal format
string intToIP(unsigned long ip)
{
    return to_string((ip >> 24) & 0xFF) + "." +
           to_string((ip >> 16) & 0xFF) + "." +
           to_string((ip >> 8) & 0xFF) + "." +
           to_string(ip & 0xFF);
}

// Perform subnet calculations and display results
void calculateSubnets(unsigned long baseIP, int originalMask, int newMask, int numSubnets)
{
    // Calculate subnet size and mask
    unsigned long subnetSize = 1UL << (32 - newMask); // IPs per subnet
    unsigned long subnetMask = ~((1UL << (32 - newMask)) - 1);

    cout << "Subnets for the given IP with " << numSubnets << " subnets (/" << newMask << "):" << endl;

    for (int i = 0; i < numSubnets; ++i)
    {
        unsigned long networkAddress = baseIP + (i * subnetSize);
        unsigned long broadcastAddress = networkAddress + subnetSize - 1;
        unsigned long firstHost = networkAddress + 1;
        unsigned long lastHost = broadcastAddress - 1;

        cout << "Subnet " << i + 1 << ":" << endl;
        cout << "  Network Address: " << intToIP(networkAddress) << endl;
        cout << "  Broadcast Address: " << intToIP(broadcastAddress) << endl;
        cout << "  First Host: " << intToIP(firstHost) << endl;
        cout << "  Last Host: " << intToIP(lastHost) << endl;
        cout << "-------------------------------" << endl;
    }
}

int main()
{
    string ip;
    int originalMask, numSubnets;

    // Input the base IP, original mask, and number of subnets
    cout << "Enter the base IP address (e.g., 180.250.138.37): ";
    cin >> ip;

    cout << "Enter the original subnet mask (e.g., 15 for /15): ";
    cin >> originalMask;

    cout << "Enter the number of subnets: ";
    cin >> numSubnets;

    // Convert IP to 32-bit integer
    unsigned long octets[4];
    sscanf(ip.c_str(), "%lu.%lu.%lu.%lu", &octets[0], &octets[1], &octets[2], &octets[3]);
    unsigned long baseIP = (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];

    // Calculate the new mask
    int additionalBits = ceil(log2(numSubnets));
    int newMask = originalMask + additionalBits;

    if (newMask > 32)
    {
        cout << "Error: Not enough address space for the requested number of subnets." << endl;
        return 1;
    }

    // Perform subnet calculations
    calculateSubnets(baseIP, originalMask, newMask, numSubnets);

    return 0;
}
