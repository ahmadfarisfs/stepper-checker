#include "binder.h"
#include "manager.h"
StepperTesterManager *CallBinder::m_man;
void CallBinder::setManObj(StepperTesterManager *man)
{
    CallBinder::m_man = man;
}
void CallBinder::onStartLeft()
{
    CallBinder::m_man->onStartMotor(Data::MotorDirection_e::Forward);
};
void CallBinder::onStartRight()
{
    CallBinder::m_man->onStartMotor(Data::MotorDirection_e::Reverse);
};
void CallBinder::onStopMotor()
{
    CallBinder::m_man->onStopMotor();
};
void CallBinder::onPlusOne()
{
    CallBinder::m_man->onChangeVars(1);
};
void CallBinder::onPlusTen()
{
    CallBinder::m_man->onChangeVars(10);
};
void CallBinder::onMinusOne()
{
    CallBinder::m_man->onChangeVars(-1);
};
void CallBinder::onMinusTen()
{
    CallBinder::m_man->onChangeVars(-10);
};
void CallBinder::onEnter()
{
    CallBinder::m_man->onEnter();
};
void CallBinder::onSave()
{
    CallBinder::m_man->onSave();
};