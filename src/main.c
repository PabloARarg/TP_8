/* 2023, Rivas Pablo
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "bcp.h"
#include "chip.h"
#include "define.h"
#include "digital.h"
#include "interface.h"
#include "pantalla.h"
#include "reloj.h"
#include <stdbool.h>
#include <string.h>

/* === Macros definitions ====================================================================== */
#ifndef TICK_POR_SEC
#define TICK_POR_SEC 1000
#endif

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

//! funcion para cambiar el estado
void CambiarModo(modo_t valor) {
    modo = valor;
    switch (modo) {
    case SIN_CONFIGURAR:
        DisplayFlashDigit(board->display, 0, 3, 250);
        break;
    case MOSTRANDO_HORA:
        DisplayFlashDigit(board->display, 0, 0, 0);
        break;
    case ACTUAL_AJUSTANDO_MINUTOS:
        DisplayFlashDigit(board->display, 2, 3, 250);
        break;
    case ACTUAL_AJUSTANDO_HORAS:
        DisplayFlashDigit(board->display, 0, 1, 250);
        break;
    case ALARMA_AJUSTANDO_MINUTOS:
        DisplayFlashDigit(board->display, 2, 3, 250);
        break;
    case ALARMA_AJUSTANDO_HORAS:
        DisplayFlashDigit(board->display, 0, 1, 250);
        break;
    default:
        break;
    }
}

void PuntoModo(modo_t modo) {
    switch (modo) {
    case SIN_CONFIGURAR:
        DisplayPunto(board->display, 1);
        break;
    case MOSTRANDO_HORA:
        DisplayPunto(board->display, 1);
        if (VERIFICAR_ALARMA) {
            DisplayPunto(board->display, 3);
        }
        if (AlarmaActivar(reloj)) {
            DisplayPunto(board->display, 0);
        }
        break;
    case ACTUAL_AJUSTANDO_MINUTOS:
        DisplayPunto(board->display, 2);
        DisplayPunto(board->display, 3);
        break;
    case ACTUAL_AJUSTANDO_HORAS:
        DisplayPunto(board->display, 0);
        DisplayPunto(board->display, 1);
        break;
    case ALARMA_AJUSTANDO_MINUTOS:

        DisplayPunto(board->display, 0);
        DisplayPunto(board->display, 1);
        DisplayPunto(board->display, 2);
        DisplayPunto(board->display, 3);
        break;
    case ALARMA_AJUSTANDO_HORAS:
        DisplayPunto(board->display, 0);
        DisplayPunto(board->display, 1);
        DisplayPunto(board->display, 2);
        DisplayPunto(board->display, 3);
        break;
    default:
        break;
    }
}

/* === Public function implementation ========================================================= */
#ifdef CIA
int main(void) {

    int divisor = 0;

    placa_t board = BoardCreate();

    while (true) {
        if (DigitalInputGetState(board->tecla_1)) {
            DigitalOutputActivate(board->led_azul);
        } else {
            DigitalOutputDesactivate(board->led_azul);
        }

        if (DigitalInputHasActivate(board->tecla_2)) {
            DigitalOutputToggle(board->led_rojo);
        }

        if (DigitalInputGetState(board->tecla_3)) {
            DigitalOutputActivate(board->led_amarillo);
        }
        if (DigitalInputGetState(board->tecla_4)) {
            DigitalOutputDesactivate(board->led_amarillo);
        }

        divisor++;
        if (divisor == 5) {
            divisor = 0;
            DigitalOutputToggle(board->led_verde);
        }

        for (int index = 0; index < 100; index++) {
            for (int delay = 0; delay < 25000; delay++) {
                __asm("NOP");
            }
        }
    }
}
#endif

#ifdef PONCHO
int main(void) {
    board = BoardCreate();

    reloj = ClockCreate(TICK_POR_SEC_TEST);

    sist_contador = 0;
    tres_sec = 0;
    treinta_sec = 0;

    CambiarModo(SIN_CONFIGURAR);

    SisTick_Init(TICK_POR_SEC);

    while (true) {

        if (DigitalInputHasActivate(board->acept)) {
            treinta_sec = 0;
            if (modo == ACTUAL_AJUSTANDO_MINUTOS) {
                CambiarModo(ACTUAL_AJUSTANDO_HORAS);
            } else if (modo == ACTUAL_AJUSTANDO_HORAS) {
                DEFINIR_HORA;
                if (VERIFICAR_HORA) {
                    CambiarModo(MOSTRANDO_HORA);
                } else {
                    CambiarModo(SIN_CONFIGURAR);
                }
            } else if (modo == ALARMA_AJUSTANDO_MINUTOS) {
                CambiarModo(ALARMA_AJUSTANDO_HORAS);
            } else if (modo == ALARMA_AJUSTANDO_HORAS) {
                DEFINIR_ALARMA;
                CambiarModo(MOSTRANDO_HORA);
            } else if (modo == MOSTRANDO_HORA) {
                if (AlarmaActivar(reloj)) {
                    AlarmaRest(reloj, TIME_OUT);
                } else if (!VERIFICAR_ALARMA) {
                    AlarmaOnOf(reloj, true);
                }
            }
        }

        if (DigitalInputHasDesactivate(board->cancel)) {
            if ((modo == ACTUAL_AJUSTANDO_MINUTOS) || (modo == ACTUAL_AJUSTANDO_HORAS)) {
                if (VERIFICAR_HORA) {
                    CambiarModo(MOSTRANDO_HORA);
                } else {
                    CambiarModo(SIN_CONFIGURAR);
                }
            } else if ((modo == ALARMA_AJUSTANDO_MINUTOS) || (modo == ALARMA_AJUSTANDO_HORAS)) {
                CambiarModo(MOSTRANDO_HORA);
            } else if (modo == MOSTRANDO_HORA) {
                if (AlarmaActivar(reloj)) {
                    AlarmaPosponer(reloj);
                } else if (VERIFICAR_ALARMA) {
                    AlarmaOnOf(reloj, false);
                }
            }
        }

        if ((!DigitalInputGetState(board->set_time))) {
            if (3 == tres_sec) {
                if ((modo == MOSTRANDO_HORA) || (modo == SIN_CONFIGURAR)) {
                    OBTENER_HORA;
                    CambiarModo(ACTUAL_AJUSTANDO_MINUTOS);
                }
            }
        }

        if ((!DigitalInputGetState(board->set_alarm))) {
            if (3 == tres_sec) {
                if (modo == MOSTRANDO_HORA) {
                    OBTENER_ALARMA;
                    CambiarModo(ALARMA_AJUSTANDO_MINUTOS);
                }
            }
        }

        if (DigitalInputHasActivate(board->decrement)) {
            treinta_sec = 0;
            if ((modo == ACTUAL_AJUSTANDO_MINUTOS) || (modo == ALARMA_AJUSTANDO_MINUTOS)) {
                AumentarMinuto(hora_obtenida);
            } else if ((modo == ACTUAL_AJUSTANDO_HORAS) || (modo == ALARMA_AJUSTANDO_HORAS)) {
                AumentarHora(hora_obtenida);
            }
        }

        if (DigitalInputHasActivate(board->increment)) {
            treinta_sec = 0;
            if ((modo == ACTUAL_AJUSTANDO_MINUTOS) | (modo == ALARMA_AJUSTANDO_MINUTOS)) {
                DisminuirMinuto(hora_obtenida);
            } else if ((modo == ACTUAL_AJUSTANDO_HORAS) | (modo == ALARMA_AJUSTANDO_HORAS)) {
                DisminuirHora(hora_obtenida);
            }
        }
    }
}

void SysTick_Handler(void) {
    // aumenta en 1 la cantidad de tick o reinica
    sist_contador = ((sist_contador + 1) % (TICK_POR_SEC));
    // obtiene la hora actual y la pinta en pantalla
    if (modo == SIN_CONFIGURAR || modo == MOSTRANDO_HORA) {
        OBTENER_HORA;
    }
    DisplayWriteBCD(board->display, hora_obtenida,
                    sizeof(hora_obtenida)); // llena los bits necesarios para completar los digitos
    // en funcion del modo pintal los puntos
    if (sist_contador < TICK_POR_SEC / 2) {
        PuntoModo(modo);
    }
    // cuentra 3 segundos para los botonoes set_time y set_alarma
    if ((!DigitalInputGetState(board->set_time)) | (!DigitalInputGetState(board->set_alarm))) {
        if (((TICK_POR_SEC - 1) == sist_contador) && (tres_sec < T_PULSADO)) {
            tres_sec++;
        }
        DisplayPunto(board->display, 2);
    } else {
        tres_sec = 0;
    }
    // cuenta 30 segundos para salir de cualquier estado de set
    if ((modo == ACTUAL_AJUSTANDO_MINUTOS) | (modo == ACTUAL_AJUSTANDO_HORAS) | (modo == ALARMA_AJUSTANDO_MINUTOS) |
        (modo == ALARMA_AJUSTANDO_HORAS)) {
        if (((TICK_POR_SEC - 1) == sist_contador) && (treinta_sec < T_ESPERADO)) {
            treinta_sec++;
        } else if (((TICK_POR_SEC - 1) == sist_contador) && (treinta_sec == T_ESPERADO)) {
            treinta_sec = 0;
            if (VERIFICAR_HORA) {
                CambiarModo(MOSTRANDO_HORA);
            } else {
                CambiarModo(SIN_CONFIGURAR);
            }
        }
    }

    DisplayRefresh(board->display);

    AumentarTick(reloj);
    ActualizarHora(reloj);
}

#endif
/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
