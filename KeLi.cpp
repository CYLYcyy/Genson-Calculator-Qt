#include "KeLi.h"

KeLi::~KeLi()
{

}

double KeLi::AE() const
{
	if (r == 1)
		return 0.15;
	else
		return 0;
}

KeLi::KeLi()
{
	Atk = 311;
	Inc += 28.8;//突破火伤
}

void KeLi::WP(int i)
{
	switch (i)
	{
	case 1://四风原典
		Atk += 608;
		CriRate += 33.1;
		Inc += 32;
		break;
	case 2://天空之卷
		Atk += 674;
		AtkBonusPer += 33.1;
		Inc += 12;
		break;
	case 3://流浪乐章1
		Atk += 510;
		CriDamage += 55.1;
		AtkBonusPer += 60;
		break;
	case 4://流浪乐章2
		Atk += 510;
		CriDamage += 55.1;
		Inc += 48;
		break;
	case 5://流浪乐章3
		Atk += 510;
		CriDamage += 55.1;
		Mystery += 200;
		break;
	default:
		break;
	}
	wp = i;
}

void KeLi::R(int i)
{
	switch (i)
	{
	case 1://魔女
		Inc += 30;
		//BP+=15;
		break;
	case 2://渡火
		Inc += 35;
		break;
	default:
		break;
	}
	r = i;
}

void KeLi::RM(int i)
{
	AtkBonusAdd += 311;//羽
	AtkBonusPer += 46.6;//沙
	switch (i)
	{
	case 1://火/暴
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

double KeLi::ExpD() const
{
	double allatk = allAtk();
	double cr = CR();
	double db = DB();
	double sp = SP();
	double ae = AE();
	return allAtk() * (1 + CR()) * (1 + DB()) * (1+SP()+AE()) * 2.0;//全打融化
}

void KeLi::Resolve(int n)
{
	KeLi temp = KeLi(*this);
	int nn = n < 45 ? n : 45;
	for (int i = 0; i <= nn && i <= Maxnabp; i++)
	{
		for (int j = 0; j <= nn - i && i <= Maxnaba; j++)
		{
			for (int k = 0; k <= nn - i - j && i <= Maxncr; k++)
			{
				if (nn - i - j - k <= Maxncd)
				{
					Role* comp = new KeLi(temp);
					comp->Iabp(i)->Iaba(j)->Icr(k)->Icd(nn - i - j - k);
					compare(comp);
					delete comp;
				}
			}
		}
	}
}
