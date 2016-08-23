#include "gameobjects/Client.h"
#include "gameobjects/GameObjectRegistry.h"
#include "graphics/GraphicsDriver.h"
#include "graphics/RenderManager.h"
#include "graphics/TextureManager.h"
#include "graphics/WindowManager.h"
#include "input/InputManager.h"
#include "networking/NetworkManagerClient.h"
#include "networking/SocketAddressFactory.h"
#include "networking/StringUtils.h"

bool Client::StaticInit()
{
    Client* client = new Client();

    if ( WindowManager::StaticInit() == false )
    {
        return false;
    }

    if ( GraphicsDriver::StaticInit(
             WindowManager::sInstance->GetMainWindow() ) == false )
    {
        return false;
    }

    TextureManager::StaticInit();
    RenderManager::StaticInit();
    InputManager::StaticInit();

    sInstance.reset( client );

    return true;
}

Client::Client()
{
    std::string destination = "127.0.0.1:45000";
    std::string name = StringUtils::GetCommandLineArg( 2 );
    SocketAddressPtr serverAddress =
        SocketAddressFactory::CreateIPv4FromString( destination );

    NetworkManagerClient::StaticInit( *serverAddress, "DUDUD" );
}

bool Client::DoFrame()
{
    // Main message loop
    SDL_Event event;
    memset( &event, 0, sizeof( SDL_Event ) );
    if ( SDL_PollEvent( &event ) )
    {
        if ( event.type == SDL_QUIT )
        {
            return false;
        }
        else
        {
            HandleEvent( &event );
        }
    }

    Timing::sInstance.Update();

    InputManager::sInstance->Update();

    Engine::DoFrame();

    NetworkManagerClient::sInstance->ProcessIncomingPackets();

    RenderManager::sInstance->Render();

    NetworkManagerClient::sInstance->SendOutgoingPackets();

    // Return keep running
    return true;
}

void Client::HandleEvent( SDL_Event* inEvent )
{
    switch ( inEvent->type )
    {
    case SDL_KEYDOWN:
        InputManager::sInstance->HandleInput( EIA_Pressed,
                                              inEvent->key.keysym.sym );
        break;
    case SDL_KEYUP:
        InputManager::sInstance->HandleInput( EIA_Released,
                                              inEvent->key.keysym.sym );
        break;
    default:
        break;
    }
}