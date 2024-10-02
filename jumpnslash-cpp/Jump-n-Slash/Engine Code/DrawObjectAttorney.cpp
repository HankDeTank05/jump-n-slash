#include "DrawObjectAttorney.h"

#include "DrawObject.h"

void DrawObjectAttorney::GameLoop::Draw(DrawObject* pDrawable)
{
	pDrawable->Draw();
}

void DrawObjectAttorney::Registration::Register(DrawObject* pDrawable)
{
	pDrawable->Register();
}

void DrawObjectAttorney::Registration::Deregister(DrawObject* pDrawable)
{
	pDrawable->Deregister();
}
