#ifndef Define_h
#define Define_h



#define FREEKEY			0x010
#define PULLKEY			0x020
#define PUSHKEY			0x040
#define HOLDKEY			0x080

#define HD_WIDTH	1280
#define HD_HEIGHT	720

#define FHD_WIDTH	1920
#define FHD_HEIGHT	1080

enum eModeTypes
{
	eModeTypes_None,
	eModeTypes_Logo,
	eModeTypes_Loading,
	eModeTypes_MainMenu,
	eModeTypes_Option,
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

enum eRenderLayer
{
	eRenderLayer_Ground,
	eRenderLayer_Object,
	eRenderLayer_Effect,
	eRenderLayer_Max,
	eRenderLayer_UI
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

//Related ToAnimationState function!!! //CSprite::ToAnimationState 함수에도 추가할것!!
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

enum eUIType
{
	eUIType_None,
	eUIType_ImageBox,
	eUIType_TextButton,
	eUIType_TextBox,//글자보여주고 스크롤기능도 있음
	eUIType_ListBox,//목록보여주고 스크롤기능도 있음
	eUIType_DropButton,
	eUIType_Max
};

enum eUITextAlignType
{
	eUITextAlignType_Horizontal_Center,
	eUITextAlignType_Horizontal_Left,
	eUITextAlignType_Horizontal_Right,
	eUITextAlignType_Vertical_Center,
	eUITextAlignType_Vertical_Left,
	eUITextAlignType_Vertical_Right
};

enum eUIEventState
{
	eUIEventState_None,
	eUIEventState_OnMouse,
};

#define  ONESECOND 1.0f

#define NORMALFONT L"Resource/Font/KBLZ_M.ttf"


#endif //Define_h