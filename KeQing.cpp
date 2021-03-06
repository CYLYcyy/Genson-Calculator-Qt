﻿#include "KeQing.h"

KeQing::~KeQing()
{

}

KeQing::KeQing()
{
	Atk = 323;
	CriRate += 15;//大招
	CriDamage += 38.4;//突破
}

void KeQing::WP(int i)
{
	switch (i)
	{
	case 1://匣里龙吟
		Atk += 510;
		AtkBonusPer += 41.3;
		Inc += 20;
		break;
	case 2://天空
		Atk += 608;
		CriRate += 4;
		Atkspd += 10;
		break;
	case 3://风鹰剑
		Atk += 674;
		AtkBonusPer += 20;
		break;
	default:
		break;
	}
	wp = i;
}

void KeQing::R(int i)
{
	switch (i)
	{
	case 1://如雷2+角斗2
		Inc += 15;
		AtkBonusPer += 18;
		break;
	case 2://平雷
		Inc += 35;
		break;
	default:
		break;
	}
	r = i;
}

void KeQing::RM(int i)
{
	AtkBonusAdd += 311;//羽
	AtkBonusPer += 46.6;//沙
	switch (i)
	{
	case 1://雷/暴
		Inc += 46.6;
		CriRate += 31.1;
        Maxncr = 24;
		break;
	case 2://雷/暴伤
		Inc += 46.6;
		CriDamage += 62.2;
        Maxncd = 24;
		break;
	case 3://攻/暴
		AtkBonusPer += 46.6;
		CriRate += 31.1;
        Maxncr = 24;
		break;
	case 4://攻/爆伤
		AtkBonusPer += 46.6;
		CriDamage += 62.2;
        Maxncd = 24;
		break;
	default:
		break;
	}
	rm = i;
}

double KeQing::ExpD() const
{
	return Role::ExpD()*(1+Atkspd/100);
}

void KeQing::Resolve(int n)
{
	KeQing temp = KeQing(*this);
	int nn = n < 45 ? n : 45;
	for (int i = 0; i <= nn && i <= Maxnabp; i++)
	{
		for (int j = 0; j <= nn - i && i <= Maxnaba; j++)
		{
			for (int k = 0; k <= nn - i - j && i <= Maxncr; k++)
			{
				if (nn - i - j - k <= Maxncd)
				{
					Role* comp = new KeQing(temp);
					comp->Iabp(i)->Iaba(j)->Icr(k)->Icd(nn - i - j - k);
					compare(comp);
					delete comp;
				}
			}
		}
	}
}
