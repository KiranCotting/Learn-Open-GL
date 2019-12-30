#pragma once
#include "Vector.h"
#include "Matrix.h"
class Camera {
private:
	Matrix view;
	Matrix projection;
public:
	/// <summary> Get the view matrix for this camera. </summary>
	Matrix getView() const;

	/// <summary> Get the projection matrix for this camera. </summary>
	Matrix getProjection() const;

	/// <summary> Initialize the projection matrix to an orthographic one. </summary>
	/// <param name="left"> The left bound of the projection. </param>
	/// <param name="right"> The right bound of the projection. </param>
	/// <param name="bottom"> The bottom bound of the projection. </param>
	/// <param name="top"> The top bound of the projection. </param>
	/// <param name="near"> The near bound of the projection. </param>
	/// <param name="far"> The far bound of the projection. </param>
	Matrix ortho(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far);

	/// <summary> Initialize the projection matrix to a perspective one. </summary>
	/// <param name="left"> The left bound of the projection. </param>
	/// <param name="right"> The right bound of the projection. </param>
	/// <param name="bottom"> The bottom bound of the projection. </param>
	/// <param name="top"> The top bound of the projection. </param>
	/// <param name="near"> The near bound of the projection. </param>
	/// <param name="far"> The far bound of the projection. </param>
	Matrix frustum(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far);
	
	/// <summary> Initialize the view matrix to look at a point. </summary>
	/// <param name="position"> The position of the camera. </param>
	/// <param name="target"> The position the camera is looking at. </param>
	/// <param name="vup"> The upward direction of the camera, for orientation. </param>
	Matrix lookAt(const Vector& position, const Vector& target, const Vector& vup);

	/// <summary> Initialize the view matrix to look in a direction. </summary>
	/// <param name="position"> The position of the camera. </param>
	/// <param name="vnormal"> The direction the camera is facing. </param>
	/// <param name="vup"> The upward direction of the camera, for orientation. </param>
	Matrix viewPoint(const Vector& position, const Vector& vnormal, const Vector& vup);
};