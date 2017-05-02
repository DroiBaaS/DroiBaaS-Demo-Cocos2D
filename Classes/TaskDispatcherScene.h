
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TaskDispatcherScene : public cocos2d::Layer,TableViewDataSource,TableViewDelegate
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
    
    void taskDispatcher();
    
    void timeTaskDispatcher();
    
    void task(Ref *pSender);
    
    void time(Ref *pSender);
    
    Label* pTest;
    
    CREATE_FUNC(TaskDispatcherScene);
};
