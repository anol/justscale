/*
 * primary_activity.h
 *
 *  Created on: 26. apr. 2016
 *      Author: Anders
 */

#ifndef primary_activity_h
#define primary_activity_h

class primary_activity {
public:
	primary_activity();
	virtual ~primary_activity();

public:
	void Initialize();
	void OnTick();
	void Diag();
	void Info();
	void SetX(int nValue);
	void SetY(int nValue);
	void SetZ(int nValue);
	void Intensity(int32_t nValue);
	void OnTrace();
	void Trace() {
		m_bTrace = ~m_bTrace;
	}

private:
	bool CheckInputs(int& rCount, bool bButton, bool bIndex) const;

private:
	aeo1::ssi_max7219 m_oDisplay_X;
	aeo1::ssi_max7219 m_oDisplay_Y;
	aeo1::ssi_max7219 m_oDisplay_Z;
	aeo1::qei_sensor m_oScale_X;
	aeo1::qei_sensor m_oScale_Y;
	int m_nPressedCount_X;
	int m_nPressedCount_Y;
	int m_nPressedCount_Z;
	bool m_bTrace;
	bool m_bIndex;
};

#endif /* primary_activity_h */
