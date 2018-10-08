//
//  Engine.h
//  networkplayground
//
//  Created by Erik Parreira on 7/9/16.
//  Copyright © 2016 Erik Parreira. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

#include <memory>

const float TIME_BETWEEN_TICKS = 0.03f;

class Engine
{
  public:
    virtual ~Engine();
    static std::unique_ptr<Engine> sInstance;

    virtual int Run();
    void Stop();

  protected:
    Engine();
    float mNextPhysicsTick;

    virtual bool DoFrame();
    bool running;

  private:
    int DoRunLoop();

};

#endif /* Engine_h */
