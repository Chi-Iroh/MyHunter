/*
** EPITECH PROJECT, 2022
** my_is_prime.c
** File description:
** ->   returns if the parameter is prime or not
*/

#include "my.h"

static int my_compute_square_root_rounded(int nb)
{
    for (int i = 0;; i++) {
        const int power = i * i;
        if (power >= nb) {
            return i - (power > nb);
        }
    }
}

int my_is_prime(int nb)
{
    if (nb <= 3) {
        if (nb < 0) {
            return 0;
        }
        return nb > 1;
    }
    if (nb % 2 == 0) {
        return 0;
    }
    for (int i = 3; i <= my_compute_square_root_rounded(nb); i += 2) {
        if (nb % i == 0 && nb > i) {
            return 0;
        }
    }
    return 1;
}
