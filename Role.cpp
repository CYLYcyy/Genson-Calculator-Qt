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
//暴击收益
double Role::CR() const
{
    if (CriRate < 100)
        return CriRate / 100 * CriDamage / 100;
    else
        return CriDamage / 100;
}
//增伤收益
double Role::DB() const
{
    return per / 100 * Inc / 100;
}
//精通收益(剧变反应需再乘以2.4)
double Role::SP() const
{
    return 25 * Mystery / (9 * (Mystery + 1400));
}

//伤害期望
double Role::ExpD() const
{
    return allAtk() * (1 + CR()) * (1 + DB());
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
        AtkBonusPer += 5.8;
        nabp++;
    }
    return this;
}

Role* Role::Iaba(int n)
{
    for (int i = 0; i < n; i++)
    {
        AtkBonusAdd += 19;
        naba++;
    }
    return this;
}

Role* Role::Icr(int n)
{
    for (int i = 0; i < n; i++)
    {
        CriRate += 3.9;
        ncr++;
    }
    return this;
}

Role* Role::Icd(int n)
{
    for (int i = 0; i < n; i++)
    {
        CriDamage += 7.8;
        ncd++;
    }
    return this;
}

//最佳属性求解,n为有效副属性点数
void Role::Resolve(int n)
{
    Role temp = Role(*this);
    int nn = n < 45 ? n : 45;
    for (int i = 0; i <= nn && i <= Maxnabp; i++)
    {
        for (int j = 0; j <= nn - i && i <= Maxnaba; j++)
        {
            for (int k = 0; k <= nn - i - j && i <= Maxncr; k++)
            {
                if (nn - i - j - k <= Maxncd)
                {
                    Role* comp = new Role(temp);
                    comp->Iabp(i)->Iaba(j)->Icr(k)->Icd(nn - i - j - k);
                    compare(comp);
                    delete comp;
                }
            }
        }
    }
}
