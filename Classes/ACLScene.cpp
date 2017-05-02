#include "ACLScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "HelloWorldScene.h"
#include "DroiUser.h"
#include "MyObject.h"
#include "MyUser.h"
#include "DroiPermission.h"

using namespace std;

#define TABEL_LABEL_TAG 1024

Scene* ACLScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ACLScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool ACLScene::init()
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
    
    auto plabel = Label::createWithTTF("ACL Test","fonts/Marker Felt.ttf",30);
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
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::plogin), "login", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::plogout), "logout", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::pautologin), "autologin", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::prigister), "rigister", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::prigistertologin), "rigistertologin", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::pchange), "change", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::pconfirm), "confirm", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::ppermission), "permission", NULL);
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::ploginfail), "loginfail", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::plogoutfail), "logoutfail", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::pautologinfail), "autologinfail", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::prigisterfail), "rigisterfail", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::prigistertologinfail), "rigistertologinfail", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::pchangefail), "changefail", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::pconfirmfail), "confirmfail", NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ACLScene::ppermissionfail), "permissionfail", NULL);
    
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

void ACLScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %zi", cell->getIdx());
    ACLScene::menuCloseCallback(cell->getIdx());
}

Size ACLScene::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(400, 30);
}

TableViewCell* ACLScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
    std::string str[20] = {"Login","Logout", "AutoLogin","Rigister","rigisterToLogin","Confirm","Permission","ChangePassWord","",""};
    
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

ssize_t ACLScene::numberOfCellsInTableView(TableView *table)
{
    return 10;
}

void* ACLScene::login(void *r)
{
    DroiError err;
    RefPtr<DroiUser> anonymousUser = DroiUser::loginWithAnonymous(&err);
    if (err.isOk() && anonymousUser != nullptr) {
        CCLOG("DroiUser User ObjectId:%s",anonymousUser->objectId().c_str());
        CCLOG("DroiUser User sessionToken:%s",anonymousUser->getSessionToken().c_str());
        NotificationCenter::getInstance()->postNotification("login",NULL);
    }else{
        NotificationCenter::getInstance()->postNotification("loginfail",NULL);
    }
    pthread_exit(NULL);
    
    return NULL;
}

void* ACLScene::logout(void *r)
{
    RefPtr<DroiUser> user = DroiUser::getCurrentUser();
    if (user != nullptr && user->isLoggedIn()) {
        DroiError err = user->logout();
        if (err.isOk()) {
            NotificationCenter::getInstance()->postNotification("logout",NULL);
        }else{
            NotificationCenter::getInstance()->postNotification("logoutfail",NULL);
        }
    }else{
        NotificationCenter::getInstance()->postNotification("logoutfail",NULL);
    }
    pthread_exit(NULL);
    
    return NULL;
}

void* ACLScene::autoLogin(void *r)
{
    std::string tableName = "MyObject";;
    RefPtrAutoReleaser<DroiObject> obj = DroiObject::createObject(tableName);
    obj->setValue("SerialNo", std::string("1111"));

    
    DroiError err = obj->save();
    
    RefPtr<DroiUser> user = DroiUser::getCurrentUser();
    if (err.isOk()) {
        NotificationCenter::getInstance()->postNotification("autologin",NULL);
    }else{
        NotificationCenter::getInstance()->postNotification("autologinfail",NULL);
    }
    
    CCLOG("user isAnonymous %d, sessionToken: %s",user->isAnonymouseUser(),user->getSessionToken().c_str());
    pthread_exit(NULL);
    
    return NULL;
}

void* ACLScene::rigister(void *r)
{
    RefPtrAutoReleaser<DroiUser> myUser = DroiUser::create();
    myUser->setUserId("TestAccount111");
    myUser->setPassword("123456");
    DroiError err = myUser->signup();
    
    if (err.isOk() && myUser != nullptr && myUser->isLoggedIn()) {
        CCLOG("Login OK");
        NotificationCenter::getInstance()->postNotification("rigister",NULL);
    }else{
        NotificationCenter::getInstance()->postNotification("rigisterfail",NULL);
    }
    pthread_exit(NULL);
    
    return NULL;
}

void* ACLScene::rigisterToLogin(void *r)
{
    DroiError err;
    
    RefPtr<DroiUser> user = DroiUser::login("TestAccount111", "123456", &err);
    
    if (err.isOk() && user != nullptr && user->isLoggedIn()) {
        log("Login ok");
        NotificationCenter::getInstance()->postNotification("rigistertologin",NULL);
    }else{
        NotificationCenter::getInstance()->postNotification("rigistertologinfail",NULL);
    }
    pthread_exit(NULL);
    
    return NULL;
}

void* ACLScene::changePassWord(void *r)
{
    RefPtr<DroiUser> user = DroiUser::getCurrentUser();
    // 旧密码是 123456
    // 新密码是 654321
    DroiError error =  user->changePassword("123456", "654321");
    if (error.isOk()) {
        NotificationCenter::getInstance()->postNotification("change",NULL);
    }else{
        NotificationCenter::getInstance()->postNotification("changefail",NULL);
    }
    
    pthread_exit(NULL);
    
    return NULL;
}

void* ACLScene::confirm(void *r)
{
    DroiError err;
    RefPtr<DroiUser> user = DroiUser::getCurrentUser();
    
    if (user == nullptr) {
        user = DroiUser::loginWithAnonymous(&err);
    }
    
    if (user != nullptr && user->isLoggedIn() && user->isAnonymouseUser()) {
        user->setUserId("userid");
        user->setPassword("p@ssword");
        user->setPhoneNumber("18916840843");
        user->setEmail("user@gmail.com");
        user->signup();
        
        if (err.isOk()) {
            CCLOG("success=======>");
            NotificationCenter::getInstance()->postNotification("confirm",NULL);
        }else{
            NotificationCenter::getInstance()->postNotification("confirmfail",NULL);
        }
    }
    pthread_exit(NULL);
    
    return NULL;
}

void* ACLScene::validateEmail(void *r)
{
    RefPtr<DroiUser> user = DroiUser::getCurrentUser();
    // 发出验证邮件
    DroiError err = user->validateEmail();
    
    // 轮询检查是否验证成功
    DroiCallback<RefPtr<DroiUser>>::onCallback2 cb = [&](RefPtr<DroiUser> user, DroiError e) {
        if (!e.isOk() || !user->isEmailVerified() ) {
            user->validateEmail();
        }
    };
    
    user->refreshValidationStatusInBackground(cb);
    
    pthread_exit(NULL);
    
    return NULL;
}

void* ACLScene::sendPinCode(void *r)
{
    RefPtr<DroiUser> user = DroiUser::getCurrentUser();
    DroiError err = user->validatePhoneNumber();
    
    if (err.isOk()) {
        log("send PinCode success");
    }
    
    pthread_exit(NULL);
    
    return NULL;
}


void* ACLScene::validatePhoneNumber(void *r)
{
    RefPtr<DroiUser> user = DroiUser::getCurrentUser();
    if (user->confirmPhoneNumberPinCode("445237").isOk()) {
        // 验证成功！
        log("success");
    }
    
    pthread_exit(NULL);
    
    return NULL;
}

void* ACLScene::permission(void *r)
{
    RefPtr<DroiUser> user = DroiUser::getCurrentUser();
    
    DroiPermission* permission = new DroiPermission;
    
    permission->setPublicReadPermission(true);
    permission->setPublicWritePermission(false);
    
    permission->setUserReadPermission(user->objectId().c_str(), true);
    permission->setUserWritePermission(user->objectId().c_str(), true);
    
    MyObject* myObject = (MyObject*) MyObject::create();
    std::string valueForStr = "name";
    myObject->setValue("stringField", valueForStr);
    myObject->setPermission(permission);
    DroiError error = myObject->save();
    
    if (error.isOk()) {
        NotificationCenter::getInstance()->postNotification("permission",NULL);
    }else{
        NotificationCenter::getInstance()->postNotification("permissionfail",NULL);
    }
    
    pthread_exit(NULL);
    
    return NULL;
}


void ACLScene::plogin(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("LOGIN_SUCCESS!!!!!");
}

void ACLScene::plogout(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("LOGOUT_SUCCESS!!!!!");
}

void ACLScene::pautologin(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("AUTOLOGIN_SUCCESS!!!!!");
}

void ACLScene::prigister(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("RIGOSTER_SUCCESS!!!!!");
}

void ACLScene::prigistertologin(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("RIGOSTER_TO_LOGIN_SUCCESS!!!!!");
}

void ACLScene::pchange(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("CHANGE_SUCCESS!!!!!");
}

void ACLScene::pconfirm(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("CONFIRM_SUCCESS!!!!!");
}

void ACLScene::ppermission(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("PERMISSION_SUCCESS!!!!!");
}

void ACLScene::ploginfail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("LOGIN_FAIL!!!!!");
}

void ACLScene::plogoutfail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("LOGOUT_FAIL!!!!!");
}

void ACLScene::pautologinfail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("AUTOLOGIN_FAIL!!!!!");
}

void ACLScene::prigisterfail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("RIGOSTER_FAIL!!!!!");
}

void ACLScene::prigistertologinfail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("RIGOSTER_TO_LOGIN_FAIL!!!!!");
}

void ACLScene::pchangefail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("CHANGE_FAIL!!!!!");
}

void ACLScene::pconfirmfail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("CONFIRM_FAIL!!!!!");
}

void ACLScene::ppermissionfail(Ref *pSender)
{
    CCLOG("testMSG");
    pTest->setString("PERMISSION_FAIL!!!!!");
}

void ACLScene::menuCloseCallback(ssize_t type)
{
    switch (type) {
        case 0:
            pthread_create(&pidrun,NULL,login,NULL);
            
            pthread_detach(pidrun);
            break;
        case 1:
            pthread_create(&pidrun,NULL,logout,NULL);
            
            pthread_detach(pidrun);
            break;
        case 2:
            pthread_create(&pidrun,NULL,autoLogin,NULL);
            
            pthread_detach(pidrun);
            break;
        case 3:
            pthread_create(&pidrun,NULL,rigister,NULL);
            
            pthread_detach(pidrun);
            break;
        case 4:
            pthread_create(&pidrun,NULL,rigisterToLogin,NULL);
            
            pthread_detach(pidrun);
            break;
        case 5:
            pthread_create(&pidrun,NULL,confirm,NULL);
            
            pthread_detach(pidrun);
            break;
        case 6:
            pthread_create(&pidrun,NULL,permission,NULL);
            
            pthread_detach(pidrun);
            break;
        case 7:
            pthread_create(&pidrun,NULL,changePassWord,NULL);
            
            pthread_detach(pidrun);
            break;
        case 8:
            pthread_create(&pidrun,NULL,validatePhoneNumber,NULL);
            
            pthread_detach(pidrun);
            break;
        case 9:
            pthread_create(&pidrun,NULL,sendPinCode,NULL);
            
            pthread_detach(pidrun);
            break;
        case 10:
            pthread_create(&pidrun,NULL,validateEmail,NULL);
            
            pthread_detach(pidrun);
            break;

        default:
            break;
    }
}
