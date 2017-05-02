#include "CloudCodeScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "HelloWorldScene.h"

using namespace std;

#define TABEL_LABEL_TAG 1024

Scene* CloudCodeScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CloudCodeScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool CloudCodeScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    TableView* tableView = TableView::create(this, Size(visibleSize.width,visibleSize.height));
    
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    
    tableView->setPosition(origin.x + (visibleSize.width - 400) / 2, origin.y-50);
    
    tableView->setDelegate(this);
    
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    auto bgSize = Director::getInstance()->getWinSize();
    auto pBg = Sprite::create("HelloWorld.png");
    pBg->setPosition(Vec2(bgSize.width / 2,bgSize.height / 2));
    
    auto plabel = Label::createWithTTF("CloudCode Test","fonts/Marker Felt.ttf",30);
    plabel->setPosition(Vec2(visibleSize.width / 2,visibleSize.height/2+135));
    
    auto pBack = Label::createWithTTF("Back","fonts/Marker Felt.ttf",30);
    pBack->setPosition(origin + Vec2(visibleSize) - Vec2(pBack->getContentSize() / 2));
    auto listenter = EventListenerTouchOneByOne::create();
    listenter->onTouchBegan = [pBack](Touch* t, Event * e) {
        
        if (pBack->getBoundingBox().containsPoint(t->getLocation())) {
            // TODO
//            MessageBox("Click Text","Click。。。。。。");
            auto scene = HelloWorld::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        return false;
    };
    
    Director::getInstance()->
    getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(listenter, pBack);
    
    this->addChild(pBack);
    this->addChild(pBg);
    this->addChild(plabel);
    this->addChild(tableView);
    
    tableView->reloadData();
    
    return true;
}

void CloudCodeScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %zi", cell->getIdx());
    CloudCodeScene::menuCloseCallback(cell->getIdx());
}

Size CloudCodeScene::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(400, 30);
}

TableViewCell* CloudCodeScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
    std::string str[20] = {"CloudCode1","CloudCode2", "CloudCode3","CloudCode4","CloudCode5"};
    
    std::string text = str[idx];
    auto cell = table->dequeueCell();
    if (!cell)
    {
        cell = TableViewCell::create();
        auto label = Label::createWithTTF(text, "fonts/arial.ttf", 20.0f);
        label->setTag(TABEL_LABEL_TAG);
        label->setPosition(200, 15);
        cell->addChild(label);
    }
    else
    {
        auto label = (Label*)cell->getChildByTag(TABEL_LABEL_TAG);
        label->setString(text);
    }
    
    return cell;
}

ssize_t CloudCodeScene::numberOfCellsInTableView(TableView *table)
{
    return 5;
}


void CloudCodeScene::menuCloseCallback(ssize_t type)
{
    switch (type) {
        case 0:
            
            break;
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        default:
            break;
    }
}
