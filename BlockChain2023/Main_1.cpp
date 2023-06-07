#include "BlockChain.h"
#include "Transaccion.h"

int main(int argc, char* argv[]) {

	CBlockChain<CBlock<Transaccion>> Cadena;

	//1.Agregar Bloque

	CBlock<Transaccion> bloque1;
	bloque1.NuevaTransaccion(Transaccion("Ana", "Beto", 41.005));
	bloque1.NuevaTransaccion(Transaccion("Carla", "Diego", 69.126));
	bloque1.NuevaTransaccion(Transaccion("Eva", "Faby", 148.25));
	bloque1.NuevaTransaccion(Transaccion("Gino", "Hugo", 126.789));
	bloque1.NuevaTransaccion(Transaccion("Iris", "Juan", 56.456));
	Cadena.InsertarBloque(bloque1);

	CBlock<Transaccion> bloque2;
	bloque2.NuevaTransaccion(Transaccion("karla", "Lily", 28.005));
	bloque2.NuevaTransaccion(Transaccion("Nancy", "Mario", 69.126));
	bloque2.NuevaTransaccion(Transaccion("Oscar", "Pedro", 147.25));
	bloque2.NuevaTransaccion(Transaccion("Qiwi", "Rosa", 896.789));
	bloque2.NuevaTransaccion(Transaccion("Sandro", "Tito", 1055.456));
	Cadena.InsertarBloque(bloque2);

	CBlock<Transaccion> bloque3;
	bloque3.NuevaTransaccion(Transaccion("karla", "Lily", 28.005));
	bloque3.NuevaTransaccion(Transaccion("Nancy", "Mario", 69.126));
	bloque3.NuevaTransaccion(Transaccion("Oscar", "Pedro", 147.25));
	bloque3.NuevaTransaccion(Transaccion("Qiwi", "Rosa", 896.789));
	bloque3.NuevaTransaccion(Transaccion("Sandro", "Tito", 1055.456));
	Cadena.InsertarBloque(bloque3);


	CBlock<Transaccion> bloque4;
	bloque4.NuevaTransaccion(Transaccion("karla", "Lily", 28.125));
	bloque4.NuevaTransaccion(Transaccion("Nancy", "Mario", 69.126));
	bloque4.NuevaTransaccion(Transaccion("Oscar", "Pedro", 147.25));
	bloque4.NuevaTransaccion(Transaccion("Qiwi", "Rosa", 896.789));
	bloque4.NuevaTransaccion(Transaccion("Sandro", "Tito", 1055.456));
	Cadena.InsertarBloque(bloque4);

	CBlock<Transaccion> bloque5;
	bloque5.NuevaTransaccion(Transaccion("karla", "Lily", 28.005));
	bloque5.NuevaTransaccion(Transaccion("Nancy", "Mario", 69.226));
	bloque5.NuevaTransaccion(Transaccion("Oscar", "Pedro", 147.25));
	bloque5.NuevaTransaccion(Transaccion("Qiwi", "Rosa", 896.779));
	bloque5.NuevaTransaccion(Transaccion("Sandro", "Tito", 1055.456));
	Cadena.InsertarBloque(bloque5);

	CBlock<Transaccion> bloque6;
	bloque6.NuevaTransaccion(Transaccion("karla", "Lily", 28.00235));
	bloque6.NuevaTransaccion(Transaccion("Nancy", "Mario", 3269.126));
	bloque6.NuevaTransaccion(Transaccion("Oscar", "Pedro", 14327.25));
	bloque6.NuevaTransaccion(Transaccion("Qiwi", "Rosa", 89326.789));
	bloque6.NuevaTransaccion(Transaccion("Sandro", "Tito", 103255.456));
	Cadena.InsertarBloque(bloque6);


	//2. Modificar Bloque

	//2.1 Agregar Transaccion

	//CBlock<Transaccion> bloque = Cadena.BuscarBloque(1);
	//bloque.NuevaTransaccion(Transaccion("ccccc", "qqqq", 3.5));
	//Cadena.ModificarBloque(bloque);
	//bloque = Cadena.BuscarBloque(1);
	//Cadena.VisualizarBloque(bloque);


	//2.2 Modificar Transaccion

	//cout << endl << "Prueba Modificando Transacciones del bloque 1" << endl << endl;
	//CBlock<Transaccion> bloque = Cadena.BuscarBloque(1);
	//bloque.ModificarTransaccion(Transaccion(3, "aaaa", "bbbbb", 128.00235));
	//bloque.ModificarTransaccion(Transaccion(5, "yyyyyy", "zzzzz", 25.123));
	//Cadena.ModificarBloque(bloque); // incluye recalculo de hash de los siguientes bloques


	//2.3 Eliminar Transaccion
	CBlock<Transaccion> bloque = Cadena.BuscarBloque(1);
	bloque.EliminarTransaccion(3);
	bloque.EliminarTransaccion(5);
	Cadena.ModificarBloque(bloque);
	bloque = Cadena.BuscarBloque(1);
	Cadena.VisualizarBloque(bloque);


	//6. Visualizar (Bloque y Cadena)

		//bloque = Cadena.BuscarBloque(1);
		//Cadena.VisualizarBloque(bloque);

	Cadena.VisualizarCadena();

	system("pause");
	return 0;
}