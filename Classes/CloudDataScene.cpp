#include "CloudDataScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "AppMacros.h"
#include "HelloWorldScene.h"
#include "DroiQuery.h"
#include "DroiCondition.h"
#include "DroiObject.h"

using namespace std;

#define TABEL_LABEL_TAG 1024

Scene* CloudDataScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CloudDataScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool CloudDataScene::init()
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
    
    auto plabel = Label::createWithTTF("CloudData Test","fonts/Marker Felt.ttf",30);
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
        
//            MessageBox("Click Text","Click。。。。。。");
            auto scene = HelloWorld::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        return false;
    };
    
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(HelloWorld::testMSG),"test",NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(CloudDataScene::saveSuc), "savesuccess", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(CloudDataScene::saveFail), "savefail", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(CloudDataScene::querySuc), "querysuccess", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(CloudDataScene::queryFail), "queryfail", NULL);
    
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

void CloudDataScene::saveSuc(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("SAVE_SUCCCESS!!!!!");
}

void CloudDataScene::saveFail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("SAVE_FAIL!!!!!");
}

void CloudDataScene::querySuc(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("QUERY_SUCCCESS!!!!!");
}

void CloudDataScene::queryFail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("QUERY_FAIL!!!!!");
}


void CloudDataScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %zi", cell->getIdx());
    CloudDataScene::menuCloseCallback(cell->getIdx());
}

Size CloudDataScene::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(400, 30);
}

TableViewCell* CloudDataScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
    std::string str[20] = {"SaveData","Query"};
    
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

ssize_t CloudDataScene::numberOfCellsInTableView(TableView *table)
{
    return 2;
}


void CloudDataScene::menuCloseCallback(ssize_t type)
{
    switch (type) {
        case 0:
            CloudDataScene::saveData();
            break;
        case 1:
            CloudDataScene::query();
            break;
        default:
            break;
    }

}

void* CloudDataScene::thread_run(void *r)
{
    DroiQuery* query = DroiQuery::create();
    
    // 设置查询条件。
    query->queryData( "Book" )	// 由Book表格取得
    .where(DroiCondition::eq( "price", Value(70) )) // price等于70
    .orderBy( "ISBN", false );	// 依照ISBN做descending排序
    
    DroiError err;
    RefVector* result = query->runQuery(&err);
    CCLOG("size是===========>%zi",result->max_size());
    if ( err.isOk() ) {
        // 成功
//                CCLOG("size======>%zi"result->get);
        NotificationCenter::getInstance()->postNotification("querysuccess",NULL);
    }else{
        NotificationCenter::getInstance()->postNotification("queryfail",NULL);
    }
    
    pthread_exit(NULL);

    return NULL;
}

void CloudDataScene::saveData()
{
    DroiObject* score = DroiObject::createObject("Book");
    score->setValue("name", "sangguoyanyi");
    score->setValue("price", 70);
    

    score->saveInBackground([score](DroiError err) {
        if (err.isOk()) {
            CCLOG("success-------------------->>>>>>>>>>>>>>");
//            CCNotificationCenter::sharedNotificationCenter()->postNotification("test",NULL);
            auto sData = String::create("success");
            sData->retain();
            NotificationCenter::getInstance()->postNotification("savesuccess",sData);
        }else{
            CCLOG("fail-------------------->>>>>>>>>>>>>>");
            NotificationCenter::getInstance()->postNotification("savefail",NULL);
        }
        score->release();
    });
}

void CloudDataScene::query(){
    
    pthread_create(&pidrun,NULL,thread_run,NULL);
    
    pthread_detach(pidrun);
    
}
