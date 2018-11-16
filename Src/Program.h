/*!
 * \class CProgram
 *
 * \brief 
 *	�Է�ó��
 *	�Ŵ��� ����
 *	
 *
 * \author mook
 * \date 7�� 2018
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