/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <keycodes.h>

uint8_t keyboardData[8] = {0,0,0,0,0,0,0,0};

void buttonScan();

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    USBFS_Start(0, USBFS_DWR_VDDD_OPERATION);
    while(!USBFS_bGetConfiguration())
    {}
    USBFS_LoadInEP(1, (uint8 *)keyboardData, 8);

    for(;;)
    {
        int i = 0;
        for (i = 0; i<8; i++)
        {
          keyboardData[i] = 0;
        }
        buttonScan();
        while(!USBFS_bGetEPAckState(1))
        {}
        USBFS_LoadInEP(1, (uint8 *)keyboardData, 8);
    }
}

void buttonScan()
{
    int i = 2; // The first two bytes (0 and 1) of our keyboard data report
               //  are reserved for control keys and ???. We want to scan over
               //  the buttons and catch up to 14 of them pressed at once.
    
    // This is awful but I don't know how else to do it. We need to check each
    //  bit, in each status register, and then put some value (defined in
    //  keycodes.h) into some keyboard buffer location, and then return if that
    //  index is greater than 6.
    
    // Player one buttons
    if ((Buttons_REG_1_Read() & 0x01) == 0)
    {
        keyboardData[0] |= KEY_LCTRL;
    }
    if ((Buttons_REG_1_Read() & 0x02) == 0)
    {
        keyboardData[0] |= KEY_LALT;
    }
    if ((Buttons_REG_1_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_SPC;
        if (i > 6) return;
    }
    if ((Buttons_REG_1_Read() & 0x08) == 0)
    {
        keyboardData[0] |= KEY_LSHIFT;
        if (i > 6) return;
    }
    if ((Buttons_REG_1_Read() & 0x10) == 0)
    {
        keyboardData[i++] = KEY_Z;
        if (i > 6) return;
    }
    if ((Buttons_REG_1_Read() & 0x20) == 0)
    {
        keyboardData[i++] = KEY_X;
        if (i > 6) return;
    }
    
    // Player two buttons
    if ((Buttons_REG_2_Read() & 0x01) == 0)
    {
        keyboardData[i++] = KEY_A;
        if (i > 6) return;
    }
    if ((Buttons_REG_2_Read() & 0x02) == 0)
    {
        keyboardData[i++] = KEY_S;
        if (i > 6) return;
    }
    if ((Buttons_REG_2_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_Q;
        if (i > 6) return;
    }
    if ((Buttons_REG_2_Read() & 0x08) == 0)
    {
        keyboardData[i++] = KEY_W;
        if (i > 6) return;
    }
    if ((Buttons_REG_2_Read() & 0x10) == 0)
    {
        keyboardData[i++] = KEY_B;
        if (i > 6) return;
    }
    if ((Buttons_REG_2_Read() & 0x20) == 0)
    {
        keyboardData[i++] = KEY_C;
        if (i > 6) return;
    }
    
    // Player three buttons
    if ((Buttons_REG_3_Read() & 0x01) == 0)
    {
        keyboardData[0] |= KEY_RCTRL;
        if (i > 6) return;
    }
    if ((Buttons_REG_3_Read() & 0x02) == 0)
    {
        keyboardData[0] |= KEY_RSHIFT;
        if (i > 6) return;
    }
    if ((Buttons_REG_3_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_RET;
        if (i > 6) return;
    }
    if ((Buttons_REG_3_Read() & 0x08) == 0)
    {
        keyboardData[i++] = KEY_M;
        if (i > 6) return;
    }
    if ((Buttons_REG_3_Read() & 0x10) == 0)
    {
        keyboardData[i++] = KEY_N;
        if (i > 6) return;
    }
    if ((Buttons_REG_3_Read() & 0x20) == 0)
    {
        keyboardData[i++] = KEY_P;
        if (i > 6) return;
    }
    
    // Player four buttons
    if ((Buttons_REG_4_Read() & 0x01) == 0)
    {
        keyboardData[i++] = KEY_KP0;
        if (i > 6) return;
    }
    if ((Buttons_REG_4_Read() & 0x02) == 0)
    {
        keyboardData[i++] = KEY_KPPER;
        if (i > 6) return;
    }
    if ((Buttons_REG_4_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_KPENT;
        if (i > 6) return;
    }
    if ((Buttons_REG_4_Read() & 0x08) == 0)
    {
        keyboardData[i++] = KEY_KP1;
        if (i > 6) return;
    }
    if ((Buttons_REG_4_Read() & 0x10) == 0)
    {
        keyboardData[i++] = KEY_KP3;
        if (i > 6) return;
    }
    if ((Buttons_REG_4_Read() & 0x20) == 0)
    {
        keyboardData[i++] = KEY_KP5;
        if (i > 6) return;
    }

    // Joystick buttons player 1
    if ((JS_REG_1_Read() & 0x01) == 0)
    {
        keyboardData[i++] = KEY_RT;
        if (i > 6) return;
    }
    if ((JS_REG_1_Read() & 0x02) == 0)
    {
        keyboardData[i++] = KEY_UP;
        if (i > 6) return;
    }
    if ((JS_REG_1_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_LT;
        if (i > 6) return;
    }
    if ((JS_REG_1_Read() & 0x08) == 0)
    {
        keyboardData[i++] = KEY_DN;
        if (i > 6) return;
    }

    // Joystick buttons player 2
    if ((JS_REG_2_Read() & 0x01) == 0)
    {
        keyboardData[i++] = KEY_F;
        if (i > 6) return;
    }
    if ((JS_REG_2_Read() & 0x02) == 0)
    {
        keyboardData[i++] = KEY_G;
        if (i > 6) return;
    }
    if ((JS_REG_2_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_R;
        if (i > 6) return;
    }
    if ((JS_REG_2_Read() & 0x08) == 0)
    {
        keyboardData[i++] = KEY_D;
        if (i > 6) return;
    }

    // JS Buttons player 3
    if ((JS_REG_3_Read() & 0x01) == 0)
    {
        keyboardData[i++] = KEY_L;
        if (i > 6) return;
    }
    if ((JS_REG_3_Read() & 0x02) == 0)
    {
        keyboardData[i++] = KEY_I;
        if (i > 6) return;
    }
    if ((JS_REG_3_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_J;
        if (i > 6) return;
    }
    if ((JS_REG_3_Read() & 0x08) == 0)
    {
        keyboardData[i++] = KEY_K;
        if (i > 6) return;
    }

    // JS Buttons player 4
    if ((JS_REG_4_Read() & 0x01) == 0)
    {
        keyboardData[i++] = KEY_KP2;
        if (i > 6) return;
    }
    if ((JS_REG_4_Read() & 0x02) == 0)
    {
        keyboardData[i++] = KEY_KP6;
        if (i > 6) return;
    }
    if ((JS_REG_4_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_KP8;
        if (i > 6) return;
    }
    if ((JS_REG_4_Read() & 0x08) == 0)
    {
        keyboardData[i++] = KEY_KP4;
        if (i > 6) return;
    }

    // Coin buttons
    if ((Coins_REG_Read() & 0x01) == 0)
    {
        keyboardData[i++] = KEY_5;
        if (i > 6) return;
    }
    if ((Coins_REG_Read() & 0x02) == 0)
    {
        keyboardData[i++] = KEY_6;
        if (i > 6) return;
    }
    if ((Coins_REG_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_7;
        if (i > 6) return;
    }
    if ((Coins_REG_Read() & 0x08) == 0)
    {
        keyboardData[i++] = KEY_8;
        if (i > 6) return;
    }

    // Start buttons
    if ((Start_REG_Read() & 0x01) == 0)
    {
        keyboardData[i++] = KEY_1;
        if (i > 6) return;
    }
    if ((Start_REG_Read() & 0x02) == 0)
    {
        keyboardData[i++] = KEY_2;
        if (i > 6) return;
    }
    if ((Start_REG_Read() & 0x04) == 0)
    {
        keyboardData[i++] = KEY_3;
        if (i > 6) return;
    }
    if ((Start_REG_Read() & 0x08) == 0)
    {
        keyboardData[i++] = KEY_4;
        if (i > 6) return;
    }
    
    // Escape key
    if ((Esc_REG_Read() & 0x01) == 0)
    {
        keyboardData[i++] = KEY_ESC;
        if (i>6) return;
    }
} 

/* [] END OF FILE */

