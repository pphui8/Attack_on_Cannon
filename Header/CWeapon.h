#ifndef CWEAPON_H
#define CWEAPON_H

#include <CommonClass.h>


class CWeapon : public CSprite
{
    public:
        CWeapon(const char *szName);
        virtual ~CWeapon();
       //set
	void SetHp(int hp);
	void SetSpeedX(float speedX) ;
	void SetOwner(int Owner);
	//get
	int GetHp();
	float GetSpeedX();
	int GetOwner();
	//
    virtual void Init(int m_iOwner);
    virtual void OnMove(int iKey, bool bPress,int m_iOwner);
    virtual void OnMove(float fPosX,float fPosY,int m_iOwner,float GunRotation);
     float m_fSpeedX;int m_iHp;int m_iOwner;
    protected:

    private:
};

#endif // CWEAPON_H
