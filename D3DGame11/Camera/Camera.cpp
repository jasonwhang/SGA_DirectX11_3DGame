#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
	: position(0,0,0)
	, forward(0,0,1)
	, up(0,1,0)
	, right(1,0,0)
{
	// 항등행렬로 행렬을 초기화해준다.
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	// LH : Left Hand(왼손좌표계)
	// At : 내가 바라보고 있는 방향
	D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);
}

Camera::~Camera()
{
}

void Camera::SetOrthographicLH(const float & w, const float & h, const float & zn, const float & zf)
{
	D3DXMatrixOrthoLH
	(
		&projection,
		w, // width
		h, // height
		zn, // z축 near(가까운 뷰 평면의 z값)
		zf // z축 far(먼 뷰 평면의 z값)
	);
}

void Camera::SetOrthographicOffCenterLH(const float & l, const float & r, const float & b, const float & t, const float & zn, const float & zf)
{
	D3DXMatrixOrthoOffCenterLH
	(
		&projection,
		l,
		r,
		b,
		t,
		zn,
		zf
	);
}
