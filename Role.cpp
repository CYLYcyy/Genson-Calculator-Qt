#include "Role.h"

Role::~Role()
{

}

void Role::WP(int i)
{
    wp = i;
}

void Role::R(int i)
{
    r = i;
}

void Role::RM(int i)
{
    AtkBonusAdd += 311;//羽
    AtkBonusPer += 46.6;//沙
    rm = i;
}

//总面板攻击
double Role::allAtk() const
{
    return (Atk * (1 + AtkBonusPer / 100) + AtkBonusAdd);
}

//伤害期望
double Role::ExpD() const
{
    if (CriRate < 100)
        return (Atk * (1 + AtkBonusPer / 100) + AtkBonusAdd) * (1 + per / 100 * Inc / 100) * (1 + CriRate / 100 * CriDamage / 100);
    else
        return (Atk * (1 + AtkBonusPer / 100) + AtkBonusAdd) * (1 + per / 100 * Inc / 100) * (1 + CriDamage / 100);
}


//直接替换为更优;
void Role::compare(Role* compare)
{
    if (compare->ExpD() > ExpD())
    {
        *this = *compare;
    }
}

Role* Role::Iabp(int n)
{

    for (int i = 0; i < n; i++)
    {
        AtkBonusPer += 4.975;
        nabp++;
    }
    return this;
}

Role* Role::Iaba(int n)
{
    for (int i = 0; i < n; i++)
    {
        AtkBonusAdd += 17;
        naba++;
    }
    return this;
}

Role* Role::Icr(int n)
{
    for (int i = 0; i < n; i++)
    {
        CriRate += 3.3;
        ncr++;
    }
    return this;
}

Role* Role::Icd(int n)
{
    for (int i = 0; i < n; i++)
    {
        CriDamage += 6.6;
        ncd++;
    }
    return this;
}

//最佳属性求解,n为有效副属性点数
void Role::Resolve(int n)
{
    Role temp = Role(*this);
    int nn = n < 45 ? n : 45;
    for (int i = 0; i <= nn &&i<=Maxnabp; i++)
    {
        for (int j = 0; j <= nn - i && i <= Maxnaba; j++)
        {
            for (int k = 0; k <= nn - i - j && i <= Maxncr; k++)
            {
                if (nn - i - j - k <= Maxncd)
                {
                    Role* comp=new Role(temp);
                    comp->Iabp(i)->Iaba(j)->Icr(k)->Icd(nn - i - j - k);
                    compare(comp);
                    delete comp;
                }
            }
        }
    }
}
