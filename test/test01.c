/*
 * 確率数列生成関数のテスト
 *  任意の自然数nとその数の確率pと確率の減少率rを与えることで
 *  nの確率をpとしてsize内で有効なp*r^i(i=1,2...)の数列n~n+iを生成する
 *  戻り値としてその有効範囲を返す
 *  その数列の各数値はそれぞれの確率と有効範囲内の自分の範囲を持つ
 *
 * 例えば, n=1, p=1/6, r=1, size=60とした場合
 *  n=1, p=0.166667, start=1, end=10
 *  n=2, p=0.166667, start=11, end=20
 *  n=3, p=0.166667, start=21, end=30
 *  n=4, p=0.166667, start=31, end=40
 *  n=5, p=0.166667, start=41, end=50
 *  n=6, p=0.166667, start=51, end=60
 *  60
 *
 * note
 *  最初にPos型の配列をsize分作るがほとんど使われないので無駄 mallocを使うとか
 *  max, minを作る．上の例で言えばn=7でbreak
 *  min to max, max to min両方実装
 *  範囲を作った．残りは有効範囲内の乱数を生成してそれによってnを決定する関数
 *  ということは，戻り値は生成した数列
 *  確率，減衰率によりランダム性を持たせるには
 *   p, r に補正値を足す/掛けるとか
 *   p, r に整数値を渡してそれを元に p, r を新たに生成するとか
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num; // ones number
    float p; // ones possibility
    int srange, erange; // range(start, end)
} Pos;

// arg: n: num, size: max range, p: possibility of m, r: reduction rate
int testf(int n, int size, float p, float r) {
    int i;
    Pos ps[size]; // posibilities

    // the first possibility
    Pos tp = {n, p, 1, size*p};
    ps[0] = tp;

    // calculating
    for (i=1; i<size; i++) {
        p = p * r;
        ps[i].num = n + i;
        ps[i].p = p;

        // is it effective?
        if (size * p > 2) {
            ps[i].srange = ps[i-1].erange + 1;
            ps[i].erange = ps[i-1].erange + size*p;
        }
        else
            break;

        // is it within range?
        if (ps[i].srange > size || ps[i].erange > size)
            break;
    }

    // test print
    int j;
    for (j=0; j<i; j++) {
        printf("n=%d, p=%f, start=%d, end=%d\n", ps[j].num, ps[j].p, ps[j].srange, ps[j].erange);
    }

    // ret effective range
    return ps[i-1].erange;
}

int main(int argc, char *argv[])
{
    if (argc == 5)
        printf("%d\n", testf(atoi(argv[1]), atoi(argv[2]), atof(argv[3]), atof(argv[4])));
    return 0;
}