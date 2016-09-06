#include "GameDataManager.h"
#include "cocos2d.h"
#include "skill\Skill.h"

USING_NS_CC;

static GameDataManager* p_gameDataManager=nullptr;

GameDataManager::GameDataManager(void)
{

}


GameDataManager::~GameDataManager(void)
{
	m_heros.clear();
	m_skills.clear();
	m_configs.clear();
	CCLOG("GameDataManager is destroy!");
}

GameDataManager* GameDataManager::getInstance()
{
	if (p_gameDataManager==nullptr)
	{
		p_gameDataManager=new GameDataManager();
		//if (p_gameDataManager)
		//{
		//	//p_gameDataManager->autorelease();
		//}else{
		//	CC_SAFE_DELETE(p_gameDataManager);
		//}
	}
	return p_gameDataManager;
}


City * GameDataManager::getCity(int id)
{
	return nullptr;
}

bool GameDataManager::loadXML()
{
	loadHeroXML();
	tinyxml2::XMLDocument* configDocment=new tinyxml2::XMLDocument();
	configDocment->LoadFile("xml/config.xml");
	tinyxml2::XMLElement* rootElement = configDocment->RootElement();
	tinyxml2::XMLElement* stringElement = rootElement->FirstChildElement("string");

	//"技能"
	while (stringElement) {
		string key=stringElement->Attribute("name");
		string value=stringElement->GetText();
		m_configs.insert(make_pair(key,value));
		stringElement = stringElement->NextSiblingElement();
	}
	return loadSkillXML();
}

bool GameDataManager::loadHeroXML()
{
	//获取文件路径
	//const char* file_path = FileUtils::getInstance()->fullPathForFilename("hero.xml").c_str();
	//CCLOG("XXXX: %100s",file_path);
	tinyxml2::XMLDocument* myDocment = new tinyxml2::XMLDocument();
	//加载文件
	if (myDocment->LoadFile("xml/hero.xml"))
		return false;

	tinyxml2::XMLElement* rootElement = myDocment->RootElement();
	tinyxml2::XMLElement* roleElement = rootElement->FirstChildElement("hero");

	//"英雄"
	while (roleElement) {
		HeroStruct hero;
		tinyxml2::XMLElement* id_element = roleElement->FirstChildElement("id");
		tinyxml2::XMLElement* name_element = roleElement->FirstChildElement("name");
		tinyxml2::XMLElement* icon_element = roleElement->FirstChildElement("icon");
		tinyxml2::XMLElement* path_element = roleElement->FirstChildElement("path");
		tinyxml2::XMLElement* race_element = roleElement->FirstChildElement("race");
		tinyxml2::XMLElement* vit_element = roleElement->FirstChildElement("vit");
		tinyxml2::XMLElement* force_element = roleElement->FirstChildElement("force");
		tinyxml2::XMLElement* wit_element = roleElement->FirstChildElement("wit");
		tinyxml2::XMLElement* quk_element = roleElement->FirstChildElement("quk");
		tinyxml2::XMLElement* def_element = roleElement->FirstChildElement("def");
		tinyxml2::XMLElement* dodge_element = roleElement->FirstChildElement("dodge");
		tinyxml2::XMLElement* skill_element = roleElement->FirstChildElement("skill");

		hero.id=atoi(id_element->GetText());
		hero.name=name_element->GetText();
		hero.icon=atoi(icon_element->GetText());
		hero.path=path_element->GetText();
		hero.race=atoi(race_element->GetText());
		hero.vit=atoi(vit_element->GetText());
		hero.force=atoi(force_element->GetText());
		hero.wit=atoi(wit_element->GetText());
		hero.quk=atoi(quk_element->GetText());
		hero.def=atoi(def_element->GetText());
		hero.dodge=atoi(dodge_element->GetText());
		hero.skills=skill_element->GetText();
		m_heros.insert(make_pair(hero.id,hero));
		roleElement = roleElement->NextSiblingElement();
	}
	return true;
}

bool GameDataManager::loadSkillXML()
{

	tinyxml2::XMLDocument* myDocment = new tinyxml2::XMLDocument();
	//加载文件
	myDocment->LoadFile("xml/skill.xml");

	tinyxml2::XMLElement* rootElement = myDocment->RootElement();
	tinyxml2::XMLElement* skillElement = rootElement->FirstChildElement("skill");

	//"技能"
	while (skillElement) {
		SkillStruct skill;
		tinyxml2::XMLElement* id_element = skillElement->FirstChildElement("id");
		tinyxml2::XMLElement* name_element = skillElement->FirstChildElement("name");
		tinyxml2::XMLElement* icon_element = skillElement->FirstChildElement("icon");
		tinyxml2::XMLElement* path_element = skillElement->FirstChildElement("path");
		tinyxml2::XMLElement* mp_element = skillElement->FirstChildElement("mp");
		tinyxml2::XMLElement* action_element = skillElement->FirstChildElement("action");

		tinyxml2::XMLElement* music_element = skillElement->FirstChildElement("music");

		tinyxml2::XMLElement* describe_element = skillElement->FirstChildElement("describe");
		tinyxml2::XMLElement* hurt_element = skillElement->FirstChildElement("hurtType");
		tinyxml2::XMLElement* value1_element = skillElement->FirstChildElement("value1");
		tinyxml2::XMLElement* value2_element = skillElement->FirstChildElement("value2");
		tinyxml2::XMLElement* value3_element = skillElement->FirstChildElement("value3");

		tinyxml2::XMLElement* atkType_element = skillElement->FirstChildElement("atkType");
		tinyxml2::XMLElement* areaType_element = skillElement->FirstChildElement("areaType");

		tinyxml2::XMLElement* addition_element = skillElement->FirstChildElement("addition");
		tinyxml2::XMLElement* hp_element = addition_element->FirstChildElement("hp");
		tinyxml2::XMLElement* attack_element = addition_element->FirstChildElement("attack");
		tinyxml2::XMLElement* defend_element = addition_element->FirstChildElement("defend");
		tinyxml2::XMLElement* speed_element = addition_element->FirstChildElement("speed");
		tinyxml2::XMLElement* dodge_element = addition_element->FirstChildElement("dodge");
		tinyxml2::XMLElement* crit_element = addition_element->FirstChildElement("crit");

		tinyxml2::XMLElement* range_element = skillElement->FirstChildElement("range");

		tinyxml2::XMLElement* area_element=nullptr;

		for (int i = 1; i < 26; i++)
		{
			string str=StringUtil::StringAddInt("range",i);
			area_element = range_element->FirstChildElement(str.c_str());
			string text(area_element->GetText());
			if (text!="-1")
			{
				skill.areas.push_back(StringUtil::splitToInt(text,","));
			}
		}

		skill.id=atoi(id_element->GetText());
		skill.music=music_element->GetText();
		skill.name=name_element->GetText();
		skill.icon=atoi(icon_element->GetText());
		skill.path=path_element->GetText();
		skill.mp=atoi(mp_element->GetText());
		skill.action=atoi(action_element->GetText());
		skill.areaType=atoi(areaType_element->GetText());
		skill.atkType=atoi(atkType_element->GetText());
		skill.describe=atoi(describe_element->GetText());
		skill.hurtType.type=atoi(hurt_element->GetText());
		skill.hurtType.value1=atoi(value1_element->GetText());
		skill.hurtType.value2=atoi(value2_element->GetText());
		skill.hurtType.value3=atoi(value3_element->GetText());

		m_skills.insert(make_pair(skill.id,skill));

		skillElement = skillElement->NextSiblingElement();
	}
	return true;
}

Animal* GameDataManager::getAnimal(int id,int direct,int level)
{

	Animal* animal=Animal::create();
	AnimalVO* animalVO=getAnimalVO(id,level);
	CCLOG("hero name:%s",animalVO->getName().c_str());
	animal->setAnimalVO(animalVO);
	animal->setDirect(direct);
	vector<int> skills=animalVO->getSkills();
	int length=skills.size();
	for (int i = 0; i < length ; i++)
	{

		Skill* skill=getSkill(skills[i]);

		skill->swithDirect(direct);
		skill->setSource(animal);
		animal->addSkill(skill,i);

	}
	animal->swichSkill(0);

	return animal;
}



AnimalVO* GameDataManager::getAnimalVO(int id,int level)
{
	AnimalVO* animalVO=AnimalVO::create();
	//CCLOG("the id: %s",m_heros.find(id)->second.name.c_str());
	HeroStruct hero = m_heros.find(id)->second;
	animalVO->setID(hero.id);
	animalVO->setName(hero.name);
	animalVO->setIcon(hero.icon);
	animalVO->setPath(hero.path);
	animalVO->setRace(hero.race);
	animalVO->setVit(hero.vit);
	animalVO->setDef(hero.def);
	animalVO->setDodge(hero.dodge);
	animalVO->setForce(hero.force);
	animalVO->setLevel(level);
	animalVO->setQuk(hero.quk);
	animalVO->setWit(hero.wit);
	animalVO->setSkills(StringUtil::splitToInt(hero.skills,","));
	Resource resource=getResorce(level);
	animalVO->setBing(resource.bing);
	animalVO->setMaxBing(resource.bing);
	animalVO->setFood(resource.food);
	animalVO->setMaxFood(resource.food);
	animalVO->setWood(resource.wood);
	animalVO->setMaxWood(resource.wood);
	animalVO->setIron(resource.iron);
	animalVO->setMaxIron(resource.iron);
	animalVO->count();
	return animalVO;
};


Skill* GameDataManager::getSkill(int id)
{
	Skill* skill=new Skill();
	skill->setSkillVO(getSkillVO(id));
	return skill;
}

SkillVO* GameDataManager::getSkillVO(int id)
{
	SkillVO* skillVO=new SkillVO();
	SkillStruct skillStruct=m_skills.find(id)->second;
	HurtValue hurtValue=skillVO->getHurtValue();
	hurtValue.type=skillStruct.hurtType.type;
	hurtValue.value1=skillStruct.hurtType.value1;
	hurtValue.value2=skillStruct.hurtType.value2;
	hurtValue.value3=skillStruct.hurtType.value3;
	skillVO->setMP(skillStruct.mp);
	skillVO->setAction(skillStruct.action);
	skillVO->setName(skillStruct.name);
	skillVO->setID(skillStruct.id);
	skillVO->setIcon(skillStruct.icon);
	skillVO->setMusic(skillStruct.music);
	skillVO->setAreas(skillStruct.areas);
	skillVO->setAreaType(skillStruct.areaType);
	skillVO->setAtkType(skillStruct.atkType);
	skillVO->setDescribe(skillStruct.describe);
	skillVO->setPath(skillStruct.path);
	return skillVO;
}

void GameDataManager::destroy()
{
	CC_SAFE_DELETE(p_gameDataManager);
}

std::string GameDataManager::getString(string key)
{
	return m_configs.at(key);
}

std::string GameDataManager::getText(string key)
{
	return p_gameDataManager->getString(key);
}

Resource GameDataManager::getResorce(int lv)
{
	Resource resource;
	resource.lv=lv;
	resource.bing=lv*1000;
	resource.food=lv*1000;
	resource.iron=lv*100;
	resource.money=lv*1000;
	resource.wood=lv*500;
	return resource;
}
