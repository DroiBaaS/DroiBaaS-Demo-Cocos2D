#include "CloudCodeScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "HelloWorldScene.h"
#include "coresdk/DroiCloud.h"
#include "DroiHttp.h"
#include "DroiObject.h"

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
    
    auto pTestLabel = Label::createWithTTF("Test Feedback:","fonts/arial.ttf",10);
    pTestLabel->setPosition(Vec2(visibleSize.width / 6,visibleSize.height/2+135));
    
    pTest = Label::createWithTTF("","fonts/arial.ttf",10);
    pTest->setPosition(Vec2(visibleSize.width / 6,visibleSize.height/2+120));
    
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
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(CloudCodeScene::addSuc), "addsuccess", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(CloudCodeScene::addFail), "addsuccess", NULL);
    
    this->addChild(pBack);
    this->addChild(pBg);
    this->addChild(plabel);
    this->addChild(tableView);
    this->addChild(pTestLabel);
    this->addChild(pTest);

    
    tableView->reloadData();
    
    return true;
}

void CloudCodeScene::addSuc(Ref *pSender)
{
    CCLOG("testMSG");
    CCString * value = (CCString*)pSender;
//    CCLOG("call notifyTest pSender=%s",(char *)(value->_string));
    
    pTest->setString(value->_string);
}

void CloudCodeScene::addFail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("ADD_FAIL!!!!!");
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
    std::string str[20] = {"CloudCode1"};
    
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
    return 1;
}


void CloudCodeScene::menuCloseCallback(ssize_t type)
{
    pthread_create(&pidrun,NULL,thread_run,NULL);
    
    pthread_detach(pidrun);

}

void* CloudCodeScene::thread_run(void *r)
{
    CCLOG("start=================>");
    DroiError error;
    std::string apiKey = "4IgjZIXPdVyvQVbadsklcdakqwilzrLxncFWPZbfJDOY-CFdZUy7VJc2mIqEvWg9";
    std::string apiPath = "/api/v2/add";
    
    DroiObject* obj = DroiObject::createObject("MyObject");
    obj->setValue("num1", 1000);
    obj->setValue("num2", 1000);
    obj->setValue("delay", 1);
    
    std::string payload;
    obj->toJson(payload);
    
    // Call RestufulAPI
    std::string res = DroiCloud::callRestfulApi(apiKey, apiPath, cocos2d::network::HttpRequest::Type::POST, payload, &error);
    CCLOG("RESULT:====>%s", res.c_str());
    NotificationCenter::getInstance()->postNotification("addsuccess",CCString::create(res));
    
    pthread_exit(NULL);
    
    return NULL;
}

