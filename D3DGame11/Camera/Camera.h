#pragma once

class Camera
{
public:
	Camera();
	virtual ~Camera();

	const D3DXVECTOR3& GetPosition() const { return position; }
	const D3DXMATRIX& GetViewMatrix() const { return view; }
	const D3DXMATRIX& GetProjecttionMatrix() const { return projection; }

	void SetOrthographicLH
	(
		const float& w,
		const float& h,
		const float& zn,
		const float& zf
	);

	void SetOrthographicOffCenterLH
	(
		const float& l,
		const float& r,
		const float& b,
		const float& t,
		const float& zn,
		const float& zf
	);

private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 forward; // (0,0,1) -> Z축 방향으로의 기저백터
	D3DXVECTOR3 up; // (0,1,0) -> Y축 방향으로의 기저백터
	D3DXVECTOR3 right; // (1,0,0) -> X축 방향으로의 기저백터
	D3DXMATRIX view;
	D3DXMATRIX projection;
};