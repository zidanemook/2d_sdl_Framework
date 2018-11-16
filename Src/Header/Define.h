#ifndef Define_h
#define Define_h

#define FREEKEY			0x010
#define PULLKEY			0x020
#define PUSHKEY			0x040
#define HOLDKEY			0x080

enum eModeTypes
{
	eModeTypes_None,
	eModeTypes_Logo,
	eModeTypes_MainMenu,
	eModeTypes_Loading,
	eModeTypes_Play,
	eModeTypes_Max
};

enum eComponentTypes
{
	eComponentTypes_None,
	eComponentTypes_Transform,
	eComponentTypes_Sprite,
	eComponentTypes_SingleTexture,
	eComponentTypes_Max
};

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

enum eRenderLayer
{
	eRenderLayer_None,
	eRenderLayer_Ground,
	eRenderLayer_Object,
	eRenderLayer_Effect,
	eRenderLayer_UI,
	eRenderLayer_Max
};

enum eKeyFunc
{
	eKeyFunc_MoveLeft,
	eKeyFunc_MoveRight,
	eKeyFunc_MoveUp,
	eKeyFunc_MoveDown,
	eKeyFunc_Defence,
	eKeyFunc_Interact,//attack, talking, open, click move ....
	eKeyFunc_Enter,
	eKeyFunc_Esc,
	eKeyFunc_Max
};

enum eAnimationState
{
	eAnimationState_Idle,
	eAnimationState_Dead,
	eAnimationState_Invincible,
	eAnimationState_Left,
	eAnimationState_Right,
	eAnimationState_Up,
	eAnimationState_Down,
	eAnimationState_Attack,
	eAnimationState_Defence,
	eAnimationState_Max
};



#endif //Define_h