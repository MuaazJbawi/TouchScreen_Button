# TouchScreen_Button Example for STM32F469 Discovery Kit

## Overview

This example demonstrates how to use a touch screen interface on the STM32F469 Discovery kit to display an image and a switch button on the LCD screen. Pressing the switch button allows the user to view a door camera feed. The application utilizes the LTDC and DSI drivers provided by the STM32 HAL.

## Project Structure

- `main.c`: The main C source file containing the application logic for displaying the image and handling the switch button.
- `main.h`: The main header file, including necessary STM32 HAL libraries and function declarations.
- `image_320x240_argb8888.h`: Header file containing the image data to be displayed.

## Features

- **LCD Display Control**: Utilizes the LTDC (LCD-TFT Display Controller) and DSI (Digital Serial Interface) for display control on the STM32F469 Discovery kit's LCD.
- **Touch Screen Button**: Interactive button on the touch screen to switch the display view.
- **Camera Feed Display**: Ability to view a door camera feed by pressing the touch screen button.

## Requirements

- STM32F469 Discovery kit.
- STM32 HAL libraries specific to STM32F469.
- An Integrated Development Environment (IDE) like STM32CubeIDE or Keil uVision.
- A compatible camera module for the door camera feed.

## Building the Project

1. **Environment Setup**: Ensure you have the STM32 HAL libraries and a compatible IDE.
2. **Project Configuration**: Open the project in your IDE and configure it for the STM32F469 Discovery kit.
3. **Compile and Build**: Use the IDE's tools to compile and build the project.

## Running the Code

1. **Upload the Firmware**: Load the compiled binary onto your STM32F469 Discovery kit.
2. **Execute**: Run the program to see an image on the LCD with a switch button. Pressing the button should display the camera feed.

## Debugging

- Ensure correct initialization of the LTDC and DSI.
- Check connections and compatibility of the camera module.
- Use debug messages or breakpoints to trace any issues in the button handling logic.

