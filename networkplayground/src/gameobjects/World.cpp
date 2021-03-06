//
//  World.cpp
//  networkplayground
//
//  Created by Erik Parreira on 7/9/16.
//  Copyright © 2016 Erik Parreira. All rights reserved.
//

#include "gameobjects/World.h"
#include "networking/Logger.h"

std::unique_ptr<World> World::sInstance;

void World::StaticInit() { sInstance.reset(new World()); }
World::World() {}
void World::AddGameObject(GameObjectPtr inGameObject)
{
    mGameObjects.push_back(inGameObject);
    inGameObject->SetIndexInWorld((int)mGameObjects.size() - 1);
}

void World::StaticAddGameObject(GameObjectPtr inGameObject)
{
    sInstance->AddGameObject(inGameObject);
}

void World::PrintInfo()
{
    for (auto go : sInstance->mGameObjects)
    {
        // TODO: Print Info delegate to game object
        std::cout << "Location of " << go->GetNetworkId() << " at " << go->GetLocation().mX << ","
                  << go->GetLocation().mY << std::endl;
    }
}

void World::RemoveGameObject(GameObjectPtr inGameObject)
{
    int index = inGameObject->GetIndexInWorld();
    int currentSize = (int)mGameObjects.size() - 1;

    if (index > currentSize || index < -1)
    {
        // Throw an error?
        return;
    }

    if (index != currentSize)
    {
        mGameObjects[index] = mGameObjects[currentSize];
        mGameObjects[index]->SetIndexInWorld(index);
    }

    inGameObject->SetIndexInWorld(-1);
    mGameObjects.pop_back();
}

void World::Update()
{
    for (auto const& go : mGameObjects)
    {
        go->Update();
    }
}

const std::vector<GameObjectPtr>& World::GetGameObjects() { return mGameObjects; }
