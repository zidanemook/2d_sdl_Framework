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

//Related ToAnimationState function!!!
enum eAnimationState
{
	eAnimationState_Idle_Left,
	eAnimationState_Idle_Left_Up,
	eAnimationState_Idle_Up,
	eAnimationState_Idle_Right_Up,
	eAnimationState_Idle_Right,
	eAnimationState_Idle_Right_Down,
	eAnimationState_Idle_Down,
	eAnimationState_Idle_Left_Down,
	eAnimationState_Walk_Left,
	eAnimationState_Walk_Left_Up,
	eAnimationState_Walk_Up,
	eAnimationState_Walk_Right_Up,
	eAnimationState_Walk_Right,
	eAnimationState_Walk_Right_Down,
	eAnimationState_Walk_Down,
	eAnimationState_Walk_Left_Down,
	eAnimationState_Run_Left,
	eAnimationState_Run_Left_Up,
	eAnimationState_Run_Up,
	eAnimationState_Run_Right_Up,
	eAnimationState_Run_Right,
	eAnimationState_Run_Right_Down,
	eAnimationState_Run_Down,
	eAnimationState_Run_Left_Down,
	eAnimationState_Attack_Left,
	eAnimationState_Attack_Left_Up,
	eAnimationState_Attack_Up,
	eAnimationState_Attack_Right_Up,
	eAnimationState_Attack_Right,
	eAnimationState_Attack_Right_Down,
	eAnimationState_Attack_Down,
	eAnimationState_Attack_Left_Down,
	eAnimationState_Talk_Left,
	eAnimationState_Talk_Left_Up,
	eAnimationState_Talk_Up,
	eAnimationState_Talk_Right_Up,
	eAnimationState_Talk_Right,
	eAnimationState_Talk_Right_Down,
	eAnimationState_Talk_Down,
	eAnimationState_Talk_Left_Down,
	eAnimationState_Beaten_Left,
	eAnimationState_Beaten_Left_Up,
	eAnimationState_Beaten_Up,
	eAnimationState_Beaten_Right_Up,
	eAnimationState_Beaten_Right,
	eAnimationState_Beaten_Right_Down,
	eAnimationState_Beaten_Down,
	eAnimationState_Beaten_Left_Down,
	eAnimationState_FallDown_Left,
	eAnimationState_FallDown_Left_Up,
	eAnimationState_FallDown_Up,
	eAnimationState_FallDown_Right_Up,
	eAnimationState_FallDown_Right,
	eAnimationState_FallDown_Right_Down,
	eAnimationState_FallDown_Down,
	eAnimationState_FallDown_Left_Down,
	eAnimationState_Max
};

enum eMoveDirection
{
	eMoveDirection_Left,
	eMoveDirection_Left_Up,
	eMoveDirection_Up,
	eMoveDirection_Right_Up,
	eMoveDirection_Right,
	eMoveDirection_Right_Down,
	eMoveDirection_Down,
	eMoveDirection_Left_Down
};

#define  ONESECOND 1.0f

#endif //Define_h