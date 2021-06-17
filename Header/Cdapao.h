#ifndef CDAPAO_H
#define CDAPAO_H
#include<CommonClass.h>
#include<CWeapon.h>
class Cdapao : public CWeapon
{
    public:
    Cdapao(const char* szName);
    virtual void Init(int m_iOwner);
    virtual void OnMove(int iKey, bool bPress,int m_iOwner);
    void OnFire();
    protected:

    private:
         float x,y;float	GunRotation;		//炮筒同地面的夹角*******
};

#endif // CDAPAO_H
