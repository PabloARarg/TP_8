/************************************************************************************************
Copyright (c) 2023, Pablo Rivas

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#ifndef DEFINE_H
#define DEFINE_H

/** \brief Archivo para crear solo definiciones para macros
 **
 ** \addtogroup
 ** \brief
 ** @{ */

/* === Headers files inclusions ================================================================ */

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

//! Si se define CIA se compila para la placa educia sin interface adicional
//#define CIA

//! Si se define PONCHO se compila para para la placa adicional de interface (poncho)
#define PONCHO

//! Si se define TICK se activa la funcion de systick
#define TICK

//! Permite configurar la cantidad de digitos maximos
#define DISPLAY_MAX_DIGITS 8

//! Define el numero de salidas digitales que se etan usando (por defecto es 4) --> digitos
#define OUTPUT_INSTANCES 4

//! Define el numero de entradas digitales (por defecto es 4) --> botones
#define INPUT_INSTANCES 6

//! Si se define la cantidad de tiks por segundos a utilizar, principalmente para la interrupcion
//--> 1000 es por defecto
#define TICK_POR_SEC 1000

//! Si se define la cantidad de tiks por cambio del segundos en el display
//--> 1000 es por defecto igual que TICK_POR_SEC, usado para incrementar la velocidad del reloj en pruebas
#define TICK_POR_SEC_TEST 25

//! Define la cantidad de minutos que se pospone la alarma
#define TIME_OUT 5

//! Tiempo que  debe pulsar cualquier pulsador de set para ingresar a la funcion
//--> por defercto 3
#define T_PULSADO 3

//! Tiempo que se espera para pulsar alguna tecla para no volver al estado por defecto
//--> por defercto 30
#define T_ESPERADO 10

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* DEFINE_H */
