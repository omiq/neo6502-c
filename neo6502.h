/*\
|*| Convenience macros for Neo6502 applications programming
|*| SPDX-License-Identifier: CC0-1.0
\*/


/* Neo6502 Kernel API control addresses */

uint8_t* API_COMMAND_ADDR    = (uint8_t*)0xFF00 ; // function group address
uint8_t* API_FUNCTION_ADDR   = (uint8_t*)0xFF01 ; // function address
uint8_t* API_PARAMETERS_ADDR = (uint8_t*)0xFF04 ; // function parameters base address (8 bytes)


/* Neo6502 Kernel API control codes (see documents/release/api.pdf) */

// Console functions (Group 2)
uint8_t API_GROUP_CONSOLE   = (uint8_t )0x02 ; // API function group ID
uint8_t API_FN_WRITE_CHAR   = (uint8_t )0x06 ; // API function ID
uint8_t API_FN_CURSOR_POS   = (uint8_t )0x07 ; // API function ID
uint8_t API_FN_INKEY        = (uint8_t )0x01 ; // API function ID


// Sound functions (Group 8)
uint8_t API_GROUP_SOUND     = (uint8_t )0x08 ; // API function group ID
uint8_t API_FN_PLAY_SOUND   = (uint8_t )0x05 ; // API function ID
uint8_t API_SOUND_CH_00     = (uint8_t )0x00 ; // API function parameter ID
uint8_t API_SOUND_EFFECT_06 = (uint8_t )0x06 ; // API function parameter ID

// Graphics functions (Group 5)
uint8_t API_GROUP_GRAPHICS  = (uint8_t )0x05 ; // API function group ID
uint8_t API_RESET_PALETTE   = (uint8_t )0x22 ; // API function ID for reset palette
uint8_t API_SET_COLOR       = (uint8_t )0x01 ; // API function ID for color
uint8_t API_DRAW_RECTANGLE  = (uint8_t )0x03 ; // API function ID Draw rectangle P01,P23 → P45,P67
