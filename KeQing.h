#pragma once
#include"Role.h"

class Role;
class KeQing :public Role
{
public:
	KeQing();
    virtual void WP(int i) override;//武器选择
    virtual void R(int i) override;//套装选择
    virtual void RM(int i) override;//主属性选择
    virtual void Resolve(int n) override;
    virtual ~KeQing();
};
