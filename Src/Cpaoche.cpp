#include "Cpaoche.h"
#include"LessonX.h"
Cpaoche::Cpaoche(const char* szName):CWeapon(szName) //对构造函数进行实现
{
    //ctor

	m_fSpeedX=0.f;
    m_iHp=2;
}
void Cpaoche::Init(int Owner)
{
				SetHp(2);
			SetSpriteCollisionActive(1,1);//设置为可以接受和bu发生碰撞
			SetSpriteVisible(true);
			SetOwner(Owner);
}
void Cpaoche::OnMove(int iKey, bool bPress,int m_iOwner)
{
	if(bPress)
		{   if(m_iOwner==0)
            {    switch (iKey)
                {
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
            if(m_iOwner==1)
            {   switch (iKey)
                {
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
			SetSpriteLinearVelocity(GetSpeedX(),0);
		}
}
