
#ifndef ssi_max7219_h
#define ssi_max7219_h
//--------------------------------
#include "ssi_peripheral.h"
//--------------------------------
namespace aeo1 {
//--------------------------------
class ssi_max7219: public ssi_peripheral {

public:
	ssi_max7219(ssi_peripheral::device_id nDevice);
	virtual ~ssi_max7219();

public:
	void Initialize();
	void Diag();
	void Set(int32_t nValue, int nDecimals = 0);
	void Set(const char* zString);
	void OnTx() {
		LoadTxFIFO();
	}

private:

private:

};
//--------------------------------
} /* namespace aeo1 */
//--------------------------------
#endif /* ssi_max7219_h */
