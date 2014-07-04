//
//  CAAlertView.h
//  CrossApp
//
//  Created by Zhujian on 14-6-27.
//  Copyright (c) 2014 http://www.9miao.com All rights reserved.
//

#ifndef __cocos2dx__CACollectionView__
#define __cocos2dx__CACollectionView__

#include "view/CAView.h"
#include "view/CAScale9ImageView.h"
#include "controller/CABarItem.h"
#include "view/CATableView.h"
#include "view/CALabel.h"

NS_CC_BEGIN

class CACollectionViewCell;
class CACollectionView;

class CACollectionViewDelegate
{
public:
	virtual ~CACollectionViewDelegate(){};

	virtual void collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int row, unsigned int item) {};

	virtual void collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int row, unsigned int item) {};

	virtual void collectionViewDidShowPullDownView(CACollectionView *collectionView) {};

	virtual void collectionViewDidShowPullUpView(CACollectionView *collectionView) {};
};


class CACollectionViewDataSource
{
public:
	virtual ~CACollectionViewDataSource(){};

	virtual CACollectionViewCell* collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int row, unsigned int item) = 0;

	virtual unsigned int numberOfRowsInCollectionView(CACollectionView *collectionView) = 0;

	virtual unsigned int numberOfItemsInRows(CACollectionView *collectionView, unsigned int row) = 0;

	virtual unsigned int collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int row) { return 0; }
};


class CC_DLL CACollectionView : public CAScrollView
{
public:
	CACollectionView();
	virtual ~CACollectionView();

	virtual void onEnterTransitionDidFinish();

	virtual void onExitTransitionDidStart();

	static CACollectionView* createWithFrame(const CCRect& rect);

	static CACollectionView* createWithCenter(const CCRect& rect);

	virtual bool init();

	void reloadData();

	void setSelectItemAtRow(unsigned int row, unsigned int item);

protected:
    
    inline virtual float maxSpeed(float delay);
    
    inline virtual float maxSpeedCache(float delay);
    
    inline virtual float decelerationRatio(float delay);
    
    inline virtual CCPoint maxBouncesLenght();
    
    virtual void update(float fDelta);
    
protected:

	virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);

	virtual void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);

	virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);

	virtual void ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent);

protected:
    
	CC_SYNTHESIZE(CACollectionViewDataSource*, m_pCollectionViewDataSource, CollectionViewDataSource);

	CC_SYNTHESIZE(CACollectionViewDelegate*, m_pCollectionViewDelegate, CollectionViewDelegate);

	CC_SYNTHESIZE_RETAIN(CAView*, m_pCollectionHeaderView, CollectionHeaderView);

	CC_SYNTHESIZE_RETAIN(CAView*, m_pCollectionFooterView, CollectionFooterView);

	CC_SYNTHESIZE_RETAIN(CAView*, m_pCollectionPullDownView, CollectionPullDownView);

	CC_SYNTHESIZE_RETAIN(CAView*, m_pCollectionPullUpView, CollectionPullUpView);

    CC_SYNTHESIZE(unsigned int, m_nCollectionHeaderHeight, CollectionHeaderHeight);
    
    CC_SYNTHESIZE(unsigned int, m_nCollectionFooterHeight, CollectionFooterHeight);
    
	CC_SYNTHESIZE(unsigned int, m_nCollectionPullViewHeight, CollectionPullViewHeight);

	CC_SYNTHESIZE_IS(bool, m_bAllowsSelection, AllowsSelection);

	CC_SYNTHESIZE_IS(bool, m_bAllowsMultipleSelection, AllowsMultipleSelection);

private:
	std::set<CACollectionViewCell*> m_pSelectedCollectionCells;

	CACollectionViewCell* m_pHighlightedCollectionCells;

	std::vector<CACollectionViewCell*> m_pCollectionCells;
};

class CC_DLL CACollectionViewCell : public CAControl
{
public:
	CACollectionViewCell();
	virtual ~CACollectionViewCell();

	static CACollectionViewCell* create(const char* reuseIdentifier);

	bool initWithReuseIdentifier(const char* reuseIdentifier);

    using CAControl::setBackGroundViewForState;
    
protected:
    
    virtual void normalTableViewCell(){};
    
    virtual void highlightedTableViewCell(){};
    
    virtual void selectedTableViewCell(){};
    
    virtual void disabledTableViewCell(){};
    
    void setControlState(CAControlState var);
    
    using CAControl::setTouchEnabled;
    
protected:

	CC_SYNTHESIZE(std::string, m_sReuseIdentifier, ReuseIdentifier);

	CC_SYNTHESIZE_READONLY(unsigned int, m_nRow, Row);

	CC_SYNTHESIZE_READONLY(unsigned int, m_nItem, Item);
    
    friend class CACollectionView;
};

NS_CC_END

#endif /* defined(__cocos2dx__CACollectionView__) */