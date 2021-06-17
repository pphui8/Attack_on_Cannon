#include "Cbomb.h"
#include <CommonClass.h>
 Cbomb:: Cbomb(const char* szName):CWeapon(szName) //对构造函数进行实现
{
    //ctor
}
void Cbomb::OnMove(float fPosX,float fPosY,int m_iOwner,float GunRotation)
{       const float g_fBumbForceY  =  10.f;
        SetSpritePosition(fPosX, fPosY);
        if(m_iOwner==0)
        {
            SetSpriteLinearVelocityPolar( 75, GunRotation);
        }
        else if(m_iOwner==1)
         {SetSpriteLinearVelocityPolar( -75, GunRotation);}
        SetSpriteConstantForceY( g_fBumbForceY );
}
