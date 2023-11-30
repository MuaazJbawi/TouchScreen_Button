/**
  ******************************************************************************
  * @file    TouchScreen_Button
  * @author  Muaaz Al-Jbawi
  * @brief   This example shows an image on the display and a switch button to see door camera feed once pressed
  ******************************************************************************
  **/



/**
 * @file main.c
 * @brief Example application for STM32F469 Discovery kit.
 * This application demonstrates the use of the LTDC and DSI for displaying
 * an image and a button on the LCD screen.
 */

/* Include necessary header files */
#include "main.h" // Main header file for the application
#include "image_320x240_argb8888.h" // Header file for the image to be displayed
#include <string.h> // Standard C library for string operations
#include <stdio.h> // Standard C library for standard input/output operations

/* External variables */
extern LTDC_HandleTypeDef hltdc_eval; // Handle for the LTDC (LCD-TFT Display Controller)
static DMA2D_HandleTypeDef hdma2d; // Handle for the DMA2D (Direct Memory Access 2D)
extern DSI_HandleTypeDef hdsi_eval; // Handle for the DSI (Digital Serial Interface)

/* Display settings macros */
#define VSYNC 1 // Vertical sync
#define VBP 1 // Vertical back porch
#define VFP 1 // Vertical front porch
#define VACT 480 // Vertical active area
#define HSYNC 1 // Horizontal sync
#define HBP 1 // Horizontal back porch
#define HFP 1 // Horizontal front porch
#define HACT 800 // Horizontal active area

#define LAYER0_ADDRESS (LCD_FB_START_ADDRESS) // Base address of layer 0

static int32_t pending_buffer = -1; // Buffer pending for update

/* Function prototypes */
static void SystemClock_Config(void); // Configures the system clock
static void OnError_Handler(uint32_t condition); // Error handler
static void CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize); // Copies a buffer
static uint8_t LCD_Init(void); // Initializes the LCD
void LTDC_Init(void); // Initializes the LTDC
static void LCD_BriefDisplay(void); // Briefly displays content on the LCD

/**
 * @brief Error handler function.
 * @param condition The condition to check if an error has occurred.
 */
static void OnError_Handler(uint32_t condition)
{
  if(condition)
  {
    BSP_LED_On(LED3); // Turn on LED3 to indicate error
    while(1) { ; } // Infinite loop to halt the program
  }
}

/**
 * @brief Draws a button on the screen.
 */
static void DrawButton(void)
{
    uint16_t x_pos = 600; // X position of the button
    uint16_t y_pos = 240; // Y position of the button
    uint16_t width = 100; // Width of the button
    uint16_t height = 50; // Height of the button

    BSP_LCD_SetTextColor(LCD_COLOR_BLACK); // Set text color to black
    BSP_LCD_FillRect(x_pos, y_pos, width, height); // Fill rectangle for the button

    BSP_LCD_SetTextColor(LCD_COLOR_WHITE); // Set text color to white
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK); // Set background color to black
    BSP_LCD_SetFont(&Font20); // Set font size to 20
    BSP_LCD_DisplayStringAt(1000 + (width/2), y_pos + (height/2), (uint8_t *)"SWITCH", CENTER_MODE); // Display "SWITCH" on the button
}

/**
 * @brief Main function.
 * @return int
 */
int main(void)
{
  uint8_t lcd_status = LCD_OK; // Variable to hold LCD status

  HAL_Init(); // Initialize the Hardware Abstraction Layer
  SystemClock_Config(); // Configure the system clock
  BSP_SDRAM_Init(); // Initialize the SDRAM
  lcd_status = LCD_Init(); // Initialize the LCD and get status
  OnError_Handler(lcd_status != LCD_OK); // Check for LCD initialization error

  BSP_LCD_LayerDefaultInit(0, LAYER0_ADDRESS); // Initialize default layer
  BSP_LCD_SelectLayer(0); // Select layer 0
  LCD_BriefDisplay(); // Display brief information on the LCD

  // Copy the image to the screen
  CopyBuffer((uint32_t *)image_320x240_argb8888, (uint32_t *)LAYER0_ADDRESS, 50, 160, 320, 240);
  pending_buffer = 0; // Set buffer as pending
  HAL_DSI_Refresh(&hdsi_eval); // Refresh the DSI
  LCD_BriefDisplay(); // Display brief information again
  CopyBuffer((uint32_t *)image_320x240_argb8888, (uint32_t *)LAYER0_ADDRESS, 50, 160, 320, 240); // Copy the buffer again
  DrawButton(); // Draw the button

  while (1)
  {
    if(pending_buffer < 0) // Check if buffer is pending
    {
      pending_buffer = 0; // Reset the pending buffer
      HAL_DSI_Refresh(&hdsi_eval); // Refresh the DSI
    }
  }
}

/**
 * @brief Callback function for DSI end of refresh.
 * @param hdsi Handle for the DSI.
 */
void HAL_DSI_EndOfRefreshCallback(DSI_HandleTypeDef *hdsi)
{
  if(pending_buffer >= 0)
  {
    pending_buffer = -1; // Reset the pending buffer
  }
}
/**
 * @brief Configures the system clock.
 *
 * This function sets up the system clock source, PLL (Phase-Locked Loop) multipliers and dividers,
 * and system clock dividers. This configuration is crucial for the CPU to function correctly,
 * as it sets the speed of the core clock and the bus clock frequencies.
 */


static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
#if defined(USE_STM32469I_DISCO_REVA)
  RCC_OscInitStruct.PLL.PLLM = 25;
#else
  RCC_OscInitStruct.PLL.PLLM = 8;
#endif
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 6;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  

  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}
/**
 * @brief Initializes the LCD display.
 *
 * This function resets the LCD, initializes the DSI (Digital Serial Interface),
 * configures the command mode, sets the DSI PHY (Physical Layer) timers, and
 * starts the DSI and LTDC (LCD-TFT Display Controller). It also handles the
 * initialization of the display hardware specific to the STM32F469 Discovery kit.
 *
 * @return uint8_t Returns LCD_OK if initialization was successful.
 */
static uint8_t LCD_Init(void)
{
  static DSI_PHY_TimerTypeDef PhyTimings;
  static DSI_CmdCfgTypeDef CmdCfg;
  static DSI_LPCmdTypeDef LPCmd;
  static DSI_PLLInitTypeDef dsiPllInit;
  static RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  BSP_LCD_Reset();
  BSP_LCD_MspInit();

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 417;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

  hdsi_eval.Instance = DSI;
  HAL_DSI_DeInit(&(hdsi_eval));

#if defined(USE_STM32469I_DISCO_REVA)  
  dsiPllInit.PLLNDIV  = 100;
  dsiPllInit.PLLIDF   = DSI_PLL_IN_DIV5;
#else
  dsiPllInit.PLLNDIV  = 125;
  dsiPllInit.PLLIDF   = DSI_PLL_IN_DIV2;  
#endif
  dsiPllInit.PLLODF  = DSI_PLL_OUT_DIV1;  
  hdsi_eval.Init.NumberOfLanes = DSI_TWO_DATA_LANES;
  hdsi_eval.Init.TXEscapeCkdiv = 0x4;
  HAL_DSI_Init(&(hdsi_eval), &(dsiPllInit));

  CmdCfg.VirtualChannelID = 0;
  CmdCfg.HSPolarity = DSI_HSYNC_ACTIVE_HIGH;
  CmdCfg.VSPolarity = DSI_VSYNC_ACTIVE_HIGH;
  CmdCfg.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH;
  CmdCfg.ColorCoding = DSI_RGB888;
  CmdCfg.CommandSize = HACT;
  CmdCfg.TearingEffectSource = DSI_TE_DSILINK;
  CmdCfg.TearingEffectPolarity = DSI_TE_RISING_EDGE;
  CmdCfg.VSyncPol = DSI_VSYNC_FALLING;
  CmdCfg.AutomaticRefresh = DSI_AR_DISABLE;
  CmdCfg.TEAcknowledgeRequest = DSI_TE_ACKNOWLEDGE_ENABLE;
  HAL_DSI_ConfigAdaptedCommandMode(&hdsi_eval, &CmdCfg);

  LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_ENABLE;
  LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_ENABLE;
  LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_ENABLE;
  LPCmd.LPGenShortReadNoP = DSI_LP_GSR0P_ENABLE;
  LPCmd.LPGenShortReadOneP = DSI_LP_GSR1P_ENABLE;
  LPCmd.LPGenShortReadTwoP = DSI_LP_GSR2P_ENABLE;
  LPCmd.LPGenLongWrite = DSI_LP_GLW_ENABLE;
  LPCmd.LPDcsShortWriteNoP = DSI_LP_DSW0P_ENABLE;
  LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_ENABLE;
  LPCmd.LPDcsShortReadNoP = DSI_LP_DSR0P_ENABLE;
  LPCmd.LPDcsLongWrite = DSI_LP_DLW_ENABLE;
  HAL_DSI_ConfigCommand(&hdsi_eval, &LPCmd);

  PhyTimings.ClockLaneHS2LPTime = 35;
  PhyTimings.ClockLaneLP2HSTime = 35;
  PhyTimings.DataLaneHS2LPTime = 35;
  PhyTimings.DataLaneLP2HSTime = 35;
  PhyTimings.DataLaneMaxReadTime = 0;
  PhyTimings.StopWaitTime = 10;
  HAL_DSI_ConfigPhyTimer(&hdsi_eval, &PhyTimings);

  LTDC_Init();
  HAL_DSI_Start(&(hdsi_eval));

#if defined (USE_STM32469I_DISCO_REVC)
  NT35510_Init(NT35510_FORMAT_RGB888, LCD_ORIENTATION_LANDSCAPE);
#else
  OTM8009A_Init(OTM8009A_COLMOD_RGB888, LCD_ORIENTATION_LANDSCAPE);
#endif

  LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_DISABLE;


  LPCmd.LPGenShortWriteOneP   = DSI_LP_GSW1P_DISABLE;
  LPCmd.LPGenShortWriteTwoP   = DSI_LP_GSW2P_DISABLE;
  LPCmd.LPGenShortReadNoP     = DSI_LP_GSR0P_DISABLE;
  LPCmd.LPGenShortReadOneP    = DSI_LP_GSR1P_DISABLE;
  LPCmd.LPGenShortReadTwoP    = DSI_LP_GSR2P_DISABLE;
  LPCmd.LPGenLongWrite        = DSI_LP_GLW_DISABLE;
  LPCmd.LPDcsShortWriteNoP    = DSI_LP_DSW0P_DISABLE;
  LPCmd.LPDcsShortWriteOneP   = DSI_LP_DSW1P_DISABLE;
  LPCmd.LPDcsShortReadNoP     = DSI_LP_DSR0P_DISABLE;
  LPCmd.LPDcsLongWrite        = DSI_LP_DLW_DISABLE;
  HAL_DSI_ConfigCommand(&hdsi_eval, &LPCmd);
  
   HAL_DSI_ConfigFlowControl(&hdsi_eval, DSI_FLOW_CONTROL_BTA);

  HAL_DSI_Refresh(&hdsi_eval);
  
  return LCD_OK;
}
/**
 * @brief Initializes the LTDC.
 *
 * This function sets up the LTDC (LCD-TFT Display Controller) parameters such as
 * synchronization timings, polarities, and the framebuffer line length. This setup
 * is essential for the LTDC to correctly drive the LCD.
 */

void LTDC_Init(void)
{

  hltdc_eval.Instance = LTDC;
  HAL_LTDC_DeInit(&hltdc_eval);
  

  hltdc_eval.Init.HorizontalSync = HSYNC;
  hltdc_eval.Init.VerticalSync = VSYNC;
  hltdc_eval.Init.AccumulatedHBP = HSYNC+HBP;
  hltdc_eval.Init.AccumulatedVBP = VSYNC+VBP;
  hltdc_eval.Init.AccumulatedActiveH = VSYNC+VBP+VACT;
  hltdc_eval.Init.AccumulatedActiveW = HSYNC+HBP+HACT;
  hltdc_eval.Init.TotalHeigh = VSYNC+VBP+VACT+VFP;
  hltdc_eval.Init.TotalWidth = HSYNC+HBP+HACT+HFP;
  

  hltdc_eval.Init.Backcolor.Blue = 0;
  hltdc_eval.Init.Backcolor.Green = 0;
  hltdc_eval.Init.Backcolor.Red = 0;
  

  hltdc_eval.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc_eval.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc_eval.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc_eval.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc_eval.Instance = LTDC;

  HAL_LTDC_Init(&hltdc_eval);
}
/**
 * @brief Displays a brief message on the LCD.
 *
 * This function sets the font, background and text colors, and displays a few strings
 * on the LCD. It's used to show an initial message or status on the screen.
 */
static void LCD_BriefDisplay(void)
{
  BSP_LCD_SetFont(&Font24);  
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_FillRect(0, 0, 800, 112);  
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_FillRect(0, 112, 800, 368);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)"                    CCTV FEED");
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayStringAtLine(4, (uint8_t *)"                  THIS IS SHOWINGH YOUR FRONT DOOR");
  BSP_LCD_DisplayStringAtLine(5, (uint8_t *)"                  USE THE SWITCH BUTTON TO SWITCH VIEW ");
  
}
/**
 * @brief Copies a buffer to a destination buffer using DMA2D.
 *
 * This function copies a buffer (image or similar data) to a destination buffer
 * on the display using the DMA2D (Direct Memory Access 2D) controller. It sets up
 * the DMA2D configuration such as color mode and offset, and initiates the transfer.
 *
 * @param pSrc Pointer to the source buffer.
 * @param pDst Pointer to the destination buffer.
 * @param x The X position where to start the copy in the destination buffer.
 * @param y The Y position where to start the copy in the destination buffer.
 * @param xsize The width of the area to be copied.
 * @param ysize The height of the area to be copied.
 */

static void CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize)
{   
  
  uint32_t destination = (uint32_t)pDst + (y * 800 + x) * 4;
  uint32_t source      = (uint32_t)pSrc;
  
  hdma2d.Init.Mode         = DMA2D_M2M;
  hdma2d.Init.ColorMode    = DMA2D_ARGB8888;
  hdma2d.Init.OutputOffset = 800 - xsize;     
  
  hdma2d.XferCpltCallback  = NULL;
  
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].InputOffset = 0;

  hdma2d.Instance          = DMA2D; 
   
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK) 
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK) 
    {
      if (HAL_DMA2D_Start(&hdma2d, source, destination, xsize, ysize) == HAL_OK)
      {
        HAL_DMA2D_PollForTransfer(&hdma2d, 100);
      }
    }
  }   
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief Assert Failed function.
 * @param file File in which the assert failed.
 * @param line Line number at which the assert failed.
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  while (1) // Infinite loop to halt the program on assert failure
  {
  }
}
#endif

