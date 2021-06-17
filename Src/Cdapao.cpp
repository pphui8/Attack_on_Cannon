#include "Cdapao.h"
#include"LessonX.h"
#define PI 3.141592653589793f
Cdapao::Cdapao(const char* szName):CWeapon(szName)
{
    //ctor
	m_fSpeedX=0.f;
    m_iHp=2;
}
void Cdapao::Init(int m_iOwner)
{
				SetHp(2);
			SetSpriteCollisionActive(0,0);//����Ϊbu���Խ��ܺ�bu������ײ
			SetSpriteVisible(true);
			SetOwner(m_iOwner);
}
void Cdapao::OnMove(int iKey, bool bPress,int m_iOwner)
{   const float	fRotateSpeed = 5.f; 				//  ҡ���ٶȣ���λ ��/��
    float fThisRotate =	fRotateSpeed * PI; // ������ת�ĽǶ�
	if(bPress)
		{   if(m_iOwner==0)
             {   switch(iKey)
                {
                case KEY_J:		//J����
                    GunRotation-= fThisRotate ;
                    break;
                case KEY_K:		//K����
                    GunRotation+= fThisRotate;
                    break;
                case KEY_A:
                        SetSpeedX(-15);
                        break;
                case KEY_D:
                        SetSpeedX(15);
                        break;
                case KEY_S:
                        SetSpeedX(0);
                        break;
                }
             }
             else if(m_iOwner==1)
             {  switch(iKey)
                {
                case KEY_1:		//J����
                    GunRotation+= fThisRotate ;
                    break;
                case KEY_2:		//K����
                    GunRotation-= fThisRotate;
                    break;
                case KEY_LEFT:
                            SetSpeedX(-15);
                            break;
                case KEY_RIGHT:
                            SetSpeedX(15);
                            break;
                case KEY_DOWN:
                        SetSpeedX(0);
                        break;
                }
             }
            SetSpriteRotation(GunRotation);	//������Ͳ�ĵ�ǰ�Ƕ�
            SetSpriteLinearVelocity(GetSpeedX(),0);

        }
}
void Cdapao::OnFire()
{
		x = GetSpriteLinkPointPosX(1);
		y = GetSpriteLinkPointPosY(1);
		g_GameMain.AddBullet(x,y,m_iOwner,GunRotation);
}


