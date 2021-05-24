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
	m_iGameState			=	1;
	zhunxin = new CSprite("zhunxin");
	dapao = new CSprite("dapao");
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
{
    CSystem::ShowCursor(false);
    m_iBombNum = 0;
    paodan_speed = 50.f;
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
    for(int i = 0; i < m_vPaodan.size(); ++i) {
        float speedY = m_vPaodan[i]->GetSpriteLinearVelocityY();
        m_vPaodan[i]->SetSpriteLinearVelocityY(speedY + 0.1);
    }
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
}
//===============================hhhhhhhhhjjk===========================================
//
// ����ƶ�
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{
    /*float fX = dapao->GetSpritePositionX();
	float fY = dapao->GetSpritePositionY();
	float  ftan =atan2((fMouseY-fY),(fMouseX-fX));	//���ʹ��ڵ������ߺ�X��ļн�
	float  fRotation=180*ftan/PI;		//	������ת��Ϊ�Ƕ�,�ڿں�X��������ļн�
    if(fRotation<0)
		fRotation+=360;
	if(fRotation>90 && fRotation<180)	//�����ڿڽǶ�
		fRotation = 90;
	else if(fRotation >= 180 && fRotation<270)	//�����ڿڽǶ�
		fRotation = 270;
	dapao->SetSpriteRotation(fRotation);
    zhunxin->SetSpritePosition(fMouseX,fMouseY);*/

}
//==========================================================================
//
// �����
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
    /*if(iMouseType == MOUSE_LEFT){	//����������
		float fPosX, fPosY;
		//��ô������ӵ�λ�ã���Ϊ�ڵ����
		fPosX = dapao->GetSpriteLinkPointPosX(1);
		fPosY = dapao->GetSpriteLinkPointPosY(1);
		char *szName;
		szName = CSystem::MakeSpriteName("paodan_%d", m_iBombNum++);	//�õ��ڵ�����
		CSprite* bomb = new CSprite(szName);
		bomb->CloneSprite("paodan_muban");		//�����ڵ�ģ��
		bomb->SetSpritePosition(fPosX, fPosY);
		bomb->SpriteMoveTo(fMouseX, fMouseY, 50, false);
		gunfire->PlayEffect(fPosX, fPosY, 0.f);	//������Ч
		m_vPaodan.push_back(bomb);		//���ڵ�ѹ��vector�м��й���
	}*/


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
// ���̵���
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
void CGameMain::OnKeyUp( const int iKey )
{

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

#include<math.h>
void CGameMain::Fire(int start_X, int start_Y, float idir)
{
		float fPosX, fPosY;
		float dire;
		float speed_x, speed_y;
		dire = dapao->GetSpriteRotation();
		//��ô������ӵ�λ�ã���Ϊ�ڵ����
		fPosX = dapao->GetSpriteLinkPointPosX(1);
		fPosY = dapao->GetSpriteLinkPointPosY(1);
		char *szName;
		szName = CSystem::MakeSpriteName("paodan_%d", m_iBombNum++);	//�õ��ڵ�����
		CSprite* bomb = new CSprite(szName);
		bomb->CloneSprite("paodan_muban");		//�����ڵ�ģ��
		bomb->SetSpritePosition(fPosX, fPosY);
		//
		speed_x = paodan_speed * cos(dire * M_PI /180);
		speed_y = paodan_speed * sin(dire * M_PI / 180);
		bomb->SetSpriteLinearVelocityX(30);
		bomb->SetSpriteLinearVelocityY(speed_y);
		//
		gunfire->PlayEffect(fPosX, fPosY, 0.f);	//������Ч
		m_vPaodan.push_back(bomb);		//���ڵ�ѹ��vector�м��й���
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
					szName = CSystem::MakeSpriteName("wall",j+i*13+i);//��������
					CSprite* pWall = new CSprite(szName); //�½�����
					pWall->CloneSprite("wall"); //��¡ǽ��
					pWall->SetSpriteCollisionActive(0,1); //����Ϊ������ײ
					pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
					x =float(-24+4*j);
					y =float(-20+4*i);
					pWall->SetSpritePosition(x,y);
				}
			}
		}
}
