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
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������
    //
    Cdapao*		m_pdapao;
    Cpaoche*	m_ppaoche;
    Cdapao*		m_pdapao2;
    Cpaoche*	m_ppaoche2;
    //
    float			GunRotation;		//��Ͳͬ����ļн�*******
    float			GunRotation2;		//��Ͳͬ����ļн�*******
    int				GunRotToLeft;		//��Ͳ�ڶ��ķ���***
    //
    int				m_iBombNum;
	CEffect*		gunfire;
	vector<CWeapon*>	   m_vWeapon;
    //
    CTextSprite*	 m_pScore; //��ʾ�������ı�����
    CTextSprite*	 m_pScore2; //��ʾ�������ı�����
    int m_iScore;//����
    int m_iScore2;//����
    //
    CSprite		*m_pKaishi;//��ʼj����
    CSprite		*m_pTitle;//��ʼj����
    CSprite		*m_pEndTitle;//��ʼj����
    CSprite		*m_pEnd;//��ʼj����
    CSprite		*m_pRed;//��ʼj����
    CSprite		*m_pBlack;//��ʼj����
    CTextSprite*    m_pCountdown;		//����ʱ�����־���
    CTextSprite*	 m_pDeltaTime; //����ʱ��Ϸ����ʱ����ı�����
    CSound* m_cSound;
    float m_fCountdown;
    float m_fCountPassedTime;
    float  m_fDeltaTime;//��ʾ��Ϸʱ��

public:
	CGameMain();            //���캯��
	~CGameMain();           //��������
    void LoadMap();
	// Get����
	int				GetGameState()											{ return m_iGameState; }

	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// ��Ϸ��ѭ����
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
    CWeapon* FindWeaponByName(const char* szName);//�������ֲ���
    void DeleteWeaponByName(const char* szName);//�������ְѾ����������ɾ��
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
