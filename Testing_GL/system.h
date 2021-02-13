#pragma once


template <class T>
T* CreateObjectComponent()
{
	return new T;
}