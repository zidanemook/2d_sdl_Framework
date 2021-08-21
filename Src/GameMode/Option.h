/*!
 * \class COption
 *
 *
 *
 * \brief
 *
 * TODO: long description
 *
 * \note
 *
 * \author mook
 *
 * \version 1.0
 *
 * \date 08¿ù 2021
 *
 *
 *
 */

#pragma once
#include "BaseMode.h"

class COption : public CBaseMode
{
private:
	explicit COption();
	~COption();

public:
	static COption* Create();
	inline virtual void Free(void);

	void Init();
	virtual void Update();
	virtual void Open();
	virtual void Close();
	virtual void Closed();

private:


};

