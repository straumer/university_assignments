static const unsigned char s_box[256] =
{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

static const unsigned char s_box_inverse[256] =
{
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

static unsigned char mix_col_matrix[4][4] =
{
    { 0x02, 0x03, 0x01, 0x01 },
    { 0x01, 0x02, 0x03, 0x01 },
    { 0x01, 0x01, 0x02, 0x03 },
    { 0x03, 0x01, 0x01, 0x02 }
};

static unsigned char inverse_mix_col_matrix[4][4] =
{
    { 0x0E, 0x0B, 0x0D, 0x09 },
    { 0x09, 0x0E, 0x0B, 0x0D },
    { 0x0D, 0x09, 0x0E, 0x0B },
    { 0x0B, 0x0D, 0x09, 0x0E }
};

// Partial polynomial, omitting the leftmost 9th bit which doesn't have to be used here.
static const unsigned char rijndael_polynomial = 0x1B;

// Precondition: positions is positive.
// Postcondition: characters in row have cyclically shifted positions times to the left.
static void shift_left(unsigned char row[4], int positions) {

    char auxiliary_row[4];
    for (int i = 0; i < 4; i++) {
        auxiliary_row[i] = row[i];
    }

    for (int i = 0; i < 4; i++) {
        row[i] = auxiliary_row[(i + positions) % 4];
    }
}

// Precondition: positions is positive.
// Postcondition: characters in row have cyclically shifted positions times to the right.
static void shift_right(unsigned char row[4], int positions) {

    char auxiliary_row[4];
    for (int i = 0; i < 4; i++) {
        auxiliary_row[i] = row[i];
    }

    for (int i = 0; i < 4; i++) {
        row[i] = auxiliary_row[(i - positions + 4) % 4]; // Add 4 to match mathematical modulus
    }
}

// Precondition: None
// Postcondition: $output = bX^n$ in $GF(2^8)$ modulo the Rijndael polynomial.
static unsigned char multiply_by_term(unsigned char b, int n) {
    for (int i = 0; i < n; i++) {
        b <<= 1;
        if (b & 0x01) {                 // is rightmost bit 1?
            b &= 0xFE;                  // remove rightmost bit
            b ^= rijndael_polynomial;   // calculate as modulo the polynomial
        }
    }
    return b;
}

// Precondition: None
// Postcondition: $output = ba$ in $GF(2^8)$ modulo the Rijndael polynomial.
static unsigned char gf_multiply(unsigned char a, unsigned char b) {

    unsigned char result = 0x00;
    for (int i = 0; i < 8; i++) {
        if (a & (0x1 << i)) {                   // does $a$ have term $X^i$?
            result ^= multiply_by_term(b, i);   // sum the results of $bX^i$
        }
    }
    return result;
}

// Precondition: None
// Postcondition: $byte\_matrix = multiplier \times byte\_matrix$ in $GF(2^8)$ modulo Rijndael polynomial.
static void matrix_multiply(unsigned char multiplier[4][4], unsigned char byte_matrix[4][4]) {
    unsigned char new_matrix[4][4];
    unsigned char x = 0x00;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int m = 0; m < 4; m++) {
                x ^= gf_multiply(multiplier[i][m], byte_matrix[m][j]);
            }
            new_matrix[i][j] = x;
            x = 0x00;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            byte_matrix[i][j] = new_matrix[i][j];
        }
    }
}

// Precondition: None
// Postcondition: byte_array bytes have been substituted via s_box.
static void substitute_bytes(unsigned char byte_array[4]) {
    for (int i = 0; i < 4; i++) {
        byte_array[i] = s_box[byte_array[i]];
    }
}

// Precondition: None
// Postcondition: byte_array bytes have been substituted via inverse s_box.
static void inverse_substitute_bytes(unsigned char byte_array[4]) {
    for (int i = 0; i < 4; i++) {
        byte_array[i] = s_box_inverse[byte_array[i]];
    }
}

// Precondition: None
// Postcondition: matrix has been filled with bytes from block in order, top row to bottom row,
//                filling each row from left to right.
static void block_to_matrix(unsigned char block[16], unsigned char matrix[4][4]) {
    int row = 0;
    for (int i = 0; i < 16; i++) {
        matrix[row][i % 4] = block[i];
        if ((i + 1) % 4 == 0) row++;
    }
}

// Precondition: None
// Postcondition: Inverse block_to_matrix.
static void matrix_to_block(unsigned char matrix[4][4], unsigned char block[16]) {
    int row = 0;
    for (int i = 0; i < 16; i++) {
        block[i] = matrix[row][i % 4];
        if ((i + 1) % 4 == 0) row++;
    }
}

// ---------------- The 4 stages of a Rijndael round and inverses -----------------

// Precondition: None
// Postcondition: Each byte value B[i][j] of byte_matrix has been replaced with s_box[B[i][j]].
static void byte_sub_transformation(unsigned char byte_matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        substitute_bytes(byte_matrix[i]);
    }
}

// Precondition: None
// Postcondition: Each byte value B[i][j] of byte_matrix has been replaced with s_box_inverse[B[i][j]].
static void inverse_byte_sub_transformation(unsigned char byte_matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        inverse_substitute_bytes(byte_matrix[i]);
    }
}

// Precondition: None
// Postcondition: Each row B[i] of byte_matrix has been cyclically shifted i positions to the left.
static void shift_row_transformation(unsigned char byte_matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        shift_left(byte_matrix[i], i);
    }
}

// Precondition: None
// Postcondition: Each row B[i] of byte_matrix has been cyclically shifted i positions to the right.
static void inverse_shift_row_transformation(unsigned char byte_matrix[4][4]) {
    for (int i = 0; i < 4; i++) {
        shift_right(byte_matrix[i], i);
    }
}

// Precondition: None
// Postcondition: $byte\_matrix = mix\_col\_matrix \times byte\_matrix$ in $GF(2^8)$ modulo Rijndael polynomial.
static void mix_column_transformation(unsigned char byte_matrix[4][4]) {
    matrix_multiply(mix_col_matrix, byte_matrix);
}

// Precondition: None
// Postcondition: $byte\_matrix = inverse\_mix\_col\_matrix \times byte\_matrix$ in $GF(2^8)$ modulo Rijndael polynomial.
static void inverse_mix_column_transformation(unsigned char byte_matrix[4][4]) {
    matrix_multiply(inverse_mix_col_matrix, byte_matrix);
}

// Precondition: None
// Postcondition: $byte\_matrix = byte\_matrix \oplus round\_key$.
static void round_key_addition(unsigned char byte_matrix[4][4], unsigned char round_key[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            byte_matrix[j][i] ^= round_key[i][j]; // round_keys are ordered by column
        }
    }
}


//------------------------- Round key generation -------------------------

// Precondition: None
// Postcondition: $output = a \oplus b$
static void xor_columns(unsigned char a[4], unsigned char b[4], unsigned char output[4]) {
    for (int i = 0; i < 4; i++) {
        output[i] = a[i] ^ b[i];
    }
}

// Precondition: column_number is a multiple of 4
// Postcondition: $output = T(a)$, where $T$ is the Rijndael column function in the round key generation.
static void transform(unsigned char a[4], unsigned char output[4], int column_number) {
    for (int i = 0; i < 4; i++) {
        output[i] = a[i];
    }
    shift_left(output, 1);
    substitute_bytes(output);
    output[0] ^= 0x01 << column_number / 4;
}

// Precondition: None
// Postcondition: round_keys holds the first 3 round keys as matrices corresponding to key.
static void generate_round_keys(unsigned char round_keys[3][4][4], unsigned char key[16]) {

    unsigned char expanded_round_keys[12][4]; // Treated as 12 columns of 4
    unsigned char auxiliary_column[4];

    // Generate first round_key by copying key into matrix
    block_to_matrix(key, expanded_round_keys);

    // Expand matrix to other columns
    for (int i = 4; i < 12; i++) {
        if (i % 4) { // i is not a multiple of 4?
            xor_columns(expanded_round_keys[i-4], expanded_round_keys[i-1], expanded_round_keys[i]);
        }
        else {
            transform(expanded_round_keys[i-1], auxiliary_column, i);
            xor_columns(expanded_round_keys[i-4], auxiliary_column, expanded_round_keys[i]);
        }
    }

    // Gather columns into the respective round keys
    for (int m = 0; m < 3; m++) {
        for (int i = 0; i < 4; i++) {
            int exp_col = i + m*4;
            for (int j = 0; j < 4; j++) {
                round_keys[m][i][j] = expanded_round_keys[exp_col][j];
            }
        }
    }
}



// ------------------------- Block level encipherment/decipherment -----------------------------

// Precondition: None
// Postcondition: block has been 2 round AES enciphered with key.
static unsigned char encipher_block(unsigned char block[16], unsigned char key[16]) {

    // Prepare block and round keys
    unsigned char round_keys[3][4][4], block_matrix[4][4];
    block_to_matrix(block, block_matrix);
    generate_round_keys(round_keys, key);

    // ARK
    round_key_addition(block_matrix, round_keys[0]);

    // 1st round: BS SR MC ARK
    byte_sub_transformation(block_matrix);
    shift_row_transformation(block_matrix);
    mix_column_transformation(block_matrix);
    round_key_addition(block_matrix, round_keys[1]);

    // 2nd round: BS SR ARK
    byte_sub_transformation(block_matrix);
    shift_row_transformation(block_matrix);
    round_key_addition(block_matrix, round_keys[2]);

    matrix_to_block(block_matrix, block);
}

// Precondition: None
// Postcondition: block has been 2 round AES deciphered with key.
static unsigned char decipher_block(unsigned char block[16], unsigned char key[16]) {

    // Prepare block and round keys
    unsigned char round_keys[3][4][4], block_matrix[4][4];
    block_to_matrix(block, block_matrix);
    generate_round_keys(round_keys, key);

    // 2nd round inversed: ARK ISR IBS
    round_key_addition(block_matrix, round_keys[2]);
    inverse_shift_row_transformation(block_matrix);
    inverse_byte_sub_transformation(block_matrix);

    // 1st round inversed: ARK IMC ISR IBS
    round_key_addition(block_matrix, round_keys[1]);
    inverse_mix_column_transformation(block_matrix);
    inverse_shift_row_transformation(block_matrix);
    inverse_byte_sub_transformation(block_matrix);

    // ARK
    round_key_addition(block_matrix, round_keys[0]);

    matrix_to_block(block_matrix, block);
}
