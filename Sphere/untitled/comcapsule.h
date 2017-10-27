#ifndef COMCAPSULE_H
#define COMCAPSULE_H

#include "err.h"
#include "obj.h"

class InterfaceCommand
{
protected:
    double var;

public:
    InterfaceCommand() : var(0) {}
    InterfaceCommand(double in) : var(in) {}
    virtual ~InterfaceCommand() {}

    virtual void exec(BaseObject&) = 0;
};


class DxCom : public InterfaceCommand
{
public:
    DxCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(BaseObject&) override;
};

class DyCom : public InterfaceCommand
{
public:
    DyCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(BaseObject&) override;
};

class DzCom : public InterfaceCommand
{
public:
    DzCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(BaseObject&) override;
};

class DxAngCom : public InterfaceCommand
{
public:
    DxAngCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(BaseObject&) override;
};

class DyAngCom : public InterfaceCommand
{
public:
    DyAngCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(BaseObject&) override;
};

class DzAngCom : public InterfaceCommand
{
public:
    DzAngCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(BaseObject&) override;
};



class PlanetDxCom : public InterfaceCommand
{
public:
    PlanetDxCom() : InterfaceCommand::InterfaceCommand() { }
    virtual void exec(BaseObject&) override;
};

class PlanetDyCom : public InterfaceCommand
{
public:
    PlanetDyCom() : InterfaceCommand::InterfaceCommand() { }
    virtual void exec(BaseObject&) override;
};

class PlanetDzCom : public InterfaceCommand
{
public:
    PlanetDzCom() : InterfaceCommand::InterfaceCommand() { }
    virtual void exec(BaseObject&) override;
};

class PlanetDxAngCom : public InterfaceCommand
{
public:
    PlanetDxAngCom() : InterfaceCommand::InterfaceCommand() { }
    virtual void exec(BaseObject&) override;
};

class PlanetDyAngCom : public InterfaceCommand
{
public:
    PlanetDyAngCom() : InterfaceCommand::InterfaceCommand() { }
    virtual void exec(BaseObject&) override;
};

class PlanetDzAngCom : public InterfaceCommand
{
public:
    PlanetDzAngCom() : InterfaceCommand::InterfaceCommand() { }
    virtual void exec(BaseObject&) override;
};

#endif // COMCAPSULE_H
