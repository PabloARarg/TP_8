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

#ifndef INTERFACE_H
#define INTERFACE_H

/* === Headers files inclusions ================================================================ */
#include "bcp.h"
#include "chip.h"
#include "define.h"
#include "digital.h"
#include "interface.h"
#include "pantalla.h"
#include "reloj.h"
#include <stdbool.h>
#include <string.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */
typedef enum {
    SIN_CONFIGURAR,
    MOSTRANDO_HORA,
    ACTUAL_AJUSTANDO_MINUTOS,
    ACTUAL_AJUSTANDO_HORAS,
    ALARMA_AJUSTANDO_MINUTOS,
    ALARMA_AJUSTANDO_HORAS,
} modo_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Funcion que establece los puntos que se mostraran en el display
 *
 * @param board puntero que señala a la placa
 * @param reloj puntero que señala al reloj
 * @param modo modo en el cual se encuetra el reloj
 */
void PuntoModo(placa_t board, clock_t reloj, modo_t modo);

/**
 * @brief Funcino para aumentar un minuto
 *
 * @param entrada puntero al vector que tiene el valor actual (vector)
 */
void AumentarMinuto(uint8_t entrada[6]);

/**
 * @brief Funcino para aumentar una hora
 *
 * @param entrada puntero al vector que tiene el valor actual (vector)
 */
void AumentarHora(uint8_t entrada[6]);

/**
 * @brief Funcino para disminuir un minuto
 *
 * @param entrada puntero al vector que tiene el valor actual (vector)
 */
void DisminuirMinuto(uint8_t entrada[6]);

/**
 * @brief Funcino para aumentar una hora
 *
 * @param entrada puntero al vector que tiene el valor actual (vector)
 */
void DisminuirHora(uint8_t entrada[6]);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* INTERFACE_H*/