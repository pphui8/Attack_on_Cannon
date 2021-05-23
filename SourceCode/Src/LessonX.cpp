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
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain()
{
	m_iGameState			=	0;
	dapao = new CSprite("dapao");
	paoche = new CSprite("paoche");
	gunfire = new CEffect("gunfire","",0.2);
}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{   CSystem::ShowCursor(false);
    m_iBombNum = 0;
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
}
//==========================================================================
//
// ����ƶ�
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// �����
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// ��굯��
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// ���̰���
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{   float fSpeedLeft = 0,fSpeedRight = 0,fSpeedup = 0;
	switch(iKey)
	{
	case KEY_A:		//A����
		fSpeedLeft = -15.f;
		break;
	case KEY_D:		//D����
		fSpeedRight = 15.f;
		break;
	}
	if((fSpeedLeft + fSpeedRight) > 0)	//���������Ҫת��
		{
		paoche->SetSpriteFlipX(false);}
	else if((fSpeedLeft + fSpeedRight) < 0)	//���������ת��
		{
		paoche->SetSpriteFlipX(true);}
	dapao->SetSpriteLinearVelocity(fSpeedLeft + fSpeedRight, fSpeedup);
	paoche->SetSpriteLinearVelocity(fSpeedLeft + fSpeedRight, fSpeedup);
	//**********************************************
	const float	fRotateSpeed = 5.f; 				//  ҡ���ٶȣ���λ ��/��
	float fThisRotate =	fRotateSpeed * PI; // ������ת�ĽǶ�
	switch(iKey)
	{
	case KEY_J:		//J����
        GunRotation+= fThisRotate ;
		break;
	case KEY_K:		//K����
		GunRotation-= fThisRotate;
		break;
	}
	dapao->SetSpriteRotation(GunRotation);	//������Ͳ�ĵ�ǰ�Ƕ�
	//*******************************
    if(iKey == KEY_L){	//����L������
		float fPosX, fPosY;
		//��ô������ӵ�λ�ã���Ϊ�ڵ����
		fPosX = dapao->GetSpriteLinkPointPosX(1);
		fPosY = dapao->GetSpriteLinkPointPosY(1);
		char *szName;
		szName = CSystem::MakeSpriteName("paodan_%d", m_iBombNum++);	//�õ��ڵ�����
		CSprite* bomb = new CSprite(szName);
		bomb->CloneSprite("paodan_muban");		//�����ڵ�ģ��
		bomb->SetSpritePosition(fPosX, fPosY);
		bomb->SpriteMoveTo(10, -10, 50, false);
		gunfire->PlayEffect(fPosX, fPosY, 0.f);	//������Ч
		m_vPaodan.push_back(bomb);		//���ڵ�ѹ��vector�м��й���
	}

}
//==========================================================================
//
// ���̵���a
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
void CGameMain::OnKeyUp( const int iKey )
{
    if( iKey == KEY_A  || iKey == KEY_D)
		dapao->SetSpriteLinearVelocity(0,0);
		paoche->SetSpriteLinearVelocity(0,0);

}
//===========================================================================
//
// �����뾫����ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{

}
//===========================================================================
//
// ����������߽���ײ
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{

}

