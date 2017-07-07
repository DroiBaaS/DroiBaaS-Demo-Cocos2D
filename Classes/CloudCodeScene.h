
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CloudCodeScene : public cocos2d::Layer,TableViewDataSource,TableViewDelegate
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
    
    pthread_t pidrun;
    
    Label* pTest;
    
    static void* thread_run(void *r);
    
    void addSuc(Ref *pSender);
    
    void addFail(Ref *pSender);
    
    CREATE_FUNC(CloudCodeScene);
};
