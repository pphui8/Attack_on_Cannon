#ifndef  CBOMB_H
#define  CBOMB_H
#include <CommonClass.h>
#include<CWeapon.h>

class  Cbomb : public CWeapon
{
    public:
         Cbomb(const char* szName);
         virtual void OnMove(float fPosX,float fPosY,int m_iOwner,float GunRotation);
    protected:

    private:
        float		GunRotation;		//炮筒同地面的夹角*******
         float fThisRotate;
};

#endif //  CBOMB_H
