#ifndef CPAOCHE_H
#define CPAOCHE_H
#include<CommonClass.h>
#include<CWeapon.h>
class Cpaoche : public CWeapon
{
    public:
        Cpaoche(const char* szName);
        virtual void Init(int m_iOwner);
    virtual void OnMove(int iKey, bool bPress,int m_iOwner);

    protected:

    private:

};

#endif // CPAOCHE_H
