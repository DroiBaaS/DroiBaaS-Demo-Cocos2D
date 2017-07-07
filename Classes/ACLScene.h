
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ACLScene : public cocos2d::Layer,TableViewDataSource,TableViewDelegate
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    virtual void scrollViewDidScroll(ScrollView* view) {};
    
    virtual void scrollViewDidZoom(ScrollView* view) {}
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
    void menuCloseCallback(ssize_t type);
    
    void tologin ();
    
    static void* login(void *r);
    
    static void* logout(void *r);
    
    static void* rigister(void *r);
    
    static void* rigisterToLogin(void *r);
    
    static void* autoLogin(void *r);
    
    static void* validateEmail(void *r);
    
    static void* sendPinCode(void *r);
    
    static void* validatePhoneNumber(void *r);
    
    static void* changePassWord(void *r);
    
    static void* confirm(void *r);
    
    static void* permission(void *r);
    
    void plogin(Ref *pSender);
    
    void plogout(Ref *pSender);
    
    void pautologin(Ref *pSender);
    
    void prigister(Ref *pSender);
    
    void prigistertologin(Ref *pSender);
    
    void pchange(Ref *pSender);
    
    void pconfirm(Ref *pSender);
    
    void ppermission(Ref *pSender);
    
    void ploginfail(Ref *pSender);
    
    void plogoutfail(Ref *pSender);
    
    void pautologinfail(Ref *pSender);
    
    void prigisterfail(Ref *pSender);
    
    void prigistertologinfail(Ref *pSender);
    
    void pchangefail(Ref *pSender);
    
    void pconfirmfail(Ref *pSender);
    
    void ppermissionfail(Ref *pSender);
    
    pthread_t pidrun;
    
    Label* pTest;
    
    CREATE_FUNC(ACLScene);
};
