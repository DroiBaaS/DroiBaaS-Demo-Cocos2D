#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "DroiObject.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CloudDataScene.h"
#include "CloudCodeScene.h"
#include "ACLScene.h"
#include "TaskDispatcherScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define TABEL_LABEL_TAG 1024

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    director = Director::getInstance();
    
    TableView* tableView = TableView::create(this, Size(visibleSize.width,visibleSize.height));
    
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    
    tableView->setPosition(origin.x + (visibleSize.width - 400) / 2, origin.y-50);
    
    tableView->setDelegate(this);
    
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    auto bgSize = Director::getInstance()->getWinSize();
    auto pBg = Sprite::create("HelloWorld.png");
    pBg->setPosition(Vec2(bgSize.width / 2,bgSize.height / 2));
    
    auto plabel = Label::createWithTTF("DrioBass Test","fonts/Marker Felt.ttf",30);
    plabel->setPosition(Vec2(visibleSize.width / 2,visibleSize.height/2+135));
    
    this->addChild(pBg);
    this->addChild(plabel);
    this->addChild(tableView);
    
    tableView->reloadData();
    
    return true;
}

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %zi", cell->getIdx());
    HelloWorld::replaceScene(cell->getIdx());
}

Size HelloWorld::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(400, 30);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx)
{
    std::string str[20] = {"CloudDataTest","ACLTest", "CloudCodeTest","TaskDispatcherTest"};
    
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

ssize_t HelloWorld::numberOfCellsInTableView(TableView *table)
{
    return 4;
}

void HelloWorld::replaceScene(ssize_t type){
    cocos2d::Scene *scene = NULL;
    switch (type) {
        case 0:
            
            scene = CloudDataScene::createScene();
            director->replaceScene(scene);
            break;
        case 1:
            
            scene = ACLScene::createScene();
            director->replaceScene(scene);
            break;
        case 2:
            
            scene = CloudCodeScene::createScene();
            director->replaceScene(scene);
            break;
        case 3:
            
            scene = TaskDispatcherScene::createScene();
            director->replaceScene(scene);
            break;
        default:
            break;
    }
}

void HelloWorld::menuCloseCallback()
{
    DroiObject* score = DroiObject::createObject("ScoreTable");
    score->setValue("name", "xiaoming");
    score->setValue("score", 61);
//    DroiError err = score->save();
//    score->release();
    score->saveInBackground([score](DroiError err) {
        if (err.isOk()) {
            CCLOG("save success-------------------->>>>>>>>>>>>>>");

        }else{
            CCLOG("save fail-------------------->>>>>>>>>>>>>>");
        }
        score->release();
    });
    
}
