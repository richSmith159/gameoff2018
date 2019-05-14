#pragma once
#include "FractalScreen.h"
#include <Tempest\IMainGame.h>


class FractalViewer : public Tempest::IMainGame
{
public:
	FractalViewer();
	~FractalViewer();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:

	std::unique_ptr<FractalScreen> m_fractalScreen = nullptr;

};

