#pragma once
#include"Role.h"

class Role;
class KeLi :public Role
{
public:
	KeLi();
    virtual void WP(int i) override;//武器选择
    virtual void R(int i) override;//套装选择
    virtual void RM(int i) override;//主属性选择

    virtual double ExpD() const override;
    virtual void Resolve(int n) override;
    virtual ~KeLi();
    
    double AE() const;
};
