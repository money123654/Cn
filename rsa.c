#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long int p, q, n, t, flag;
long int e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];

int prime(long int pr) {
    int i;
    if (pr == 1) return 0;
    for (i = 2; i <= sqrt(pr); i++) {
        if (pr % i == 0) return 0;
    }
    return 1;
}

void ce() {
    int k = 0;
    for (i = 2; i < t; i++) {
        if (t % i == 0) continue;
        flag = prime(i);
        if (flag == 1 && i != p && i != q) {
            e[k] = i;
            long int k1 = 1;
            while (1) {
                k1 = k1 + t;
                if (k1 % e[k] == 0) {
                    d[k] = k1 / e[k];
                    break;
                }
            }
            k++;
        }
    }
    j = k;
}

void encrypt() {
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);
    while (i < len) {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    printf("\nTHE ENCRYPTED MESSAGE IS:\n");
    for (i = 0; en[i] != -1; i++)
        printf("%c", (char)en[i]);
}

void decrypt() {
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1) {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    printf("\nTHE DECRYPTED MESSAGE IS:\n");
    for (i = 0; m[i] != -1; i++)
        printf("%c", (char)m[i]);
}

int main() {
    printf("ENTER FIRST PRIME NUMBER: ");
    scanf("%ld", &p);
    flag = prime(p);
    if (flag == 0) {
        printf("WRONG INPUT\n");
        exit(1);
    }
    printf("ENTER ANOTHER PRIME NUMBER: ");
    scanf("%ld", &q);
    flag = prime(q);
    if (flag == 0 || p == q) {
        printf("WRONG INPUT\n");
        exit(1);
    }
    printf("ENTER MESSAGE: ");
    scanf("%s", msg);
    for (i = 0; msg[i] != '\0'; i++)
        m[i] = msg[i];
    n = p * q;
    t = (p - 1) * (q - 1);
    ce();
    printf("\nPOSSIBLE VALUES OF e AND d ARE:\n");
    for (i = 0; i < j; i++)
        printf("%ld\t%ld\n", e[i], d[i]);
    encrypt();
    decrypt();
    return 0;
}
