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
#ifndef RELOJ_H
#define RELOJ_H

/** \brief Declaraciones publicas del modulo de alumnos
 **
 ** \addtogroup alumno Alumno
 ** \brief Modulo para gestion de aulumno
 ** @{ */

/* === Headers files inclusions ================================================================ */
#include "define.h"
#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

//! Referencia para gestionar el reloj
typedef struct clock_s * clock_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Auementa el contador interno del reloj en 1
 *
 * @param reloj puntero que referencia al reloj
 */
void AumentarTick(clock_t reloj);

/**
 * @brief Funcion que crea el reloj
 *
 * @param ticks_por_segundos cantidad de ticks por segundos para el cambio del contador interno
 * @return clock_t debuelve el puntero referencia al reloj
 */
clock_t ClockCreate(uint32_t ticks_por_segundos);

/**
 * @brief función para ajustar la hora actual.
 *
 * @param reloj puntero que referencia al reloj
 * @param hora vector de 6 entero --> (puntero)
 * @param size Tamaño del vector en bytes
 * @return true cuando se guardo correctamente,
 * @return false cuando no se pudo guardar
 * @note Copia el contenido de "hora" en el reloj campo->hora_actual y cambia campo->valida a "true"
 */
bool ClockSetTime(clock_t reloj, const uint8_t * hora, uint32_t size);

/**
 * @brief Funcion que obteine la hora
 *
 * @param reloj puntero que referencia al reloj
 * @param hora vector de 6 entero --> (puntero)
 * @param size Tamaño del vector en bytes
 * @return true cuando se obtuvo correctamente,
 * @return false cuando no se pudo obtener
 * @note Copia el contenido del reloj campo->hora_actual en "hora"
 */
bool ClockGetTime(clock_t reloj, uint8_t * hora, uint32_t size);

/**
 * @brief Actualiza la hora
 *
 * @param reloj puntero que referencia al reloj
 * @note Actializa la hora interna del reloj si la cantidad de ticks se alcanzaron para que cambie 1 seg
 */
void ActualizarHora(clock_t reloj);

/**
 * @brief función para fijar la hora de la alarma.
 *
 * @param reloj puntero que referencia al reloj
 * @param hora vector de 6 entero --> (puntero)
 * @param size Tamaño del vector en bytes
 * @return true Tamaño del vector en bytes
 * @return false cuando no se pudo guardar
 * @note Copia el contenido de "hora" en el reloj campo->alarma y cambia campo->alarma_on a "true"
 */
bool ClockSetAlarm(clock_t reloj, const uint8_t * hora, uint32_t size);

/**
 * @brief función para consultar la hora fijada para la alarma.
 *
 * @param reloj puntero que referencia al reloj
 * @param hora vector de 6 entero --> (puntero)
 * @param size Tamaño del vector en bytes
 * @return true si la alarma esta configurada para sonar,
 * @return false si no esta configurada
 * @note copia el campo->alarma a "hora"
 */
bool ClockGetAlarm(clock_t reloj, uint8_t * hora, uint32_t size);

/**
 * @brief función para habilitar y deshabilitar la alarma.
 *
 * @param reloj puntero que referencia al reloj
 * @param estado_requerido estado que se requiere la alarma
 * @return debuelve el estado de la alarma, parametro->alarma_on
 */
bool AlarmaOnOf(clock_t reloj, bool estado_requerido);

/**
 * @brief función para consultar si la alarma está, o no, habilitada.
 *
 * @param reloj puntero que referencia al reloj
 * @return debuelve el estado de la alarma, parametro->alarma_on
 */
bool AlarmaGetState(clock_t reloj);

/**
 * @brief función para posponer la alarma una cantidad arbitraria en minutos
 *
 * @param reloj puntero que referencia al reloj
 * @param tiempo_muerto cantidad de minutos a posponer
 * @return true si exite un valor para posponer el timepo,
 * @return false si el valor es 0
 */
bool AlarmaRest(clock_t reloj, uint8_t tiempo_muerto);

/**
 * @brief Funcion hace sonar la alarma
 *
 * @param reloj puntero que referencia al reloj
 * @return true si la alrama esta sonando,
 * @return false si no lo esta
 * @note compara la hora actual, la alarma y si esta activa, si se cumple activa el campo->alarma_activada y comprueba
 * si no esta pospuesta para que debolver el valor el estado
 */
bool AlarmaActivar(clock_t reloj);

/**
 * @brief Funcion cancela pospone la alarma por un dia
 *
 * @param reloj puntero que referencia al reloj
 * @return debuelve el estado del campo->alarma_activada (indica si esta sonado)
 */
bool AlarmaPosponer(clock_t reloj);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* RELOJ_H */
