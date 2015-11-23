//
//  ListMediator.h
//  makeup
//
//  Created by apple13 on 14/12/4.
//
//

#ifndef __makeup__ListMediator__
#define __makeup__ListMediator__

#include "cocos2d.h"
USING_NS_CC;
#include <vector>
#include "ListIconMediator.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
class ListMediator : public Layer, public TableViewDelegate, public TableViewDataSource
{
private:
    
    bool _isVer;
public:
    TableView *_tableView;
    std::vector<ListIconMediator *> iconList;
    /**
     *  给list射视图
     *  @param list 视图数组
     *  @param is_ver 方向 true 竖 false 横
     *  @param containerSize list的宽高
     */
    void setListView(std::vector<ListIconMediator *>* list, bool is_ver, Size containerSize, bool isDrop = false);
    /**
     *  从尾滑到头
     */
    void runEndSlideStart();
    /**
     *  从头滑到尾
     */
    void runStartSlideEnd();
    /**
     *  直接滑到尾
     */
    void runSlideEnd(Vec2 pVec2);
    void runSlideStart(Vec2 pVec2);
    
    Vec2 getListMinContentOffset();
    
    Vec2 getListMaxContentOffset();
public:
    ListMediator()
    : _callbackNode(NULL)
    {};
    virtual void onEnter();
    virtual void onExit();
    
    CREATE_FUNC(ListMediator);
    
    void setListDrop(bool dropState);
public:
    virtual void scrollOnTouchBegin(TableView* table, TableViewCell* cell, Touch* pTouch);
    virtual void scrollOnTouchMoved(TableView* table, TableViewCell* cell, Touch* pTouch);
    virtual void scrollOnTouchEnd(TableView* table, TableViewCell* cell, Touch* pTouch);
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
    CC_SYNTHESIZE(Node* , _callbackNode, CallBackNode);
    
    /**
     *  list选中状态
     */
    void changeSeleteStyle();
private:
    Size getIconSize(ssize_t idx);
};

#endif /* defined(__makeup__ListMediator__) */
