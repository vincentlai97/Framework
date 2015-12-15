#ifndef MYVIEW_H
#define MYVIEW_H

#include "View_3D.h"

class MyView : public View_3D
{
public:
	MyView(Model *model);
	~MyView();

	virtual void Render();

private:
};

#endif