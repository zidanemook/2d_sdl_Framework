/*!
 * \class CProgram
 *
 * \brief 
 *	涝仿贸府
 *	概聪历 包府
 *	
 *
 * \author mook
 * \date 7岿 2018
 */

#ifndef CProgram_h
#define CProgram_h

#include "BaseMode.h"

class CProgram : public CBase
{
private:
	explicit CProgram();
	~CProgram();

public:
	static CProgram* Create();
	inline virtual void Free(void);
public:

	void Init();

	void HandleEvents();
	void Update();
	bool IsRunning();

private:
	bool m_bIsRunning;

};

#endif