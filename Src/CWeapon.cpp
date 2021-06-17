#include "CWeapon.h"

CWeapon::CWeapon(const char *szName):CSprite(szName)
{
    //ctor
    m_fSpeedX=0.f;
	m_iHp=2;
}

CWeapon::~CWeapon()
{
    //dtor
}
   //set
    void CWeapon::SetHp(int hp)									             {m_iHp = hp;}
	void CWeapon::SetSpeedX(float speedX)    						{m_fSpeedX = speedX;}
	void CWeapon::SetOwner(int Owner) {m_iOwner=Owner;}
	//get
	int CWeapon::GetHp()                   										{return m_iHp;}
	float CWeapon::GetSpeedX()            								{return m_fSpeedX;}
    int CWeapon::GetOwner() {return m_iOwner;}
    //
    void CWeapon::OnMove(float fPosX,float fPosY,int m_iOwner,float GunRotation){}
    void CWeapon::OnMove(int iKey, bool bPress,int m_iOwner){}
   void CWeapon::Init(int m_iOwner){}
