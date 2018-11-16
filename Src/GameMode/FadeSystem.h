#pragma once


enum eFadeStage
{
	eFadeStage_In,
	eFadeStage_Out,
	eFadeStage_Max
};

class CFadeSystem
{
private:
	static CFadeSystem*		m_pInst;

public:
	static CFadeSystem* GetInst(void)
	{
		if(m_pInst == nullptr)
			m_pInst = new CFadeSystem;

		return m_pInst;
	}

	void DestroyInst(void)
	{
		delete m_pInst;
		m_pInst = nullptr;
	}


public:
	CFadeSystem();
	~CFadeSystem();


	bool Create();
	void Destroy();
	void Initialize();
	void OnRender();

	void StartFade(eFadeStage eFadeType, double fFadeTime = 1.0f );
	bool IsPlaying() { return m_bPlay; }

private:
	eFadeStage m_eFadeType;
	bool m_bPlay;
	double m_fTotalTime;
	double m_fCurrentTime;
	float m_fCurrentAlpha;
};

#define FadeSystem CFadeSystem::GetInst()