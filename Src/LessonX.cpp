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
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain()
{    //
    m_pKaishi = new CSprite("kaishi");
    m_pTitle = new CSprite("title");
    m_cSound=new CSound("kaipao.ogg",false,1);//12964.wav

    //
    m_pCountdown = new CTextSprite("countdown");//ʱ���ı�
	m_fCountdown = 0.f;
	//
    m_pDeltaTime = new CTextSprite("time");//ʱ���ı�
	m_fDeltaTime = 0.f;
    //
	m_iGameState			=	1;
	gunfire = new CEffect("gunfire","",0.2);
	m_pScore = new CTextSprite("score");//�����ı�
	m_iScore=0;//����
	//
	m_pScore2 = new CTextSprite("score2");//�����ı�
	m_iScore2=0;//����
	//
	m_pEndTitle=new CSprite("endtitle");
	m_pEnd=new CSprite("end");
	m_pRed=new CSprite("bred");
	m_pBlack=new CSprite("black");
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
    case 3:
	case 4:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if(  m_fDeltaTime>0 )
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
    CSystem::ShowCursor(false);//ָ��������
    m_pEndTitle->SetSpriteVisible(false);
    m_pEnd->SetSpriteVisible(false);
    m_pRed->SetSpriteVisible(false);
    m_pBlack->SetSpriteVisible(false);
     //
    //
    m_ppaoche=new Cpaoche("paoche");//�½�һ���������ڳ����ҷ��ڳ�����
    m_ppaoche->CloneSprite("paoche");
    m_ppaoche->SetSpritePosition(-40.f,19.5f);//����λ��
    m_ppaoche->SetSpriteWorldLimit(WORLD_LIMIT_STICKY, -49, 13.4, -10, 27);//�߽�����
    m_ppaoche->Init(0);
    m_vWeapon.push_back(m_ppaoche);
    //
    m_ppaoche2=new Cpaoche("paoche2");//�½�һ��������paoche2���ҷ��ڳ�����
    m_ppaoche2->CloneSprite("paoche2");
    m_ppaoche2->SetSpritePosition(40.f,19.5f);
    m_ppaoche2->SetSpriteWorldLimit(WORLD_LIMIT_STICKY, 10, 10, 48, 25);
    m_ppaoche2->Init(1);
    m_vWeapon.push_back(m_ppaoche2);
    //
    m_pdapao=new Cdapao("dapao");//�½�һ��������dapao����
    m_pdapao->CloneSprite("dapao");
     m_pdapao->SetSpritePosition(-41.f,19.f);
     m_pdapao->SetSpriteWorldLimit(WORLD_LIMIT_STICKY, -50, 10, -11, 25);
     m_pdapao->Init(0);
     m_vWeapon.push_back(m_pdapao);
     //
    m_pdapao2=new Cdapao("dapao2");//�½�һ��������myPlayer���ҷ�̹�˶���
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
    m_fCountdown = 5;		//����ʱʱ��Ϊ5s
    m_fCountPassedTime=0.f;
    m_pCountdown->SetSpriteVisible(false);		//���õ���ʱ���ɼ�
    //
    m_fDeltaTime = 30.f;//���õ���ʱ��ʱ��
    m_pDeltaTime->SetSpriteVisible(false);
    //
    m_iScore = 0;//���1��paoche�ķ���
    m_pScore->SetSpriteVisible(false);
    //
    m_iScore2 = 0;//���2��paoche2�ķ���
    m_pScore2->SetSpriteVisible(false);
    //
    m_iBombNum = 0;//�ڵ�����
    LoadMap();
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{    //
    if(m_iGameState==3)
    {	//m_iGameState Ϊ3ʱ��ִ��
		m_fCountPassedTime += fDeltaTime;	//ͳ�ƾ�����ʱ�䣬���洢��countPassedTime
        m_pCountdown->SetTextValue(m_fCountdown -m_fCountPassedTime);
		if(m_fCountPassedTime >= m_fCountdown){	//������ʱ�䳬��countdownTime
			m_pCountdown->SetSpriteVisible(false);	//����countdown
			m_fCountPassedTime = 0;		//���þ�����ʱ�䣬Ϊ��һ����Ϸ��׼��
			m_iGameState = 4;		//�л�g_iGameState 3->4
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
// ������Ϸ����
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
{
    if( KEY_SPACE == iKey && m_iGameState==2 )	//���¿ո�����Ϸ״̬Ϊ2ʱ
    {   m_iGameState =	3;	//������Ϸ״̬���뵹��ʱ����3
		m_pCountdown->SetSpriteVisible(true);	//��ʾ����ʱ�ı���
		m_pKaishi->SetSpriteVisible(false);		//���ء��ո�ʼ��
	}
	else if(m_iGameState==4)
    {      m_ppaoche->OnMove(iKey,true,0);
            m_ppaoche2->OnMove(iKey,true,1);
            m_pdapao->OnMove(iKey,true,0);
            m_pdapao2->OnMove(iKey,true,1);
            if(iKey == KEY_L)//�жϰ��¼��ǹ�ΪJ��
                {
                    m_pdapao->OnFire();
                }
            else if(iKey == KEY_3)//�жϰ��¼��ǹ�ΪJ��
                {
                    m_pdapao2->OnFire();
                }
    }
}
//==========================================================================
//
// ���̵���a
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
void CGameMain::OnKeyUp( const int iKey )
{
}
void CGameMain::OnMove(int iKey, bool bPress)
{

}

//===========================================================================
//
// �����뾫����ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
    CWeapon* tarSprite = FindWeaponByName(szTarName);
	if(strcmp(szSrcName,"paoche")==0) //������ײΪ�ҷ�̹��
	{
        if(strstr(szTarName,"bomb")!=NULL)//������ײΪ�ӵ�strstr(abc,ab)
        {   m_iScore2++;
            DeleteWeaponByName(szTarName);
        }
	}
	if(strcmp(szSrcName,"paoche2")==0)//������ײΪ�з�̹��
	{
        if(strstr(szTarName,"paodan") !=NULL)//������ײΪ�ӵ�
        {   m_iScore++;
            DeleteWeaponByName(szTarName);
        }
	}

}
//===========================================================================
//
// ����������߽���ײ
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
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
					szName = CSystem::MakeSpriteName("wall_%d",j+i*13+i);//��������
					CWeapon* pWall = new CWeapon(szName);
					pWall->CloneSprite("wall"); //��¡ǽ��
					pWall->SetSpriteCollisionActive(0,0); //����Ϊ������ײ
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
		{szName = CSystem::MakeSpriteName("paodan",m_iBombNum++);}//����paodan����
		else if(m_iOwner==1)
        {szName = CSystem::MakeSpriteName("bomb",m_iBombNum++);}//����paodan����m_iBombNum++
		CWeapon* pBullet = new Cbomb(szName);
		pBullet->CloneSprite("paodan_muban");
		pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL,-26, -22, 26, 22); //��������߽�
		pBullet->SetSpriteCollisionActive(0,1); //���÷���������
		pBullet->OnMove(fPosX,fPosY,m_iOwner,GunRotation);
        gunfire->PlayEffect(fPosX, fPosY, 0.f);	//������Ч
         m_cSound->PlaySound();//game/data/audio/
		if(m_iOwner == 1)
		{
			pBullet->SetOwner(1);//1��ʾd̹�˷�����ӵ�
		}
		else
		{
			pBullet->SetOwner(0); //0��ʾw̹�˷�����ӵ�
		}
		m_vWeapon.push_back(pBullet);		//���ڵ�ѹ��vector�м��й���
}
CWeapon* CGameMain::FindWeaponByName(const char* szName)//�������ֲ��ҵ�����
{
	for(int i=0; i<m_vWeapon.size(); i++)
	{
			if(strcmp(szName,m_vWeapon[i]->GetName()) == 0)
			{
				return m_vWeapon[i];
			}
	}
}
void CGameMain::DeleteWeaponByName(const char* szName)//�������ְѾ����������ɾ��
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

