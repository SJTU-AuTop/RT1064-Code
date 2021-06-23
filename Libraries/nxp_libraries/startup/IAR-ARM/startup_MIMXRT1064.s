; -------------------------------------------------------------------------
;  @file:    startup_MIMXRT1064.s
;  @purpose: CMSIS Cortex-M7 Core Device Startup File
;            MIMXRT1064
;  @version: 0.1
;  @date:    2018-6-22
;  @build:   b180820
; -------------------------------------------------------------------------
;
; Copyright 1997-2016 Freescale Semiconductor, Inc.
; Copyright 2016-2018 NXP
;
; SPDX-License-Identifier: BSD-3-Clause
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        ;SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        EXTERN  __zf_vector_table


        ;DATA
;__iar_init$$done:              ; The vector table is not needed


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        SECTION .text:CODE:ROOT(2)
        EXPORT Reset_Handler
        ;SECTION .text:CODE:REORDER:ROOT(2)
        
_iomux_gpr14_adr    EQU 0x400AC038
_iomux_gpr16_adr    EQU 0x400AC040
_iomux_gpr17_adr    EQU 0x400AC044
_flexram_bank_cfg   EQU 0xAAAAAAAF
_flexram_itcm_size  EQU 0x7;64KB
_flexram_dtcm_size  EQU 0xA;448KB
        
Reset_Handler
        CPSID   I               ; Mask interrupts

;#ifdef FLEXRAM_CF_ENABLE
        LDR R0,=_iomux_gpr17_adr
        MOV32 R1,_flexram_bank_cfg
        STR R1,[R0]
        LDR R0,=_iomux_gpr16_adr
        LDR R1,[R0]
        ORR R1,R1,#4
        STR R1,[R0]
        
        ;¹Ø±ÕITCM
        ;LDR R0,=_iomux_gpr16_adr
        ;LDR R1,[R0]
        ;AND R1,R1,#0xFFFFFFFE
        ;STR R1,[R0]
        
        LDR R0,=_iomux_gpr14_adr
        LDR R1,[R0]
        MOVT R1,#0x0000
        MOV R2,#_flexram_itcm_size
        MOV R3,#_flexram_dtcm_size
        LSL R2,R2,#16
        LSL R3,R3,#20
        ORR R1,R2,R3
        STR R1,[R0]
;#endif

        LDR     R0, =0xE000ED08
        LDR     R1, =__zf_vector_table
        STR     R1, [R0]
        LDR     R2, [R1]
        MSR     MSP, R2
        LDR     R0, =SystemInit
        BLX     R0
        CPSIE   I               ; Unmask interrupts
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK DefaultISR
        SECTION .text:CODE:REORDER:NOROOT(1)
DefaultISR
        B DefaultISR

        END
