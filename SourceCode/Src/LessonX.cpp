/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
#include <cmath>
#define PI 3.141592653589793f

////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
	m_iGameState			=	0;
	dapao = new CSprite("dapao");
	paoche = new CSprite("paoche");
	gunfire = new CEffect("gunfire","",0.2);
}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态.
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
		{
			GameInit();
			SetGameState(2); // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
			{
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{   CSystem::ShowCursor(false);
    m_iBombNum = 0;
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
}
//==========================================================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// 鼠标弹起
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// 键盘按下
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{   float fSpeedLeft = 0,fSpeedRight = 0,fSpeedup = 0;
	switch(iKey)
	{
	case KEY_A:		//A向左
		fSpeedLeft = -15.f;
		break;
	case KEY_D:		//D向右
		fSpeedRight = 15.f;
		break;
	}
	if((fSpeedLeft + fSpeedRight) > 0)	//如果向左则要转向
		{
		paoche->SetSpriteFlipX(false);}
	else if((fSpeedLeft + fSpeedRight) < 0)	//如果向右则不转向
		{
		paoche->SetSpriteFlipX(true);}
	dapao->SetSpriteLinearVelocity(fSpeedLeft + fSpeedRight, fSpeedup);
	paoche->SetSpriteLinearVelocity(fSpeedLeft + fSpeedRight, fSpeedup);
	//**********************************************
	const float	fRotateSpeed = 5.f; 				//  摇摆速度，单位 度/秒
	float fThisRotate =	fRotateSpeed * PI; // 本次旋转的角度
	switch(iKey)
	{
	case KEY_J:		//J向上
        GunRotation+= fThisRotate ;
		break;
	case KEY_K:		//K向下
		GunRotation-= fThisRotate;
		break;
	}
	dapao->SetSpriteRotation(GunRotation);	//设置炮筒的当前角度
	//*******************************
    if(iKey == KEY_L){	//键盘L键按下
		float fPosX, fPosY;
		//获得大炮链接点位置，作为炮弹起点
		fPosX = dapao->GetSpriteLinkPointPosX(1);
		fPosY = dapao->GetSpriteLinkPointPosY(1);
		char *szName;
		szName = CSystem::MakeSpriteName("paodan_%d", m_iBombNum++);	//得到炮弹名字
		CSprite* bomb = new CSprite(szName);
		bomb->CloneSprite("paodan_muban");		//复制炮弹模板
		bomb->SetSpritePosition(fPosX, fPosY);
		bomb->SpriteMoveTo(10, -10, 50, false);
		gunfire->PlayEffect(fPosX, fPosY, 0.f);	//播放特效
		m_vPaodan.push_back(bomb);		//将炮弹压入vector中集中管理
	}

}
//==========================================================================
//
// 键盘弹起a
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp( const int iKey )
{
    if( iKey == KEY_A  || iKey == KEY_D)
		dapao->SetSpriteLinearVelocity(0,0);
		paoche->SetSpriteLinearVelocity(0,0);

}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{

}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{

}

