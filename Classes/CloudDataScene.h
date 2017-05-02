
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CloudDataScene : public cocos2d::Layer,TableViewDataSource,TableViewDelegate
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
    
    void saveData();
    
    void query();
    
    void makeBook();
    
    void saveSuc(Ref *pSender);
    
    void saveFail(Ref *pSender);

    void querySuc(Ref *pSender);
    
    void queryFail(Ref *pSender);

    
    static void* thread_run(void *r); 
    
    Label* pTest;
    
    static std:: string pt;
    
    pthread_t pidrun;
    
    CREATE_FUNC(CloudDataScene);
};
