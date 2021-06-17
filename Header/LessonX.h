/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include<vector>
#include<Cpaoche.h>
#include<Cdapao.h>
#include<Cbomb.h>
#include "CommonClass.h"
using namespace std;

/////////////////////////////////////////////////////////////////////////////////
//
// 游戏总管类。负责处理游戏主循环、游戏初始化、结束等工作
class	CGameMain
{
private:
	int				m_iGameState;				// 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中
    //
    Cdapao*		m_pdapao;
    Cpaoche*	m_ppaoche;
    Cdapao*		m_pdapao2;
    Cpaoche*	m_ppaoche2;
    //
    float			GunRotation;		//炮筒同地面的夹角*******
    float			GunRotation2;		//炮筒同地面的夹角*******
    int				GunRotToLeft;		//炮筒摆动的方向：***
    //
    int				m_iBombNum;
	CEffect*		gunfire;
	vector<CWeapon*>	   m_vWeapon;
    //
    CTextSprite*	 m_pScore; //表示分数的文本精灵
    CTextSprite*	 m_pScore2; //表示分数的文本精灵
    int m_iScore;//分数
    int m_iScore2;//分数
    //
    CSprite		*m_pKaishi;//开始j精灵
    CSprite		*m_pTitle;//开始j精灵
    CSprite		*m_pEndTitle;//开始j精灵
    CSprite		*m_pEnd;//开始j精灵
    CSprite		*m_pRed;//开始j精灵
    CSprite		*m_pBlack;//开始j精灵
    CTextSprite*    m_pCountdown;		//倒计时的文字精灵
    CTextSprite*	 m_pDeltaTime; //倒计时游戏进行时间的文本精灵
    CSound* m_cSound;
    float m_fCountdown;
    float m_fCountPassedTime;
    float  m_fDeltaTime;//表示游戏时间

public:
	CGameMain();            //构造函数
	~CGameMain();           //析构函数
    void LoadMap();
	// Get方法
	int				GetGameState()											{ return m_iGameState; }

	// Set方法
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// 游戏主循环等
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	void 			OnMouseMove( const float fMouseX, const float fMouseY );
	void 			OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
	void 			OnKeyUp( const int iKey );
	void 			OnSpriteColSprite( const char *szSrcName, const char *szTarName );
	void 			OnSpriteColWorldLimit( const char *szName, const int iColSide );
	//
    void OnMove(int iKey, bool bPress);
    void AddBullet(float fPosX,float fPosY ,int iOwner,float GunRotation);
    CWeapon* FindWeaponByName(const char* szName);//根据名字查找
    void DeleteWeaponByName(const char* szName);//根据名字把精灵从容器中删除
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
