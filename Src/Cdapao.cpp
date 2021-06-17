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
			SetSpriteCollisionActive(0,0);//设置为bu可以接受和bu发生碰撞
			SetSpriteVisible(true);
			SetOwner(m_iOwner);
}
void Cdapao::OnMove(int iKey, bool bPress,int m_iOwner)
{   const float	fRotateSpeed = 5.f; 				//  摇摆速度，单位 度/秒
    float fThisRotate =	fRotateSpeed * PI; // 本次旋转的角度
	if(bPress)
		{   if(m_iOwner==0)
             {   switch(iKey)
                {
                case KEY_J:		//J向上
                    GunRotation-= fThisRotate ;
                    break;
                case KEY_K:		//K向下
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
                case KEY_1:		//J向上
                    GunRotation+= fThisRotate ;
                    break;
                case KEY_2:		//K向下
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
            SetSpriteRotation(GunRotation);	//设置炮筒的当前角度
            SetSpriteLinearVelocity(GetSpeedX(),0);

        }
}
void Cdapao::OnFire()
{
		x = GetSpriteLinkPointPosX(1);
		y = GetSpriteLinkPointPosY(1);
		g_GameMain.AddBullet(x,y,m_iOwner,GunRotation);
}


