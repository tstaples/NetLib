#ifndef INCLUDED_NETLIB_NETWORKMANAGER
#define INCLUDED_NETLIB_NETWORKMANAGER
#pragma once

class NetworkManager
{
public:
    NetworkManager();
    ~NetworkManager();

    // Initialize the network
    bool Init();

    // Cleanup connections
    bool Shutdown();

private:
    bool mNetworkInitialized;
    u16 mMaxSockets;
};

#endif