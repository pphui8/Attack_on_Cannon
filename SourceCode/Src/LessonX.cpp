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
	m_iGameState			=	1;
	zhunxin = new CSprite("zhunxin");
	dapao = new CSprite("dapao");
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
{
    CSystem::ShowCursor(false);
    m_iBombNum = 0;
    paodan_speed = 50.f;
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
    for(int i = 0; i < m_vPaodan.size(); ++i) {
        float speedY = m_vPaodan[i]->GetSpriteLinearVelocityY();
        m_vPaodan[i]->SetSpriteLinearVelocityY(speedY + 0.1);
    }
}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
}
//===============================hhhhhhhhhjjk===========================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{
    /*float fX = dapao->GetSpritePositionX();
	float fY = dapao->GetSpritePositionY();
	float  ftan =atan2((fMouseY-fY),(fMouseX-fX));	//鼠标和大炮的连接线和X轴的夹角
	float  fRotation=180*ftan/PI;		//	弧度制转换为角度,炮口和X轴正方向的夹角
    if(fRotation<0)
		fRotation+=360;
	if(fRotation>90 && fRotation<180)	//限制炮口角度
		fRotation = 90;
	else if(fRotation >= 180 && fRotation<270)	//限制炮口角度
		fRotation = 270;
	dapao->SetSpriteRotation(fRotation);
    zhunxin->SetSpritePosition(fMouseX,fMouseY);*/

}
//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
    /*if(iMouseType == MOUSE_LEFT){	//鼠标左键按下
		float fPosX, fPosY;
		//获得大炮链接点位置，作为炮弹起点
		fPosX = dapao->GetSpriteLinkPointPosX(1);
		fPosY = dapao->GetSpriteLinkPointPosY(1);
		char *szName;
		szName = CSystem::MakeSpriteName("paodan_%d", m_iBombNum++);	//得到炮弹名字
		CSprite* bomb = new CSprite(szName);
		bomb->CloneSprite("paodan_muban");		//复制炮弹模板
		bomb->SetSpritePosition(fPosX, fPosY);
		bomb->SpriteMoveTo(fMouseX, fMouseY, 50, false);
		gunfire->PlayEffect(fPosX, fPosY, 0.f);	//播放特效
		m_vPaodan.push_back(bomb);		//将炮弹压入vector中集中管理
	}*/


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
{
    if(KEY_J == iKey) {
        float fRotation = dapao->GetSpriteRotation();
        if(fRotation<0) fRotation+=360;
        if(fRotation>90 && fRotation<180) fRotation = 90;
        else if(fRotation >= 180 && fRotation<270) fRotation = 270;
        dapao->SetSpriteRotation(fRotation + 10);
    }
    if(KEY_K == iKey) {
        float fRotation = dapao->GetSpriteRotation();
        if(fRotation<0) fRotation+=360;
        if(fRotation>90 && fRotation<180) fRotation = 90;
        else if(fRotation >= 180 && fRotation<270) fRotation = 270;
        dapao->SetSpriteRotation(fRotation - 10);
    }
    if(KEY_L == iKey) {
        Fire(dapao->GetSpriteLinkPointPosX(1), dapao->GetSpriteLinkPointPosY(1), dapao->GetSpriteRotation());
    }
    //IF(kA)
}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp( const int iKey )
{

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

#include<math.h>
void CGameMain::Fire(int start_X, int start_Y, float idir)
{
		float fPosX, fPosY;
		float dire;
		float speed_x, speed_y;
		dire = dapao->GetSpriteRotation();
		//获得大炮链接点位置，作为炮弹起点
		fPosX = dapao->GetSpriteLinkPointPosX(1);
		fPosY = dapao->GetSpriteLinkPointPosY(1);
		char *szName;
		szName = CSystem::MakeSpriteName("paodan_%d", m_iBombNum++);	//得到炮弹名字
		CSprite* bomb = new CSprite(szName);
		bomb->CloneSprite("paodan_muban");		//复制炮弹模板
		bomb->SetSpritePosition(fPosX, fPosY);
		//
		speed_x = paodan_speed * cos(dire * M_PI /180);
		speed_y = paodan_speed * sin(dire * M_PI / 180);
		bomb->SetSpriteLinearVelocityX(30);
		bomb->SetSpriteLinearVelocityY(speed_y);
		//
		gunfire->PlayEffect(fPosX, fPosY, 0.f);	//播放特效
		m_vPaodan.push_back(bomb);		//将炮弹压入vector中集中管理
}

void CGameMain::LoadMap()
{
		char* szName;
		int i,j;
		float x,y;
		for(i=0;i<11;i++)
		{
			for(j=0;j<13;j++)
			{
				if(g_iMap[i][j]==1)
				{
					szName = CSystem::MakeSpriteName("wall",j+i*13+i);//重新起名
					CSprite* pWall = new CSprite(szName); //新建对象
					pWall->CloneSprite("wall"); //克隆墙块
					pWall->SetSpriteCollisionActive(0,1); //设置为接受碰撞
					pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
					x =float(-24+4*j);
					y =float(-20+4*i);
					pWall->SetSpritePosition(x,y);
				}
			}
		}
}
