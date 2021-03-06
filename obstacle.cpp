#include "obstacle.h"

Obstacle::Obstacle(float size_ratio, b2Vec2 pos, QSizeF wh): GameItem(size_ratio)
{
    g_size = QSizeF(g_worldsize.height()*ratio*wh.width(),g_worldsize.height()*ratio*wh.height());
    g_pixmap.setPixmap(QPixmap(":/image/image/obstacle.png").scaled(g_scene->height()*ratio*wh.width(),g_scene->height()*ratio*wh.height()));
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(pos.x,pos.y);
    bodydef.userData = this;
    g_body = g_world->CreateBody(&bodydef);

    b2PolygonShape bodyshape;
    bodyshape.SetAsBox(g_size.width()/2,g_size.height()/2);

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = OBSTACLE_DENSITY;
    fixturedef.friction = OBSTACLE_FRICTION;
    fixturedef.restitution = OBSTACLE_RESTITUTION;
    g_body->CreateFixture(&fixturedef);
    g_body->SetAngularDamping(1);

    paint();
    g_scene->addItem(&g_pixmap);

    vulnerable=true;

    connect(g_timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(g_timer, SIGNAL(timeout()), this, SLOT(checkPos()));
}

Obstacle::~Obstacle()
{
    GameItem::score+=500;
}
