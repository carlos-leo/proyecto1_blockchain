#ifndef __TRANSACCION_H
#define __TRANSACCION_H

#include <string>
#include "Utiles.h"

using namespace std;

class Transaccion
{
private:
	int id_tran;
	string emisor;
	string receptor;
	double monto;
	string fecha_tran;
	
public:

	Transaccion()
	{
		id_tran = 0;
		emisor = "";
		receptor = "";
		monto = 0.0;
		fecha_tran = "";
	}

	Transaccion(const string& _emisor, const string& _receptor, const double& _monto)
	{
		id_tran = 0;
		emisor = _emisor;
		receptor = _receptor;
		monto = _monto;
		fecha_tran = ObtieneFechaActual();
	}

	Transaccion(const int& _id, const string& _emisor, const string& _receptor, const double& _monto)
	{
		id_tran = _id;
		emisor = _emisor;
		receptor = _receptor;
		monto = _monto;
		fecha_tran = ObtieneFechaActual();
	}


	// Getters

	int getIdTran() const
	{
		return id_tran;
	}

	string getEmisor() const
	{
		return emisor;
	}

	string getReceptor() const
	{
		return receptor;
	}

	double getMonto() const
	{
		return monto;
	}

	string getFechaTran() const
	{
		return fecha_tran;
	}

	void SetIdTran(int _index) {
		this->id_tran = _index;
	}
};

#endif // !__TRANSACCION_H