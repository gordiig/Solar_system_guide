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

    virtual void exec(Camera&) = 0;
};


class DxCom : public InterfaceCommand
{
public:
    DxCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(Camera&) override;
};

class DyCom : public InterfaceCommand
{
public:
    DyCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(Camera&) override;
};

class DzCom : public InterfaceCommand
{
public:
    DzCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(Camera&) override;
};

class DxAngCom : public InterfaceCommand
{
public:
    DxAngCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(Camera&) override;
};

class DyAngCom : public InterfaceCommand
{
public:
    DyAngCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(Camera&) override;
};

class DzAngCom : public InterfaceCommand
{
public:
    DzAngCom(double in) : InterfaceCommand::InterfaceCommand(in) { }
    virtual void exec(Camera&) override;
};

#endif // COMCAPSULE_H
