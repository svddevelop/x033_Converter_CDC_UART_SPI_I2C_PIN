#include <string.h>
#include <ctype.h>
#include <stdint.h>

/**
 * Parse hex data after '=' symbol until ']' into hex buffer
 * @param dev - pointer to "CFG=0DAA987345123458]"
 * @param ek - pointer to ']' character
 * @param hex_buf - output buffer for hex data
 * @param hex_buf_size - size of output buffer
 * @return number of parsed bytes, or -1 on error
 */
int parse_hex_config(const char* dev, const char* ek, char* hex_buf, int hex_buf_size) {
    // Find '=' symbol
    const char* equal_sign = strchr(dev, '=');
    if (equal_sign == NULL) {
        return -1; // '=' not found
    }
    
    // Move to the first character after '='
    const char* hex_start = equal_sign + 1;
    
    // Verify that hex_start is before ek
    if (hex_start >= ek) {
        return -1; // No hex data between '=' and ']'
    }
    
    // Calculate hex string length
    int hex_str_len = ek - hex_start;
    if (hex_str_len % 2 != 0) {
        return -1; // Hex string must have even number of characters
    }
    
    // Calculate required bytes (2 hex chars = 1 byte)
    int required_bytes = hex_str_len / 2;
    if (required_bytes > hex_buf_size) {
        return -1; // Output buffer too small
    }
    
    // Parse hex string
    for (int i = 0; i < required_bytes; i++) {
        const char* hex_byte = hex_start + (i * 2);
        
        // Convert two hex characters to byte
        uint8_t byte = 0;
        for (int j = 0; j < 2; j++) {
            char c = hex_byte[j];
            byte <<= 4;
            
            if (c >= '0' && c <= '9') {
                byte |= (c - '0');
            } else if (c >= 'A' && c <= 'F') {
                byte |= (c - 'A' + 10);
            } else if (c >= 'a' && c <= 'f') {
                byte |= (c - 'a' + 10);
            } else {
                return -1; // Invalid hex character
            }
        }
        
        hex_buf[i] = byte;
    }
    
    return required_bytes;
}


/*
// Alternative version with more detailed error codes
typedef enum {
    PARSE_OK = 0,
    PARSE_NO_EQUAL,
    PARSE_NO_DATA,
    PARSE_ODD_LENGTH,
    PARSE_BUFFER_TOO_SMALL,
    PARSE_INVALID_HEX
} parse_result_t;
*/
/**
 * Enhanced version with detailed error reporting
 */
 /*
parse_result_t parse_hex_config_ex(const char* dev, const char* ek, 
                                   uint8_t* hex_buf, int hex_buf_size, 
                                   int* parsed_bytes) {
    const char* equal_sign = strchr(dev, '=');
    if (equal_sign == NULL) {
        return PARSE_NO_EQUAL;
    }
    
    const char* hex_start = equal_sign + 1;
    if (hex_start >= ek) {
        return PARSE_NO_DATA;
    }
    
    int hex_str_len = ek - hex_start;
    if (hex_str_len % 2 != 0) {
        return PARSE_ODD_LENGTH;
    }
    
    int required_bytes = hex_str_len / 2;
    if (required_bytes > hex_buf_size) {
        return PARSE_BUFFER_TOO_SMALL;
    }
    
    for (int i = 0; i < required_bytes; i++) {
        const char* hex_byte = hex_start + (i * 2);
        uint8_t byte = 0;
        
        for (int j = 0; j < 2; j++) {
            char c = hex_byte[j];
            byte <<= 4;
            
            if (c >= '0' && c <= '9') {
                byte |= (c - '0');
            } else if (c >= 'A' && c <= 'F') {
                byte |= (c - 'A' + 10);
            } else if (c >= 'a' && c <= 'f') {
                byte |= (c - 'a' + 10);
            } else {
                return PARSE_INVALID_HEX;
            }
        }
        
        hex_buf[i] = byte;
    }
    
    *parsed_bytes = required_bytes;
    return PARSE_OK;
}
*/

/*
// Helper function to print hex buffer
void print_hex_buffer(const uint8_t* buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");
}
*/

/*
// Example usage
void example_usage(void) {
    char data[] = "[SET:CFG=0DAA987345123458]";
    char* dev = strstr(data, "CFG=") + 4; // Points to "0DAA987345123458]"
    char* ek = strchr(dev, ']');          // Points to ']'
    
    uint8_t hex_buf[8];
    int result = parse_hex_config(dev, ek, hex_buf, sizeof(hex_buf));
    
    if (result > 0) {
        printf("Parsed %d bytes: ", result);
        print_hex_buffer(hex_buf, result);
        // Output: Parsed 8 bytes: 0D AA 98 73 45 12 34 58
    } else {
        printf("Parse error: %d\n", result);
    }
}
*/