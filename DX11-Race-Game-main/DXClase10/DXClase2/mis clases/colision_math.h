#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <iostream>
#include <fstream>



struct rectangle_ {


private:

	float width, height, depth;
	


	void set_points() {



		P1 = D3DXVECTOR3(-width, -height, -depth);
		P2 = D3DXVECTOR3(width, -height, -depth);
		P3 = D3DXVECTOR3(-width, -height, depth);
		P4 = D3DXVECTOR3(width, -height, depth);

		P5 = D3DXVECTOR3(-width, height, -depth);
		P6 = D3DXVECTOR3(width, height, -depth);
		P7 = D3DXVECTOR3(-width, height, depth);
		P8 = D3DXVECTOR3(width, height, depth);

		m_vecMax = D3DXVECTOR3(width, height, depth);
		m_vecMin = D3DXVECTOR3(-width, -height, -depth);


	}

public:
	D3DXVECTOR3 P1, P2, P3, P4, P5, P6, P7, P8;


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



class race_check_point {

private:

	/*
	1.- (241.98, 259.289 )
	2.- (196.759, 221.593 )
	3.- (183.185, 145.018 )
	4.- (244.419, 108.743 )
	5.- (271.999, 71.6695 )
	6.- (277.91, 134.729 )
	7.- (315.982, 238.758 )
	8.- (349.653, 360.639 )
	9.- (306.356, 381.943 )
	10.- (273.519, 330.56 )
	11.- (236.286, 304.801 )

	*/


	rectangle_colision CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9,CH10,CH11;
	bool colisiones[11] = { false,false,false,false,false,false,false,false,false,false,false };
	
	

	int vueltas = 0;
	int max_vueltas = 2;

	


public:
	bool checkpoints[11] = { false,false,false,false,false,false,false,false,false,false,false };
	bool ganar=false;
	void init_race() {

		CH1.init_rectangle(4, 20, 4);
		CH2.init_rectangle(4, 20, 4);
		CH3.init_rectangle(4, 20, 4);
		CH4.init_rectangle(4, 20, 4);
		CH5.init_rectangle(4, 20, 4);
		CH6.init_rectangle(4, 20, 4);
		CH7.init_rectangle(4, 20, 4);
		CH8.init_rectangle(4, 20, 4);
		CH9.init_rectangle(4, 20, 4);
		CH10.init_rectangle(4, 20, 4);
		CH11.init_rectangle(4, 20, 4);

		CH1.set_position(D3DXVECTOR3(241.98,2, 259.289));
		CH2.set_position(D3DXVECTOR3(196.759,2, 221.593));
		CH3.set_position(D3DXVECTOR3(183.185, 2, 145.018));
		CH4.set_position(D3DXVECTOR3(244.419, 2, 108.743));
		CH5.set_position(D3DXVECTOR3(271.999, 2, 71.6695));
		CH6.set_position(D3DXVECTOR3(277.91, 2, 134.729));
		CH7.set_position(D3DXVECTOR3(315.982, 2, 238.758));
		CH8.set_position(D3DXVECTOR3(349.653, 2, 360.639));
		CH9.set_position(D3DXVECTOR3(306.356, 2, 381.943));
		CH10.set_position(D3DXVECTOR3(273.519, 2, 330.56));
		CH11.set_position(D3DXVECTOR3(236.286, 2, 304.801));

	}


	void set_vueltas(int set) {
		max_vueltas = set;
	}

	void set_ganar(bool set) {
		ganar = set;
	}

	bool get_colisiones() {
		return colisiones;
	}

	void check(rectangle_colision& in) {

		colisiones[0] = CH1.check_colision(in);
		colisiones[1] = CH2.check_colision(in);
		colisiones[2] = CH3.check_colision(in);
		colisiones[3] = CH4.check_colision(in);
		colisiones[4] = CH5.check_colision(in);
		colisiones[5] = CH6.check_colision(in);
		colisiones[6] = CH7.check_colision(in);
		colisiones[7] = CH8.check_colision(in);
		colisiones[8] = CH9.check_colision(in);
		colisiones[9] = CH10.check_colision(in);
		colisiones[10] = CH11.check_colision(in);

		

		for (int i = 1; i < 11; i++) {

			if (colisiones[0]) {
				checkpoints[0] = true;
			}
			else {
				if (colisiones[i] && checkpoints[i - 1]) {
					checkpoints[i] = true;
				}
			}
		}



		if (checkpoints[10]) {
			if (vueltas <= max_vueltas) {
				
				become_false();
				vueltas++;
			}
			else {
				ganar = true;
			}
		}
	}

	void become_false() {
		for (int i = 0; i < 11; i++) {
			checkpoints[i] = false;
		};
	}
	
	int return_vueltas() {
		return vueltas;
	}

	void print() {

	}

};
