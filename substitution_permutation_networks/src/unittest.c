#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "aes.h"

static void test_xor_columns(void **state) {
    unsigned char a[4] = { 0x11, 0x01, 0x10, 0x00 }, b[4] = { 0x01, 0x00, 0x11, 0x00 }, output[4];
    char old = output[0];
    xor_columns(a, b, output);
    assert_true(output[0] == 0x10);
    assert_true(output[1] == 0x01);
    assert_true(output[2] == 0x01);
    assert_true(output[3] == 0x00);
}

static void test_gf_multiply(void **state) {
    unsigned char a = 0x02, b = 0xCB, expected_result = 0x8B, result;
    result = gf_multiply(a, b);
    assert_true(result == expected_result);

    a = 0x03;
    b = 0xFF;
    expected_result = 0x1B;
    result = gf_multiply(a, b);
    assert_true(result == expected_result);

    a = 0x01;
    b = 0xAD;
    expected_result = b;
    result = gf_multiply(a, b);
    assert_true(result == expected_result);

    a = 0x01;
    b = 0x60;
    expected_result = b;
    result = gf_multiply(a, b);
    assert_true(result == expected_result);

    a = 0x03;
    b = 0x09;
    expected_result = 0x7B;
    result = gf_multiply(a, b);
    assert_true(result == expected_result);

}

static void test_byte_sub_transformation(void **state) {
    unsigned char byte_matrix[4][4] =
    {
        { 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x84, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 },
    };
    byte_sub_transformation(byte_matrix);
    assert_true(byte_matrix[0][0] == 0x63);
    assert_true(byte_matrix[1][2] == 0x5F);
    inverse_byte_sub_transformation(byte_matrix);
    assert_true(byte_matrix[0][0] == 0x00);
    assert_true(byte_matrix[1][2] == 0x84);
}

static void test_shift_row_transformation(void **state) {
    unsigned char byte_matrix[4][4] =
    {
        { 0x00, 0x00, 0x00, 0xF0 },
        { 0x00, 0x00, 0x84, 0x00 },
        { 0x00, 0x09, 0x00, 0x00 },
        { 0x08, 0x00, 0x00, 0x00 },
    };
    shift_row_transformation(byte_matrix);
    assert_true(byte_matrix[0][3] == 0xF0);
    assert_true(byte_matrix[1][2] == 0x00);
    assert_true(byte_matrix[1][1] == 0x84);
    assert_true(byte_matrix[2][1] == 0x00);
    assert_true(byte_matrix[2][3] == 0x09);
    assert_true(byte_matrix[3][0] == 0x00);
    assert_true(byte_matrix[3][1] == 0x08);
    inverse_shift_row_transformation(byte_matrix);
    assert_true(byte_matrix[0][3] == 0xF0);
    assert_true(byte_matrix[1][2] == 0x84);
    assert_true(byte_matrix[1][1] == 0x00);
    assert_true(byte_matrix[2][1] == 0x09);
    assert_true(byte_matrix[2][3] == 0x00);
    assert_true(byte_matrix[3][0] == 0x08);
    assert_true(byte_matrix[3][1] == 0x00);
}

static void test_mix_column_transformation(void **state) {
    unsigned char byte_matrix[4][4] =
    {
        { 0x00, 0x00, 0x60, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x09, 0x00 },
    };
    mix_column_transformation(byte_matrix);
    assert_true(byte_matrix[2][2] == 0x7B);
    inverse_mix_column_transformation(byte_matrix);
    assert_true(byte_matrix[2][2] == 0x00);
}

static void test_round_key_addition(void **state) {
    unsigned char byte_matrix[4][4] =
    {
        { 0x00, 0x00, 0x00, 0xA4 },
        { 0x05, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0xE0, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 },
    };
    unsigned char round_key[4][4] =
    {
        { 0x00, 0x05, 0x00, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0xE0, 0x00 },
        { 0xA4, 0x00, 0x00, 0x00 },
    };

    round_key_addition(byte_matrix, round_key);
    assert_true(byte_matrix[1][0] == 0x00);
    assert_true(byte_matrix[0][3] == 0x00);
    assert_true(byte_matrix[2][2] == 0x00);
    round_key_addition(byte_matrix, round_key);
    assert_true(byte_matrix[1][0] == 0x05);
    assert_true(byte_matrix[0][3] == 0xA4);
    assert_true(byte_matrix[2][2] == 0xE0);
}

static void test_generate_round_keys(void **state) {
    char key[16] = "abcdefghijklmnop";
    unsigned char round_keys[3][4][4];
    generate_round_keys(round_keys, key);
    assert_true(round_keys[0][0][0] == 'a');
    assert_true(round_keys[0][3][3] == 'p');
    assert_true(round_keys[1][0][1] == 0xCA);
}

static void test_encipher_decipher_block(void **state) {
    unsigned char key[16] = "abcdefghijklmnop", block[16] = "Hello it is good", previous_block[16];

    for (int i = 0; i < 16; i++) {
        previous_block[i] = block[i];
    }

    encipher_block(block, key);
    decipher_block(block, key);

    for (int i = 0; i < 16; i++) {
        assert_true(previous_block[i] == block[i]);
    }
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_xor_columns),
        cmocka_unit_test(test_byte_sub_transformation),
        cmocka_unit_test(test_shift_row_transformation),
        cmocka_unit_test(test_mix_column_transformation),
        cmocka_unit_test(test_round_key_addition),
        cmocka_unit_test(test_generate_round_keys),
        cmocka_unit_test(test_encipher_decipher_block)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
