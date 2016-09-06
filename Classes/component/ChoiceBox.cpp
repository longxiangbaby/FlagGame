#include "ChoiceBox.h"
#include "BaseBtn.h"

ChoiceBox::ChoiceBox(void):selectIndex(0)
{

}

ChoiceBox::~ChoiceBox(void)
{
	map<int,Item>::iterator it;
	for(it=m_items.begin();it!=m_items.end();++it){
		it->second.destroy();
	}
	m_items.clear();
	onTouch=nullptr;
	CCLOG("ChoiceBox is destroy!");
}

ChoiceBox* ChoiceBox::createChoiceBox(string iconName)
{
	ChoiceBox* choiceBox=new ChoiceBox();
	choiceBox->setIconName(iconName);
	choiceBox->autorelease();
	return choiceBox;
}


Item ChoiceBox::getItem(int index)
{
	return m_items.at(index);
}

void ChoiceBox::setSelectIndex(int index)
{
	getItem(selectIndex).component->getChildByName("kuan")->setVisible(false);
	selectIndex=index;
	getItem(selectIndex).component->getChildByName("kuan")->setVisible(true);
}

int ChoiceBox::getSelectIndex()
{
	return selectIndex;
}

void ChoiceBox::setComponents(Widget** components,int size)
{

	for (int i = 0; i < size ; i++)
	{
		Widget* widget=components[i];
		BaseBtn* component=BaseBtn::createBtn(widget);

		component->doTouchEvent=CC_CALLBACK_4(ChoiceBox::onTouchEvent,this);
		this->addChild(component);
		Item item;
		item.component=component;
		item.data=nullptr;
		item.iconBox=IconBox2::createBox(iconName);
		item.iconBox->setPosition(widget->getSize().width/2,widget->getSize().height/2);
		widget->addChild(item.iconBox);
		widget->reorderChild(widget->getChildByName("kuan"),1);
		m_items.insert(make_pair(i,item));
	}
	length=size;
}

void ChoiceBox::provide(Icon** datas,int size)
{
	for (int i = 0; i < size ; i++)
	{
		Icon* icon=datas[i];
		auto itor=m_items.find(i);
		if (itor!=m_items.end())
		{
			itor->second.data=icon;
			itor->second.iconBox->setIndex((icon==nullptr)?0:icon->getIcon());
		}
	}

}

void ChoiceBox::onTouchEvent(TouchEventType type,Widget* target,int id,string name)
{

		if (type == TOUCH_EVENT_BEGAN)
		{
			if (onChangeEvent(type,getItem(id),id,name))
			{
				setSelectIndex(id);	
			}
		}
		if (type == TOUCH_EVENT_ENDED)
		{
		}

}

void ChoiceBox::destroy()
{

}

//void ChoiceBox::onEnter()
//{
//	Node::onEnter();
//
//}
//
//void ChoiceBox::onExit()
//{
//	Node::onExit();
//	m_items.clear();
//	selectIndex=0;
//}
