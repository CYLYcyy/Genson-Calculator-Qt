#ifndef Role_H
#define Role_H

class Role
{
public:
    Role()
        :Atk(0), AtkBonusPer(0), AtkBonusAdd(0), Inc(0), per(100), CriRate(5), CriDamage(50){}
    //攻击力,攻击力百分比,攻击力数值,属伤加成,属伤占比,暴击率,暴击伤害
    Role(double a, double abp, double aba, double i, double p, double cr, double cd)
        :Atk(a), AtkBonusPer(abp), AtkBonusAdd(aba), Inc(i), per(p), CriRate(cr), CriDamage(cd){}
    virtual ~Role();

    virtual void WP(int i);//武器选择
    virtual void R(int i);//套装选择
    virtual void RM(int i);//主属性选择

    //总面板攻击
    virtual double allAtk() const;
    //暴击收益
    virtual double CR() const;
    //增伤收益
    virtual double DB() const;
    //精通收益(剧变反应需再乘以2.4)
    virtual double SP() const;
    //伤害期望
    virtual double ExpD() const;

    //直接替换为更优;
    virtual void compare(Role* compare);

    //最佳属性求解,n为有效副属性点数
    virtual void Resolve(int n);

    Role* Iabp(int n);
    Role* Iaba(int n);
    Role* Icr(int n);
    Role* Icd(int n);

    double Atk;//基础攻击
    double AtkBonusPer;//基础攻击加成%
    double AtkBonusAdd;//攻击力提高(死之羽,班尼特,食物)
    double Inc;//增伤%
    double per;//被增伤占比%(若物理角色全打物伤,属性角色全打属伤,则收益为100)
    double CriRate;//暴击率(双冰,岩主大招,食物)
    double CriDamage;//暴击伤害

    double Mystery = 0;//元素精通
    double Atkspd = 0;//攻速加成

    int nabp = 0;//攻击百分比条数
    int naba = 0;//攻击数值条数
    int ncr = 0;//暴击率条数
    int ncd = 0;//暴击伤害条数

    int Maxnabp = 24;//最大攻击百分比条数
    int Maxnaba = 24;//最大攻击数值条数
    int Maxncr = 30;//最大暴击率条数
    int Maxncd = 30;//最大暴击伤害条数

    int wp=0;
    int r=0;
    int rm=0;
};
#endif// Role_H
