/*****************************************************************************
* | File      	:   EPD_4in2bc_test.c
* | Author      :   Waveshare team
* | Function    :   4.2inch B&C e-paper test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-06-13
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "EPD_4in2bc.h"
#include "string.h"

#ifdef EPD_4IN2BC
int EPD_test(void)
{
    printf("EPD_4IN2BC_test Demo\r\n");
    EPD_Module_Init();

    printf("e-Paper init...\r\n");
    EPD_4IN2BC_Init();
    EPD_Delay_ms(500);
    EPD_4IN2BC_ClearRam();

    //Create a new image cache named IMAGE_BW and fill it with white
    UBYTE *BlackImage, *RYImage; // Red or Yellow
    UWORD Imagesize = EPD_BYTE_WIDTH * EPD_BYTE_HEIGHT;

    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    if((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for red memory...\r\n");
        return -1;
    }
    printf("NewImage:BlackImage and RYImage\r\n");
    Paint_NewImage(BlackImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 270, EPD_4IN2BC_B_WHITE);
    Paint_NewImage(RYImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 270, EPD_4IN2BC_R_WHITE);

#if 1   // show image for array    
    printf("show image for array\r\n");
    Paint_SelectImage(BlackImage);
    Paint_DrawBitMap(gImage_4in2bc_b);
    EPD_4IN2BC_SetRam(BlackImage, NULL);
    EPD_4IN2BC_RefreshDisplay();
    EPD_Delay_ms(2000);
    // Update partial image (for small ram parts, this won't speed up refresh)
    printf("Partial update\r\n");
    EPD_4IN2BC_SetPartialRamBlack(gImage_1in54, 0, 50, 200, 200);
    EPD_4IN2BC_RefreshDisplay();
    EPD_Delay_ms(2000);

#endif

#if 1   // show image for array    
    printf("show image for array\r\n");
    Paint_SelectImage(BlackImage);
    Paint_DrawBitMap(gImage_4in2bc_b);
    Paint_SelectImage(RYImage);
    Paint_DrawBitMap2(gImage_4in2bc_ry, TRUE);
    EPD_4IN2BC_SetRam(BlackImage, RYImage);
    EPD_4IN2BC_RefreshDisplay();
    EPD_Delay_ms(2000);
#endif

#if 1   // Drawing on the image
    /*Horizontal screen*/
    //1.Draw black image
    printf("Draw black image\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);      
    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
    Paint_DrawString_CN(130, 20, "微雪电子", &Font24CN, WHITE, BLACK);
    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);

    //2.Draw red image
    printf("Draw red image\r\n");
    Paint_SelectImage(RYImage);
    Paint_Clear(EPD_4IN2BC_R_WHITE);
    Paint_DrawCircle(160, 95, 20, EPD_4IN2BC_R_RED, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(210, 95, 20, EPD_4IN2BC_R_RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawLine(85, 95, 125, 95, EPD_4IN2BC_R_RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(105, 75, 105, 115, EPD_4IN2BC_R_RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);  
    Paint_DrawString_CN(130, 0,"你好abc", &Font12CN, EPD_4IN2BC_R_RED, EPD_4IN2BC_R_WHITE);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, EPD_4IN2BC_R_WHITE, EPD_4IN2BC_R_RED);
    Paint_DrawNum(10, 33, 123456789, &Font12, EPD_4IN2BC_R_RED, EPD_4IN2BC_R_WHITE);

    printf("EPD_Display\r\n");
    EPD_4IN2BC_SetRam(BlackImage, RYImage);
    EPD_4IN2BC_RefreshDisplay();
    EPD_Delay_ms(2000);
#endif

    printf("Clear...\r\n");
    EPD_4IN2BC_Clear();

    printf("Goto Sleep...\r\n");
    EPD_4IN2BC_Sleep();
    free(BlackImage);
    free(RYImage);
    BlackImage = NULL;
    RYImage = NULL;

    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    EPD_Module_Exit();
    
    return 0;
}
#endif
