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

class CollidingDraggable : public Draggable
{
//    protected:
//    void onMove(const Vector2& position) override {
//    }
};

class MainActor: public Actor
{
public:
    CollidingDraggable _draggable;

    MainActor(Vector2 initialPosition)
    {
        spSprite button = new Sprite();
        button->setResAnim(gameResources.getResAnim("button"));
        button->setPosition(initialPosition);
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

    for (int i=0; i<3; i++) {
        Vector2 pos = Vector2(100*i, 0);
        spMainActor actor = new MainActor(pos);
        getStage()->addChild(actor);
        actor->foo();
    }
}

void example_update()
{
}

void example_destroy()
{
    gameResources.free();
}
