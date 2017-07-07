#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::Layer,TableViewDataSource,TableViewDelegate
{
public:
    static cocos2d::Scene* createScene();
    
    Director * director;
    virtual bool init();
    virtual void scrollViewDidScroll(ScrollView* view) {};
    
    virtual void scrollViewDidZoom(ScrollView* view) {}
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    
    virtual ssize_t numberOfCellsInTableView(TableView *table);

    void menuCloseCallback();
    void replaceScene(ssize_t type);
    
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
