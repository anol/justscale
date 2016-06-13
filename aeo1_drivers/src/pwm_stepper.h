/*
 * pwm_stepper.h
 *
 *  Created on: 27. mar. 2015
 *      Author: anol
 */
//--------------------------------
#ifndef SRC_PWM_STEPPER_H_
#define SRC_PWM_STEPPER_H_
//--------------------------------
#include "driverlib/pwm.h"
//--------------------------------
namespace aeo1 {
class pwm_stepper {
private:
	enum {
		Base = PWM1_BASE,
		Generator = PWM_GEN_1,
		Default_StartSpeed = 16000,
		Default_TargetSpeed = 4000,
		Default_Acceleration = 10
	};
	enum Phase {
		Phase_Idle,
		Phase_Accel,
		Phase_Steady,
		Phase_Decel,
		Phase_Stop,
		Phase_Halt
	};

public:
	pwm_stepper();
	virtual ~pwm_stepper();
	void Initialize();
	void Diag();
	void Direction( bool bForward );
	void Move(uint32_t nSteps);
	void Stop(bool bHard);
	void OnInterrupt();
	uint32_t Get(const char* zName);
	int Get(const char* zName, uint32_t& rFieldValue);
	int Set(const char* zName, uint32_t nFieldValue);

private:
	int32_t m_nRelativeSteps;
	int32_t m_nSteps;
	int32_t m_nSpeed;
	int32_t m_nStartSpeed;
	int32_t m_nTargetSpeed;
	int32_t m_nAcceleration;
	int32_t m_nDeceleration;
	Phase m_nPhase;
	bool m_bDirectionForward;
};
} /* namespace aeo1 */
//--------------------------------
#endif /* SRC_PWM_STEPPER_H_ */
//--------------------------------
