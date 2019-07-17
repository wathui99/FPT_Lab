#ifndef __ATOM_PORT_TESTS_H
#define __ATOM_PORT_TESTS_H

/* Include Atomthreads kernel API */
#include "atom.h"

/* Prerequisite include for ATOMLOG() macro (via printf) */
#include <stdio.h>

/* Default thread stack size (in bytes) */
#define TEST_THREAD_STACK_SIZE      192

/* Uncomment to enable logging of stack usage to UART */
#define TESTS_LOG_STACK_USAGE

/**
 * IAR EWSTM8: Ignore warnings on volatile ordering thrown up
 * by ATOMLOG() statements in the test modules.
 */
#ifdef __IAR_SYSTEMS_ICC__
#pragma diag_suppress=Pa082
#endif


#endif /* __ATOM_PORT_TESTS_H */

