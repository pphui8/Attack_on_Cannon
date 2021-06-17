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
int g_iMap[11][20]=
{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1}
};
CGameMain		g_GameMain;

//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{    //
    m_pKaishi = new CSprite("kaishi");
    m_pTitle = new CSprite("title");
    m_cSound=new CSound("kaipao.ogg",false,1);//12964.wav

    //
    m_pCountdown = new CTextSprite("countdown");//时间文本
	m_fCountdown = 0.f;
	//
    m_pDeltaTime = new CTextSprite("time");//时间文本
	m_fDeltaTime = 0.f;
    //
	m_iGameState			=	1;
	gunfire = new CEffect("gunfire","",0.2);
	m_pScore = new CTextSprite("score");//分数文本
	m_iScore=0;//分数
	//
	m_pScore2 = new CTextSprite("score2");//分数文本
	m_iScore2=0;//分数
	//
	m_pEndTitle=new CSprite("endtitle");
	m_pEnd=new CSprite("end");
	m_pRed=new CSprite("bred");
	m_pBlack=new CSprite("black");
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
    case 3:
	case 4:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if(  m_fDeltaTime>0 )
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
    CSystem::ShowCursor(false);//指针光标隐藏
    m_pEndTitle->SetSpriteVisible(false);
    m_pEnd->SetSpriteVisible(false);
    m_pRed->SetSpriteVisible(false);
    m_pBlack->SetSpriteVisible(false);
     //
    //
    m_ppaoche=new Cpaoche("paoche");//新建一个名字是炮车的我方炮车对象
    m_ppaoche->CloneSprite("paoche");
    m_ppaoche->SetSpritePosition(-40.f,19.5f);//出现位置
    m_ppaoche->SetSpriteWorldLimit(WORLD_LIMIT_STICKY, -49, 13.4, -10, 27);//边界限制
    m_ppaoche->Init(0);
    m_vWeapon.push_back(m_ppaoche);
    //
    m_ppaoche2=new Cpaoche("paoche2");//新建一个名字是paoche2的我方炮车对象
    m_ppaoche2->CloneSprite("paoche2");
    m_ppaoche2->SetSpritePosition(40.f,19.5f);
    m_ppaoche2->SetSpriteWorldLimit(WORLD_LIMIT_STICKY, 10, 10, 48, 25);
    m_ppaoche2->Init(1);
    m_vWeapon.push_back(m_ppaoche2);
    //
    m_pdapao=new Cdapao("dapao");//新建一个名字是dapao对象
    m_pdapao->CloneSprite("dapao");
     m_pdapao->SetSpritePosition(-41.f,19.f);
     m_pdapao->SetSpriteWorldLimit(WORLD_LIMIT_STICKY, -50, 10, -11, 25);
     m_pdapao->Init(0);
     m_vWeapon.push_back(m_pdapao);
     //
    m_pdapao2=new Cdapao("dapao2");//新建一个名字是myPlayer的我方坦克对象
    m_pdapao2->CloneSprite("dapao2");
     m_pdapao2->SetSpritePosition(42.f,19.f);
    m_pdapao2->SetSpriteWorldLimit(WORLD_LIMIT_STICKY, 12, 2, 50, 28);
     m_pdapao2->Init(1);
     m_vWeapon.push_back(m_pdapao2);
     //
     m_ppaoche->SetSpriteVisible(false);
     m_ppaoche2->SetSpriteVisible(false);
     m_pdapao->SetSpriteVisible(false);
     m_pdapao2->SetSpriteVisible(false);
     //
    m_fCountdown = 5;		//倒计时时间为5s
    m_fCountPassedTime=0.f;
    m_pCountdown->SetSpriteVisible(false);		//设置倒计时不可见
    //
    m_fDeltaTime = 30.f;//设置倒计时的时间
    m_pDeltaTime->SetSpriteVisible(false);
    //
    m_iScore = 0;//玩家1，paoche的分数
    m_pScore->SetSpriteVisible(false);
    //
    m_iScore2 = 0;//玩家2，paoche2的分数
    m_pScore2->SetSpriteVisible(false);
    //
    m_iBombNum = 0;//炮弹数量
    LoadMap();
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{    //
    if(m_iGameState==3)
    {	//m_iGameState 为3时才执行
		m_fCountPassedTime += fDeltaTime;	//统计经过的时间，并存储到countPassedTime
        m_pCountdown->SetTextValue(m_fCountdown -m_fCountPassedTime);
		if(m_fCountPassedTime >= m_fCountdown){	//经过的时间超过countdownTime
			m_pCountdown->SetSpriteVisible(false);	//隐藏countdown
			m_fCountPassedTime = 0;		//重置经过的时间，为下一轮游戏做准备
			m_iGameState = 4;		//切换g_iGameState 3->4
			//
			m_pTitle->SetSpriteVisible(false);
			//
			m_pDeltaTime->SetSpriteVisible(true);
            m_pScore2->SetSpriteVisible(true);
            m_pScore->SetSpriteVisible(true);
            m_ppaoche->SetSpriteVisible(true);
            m_ppaoche2->SetSpriteVisible(true);
            m_pdapao->SetSpriteVisible(true);
            m_pdapao2->SetSpriteVisible(true);
		}
    }
    else if(m_iGameState==4)
    {
        m_fDeltaTime -= fDeltaTime;
        m_pDeltaTime->SetTextValue(m_fDeltaTime);
        //
        m_pKaishi->SetSpriteVisible(false);
        //
        m_pScore->SetTextValue(m_iScore);
        //
        m_pScore2->SetTextValue(m_iScore2);
    }
}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{   m_pEndTitle->SetSpriteVisible(true);
    m_pEnd->SetSpriteVisible(true);
    if(m_iScore>=m_iScore2)
    {m_pRed->SetSpriteVisible(true);}
    else if(m_iScore<m_iScore2)
    {m_pBlack->SetSpriteVisible(true);}
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
{
    if( KEY_SPACE == iKey && m_iGameState==2 )	//按下空格且游戏状态为2时
    {   m_iGameState =	3;	//设置游戏状态进入倒计时，即3
		m_pCountdown->SetSpriteVisible(true);	//显示倒计时文本框
		m_pKaishi->SetSpriteVisible(false);		//隐藏“空格开始”
	}
	else if(m_iGameState==4)
    {      m_ppaoche->OnMove(iKey,true,0);
            m_ppaoche2->OnMove(iKey,true,1);
            m_pdapao->OnMove(iKey,true,0);
            m_pdapao2->OnMove(iKey,true,1);
            if(iKey == KEY_L)//判断按下键是够为J键
                {
                    m_pdapao->OnFire();
                }
            else if(iKey == KEY_3)//判断按下键是够为J键
                {
                    m_pdapao2->OnFire();
                }
    }
}
//==========================================================================
//
// 键盘弹起a
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp( const int iKey )
{
}
void CGameMain::OnMove(int iKey, bool bPress)
{

}

//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
    CWeapon* tarSprite = FindWeaponByName(szTarName);
	if(strcmp(szSrcName,"paoche")==0) //发送碰撞为我方坦克
	{
        if(strstr(szTarName,"bomb")!=NULL)//发送碰撞为子弹strstr(abc,ab)
        {   m_iScore2++;
            DeleteWeaponByName(szTarName);
        }
	}
	if(strcmp(szSrcName,"paoche2")==0)//发送碰撞为敌方坦克
	{
        if(strstr(szTarName,"paodan") !=NULL)//接受碰撞为子弹
        {   m_iScore++;
            DeleteWeaponByName(szTarName);
        }
	}

}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{

}
void CGameMain::LoadMap()
{
		char* szName;
		int i,j;
		float x,y;
		for(i=0;i<11;i++)
		{
			for(j=0;j<20;j++)
			{
				if(g_iMap[i][j]==1)
				{
					szName = CSystem::MakeSpriteName("wall_%d",j+i*13+i);//重新起名
					CWeapon* pWall = new CWeapon(szName);
					pWall->CloneSprite("wall"); //克隆墙块
					pWall->SetSpriteCollisionActive(0,0); //设置为接受碰撞
					pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
					x =float(-47+5*j);
					y =float(-15+5*i);
					pWall->SetSpritePosition(x,y);
					m_vWeapon.push_back(pWall);
				}
			}
		}
}
void CGameMain::AddBullet(float fPosX,float fPosY ,int m_iOwner,float GunRotation)
{       char* szName;
    if(m_iOwner==0)
		{szName = CSystem::MakeSpriteName("paodan",m_iBombNum++);}//创建paodan名字
		else if(m_iOwner==1)
        {szName = CSystem::MakeSpriteName("bomb",m_iBombNum++);}//创建paodan名字m_iBombNum++
		CWeapon* pBullet = new Cbomb(szName);
		pBullet->CloneSprite("paodan_muban");
		pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL,-26, -22, 26, 22); //设置世界边界
		pBullet->SetSpriteCollisionActive(0,1); //设置发生不接受
		pBullet->OnMove(fPosX,fPosY,m_iOwner,GunRotation);
        gunfire->PlayEffect(fPosX, fPosY, 0.f);	//播放特效
         m_cSound->PlaySound();//game/data/audio/
		if(m_iOwner == 1)
		{
			pBullet->SetOwner(1);//1表示d坦克发射的子弹
		}
		else
		{
			pBullet->SetOwner(0); //0表示w坦克发射的子弹
		}
		m_vWeapon.push_back(pBullet);		//将炮弹压入vector中集中管理
}
CWeapon* CGameMain::FindWeaponByName(const char* szName)//根据名字查找到对象
{
	for(int i=0; i<m_vWeapon.size(); i++)
	{
			if(strcmp(szName,m_vWeapon[i]->GetName()) == 0)
			{
				return m_vWeapon[i];
			}
	}
}
void CGameMain::DeleteWeaponByName(const char* szName)//根据名字把精灵从容器中删除
{
	for(vector<CWeapon*>::iterator it=m_vWeapon.begin();it!=m_vWeapon.end();)
	{
		CWeapon* cw =*it;
		if(strcmp(szName,cw->GetName()) == 0)
		{
			m_vWeapon.erase(it);
			cw->DeleteSprite();
			delete cw;
			break;
		}
		else
		{
			it++;
		}
	}
}

