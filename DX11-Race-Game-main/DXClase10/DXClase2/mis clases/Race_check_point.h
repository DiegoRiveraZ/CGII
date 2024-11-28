#pragma once


#include <GameMath.h>
#include <colision_math.h>


#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <iostream>
#include <fstream>


class race_check_point {

private:

	/*
	(42.9201, -20.3594)
	(100.94, 3.57478)
	(81.1081, 51.4746)
	(62.2656, 8.78733)
	(22.2431, 8.38955)
	(35.0577, 56.3332)
	(19.5873, 33.9504)
	(2.98123, 3.28955)
	(16.523, -20.2937)
	*/


	rectangle_colision CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9;
	bool colisiones[9] = { false,false,false,false,false,false,false,false,false };
	bool checkpoints[9] = { false,false,false,false,false,false,false,false,false };

	bool ganar;

	int vueltas = 0;
	int max_vueltas = 2;

public:

	void init_race() {
		CH1.init_rectangle(4, 4, 4);
		CH2.init_rectangle(4, 4, 4);
		CH3.init_rectangle(4, 4, 4);
		CH4.init_rectangle(4, 4, 4);
		CH5.init_rectangle(4, 4, 4);
		CH6.init_rectangle(4, 4, 4);
		CH7.init_rectangle(4, 4, 4);
		CH8.init_rectangle(4, 4, 4);
		CH9.init_rectangle(4, 4, 4);
		
		CH1.set_position(D3DXVECTOR3(42.9201, 0,-20.3594));
		CH2.set_position(D3DXVECTOR3(100.94, 0,  3.57478));
		CH3.set_position(D3DXVECTOR3(81.1081, 0, 51.4746));
		CH4.set_position(D3DXVECTOR3(62.2656, 0, 8.78733));
		CH5.set_position(D3DXVECTOR3(22.2431, 0, 8.38955));
		CH6.set_position(D3DXVECTOR3(35.0577, 0, 56.3332));
		CH7.set_position(D3DXVECTOR3(19.5873, 0, 33.9504));
		CH8.set_position(D3DXVECTOR3(2.98123, 0, 3.28955));
		CH9.set_position(D3DXVECTOR3(16.523, 0, -20.2937));

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


		if (colisiones[0]) {
			checkpoints[0] = true;
		}

		for (int i = 1; i < 8; i++) {

			if (colisiones[0]) {
				checkpoints[0] = true;
			}
			else {
				if (colisiones[i] && checkpoints[i - 1]) {
					checkpoints[i] = true;
				}
			}
		}
	


		if (checkpoints[8]) {
			if (vueltas < max_vueltas) {
				vueltas++;
			}
			else {
				ganar = true;
			}
		}
	}


};