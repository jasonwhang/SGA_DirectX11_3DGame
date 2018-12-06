#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
	: position(0,0,0)
	, forward(0,0,1)
	, up(0,1,0)
	, right(1,0,0)
{
	// �׵���ķ� ����� �ʱ�ȭ���ش�.
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	// LH : Left Hand(�޼���ǥ��)
	// At : ���� �ٶ󺸰� �ִ� ����
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
		zn, // z�� near(����� �� ����� z��)
		zf // z�� far(�� �� ����� z��)
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
