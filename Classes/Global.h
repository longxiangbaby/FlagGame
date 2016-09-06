
#define USING_NS_YLING yling

#define EFFECT_FILE       "effect1.wav"  //��Ч
#define MUSIC_FILE        "music/back2.mp3"  //����
#define MUSIC_FIGHT       "music/fight9.mp3"  //����
#define MUSIC_SELECT      "music/selectskill.mp3"  //����

#define TILE_PATH       "music/fight9.mp3"  //����
#define CITY_PATH       "music/fight9.mp3"  //����

#define ROLE_PATH(val)       "Role/"+val+"/"+val  //��ɫ·��
#define SKILL_PATH(val)       "skill/"+val  //����·��

#define CITY_ICON       "icon/city/"  //�ǳ�ͼ��·��
#define SKILL_ICON       "icon/skill/"  //����ͼ��·��
#define ROLE_BIG_ICON       "icon/hero1/"  //��ɫ��ͼ��·��
#define ROLE_SMALL_ICON       "icon/hero2/"  //��ɫСͼ��·��

#define FONT_NAME             "fonts/Thonburi.ttf"
#define FONT_SIZE              36

typedef enum 
{
	NPC,
	PLAYER,
	CAMP1,
	CAMP2,
	CAMP3
} CampFlag;

typedef enum 
{
	SOLDIERS,
	ARCHERS,
	MAGE
} Race;

typedef enum
{
	DIRECT_UP=0,
	DIRECT_LEFT=1,
	DIRECT_RIGHT=2,
	DIRECT_DOWN=3
}Direct;

typedef enum 
{
	ATCTIVE=1,
	PASSIVE=2
}SkillType;

typedef enum {
	MDISTANCE=4
} ATKType;

