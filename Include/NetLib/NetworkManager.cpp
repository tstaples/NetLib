#include "stdafx.h"
#include "NetworkManager.h"

#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

NetworkManager::NetworkManager()
    : mMaxSockets(0)
    , mNetworkInitialized(false)
{
}
//----------------------------------------------------------------------------------------------------

NetworkManager::~NetworkManager()
{
}
//----------------------------------------------------------------------------------------------------

bool NetworkManager::Init()
{
    WSADATA wsadata;

    // Request version 2.0 of winsock
    s32 err = WSAStartup(MAKEWORD(2, 0), &wsadata);
    if (err == 0)
    {
        mMaxSockets = wsadata.iMaxSockets;
        mNetworkInitialized = true;
    }
    return mNetworkInitialized;
}
//----------------------------------------------------------------------------------------------------

bool NetworkManager::Shutdown()
{
    WSACleanup();
    mNetworkInitialized = false;
}