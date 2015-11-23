//
//  ListMediator.cpp
//  makeup
//
//  Created by apple13 on 14/12/4.
//
//

#include "ListMediator.h"
#include "GameOther.h"
//#include "DressIconMediator.h"
#include "GameData.h"
//#include "DressUpMediator.h"
//#include "GameEffectLayer.h"
//#include "MakeUpMediator.h"
//#include "FriendDressUpMediator.h"
//#include "ManDressUpMediator.h"
void ListMediator::onEnter()
{
   
    Layer::onEnter();
}

void ListMediator::onExit()
{
    for(int i = 0; i < iconList.size(); i++)
    {
        CC_SAFE_RELEASE(iconList.at(i));
    }
    Layer::onExit();
}

void ListMediator::setListView(std::vector<ListIconMediator *>* list, bool is_ver, Size containerSize, bool isDrop)
{
    iconList = *list;
    _isVer = is_ver;
    this->setContentSize(containerSize);
    _tableView = TableView::create(this, containerSize);
    _tableView->setDirection(is_ver ? cocos2d::extension::ScrollView::Direction::VERTICAL : cocos2d::extension::ScrollView::Direction::HORIZONTAL);
    _tableView->setPosition(Vec2::ZERO);
    _tableView->setDelegate(this);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(_tableView);
    _tableView->setDropState(isDrop);
    _tableView->setScrollTouch(true);
//    if(dynamic_cast<MakeUpMediator* >(this->getCallBackNode()))
//        _tableView->setDropState(false);
//    if(dynamic_cast<DressUpMediator* >(this->getCallBackNode()))
//        _tableView->setDropState(true);
//    if(dynamic_cast<FriendDressUpMediator* >(this->getCallBackNode()))
//        _tableView->setDropState(true);
//    if(dynamic_cast<ManDressUpMediator* >(this->getCallBackNode()))
//        _tableView->setDropState(true);
}

void ListMediator::runEndSlideStart()
{
    _tableView->reloadData();
    if(_tableView->getDirection() == cocos2d::extension::ScrollView::Direction::HORIZONTAL)
    {
        _tableView->setContentOffset(_tableView->maxContainerOffset());
        _tableView->setContentOffsetInDuration(_tableView->minContainerOffset(), 0.5f);
        
    }
    else
    {
        _tableView->setContentOffset(_tableView->maxContainerOffset());
        _tableView->setContentOffsetInDuration(_tableView->minContainerOffset(), 0.5f);
    }
}

void ListMediator::runStartSlideEnd()
{
    _tableView->reloadData();
    if(_tableView->getDirection() == cocos2d::extension::ScrollView::Direction::HORIZONTAL)
    {
        _tableView->setContentOffset(_tableView->minContainerOffset());
        _tableView->setContentOffsetInDuration(_tableView->maxContainerOffset(), 0.5f);
        
    }
    else
    {
        _tableView->setContentOffset(_tableView->minContainerOffset());
        _tableView->setContentOffsetInDuration(_tableView->maxContainerOffset(), 0.5f);
    }
}

void ListMediator::runSlideEnd(Vec2 pVec2)
{
    _tableView->reloadData();
    if(_tableView->getDirection() == cocos2d::extension::ScrollView::Direction::HORIZONTAL)
    {
        _tableView->setContentOffset(_tableView->minContainerOffset());
        _tableView->setContentOffsetInDuration(_tableView->minContainerOffset(), 0);
    }
    else
    {
        _tableView->setContentOffset(pVec2);
        _tableView->setContentOffsetInDuration(_tableView->maxContainerOffset(), 0);
    }
}

Vec2 ListMediator::getListMinContentOffset()
{
    return _tableView->minContainerOffset();
}

Vec2 ListMediator::getListMaxContentOffset()
{
    return _tableView->maxContainerOffset();
}

Size ListMediator::getIconSize(ssize_t idx)
{
    Node* __node = iconList.at(idx);
    float __iconWidth;
    float __iconHeight;
    if(_isVer)
    {
        __iconWidth = this->getContentSize().width;
        __iconHeight = __node->getContentSize().height < 100 ? 100 : __node->getContentSize().height;
    }
    else
    {
        __iconWidth = __node->getContentSize().width < 100 ? 100 : __node->getContentSize().width;
        __iconHeight = this->getContentSize().height;
    }
    return Size(__iconWidth, __iconHeight);
}

void ListMediator::changeSeleteStyle()
{
//    for(int i = 0; i < iconList.size(); i++)
//    {
//        if(dynamic_cast<DressIconMediator* >(iconList.at(i)))
//        {
//            DressIconMediator* __icon = dynamic_cast<DressIconMediator* >(iconList.at(i));
//            __icon->decodeClickEffect();
//        }
//    }
}

Size ListMediator::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return this->getIconSize(idx);
}

TableViewCell* ListMediator::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell *cell;
    cell = table->cellAtIndex(idx);
    if(!cell)
    {
        Node* __node = iconList.at(idx);
        cell = new TableViewCell();
        cell->setContentSize(this->getIconSize(idx));
        cell->autorelease();
        if(__node->getParent())
            __node->removeFromParent();
        __node->setPosition(Vec2(cell->getContentSize().width / 2, cell->getContentSize().height / 2));
        cell->addChild(iconList.at(idx));
        this->changeSeleteStyle();
    }
    return cell;
}

ssize_t ListMediator::numberOfCellsInTableView(TableView *table)
{
    return iconList.size();
}

void ListMediator::tableCellTouched(TableView* table, TableViewCell* cell)
{
    if(cell->getIdx() >= 0)
    {
        dynamic_cast<ListIconMediator* >(iconList.at(cell->getIdx()))->onClick();
    }
    
    this->changeSeleteStyle();
}

void ListMediator::scrollOnTouchBegin(TableView* table, TableViewCell* cell, Touch* pTouch)
{
    if(cell->getIdx() >= 0)
    {
        dynamic_cast<ListIconMediator* >(iconList.at(cell->getIdx()))->onBeginTouch(pTouch);
    }
}

void ListMediator::scrollOnTouchMoved(TableView* table, TableViewCell* cell, Touch* pTouch)
{
    if(cell->getIdx() >= 0)
    {
        dynamic_cast<ListIconMediator* >(iconList.at(cell->getIdx()))->onMoveTouch(pTouch);
    }
    
}

void ListMediator::scrollOnTouchEnd(TableView* table, TableViewCell* cell, Touch* pTouch)
{
    if(cell->getIdx() >= 0)
    {
        dynamic_cast<ListIconMediator* >(iconList.at(cell->getIdx()))->onEndTouch(pTouch);
    }
    
}