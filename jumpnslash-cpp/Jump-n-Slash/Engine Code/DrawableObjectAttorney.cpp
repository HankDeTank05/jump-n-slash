#include "DrawableObjectAttorney.h"

#include "DrawableObject.h"

void DrawableObjectAttorney::GameLoop::Draw(DrawableObject* pDrawable)
{
	pDrawable->Draw();
}

void DrawableObjectAttorney::Registration::Register(DrawableObject* pDrawable)
{
	pDrawable->Register();
}
