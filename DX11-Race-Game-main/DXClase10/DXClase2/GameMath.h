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

void deleteList(coordenadas* curr) {

	// Base case: If the list is empty, return
	if (curr == nullptr) {
		return;
	}

	// Recursively delete the next node
	deleteList(curr->siguiente);

	// Delete the current node
	delete curr;
}


float clamp(float &clamped,float min, float max) {


	if (clamped > max) {
		clamped = max;
	}

	if (clamped < min) {
		clamped = min;
	}

	return clamped;
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

	D3DXVECTOR2 puntos[54];

	int selector = 0;


public:
	  
	RaceCoords() {

	}

	//las coordenadsa de los puntos hacia donde debe de ir el carro en la pista.

	void rellenar() {

		puntos[0]  =  D3DXVECTOR2(231.856, 293.321);
		puntos[1]  =  D3DXVECTOR2(235.866, 274.226);
		puntos[2]  =  D3DXVECTOR2(242.822, 262.504);
		puntos[3]  =  D3DXVECTOR2(239.579, 247.309);
		puntos[4]  =  D3DXVECTOR2(233.398, 244.663);
		puntos[5]  =  D3DXVECTOR2(221.309, 241.961);
		puntos[6]  =  D3DXVECTOR2(208.236, 238.036);
		puntos[7]  =  D3DXVECTOR2(198.998, 226.525);
		puntos[8]  =  D3DXVECTOR2(181.834, 185.524);
		puntos[9]  =  D3DXVECTOR2(178.399, 167.072);
		
		puntos[10]  =  D3DXVECTOR2(177.493, 151.417);
		puntos[11]  =  D3DXVECTOR2(181.639, 143.218);
		puntos[12]  =  D3DXVECTOR2(190.338, 134.553);
		puntos[13]  =  D3DXVECTOR2(200.914, 126.229);
		puntos[14]  =  D3DXVECTOR2(219.802, 117.479);
		puntos[15]  =  D3DXVECTOR2(235.329, 111.665);

		puntos[16]  =  D3DXVECTOR2(242.89, 108.252) ;
		puntos[17]  =  D3DXVECTOR2(247.825, 103.078);
		puntos[18]  =  D3DXVECTOR2(245.085, 95.6535);
		puntos[19]  =  D3DXVECTOR2(239.679, 83.5263);
		puntos[20]  =  D3DXVECTOR2(237.487, 74.7529);

		puntos[21]  =  D3DXVECTOR2(245.549, 62.8816);
		puntos[22]  =  D3DXVECTOR2(260.456, 60.4258);
		puntos[23]  =  D3DXVECTOR2(269.559, 65.5682);
		puntos[24]  =  D3DXVECTOR2(275.975, 74.045) ;
		puntos[25]  =  D3DXVECTOR2(274.841, 82.8916);

		puntos[26]  =  D3DXVECTOR2(271.209, 91.0526);
		puntos[27]  =  D3DXVECTOR2(268.62, 99.4299) ;
		puntos[28]  =  D3DXVECTOR2(266.778, 108.889);
		puntos[29]  =  D3DXVECTOR2(268.451, 118.613);
		puntos[30]  =  D3DXVECTOR2(297.197, 181.076);

		puntos[31]  =  D3DXVECTOR2(311.219, 204.398);
		puntos[32]  =  D3DXVECTOR2(319.789, 224.143);
		puntos[33]  =  D3DXVECTOR2(315.882, 237.842);
		puntos[34]  =  D3DXVECTOR2(305.44, 252.916) ;
		puntos[35]  =  D3DXVECTOR2(302.446, 268.332);

		puntos[36]  =  D3DXVECTOR2(309.559, 286.308);
		puntos[37]  =  D3DXVECTOR2(321.319, 307.742);
		puntos[38]  =  D3DXVECTOR2(331.505, 327.63) ;
		puntos[39]  =  D3DXVECTOR2(340.778, 342.959);
		puntos[40]  =  D3DXVECTOR2(349.86, 359.939) ;

		puntos[41]  =  D3DXVECTOR2(348.951, 371.073);
		puntos[42]  =  D3DXVECTOR2(337.652, 382.864);
		puntos[43]  =  D3DXVECTOR2(325.052, 387.921);
		puntos[44]  =  D3DXVECTOR2(312.146, 388.411);
		puntos[45]  =  D3DXVECTOR2(305.306, 381.222);

		puntos[46]  =  D3DXVECTOR2(289.252, 341.532);
		puntos[47]  =  D3DXVECTOR2(281.986, 331.95) ;
		puntos[48]  =  D3DXVECTOR2(273.688, 327.332);
		puntos[49]  =  D3DXVECTOR2(260.06, 328.541) ;
		puntos[50]  =  D3DXVECTOR2(249.818, 328.82) ;

		puntos[51]  =  D3DXVECTOR2(242.873, 321.745);
		puntos[52]  =  D3DXVECTOR2(237.577, 313.093);
		puntos[53]  =  D3DXVECTOR2(234.209, 302.751);


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

		
		
		if (selector > 53) {
			selector = 0;
		}



		if (comparator.x < trheshold && comparator.y < trheshold) {
			selector++;
			
			std::cout << inVec.x<<" --- " << inVec.y;
		}




	}

};
