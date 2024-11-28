#pragma once




#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <iostream>
#include <fstream>



struct rectangle_ {


private:

	float width, height, depth;
	D3DXVECTOR3 P1, P2, P3, P4, P5, P6, P7, P8;



	void set_points() {



		P1 = D3DXVECTOR3(-width, -height, -depth);
		P2 = D3DXVECTOR3(width, -height, 0);
		P3 = D3DXVECTOR3(0, -height, depth);
		P4 = D3DXVECTOR3(width, -height, depth);

		P5 = D3DXVECTOR3(-width, height, -depth);
		P6 = D3DXVECTOR3(width, height, 0);
		P7 = D3DXVECTOR3(0, height, depth);
		P8 = D3DXVECTOR3(width, height, depth);

		m_vecMax = D3DXVECTOR3(width, height, depth);
		m_vecMin = D3DXVECTOR3(-width, -height, -depth);


	}

public:

	D3DXVECTOR3 m_vecMax, m_vecMin;

	rectangle_() {

	};

	rectangle_(float width, float height, float depth) {


		set_rectangle(width, height, depth);

	};

	void set_rectangle(float width, float height, float depth) {

		this->width = width / 2;
		this->height = height / 2;
		this->depth = depth / 2;

		set_points();

	}

	rectangle_ add_position(float X, float Y, float Z) {

	}


	rectangle_ operator+(D3DXVECTOR3 const& obj)
	{
		rectangle_ res;
		res.P1 = P1 + obj;
		res.P2 = P2 + obj;
		res.P3 = P3 + obj;
		res.P4 = P4 + obj;

		res.P5 = P5 + obj;
		res.P6 = P6 + obj;
		res.P7 = P7 + obj;
		res.P8 = P8 + obj;

		res.m_vecMax = m_vecMax + obj;
		res.m_vecMin = m_vecMin + obj;


		return res;



		return res;

	}

	rectangle_ operator+(rectangle_ const& obj)
	{
		rectangle_ res;
		res.P1 = P1 + obj.P1;
		res.P2 = P2 + obj.P2;
		res.P3 = P3 + obj.P3;
		res.P4 = P4 + obj.P4;

		res.P5 = P5 + obj.P5;
		res.P6 = P6 + obj.P6;
		res.P7 = P7 + obj.P7;
		res.P8 = P8 + obj.P8;

		res.m_vecMax = m_vecMax + obj.m_vecMax;
		res.m_vecMin = m_vecMin + obj.m_vecMin;
		return res;





	}

	rectangle_ operator*(float m)
	{
		rectangle_ res;
		res.P1 = P1 * m;
		res.P2 = P2 * m;
		res.P3 = P3 * m;
		res.P4 = P4 * m;

		res.P5 = P5 * m;
		res.P6 = P6 * m;
		res.P7 = P7 * m;
		res.P8 = P8 * m;

		res.m_vecMax = m_vecMax * m;
		res.m_vecMin = m_vecMin * m;
		return res;
	}

	rectangle_ operator/(float m)
	{
		rectangle_ res;
		res.P1 = P1 / m;
		res.P2 = P2 / m;
		res.P3 = P3 / m;
		res.P4 = P4 / m;

		res.P5 = P5 / m;
		res.P6 = P6 / m;
		res.P7 = P7 / m;
		res.P8 = P8 / m;

		res.m_vecMax = m_vecMax / m;
		res.m_vecMin = m_vecMin / m;

		return res;
	}

	void print() {
		std::cout << "" << std::endl;
		std::cout << "P1(" << P1.x << ", " << P1.y << ", " << P1.z << ")" << std::endl;
		std::cout << "P2(" << P2.x << ", " << P2.y << ", " << P2.z << ")" << std::endl;
		std::cout << "P3(" << P3.x << ", " << P3.y << ", " << P3.z << ")" << std::endl;
		std::cout << "P4(" << P4.x << ", " << P4.y << ", " << P4.z << ")" << std::endl;

		std::cout << "P5(" << P5.x << ", " << P5.y << ", " << P5.z << ")" << std::endl;
		std::cout << "P6(" << P6.x << ", " << P6.y << ", " << P6.z << ")" << std::endl;
		std::cout << "P7(" << P7.x << ", " << P7.y << ", " << P7.z << ")" << std::endl;
		std::cout << "P8(" << P8.x << ", " << P8.y << ", " << P8.z << ")" << std::endl;

	}

	void printMinMax() {
		std::cout << "" << std::endl;
		std::cout << "Min(" << m_vecMin.x << ", " << m_vecMin.y << ", " << m_vecMin.z << ")" << std::endl;
		std::cout << "Max(" << m_vecMax.x << ", " << m_vecMax.y << ", " << m_vecMax.z << ")" << std::endl;


	}

};


class rectangle_colision {

private:

	D3DXVECTOR3 translation;
	D3DXMATRIX object_matrix;
	rectangle_ rectangulo;

public:


	rectangle_colision() {

	}

	void init_rectangle(float a, float b, float c) {

		rectangulo.set_rectangle(a, b, c);
	}

	void set_matrix() {


		D3DXMatrixTranslation(&object_matrix, translation.x, translation.y, translation.z);

	}

	void set_position(float X, float Y, float Z) {


		translation = D3DXVECTOR3(X, Y, Z);
	}
	

	void set_position(D3DXVECTOR3 translation) {


		this->translation = translation;
	}

	D3DXVECTOR3 get_position() {
		return translation;
	}

	rectangle_ return_translated_position() {


		return rectangulo + translation;

	};

	rectangle_ return_rectangle() {
		return rectangulo;
	}



	bool check_colision(rectangle_colision& ColRect) {


		if (
			return_translated_position().m_vecMax.x > ColRect.return_translated_position().m_vecMin.x &&
			return_translated_position().m_vecMin.x < ColRect.return_translated_position().m_vecMax.x &&
			return_translated_position().m_vecMax.y > ColRect.return_translated_position().m_vecMin.y &&
			return_translated_position().m_vecMin.y < ColRect.return_translated_position().m_vecMax.y &&
			return_translated_position().m_vecMax.z > ColRect.return_translated_position().m_vecMin.z &&
			return_translated_position().m_vecMin.z < ColRect.return_translated_position().m_vecMax.z)
		{
			return true;
		}
		else {
			return false;
		}


	}


	//void set_position_points(D3DXVECTOR3 position) {
	//	P1 = P1 + position;
	//	P2 = P2 + position;
	//	P3 = P3 + position;
	//	P4 = P4 + position;

	//	P5 = P5 + position;
	//	P6 = P6 + position;
	//	P7 = P7 + position;
	//	P8 = P8 + position;
	//}

};


