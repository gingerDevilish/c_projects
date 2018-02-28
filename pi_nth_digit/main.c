#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "singly_linked_list.h"

int N_ZERO = 2;

typedef struct _prime_info
{
    long prime;
    long quantity;
} prime_info;

// computes all prime factors of n that are less or equal to k and amounts of each one
// defaults to k=sqrtl(n), for that, set k=0
// returns a list of prime_info
node *prime_factors(long n, long double k)
{
    node *head = NULL;
    prime_info *info = NULL;
    if (!k)
    {
        k = sqrtl(n);
    }
    int count = 0;
    while ((n & 1) == 0)
    {
        count++;
        n = n / 2;
    }
    info = (prime_info *)malloc(sizeof(prime_info));
    info->prime = 2;
    info->quantity = count;
    append(&head, (void *)info);
    for (int i = 3; i <= k; i += 2)
    {
        int count = 0;
        while (n % i == 0)
        {
            count++;
            n = n / i;
        }
        info = (prime_info *)malloc(sizeof(prime_info));
        info->prime = i;
        info->quantity = count;
        append(&head, (void *)info);
    }
    if ((n > 2) && (n <= k))
    {
        info = (prime_info *)malloc(sizeof(prime_info));
        info->prime = n;
        info->quantity = 1;
        append(&head, (void *)info);
    }
    return head;
}

// performs decomposition of source (fully decomposed to target)
// into factors and remaining part
long decompose(node *factors, node **target, long source)
{
    node *cursor = factors;
    node *decomposition = NULL;
    prime_info *info_1 = NULL;
    prime_info *info_2 = NULL;
    while (cursor && (*target))
    {
        info_1 = (prime_info *)(cursor->data);
        info_2 = (prime_info *)((*target)->data);
        if ((info_1->prime) == (info_2->prime))
        {
            prepend(&decomposition, (void *)info_2);
            remove_front(target);
            source /= powl(info_2->prime, info_2->quantity);
            cursor = cursor->next;
        }
        else if ((info_1->prime) > (info_2->prime))
        {
            free(remove_front(target));
            free(info_2);
        }
        else
        {
            cursor = cursor->next;
        }
    }
    while (*target)
    {
        prime_info *info = (prime_info *)((*target)->data);
        free(remove_front(target));
        free(info);
    }
    *target = decomposition;
    return source;
}

// extended Euclidean algorithm
// result[0] - resulting part of equation; should be 1 for multiplicative inverses, then:
// result[1] - multiplicative inverse of a modulo b
// result[2] - multiplicative inverse of b bodulo a
void xgcd(long *result, long a, long b)
{
    long aa[2] = {1, 0}, bb[2] = {0, 1}, q, r;
    for (;;)
    {
        q = a / b;
        a = a % b;
        aa[0] -= q * aa[1];
        bb[0] -= q * bb[1];
        if (!a)
        {
            result[0] = b;
            result[1] = aa[1];
            result[2] = bb[1];
            return;
        }
        q = b / a;
        b = b % a;
        aa[1] -= q * aa[0];
        bb[1] -= q * bb[0];
        if (!b)
        {
            result[0] = a;
            result[1] = aa[0];
            result[2] = bb[0];
            return;
        }
    }
}

//! Algorithm 2 is about computation of sum of binomials modulo an integer
// Let us name this sum of binomials S = sum_(j = 0 to k){N choose j}
long modulo(long N, long k, long m)
{
    // compute prime factors of m less than k
    node *factors = prime_factors(m, k);
    // initialize A, B, C, R
    int length = count(factors);
    long *R = (long *)malloc(length * sizeof(long));
    int A = 1, B = 1, C = 1;
    for (int i = 0; i < length; i++)
    {
        R[i] = 1;
    }
    // main loop
    for (int j = 1; j <= k; j++)
    {
        // assign a and b
        long a = N - j + 1;
        long b = j;
        // decompose a and b to the needed form
        node *a_decomposition = prime_factors(a, sqrtl(a));
        node *b_decomposition = prime_factors(b, sqrtl(b));
        long a_star = decompose(factors, &a_decomposition, a);
        long b_star = decompose(factors, &b_decomposition, b);
        // compute R[i]
        node *cursor_a = a_decomposition;
        node *cursor_b = b_decomposition;
        for (int i = 0; i < length; i++)
        {
            prime_info *info_a = (prime_info *)(cursor_a->data);
            prime_info *info_b = (prime_info *)(cursor_b->data);
            R[i] *= powl(info_a->prime, info_a->quantity);
            R[i] /= powl(info_b->prime, info_b->quantity);
        }
        // compute A, B, C
        //? probably need to put C assignment on top (A used)
        long auxiliary = A;
        A = (A * a_star) % m;
        B = (B * b_star) % m;
        //long auxiliary = A;
        for (int i = 0; i < length; i++)
        {
            auxiliary *= R[i];
        }
        //? probably mod operation is for the whole expression
        //C = C * b_star + (auxiliary % m);
        C = (C*b_star + auxiliary)%m;
    }
    // compute the required value
    long gcd[3];
    xgcd(gcd, B, m);
    //! here gcd[0]==1 - add assert
    return (C * gcd[1]) % m;
}

// Computes nth decimal digit of pi
// The algorithm used computes fractional part of 10^n*pi with an error < 10^(-N_ZERO) when n > 4*N_ZERO 
long n_digit(long n)
{
    // Define M and N
    long M = 2 * ceill(n / powl(logl(n), 3));
    long N = ceill((n + N_ZERO + 1) * logl(10) / (logl(2 * M) + 1));
    // Compute B
    long double b = 0;
    for (int k = 0; k < (M + 1) * N; k++)
    {
        long x = (long)(4 * powl(10, n)) % (2 * k + 1);
        b = b + powl(-1, k) * x / (long double)(2 * k + 1);
    }
    // Compute C
    long double c = 0;
    for (int k = 0; k < N; k++)
    {
        long x = modulo(N, k, 2 * M * N + 2 * k + 1);
        long y = (long)(powl(5, N - 2) * powl(10, n - N + 2) * x) % (2 * M * N + 2 * k + 1);
        c = c + powl(-1, k) * y / (long double)(2 * M * N + 2 * k + 1);
    }
    // Final step - compute x, the needed approximation
    long double x = b - c - floorl(b - c);
    printf("%Lf\n", x);
    return floorl(10 * x);
}

int main()
{
    // TODO: Here is where the tests will be
    for (int n = 10 ; n<30; n++)
    {
        //printf("%ld", n_digit(n));
        n_digit(n);
    }
    return 0;
}