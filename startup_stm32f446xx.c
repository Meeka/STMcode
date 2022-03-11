#include "stdint.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx.h"

// Constants from linker
extern uint32_t _sidata;    // Start of init data
extern uint32_t _sdata;     // Start of data
extern uint32_t _edata;     // End of data
extern uint32_t _sbss;      // Start of bss
extern uint32_t _ebss;      // End of bss
extern uint32_t _estack;    // End of raw memory and top of stack

// Static constructor initializator from libc
extern void __libc_init_array();

// Main program entry point
extern void main();

// Reset handler
void Reset_Handler() {

    // Initialize data segment
    uint32_t *dataInit = &_sidata;
    uint32_t *data = &_sdata;

    while(data < &_edata) {
        *data++ = *dataInit++;
    }

    // Initialize bss segment
    uint32_t *bss = &_sbss;
    while(bss < &_ebss) {
        *bss++ = 0;
    }

    // Run ST from BSP
    SystemInit();

    // Initialize static constructors
    __libc_init_array();

    // Enter main program
    main();

    // Handle case where main function returns
    while(1);
}

// Default handler for unimplemented interrupts
void Default_Handler(void) {
    while(1);
}

// Hard fault handler
__weak void HardFault_Handler(void) {
    while(1);
}

// Weak definitions of interrupt handlers
__weak void NMI_Handler (void)                     { Default_Handler(); }
__weak void MemManage_Handler (void)               { Default_Handler(); }
__weak void BusFault_Handler (void)                { Default_Handler(); }
__weak void UsageFault_Handler (void)              { Default_Handler(); }
__weak void SVC_Handler (void)                     { Default_Handler(); }
__weak void DebugMon_Handler (void)                { Default_Handler(); }
__weak void PendSV_Handler (void)                  { Default_Handler(); }
__weak void SysTick_Handler (void)                 { Default_Handler(); }
__weak void WWDG_IRQHandler (void)                 { Default_Handler(); }
__weak void PVD_IRQHandler (void)                  { Default_Handler(); }
__weak void TAMP_STAMP_IRQHandler (void)           { Default_Handler(); }
__weak void RTC_WKUP_IRQHandler (void)             { Default_Handler(); }
__weak void FLASH_IRQHandler (void)                { Default_Handler(); }
__weak void RCC_IRQHandler (void)                  { Default_Handler(); }
__weak void EXTI0_IRQHandler (void)                { Default_Handler(); }
__weak void EXTI1_IRQHandler (void)                { Default_Handler(); }
__weak void EXTI2_IRQHandler (void)                { Default_Handler(); }
__weak void EXTI3_IRQHandler (void)                { Default_Handler(); }
__weak void EXTI4_IRQHandler (void)                { Default_Handler(); }
__weak void DMA1_Stream0_IRQHandler (void)         { Default_Handler(); }
__weak void DMA1_Stream1_IRQHandler (void)         { Default_Handler(); }
__weak void DMA1_Stream2_IRQHandler (void)         { Default_Handler(); }
__weak void DMA1_Stream3_IRQHandler (void)         { Default_Handler(); }
__weak void DMA1_Stream4_IRQHandler (void)         { Default_Handler(); }
__weak void DMA1_Stream5_IRQHandler (void)         { Default_Handler(); }
__weak void DMA1_Stream6_IRQHandler (void)         { Default_Handler(); }
__weak void ADC_IRQHandler (void)                  { Default_Handler(); }
__weak void CAN1_TX_IRQHandler (void)              { Default_Handler(); }
__weak void CAN1_RX0_IRQHandler (void)             { Default_Handler(); }
__weak void CAN1_RX1_IRQHandler (void)             { Default_Handler(); }
__weak void CAN1_SCE_IRQHandler (void)             { Default_Handler(); }
__weak void EXTI9_5_IRQHandler (void)              { Default_Handler(); }
__weak void TIM1_BRK_TIM9_IRQHandler (void)        { Default_Handler(); }
__weak void TIM1_UP_TIM10_IRQHandler (void)        { Default_Handler(); }
__weak void TIM1_TRG_COM_TIM11_IRQHandler (void)   { Default_Handler(); }
__weak void TIM1_CC_IRQHandler (void)              { Default_Handler(); }
__weak void TIM2_IRQHandler (void)                 { Default_Handler(); }
__weak void TIM3_IRQHandler (void)                 { Default_Handler(); }
__weak void TIM4_IRQHandler (void)                 { Default_Handler(); }
__weak void I2C1_EV_IRQHandler (void)              { Default_Handler(); }
__weak void I2C1_ER_IRQHandler (void)              { Default_Handler(); }
__weak void I2C2_EV_IRQHandler (void)              { Default_Handler(); }
__weak void I2C2_ER_IRQHandler (void)              { Default_Handler(); }
__weak void SPI1_IRQHandler (void)                 { Default_Handler(); }
__weak void SPI2_IRQHandler (void)                 { Default_Handler(); }
__weak void USART1_IRQHandler (void)               { Default_Handler(); }
__weak void USART2_IRQHandler (void)               { Default_Handler(); }
__weak void USART3_IRQHandler (void)               { Default_Handler(); }
__weak void EXTI15_10_IRQHandler (void)            { Default_Handler(); }
__weak void RTC_Alarm_IRQHandler (void)            { Default_Handler(); }
__weak void OTG_FS_WKUP_IRQHandler (void)          { Default_Handler(); }
__weak void TIM8_BRK_TIM12_IRQHandler (void)       { Default_Handler(); }
__weak void TIM8_UP_TIM13_IRQHandler (void)        { Default_Handler(); }
__weak void TIM8_TRG_COM_TIM14_IRQHandler (void)   { Default_Handler(); }
__weak void TIM8_CC_IRQHandler (void)              { Default_Handler(); }
__weak void DMA1_Stream7_IRQHandler (void)         { Default_Handler(); }
__weak void FMC_IRQHandler (void)                  { Default_Handler(); }
__weak void SDIO_IRQHandler (void)                 { Default_Handler(); }
__weak void TIM5_IRQHandler (void)                 { Default_Handler(); }
__weak void SPI3_IRQHandler (void)                 { Default_Handler(); }
__weak void UART4_IRQHandler (void)                { Default_Handler(); }
__weak void UART5_IRQHandler (void)                { Default_Handler(); }
__weak void TIM6_DAC_IRQHandler (void)             { Default_Handler(); }
__weak void TIM7_IRQHandler (void)                 { Default_Handler(); }
__weak void DMA2_Stream0_IRQHandler (void)         { Default_Handler(); }
__weak void DMA2_Stream1_IRQHandler (void)         { Default_Handler(); }
__weak void DMA2_Stream2_IRQHandler (void)         { Default_Handler(); }
__weak void DMA2_Stream3_IRQHandler (void)         { Default_Handler(); }
__weak void DMA2_Stream4_IRQHandler (void)         { Default_Handler(); }
__weak void CAN2_TX_IRQHandler (void)              { Default_Handler(); }
__weak void CAN2_RX0_IRQHandler (void)             { Default_Handler(); }
__weak void CAN2_RX1_IRQHandler (void)             { Default_Handler(); }
__weak void CAN2_SCE_IRQHandler (void)             { Default_Handler(); }
__weak void OTG_FS_IRQHandler (void)               { Default_Handler(); }
__weak void DMA2_Stream5_IRQHandler (void)         { Default_Handler(); }
__weak void DMA2_Stream6_IRQHandler (void)         { Default_Handler(); }
__weak void DMA2_Stream7_IRQHandler (void)         { Default_Handler(); }
__weak void USART6_IRQHandler (void)               { Default_Handler(); }
__weak void I2C3_EV_IRQHandler (void)              { Default_Handler(); }
__weak void I2C3_ER_IRQHandler (void)              { Default_Handler(); }
__weak void OTG_HS_EP1_OUT_IRQHandler (void)       { Default_Handler(); }
__weak void OTG_HS_EP1_IN_IRQHandler (void)        { Default_Handler(); }
__weak void OTG_HS_WKUP_IRQHandler (void)          { Default_Handler(); }
__weak void OTG_HS_IRQHandler (void)               { Default_Handler(); }
__weak void DCMI_IRQHandler (void)                 { Default_Handler(); }
__weak void FPU_IRQHandler (void)                  { Default_Handler(); }
__weak void SPI4_IRQHandler (void)                 { Default_Handler(); }
__weak void SAI1_IRQHandler (void)                 { Default_Handler(); }
__weak void SAI2_IRQHandler (void)                 { Default_Handler(); }
__weak void QUADSPI_IRQHandler (void)              { Default_Handler(); }
__weak void CEC_IRQHandler (void)                  { Default_Handler(); }
__weak void SPDIF_RX_IRQHandler (void)             { Default_Handler(); }
__weak void FMPI2C1_EV_IRQHandler (void)           { Default_Handler(); }
__weak void FMPI2C1_ER_IRQHandler (void)           { Default_Handler(); }

// Interrupt vector table
__attribute__((section(".isr_vector")))
const void (*VectorTable[])(void) = {
    (const void(*)(void)) &_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,
    PVD_IRQHandler,
    TAMP_STAMP_IRQHandler,
    RTC_WKUP_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Stream0_IRQHandler,
    DMA1_Stream1_IRQHandler,
    DMA1_Stream2_IRQHandler,
    DMA1_Stream3_IRQHandler,
    DMA1_Stream4_IRQHandler,
    DMA1_Stream5_IRQHandler,
    DMA1_Stream6_IRQHandler,
    ADC_IRQHandler,
    CAN1_TX_IRQHandler,
    CAN1_RX0_IRQHandler,
    CAN1_RX1_IRQHandler,
    CAN1_SCE_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_TIM9_IRQHandler,
    TIM1_UP_TIM10_IRQHandler,
    TIM1_TRG_COM_TIM11_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_Alarm_IRQHandler,
    OTG_FS_WKUP_IRQHandler,
    TIM8_BRK_TIM12_IRQHandler,
    TIM8_UP_TIM13_IRQHandler,
    TIM8_TRG_COM_TIM14_IRQHandler,
    TIM8_CC_IRQHandler,
    DMA1_Stream7_IRQHandler,
    FMC_IRQHandler,
    SDIO_IRQHandler,
    TIM5_IRQHandler,
    SPI3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    TIM6_DAC_IRQHandler,
    TIM7_IRQHandler,
    DMA2_Stream0_IRQHandler,
    DMA2_Stream1_IRQHandler,
    DMA2_Stream2_IRQHandler,
    DMA2_Stream3_IRQHandler,
    DMA2_Stream4_IRQHandler,
    0,
    0,
    CAN2_TX_IRQHandler,
    CAN2_RX0_IRQHandler,
    CAN2_RX1_IRQHandler,
    CAN2_SCE_IRQHandler,
    OTG_FS_IRQHandler,
    DMA2_Stream5_IRQHandler,
    DMA2_Stream6_IRQHandler,
    DMA2_Stream7_IRQHandler,
    USART6_IRQHandler,
    I2C3_EV_IRQHandler,
    I2C3_ER_IRQHandler,
    OTG_HS_EP1_OUT_IRQHandler,
    OTG_HS_EP1_IN_IRQHandler,
    OTG_HS_WKUP_IRQHandler,
    OTG_HS_IRQHandler,
    DCMI_IRQHandler,
    0,
    0,
    FPU_IRQHandler,
    0,
    0,
    SPI4_IRQHandler,
    0,
    0,
    SAI1_IRQHandler,
    0,
    0,
    0,
    SAI2_IRQHandler,
    QUADSPI_IRQHandler,
    CEC_IRQHandler,
    SPDIF_RX_IRQHandler,
    FMPI2C1_EV_IRQHandler,
    FMPI2C1_ER_IRQHandler
};