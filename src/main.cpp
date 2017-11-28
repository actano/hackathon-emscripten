#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"
#include "example.h"
#include "SDL_main.h"
#include "SDL.h"

using namespace oxygine;

// This function is called each frame
int mainloop()
{
    // Update engine-internal components
    // If input events are available, they are passed to Stage::instance.handleEvent
    // If the function returns true, it means that the user requested the application to terminate
    bool done = core::update();

    // It gets passed to our example game implementation
    example_update();

    // Update our stage
    // Update all actors. Actor::update will also be called for all its children
    getStage()->update();

    if (core::beginRendering())
    {
        Color clearColor(32, 32, 32, 255);
        Rect viewport(Point(0, 0), core::getDisplaySize());
        // Render all actors inside the stage. Actor::render will also be called for all its children
        getStage()->render(clearColor, viewport);

        core::swapDisplayBuffers();
    }

    return done ? 1 : 0;
}

// Application entry point
void run()
{
    ObjectBase::__startTracingLeaks();

    // Initialize Oxygine's internal stuff
    core::init_desc desc;
    desc.title = "Oxygine Application";

    // The initial window size can be set up here on SDL builds
    desc.w = 960;
    desc.h = 640;
    // Marmalade settings can be modified from the emulator's menu

    example_preinit();
    core::init(&desc);


    // Create the stage. Stage is a root node for all updateable and drawable objects
    Stage::instance = new Stage(true);
    Point size = core::getDisplaySize();
    getStage()->setSize(size);

    // DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff
    DebugActor::show();

    // Initializes our example game. See example.cpp
    example_init();
}


extern "C"
{
    void one(void* param) { mainloop(); }
    void oneEmsc() { mainloop(); }

    int main(int argc, char* argv[])
    {

        run();
        emscripten_set_main_loop(oneEmsc, 0, 0);
        return 0;
    }
};
