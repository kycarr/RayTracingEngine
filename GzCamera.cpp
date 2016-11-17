#include "stdafx.h"
#include "GzCamera.h"

GzCamera::GzCamera() : position(0.0f, 0.0f, 0.0f), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), right(1.0f, 0.0f, 0.0f), fovScale(1.0f)
{
}
