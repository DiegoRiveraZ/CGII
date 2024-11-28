#pragma once



#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <iostream>
#include <fstream>


using namespace std;

struct coordenadas {
	float x;
	float y;

	coordenadas* siguiente;
};

coordenadas *nodo = NULL;


coordenadas* recorrer() {

	

	if (nodo == NULL) {
		return NULL;

	}

	else {
		coordenadas* recorre = nodo;
		while (recorre->siguiente != NULL){
			recorre = recorre->siguiente;

		}
		return recorre;
	}


}

void agregar_coordenadas(float X, float Y) {

	coordenadas* nuevo = nodo;
	

	if (nodo == NULL) {
		nuevo = new coordenadas;
		nuevo->x = X;
		nuevo->y = Y;
		nuevo->siguiente = NULL;
		nodo = nuevo;
		
	}
	else {



		nuevo = new coordenadas;
		nuevo->x = X;
		nuevo->y = Y;
		nuevo->siguiente = NULL;
		

		recorrer()->siguiente = nuevo;
		
	}
}

void escribir_archivo()
{
	int i = 1;
	float EX = -255.25;
	float EY = -255.25;
	// Create and open a text file
	ofstream MyFile("coordenadas.txt");


	if (nodo == NULL) {
		MyFile.close();

	}

	else {
		coordenadas* recorre = nodo;
		while (recorre->siguiente != NULL) {
			if(EX !=recorre->x && EY != recorre->y){
				MyFile << i << ".- (" << recorre->x << ", " << recorre->y << " )" << endl;
				EX = recorre->x;
				EY = recorre->y;
				
				i++; 
			}
			recorre = recorre->siguiente;
		}
		
	}

	// Close the file
	MyFile.close();
	
}



//Normaliza un vector 2
D3DXVECTOR2 nomralizeVec2(D3DXVECTOR2 VecToNormalize)
{

	float v = sqrt((VecToNormalize.x * VecToNormalize.x) + (VecToNormalize.y * VecToNormalize.y) + 0);

	VecToNormalize.x = VecToNormalize.x / v;
	VecToNormalize.y = VecToNormalize.y / v;
	
	return VecToNormalize;
}


//calcula el angulo hacia donde se mueve un objeto. para que vea hacia donde se mueve
float AngleofVectorT(D3DXVECTOR2 VecToAngle)
{

	return atan2(VecToAngle.x, VecToAngle.y) * 180.0f / 3.1416;;
}


//El objeto que define hacia donde deben de ir las coordenasas de la pista.
class RaceCoords {
private:

	D3DXVECTOR2 puntos[37];

	int selector = 0;


public:
	  
	RaceCoords() {

	}

	//las coordenadsa de los puntos hacia donde debe de ir el carro en la pista.

	void rellenar() {

		puntos[0] = D3DXVECTOR2(23.2602, -20.6736);
		puntos[1] = D3DXVECTOR2(68.6586, -20.3832);
		puntos[2] = D3DXVECTOR2(73.6272, -19.8252);
		puntos[3] = D3DXVECTOR2(79.9257, -18.1575);
		puntos[4] = D3DXVECTOR2(82.909, -4.14951);
		puntos[5] = D3DXVECTOR2(83.8502, 2.20306);
		puntos[6] = D3DXVECTOR2(101.39, 3.63957);
		puntos[7] = D3DXVECTOR2(107.16, 6.21434);
		puntos[8] = D3DXVECTOR2(106.708, 18.4558);
		puntos[9] = D3DXVECTOR2(104.787, 22.6905);
		puntos[10] = D3DXVECTOR2(103.028, 26.9805);
		puntos[11] = D3DXVECTOR2(90.0945, 27.6181);
		puntos[12] = D3DXVECTOR2(85.1706, 29.1348);
		puntos[13] = D3DXVECTOR2(82.8765, 46.1051);
		puntos[14] = D3DXVECTOR2(75.5482, 51.824);
		puntos[15] = D3DXVECTOR2(64.6552, 50.1858);
		puntos[16] = D3DXVECTOR2(62.0334, 2.56001);
		puntos[17] = D3DXVECTOR2(59.9795, -4.52882);
		puntos[18] = D3DXVECTOR2(56.1053, -7.25111);
		puntos[19] = D3DXVECTOR2(35.6617, -7.45482);
		puntos[20] = D3DXVECTOR2(30.0139, -6.71532);
		puntos[21] = D3DXVECTOR2(24.4336, -4.73922);
		puntos[22] = D3DXVECTOR2(23.0478, 10.0596);
		puntos[23] = D3DXVECTOR2(25.4669, 15.6823);
		puntos[24] = D3DXVECTOR2(43.5712, 18.8534);
		puntos[25] = D3DXVECTOR2(47.7069, 20.0516);
		puntos[26] = D3DXVECTOR2(47.4722, 49.2458);
		puntos[27] = D3DXVECTOR2(46.3125, 56.0999);
		puntos[28] = D3DXVECTOR2(31.5686, 55.8292);
		puntos[29] = D3DXVECTOR2(24.0354, 54.0818);
		puntos[30] = D3DXVECTOR2(23.254, 41.8191);
		puntos[31] = D3DXVECTOR2(22.9695, 33.6497);
		puntos[32] = D3DXVECTOR2(3.09866, 32.1715);
		puntos[33] = D3DXVECTOR2(-1.72648, 28.1964);
		puntos[34] = D3DXVECTOR2(-1.32253, -12.7508);
		puntos[35] = D3DXVECTOR2(-0.914822, -19.7274);
		puntos[36] = D3DXVECTOR2(11.0379, -20.6017);

	};

	D3DXVECTOR2 get_punto(int ubicacion) {
		return puntos[ubicacion];

	}
	int get_array_size() {
		return sizeof(puntos) / sizeof(puntos[0]);
	}

	D3DXVECTOR2 get_selector_punto() {
		return puntos[selector];
	}


	void get_checkpoint(D3DXVECTOR2 inVec) {


		int trheshold = 1;
		D3DXVECTOR2 comparator;

		int puntoX, puntoY;

		puntoX = get_punto(selector).x;
		puntoY = get_punto(selector).y;

		comparator.x = fabs(fabs(puntoX) - fabs(inVec.x));
		comparator.y = fabs(fabs(puntoY) - fabs(inVec.y));

		
		
		if (selector > 36) {
			selector = 0;
		}



		if (comparator.x < trheshold && comparator.y < trheshold) {
			selector++;
			
			std::cout << inVec.x<<" --- " << inVec.y;
		}




	}

};


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


	}

public:
	
	void set_rectangle(float width, float height, float depth) {

		this->width = width / 2;
		this->height = height / 2;
		this->depth = depth / 2;

		set_points();

	}

	rectangle_ add_position(float X, float Y, float Z) {

	}


};


class rectangle_colision {

private:

	D3DXVECTOR3 P1,P2,P3,P4,P5,P6,P7,P8;

	D3DXVECTOR3 translation;
	D3DXMATRIX object_matrix;

	float width,height, depth;

	void set_points() {

	

		P1 = D3DXVECTOR3(-width, -height, -depth);
		P2 = D3DXVECTOR3(width, -height, 0);
		P3 = D3DXVECTOR3(0, -height, depth);
		P4 = D3DXVECTOR3(width, -height, depth);

		P5 = D3DXVECTOR3(-width, height, -depth);
		P6 = D3DXVECTOR3(width, height, 0);
		P7 = D3DXVECTOR3(0, height, depth);
		P8 = D3DXVECTOR3(width, height, depth);


	}

	float return_area() {

		return (width * 2) * (height * 2) * (depth * 2);


	}


public:


	void set_rectangle(float width,float height,float depth) {

		this->width = width/2;
		this->height = height/2;
		this->depth = depth/2;

		set_points();

	}

	void set_matrix(float X, float Y,float Z) {


		D3DXMatrixTranslation(&object_matrix, X, Y, Z);

	}

	void set_position(float X, float Y, float Z) {
		

		translation = D3DXVECTOR3(X, Y, Z);
	}

	void set_position(D3DXVECTOR3 in) {


		translation = in;
	}

	D3DXVECTOR3 get_position() {
		return translation;
	}
	
	void set_position_points(D3DXVECTOR3 position) {
		P1 = P1 + position;
		P2 = P2 + position;
		P3 = P3 + position;
		P4 = P4 + position;

		P5 = P5 + position;
		P6 = P6 + position;
		P7 = P7 + position;
		P8 = P8 + position;
	}

};


