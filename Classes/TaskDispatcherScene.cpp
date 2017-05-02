#include "TaskDispatcherScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "HelloWorldScene.h"
#include "DroiTaskDispatcher.h"

using namespace std;

#define TABEL_LABEL_TAG 1024

Scene* TaskDispatcherScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TaskDispatcherScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool TaskDispatcherScene::init()
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
    
    auto plabel = Label::createWithTTF("TaskDispatcher Test","fonts/Marker Felt.ttf",30);
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
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(TaskDispatcherScene::task), "task", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(TaskDispatcherScene::time), "time", NULL);
    
    Director::getInstance()->
    getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(listenter, pBack);
    
    this->addChild(pBack);
    this->addChild(pBg);
    this->addChild(plabel);
    this->addChild(tableView);
    this->addChild(pTestLabel);
    this->addChild(pTest);

    
    tableView->reloadData();
    
    return true;
}

void TaskDispatcherScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %zi", cell->getIdx());
    TaskDispatcherScene::menuCloseCallback(cell->getIdx());
}

Size TaskDispatcherScene::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(400, 30);
}

TableViewCell* TaskDispatcherScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
    std::string str[20] = {"TaskDispatcher","TimerTaskDispatcher"};
    
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

ssize_t TaskDispatcherScene::numberOfCellsInTableView(TableView *table)
{
    return 2;
}

void TaskDispatcherScene::task(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("TASK_SUCCCESS!!!!!");
}

void TaskDispatcherScene::time(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("TIME_TASK_SUCCCESS!!!!!");
}


void TaskDispatcherScene::menuCloseCallback(ssize_t type)
{
    switch (type) {
        case 0:
            TaskDispatcherScene::taskDispatcher();
            break;
        case 1:
            TaskDispatcherScene::timeTaskDispatcher();
            break;
        default:
            break;
    }
}

void TaskDispatcherScene::taskDispatcher()
{
    DroiTaskDispatcher& taskDispatcher = DroiTaskDispatcher::getTaskDispatcher(DroiBackgroundThreadName);
    taskDispatcher.enqueueTask([]{
        NotificationCenter::getInstance()->postNotification("task",NULL);
    });
}

void TaskDispatcherScene::timeTaskDispatcher()
{
    DroiTaskDispatcher& taskDispatcher = DroiTaskDispatcher::getTaskDispatcher(DroiBackgroundThreadName);
    taskDispatcher.enqueueTimerTask("TimeTask",[]{
        NotificationCenter::getInstance()->postNotification("time",NULL);
    },1000,false);
}

