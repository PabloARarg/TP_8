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
#define VERIFICAR_OBTENER_HORA ClockGetTime(reloj, hora_obtenida, sizeof(hora_obtenida))
#define DEFINIR_HORA ClockSetTime(reloj, hora_obtenida, sizeof(hora_obtenida))
#define VERIFICAR_OBTENER_ALARMA ClockGetAlarm(reloj, hora_obtenida, sizeof(hora_obtenida))
#define DEFINIR_ALARMA ClockSetAlarm(reloj, hora_obtenida, sizeof(hora_obtenida))

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

static placa_t board;
static modo_t modo;
static clock_t reloj;
static uint8_t hora_obtenida[6];
static uint8_t tres_sec;
static uint8_t treinta_sec;
static uint16_t sist_contador;

/* === Public function declarations ============================================================ */
void CambiarModo(modo_t valor);

void PuntoModo(modo_t modo);

void GetHoraModo(modo_t modo);

void AumentarMinuto(uint8_t entrada[6]);

void AumentarHora(uint8_t entrada[6]);

void DisminuirMinuto(uint8_t entrada[6]);

void DisminuirHora(uint8_t entrada[6]);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* INTERFACE_H*/