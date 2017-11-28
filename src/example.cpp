#include "oxygine-framework.h"
#include <functional>
#include <iostream>
using namespace oxygine;

//it is our resources
//in real project you would have more than one Resources declarations.
//It is important on mobile devices with limited memory and you would load/unload them
Resources gameResources;

class MainActor;

typedef oxygine::intrusive_ptr<MainActor> spMainActor;
typedef oxygine::intrusive_ptr<Draggable> spDraggable;

class MainActor: public Actor
{
public:
    Draggable _draggable;

    MainActor()
    {
        spSprite button = new Sprite();
        button->setResAnim(gameResources.getResAnim("button"));
        Vector2 pos = getStage()->getSize() / 2 - button->getSize() / 2;
        button->setPosition(pos);
        addChild(button);
    }

    void foo() {
        this->_draggable.init(this);
    }
};

void example_preinit() {}

void example_init()
{
    gameResources.loadXML("res.xml");

    spMainActor actor = new MainActor;
    getStage()->addChild(actor);
    actor->foo();
}

void example_update()
{
}

void example_destroy()
{
    gameResources.free();
}
