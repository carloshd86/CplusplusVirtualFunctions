// Practica15CarlosHD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "File.h"
#include "FileNoStream.h"


int main()
{
	CFile * file_temp = nullptr;
	CFileNoStream * file_no_stream_temp = nullptr;


	/********************************************/


	// •	¿Cuánto espacio ocupa la tabla de funciones virtuales?
	// El tamaño del puntero multiplicado por el número de funciones virtuales de la base
	// En este caso sería 4 bytes * 4 funciones = 16 bytes.
	// - Se adjunta captura de de watch (practica_15_01_captura_tabla_funciones_virtuales.jpg)

	//•	¿Dónde está situada la tabla de funciones virtuales?
	//  - En una zona de memoria protegida. Si intentamos escribir en ella, dará error.
	// 1 - Los primeros 4 bytes asignados a la instancia de CFile corresponden al puntero a la tabla de funciones virtuales.
	//     Si accedemos a la dirección a la que apunta el contenido de ese puntero, tendremos la tabla de funciones virtuales.
	file_temp = new CFile();
	int ** p_virtual_functions_table = reinterpret_cast<int **>(file_temp);
	//     En windows el tipo int y el puntero pesan 4 bytes, por lo que t_virtual_functions_table puede utilizarse
	//     con aritmética de punteros para acceder e intentar modificar los valores de la tabla de funciones virtuales.
	int * t_virtual_functions_table = *p_virtual_functions_table;
	// 2 - Si  intentamos cambiar uno de los valores, dará error de ejecución.
	//     Se adjunta captura de inspect para demostrar que se accede realmente a la tabla de funciones virtuales
	//     (practica_15_02_modificacion_tabla_funciones_virtuales.jpg)

	// Si se ejecuta la siguiente línea, habrá un error en ejecución por intenar escibir en una zona de memoria protegida.
	//t_virtual_functions_table[0] = 23445;

	delete file_temp;


	/********************************************/


	//•	¿Cuánto espacio ocupa adicionalmente un objeto por tener una tabla de funciones virtuales?
	// El tamaño de un puntero
	// - Demostración: 
	//   La tabla de CFile ocupa 48 bytes: dos enteros por objeto, foo1 y foo2, + un puntero:
	//   (4 bytes * 2 (int) + 4 bytes (puntero)) * 4 = 48 
	//   La tabla de CFileNoStream ocupa 32 bytes: dos enteros por objeto, foo1 y foo2:
	//   4 bytes * 2 (int) * 4 = 32
	CFile t_file[4];
	t_file[0].m_foo1 = 0;
	t_file[1].m_foo1 = 1;
	t_file[2].m_foo1 = 3;
	t_file[3].m_foo1 = 4;
	t_file[0].m_foo2 = 0;
	t_file[1].m_foo2 = 1;
	t_file[2].m_foo2 = 3;
	t_file[3].m_foo2 = 4;

	CFileNoStream t_file_no_stream[4];
	t_file_no_stream[0].m_foo1 = 5;
	t_file_no_stream[1].m_foo1 = 6;
	t_file_no_stream[2].m_foo1 = 7;
	t_file_no_stream[3].m_foo1 = 8;
	t_file_no_stream[0].m_foo2 = 5;
	t_file_no_stream[1].m_foo2 = 6;
	t_file_no_stream[2].m_foo2 = 7;
	t_file_no_stream[3].m_foo2 = 8;

	unsigned int size_of_file = sizeof(t_file);
	unsigned int size_of_file_no_stream = sizeof(t_file_no_stream);
	printf("\nSize of CFile * 4: %u", size_of_file);
	printf("\nSize of CFileNoStream * 4: %u", size_of_file_no_stream);
	// Se adjunta inspect de las dos tablas (practica_15_03_tablas_objetos.jpg)

	/********************************************/


	//•	¿Qué pasa si llamo a un método virtual desde el constructor?
	// Se llamará a la función porque se accede en tiempo de ejecución, 
	// y es en compilación cuando se crea la tabla de funciones virtuales
	// pero los resultados pueden ser indeseados ya que al no estar el objeto construido, puede accederse a basura.
	printf("\n *************\n Llamada a constructor que invoca funcion virtual Open");
	file_temp = new CFile();
	// En el constructor se llama a Open, que saca en pantalla el valor de m_foo1.
	// Posteriormente se inicializa con el valor 999111. Si llamamos a open, se ve que el valor anterior de m_foo1 era basura.
	printf("\n Llamada a funcion virtual Open tras inicializar");
	file_temp->Open();
	printf("\n *************\n");

	delete file_temp;


	/********************************************/


	//•	Comparar la llamada a una función virtual con la llamada a una función no virtual. ¿Cuántos pasos adicionales tienen que realizarse para llamar a una función cuando esta es virtual?
	// - Tiene que accederse a la dirección del puntero de la tabla de funciones virtuales, 
	//   recorrerla hasta encontrar la función, y ahora sí, llamar a esa función 
	//   a través del puntero de la tabla de funciones virtuales. Tres acciones en vez de una sola llamada.
	file_temp = new CFile();
	file_no_stream_temp = new CFileNoStream();

	// Se adjunta captura de desensamblado de las siguientes lineas
	// * En la llamada a función virtual primero se accede al puntero de la tabla de funciones virtuales,
	//   después se recorren sus elementos (Open es el primero de ellos),
	//   posteriormente se guarda file_temp como parámetro de la función (al ser una función miembro)
	//   y finalmente se llama a la función, a la que se accede desde la tabla de funciones virtuales.
	//  (5 comandos de ensamblador)
	file_temp->Open();

	// *  En la llamada a función no virtual, simplemente se guarda file_no_stream_temp como parámetro de la función,
	//    y posteriormente se la llama, sin nigún otro paso intermedio.
	//  (2 comandos de ensamblador)
	file_no_stream_temp->Open();

	delete file_no_stream_temp;
	delete file_temp;


	/********************************************/


	printf("\n\nPress Enter to quit...");
	getchar();

	return 0;
}



